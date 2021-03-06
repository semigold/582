/*
 * Copyright (c) 2011, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Yet another machine dependent MSP430X UART1 code.
 * IF2, etc. can not be used here... need to abstract to some macros
 * later.
 */

#include "contiki.h"
#include <stdlib.h>
#include "sys/energest.h"
#include "dev/uart.h"
#include "dev/watchdog.h"
#include "isr_compat.h"

static int (*uart1_input_handler)(unsigned char c);

#ifdef UART1_CONF_RX_WITH_DMA
#define RX_WITH_DMA UART1_CONF_RX_WITH_DMA
#else /* UART1_CONF_RX_WITH_DMA */
#define RX_WITH_DMA 1
#endif /* UART1_CONF_RX_WITH_DMA */

#if RX_WITH_DMA
#define RXBUFSIZE 128

static uint8_t rxbuf[RXBUFSIZE];
static uint16_t last_size;
static struct ctimer rxdma_timer;

static void
handle_rxdma_timer(void *ptr)
{
  uint16_t size;
  size = DMA0SZ; /* Note: loop requires that size is less or eq to RXBUFSIZE */
  while(last_size != size) {
    uart1_input_handler((unsigned char)rxbuf[RXBUFSIZE - last_size]);
    last_size--;
    if(last_size == 0) {
      last_size = RXBUFSIZE;
    }
  }

  ctimer_reset(&rxdma_timer);
}
#endif /* RX_WITH_DMA */

/*---------------------------------------------------------------------------*/
uint8_t
uart1_active(void)
{
  return (UCA1STATW & UCBUSY);
}
/*---------------------------------------------------------------------------*/
void
uart1_set_input(int (*input)(unsigned char c))
{
#if RX_WITH_DMA /* This needs to be called after ctimer process is started */
  ctimer_set(&rxdma_timer, CLOCK_SECOND / 64, handle_rxdma_timer, NULL);
#endif
  uart1_input_handler = input;
}
/*---------------------------------------------------------------------------*/
void
uart1_writeb(unsigned char c)
{
  watchdog_periodic();
  /* Loop until the transmission buffer is available. */
  while(!(UCA1IFG & UCTXIFG));

  /* Transmit the data. */
  UCA1TXBUF = c;
}
/*---------------------------------------------------------------------------*/
/**
 * Initalize the RS232 port.
 *
 */
void
uart1_init(unsigned long baud)
{
  // Configure GPIO

  /* P2DIR value is controlled by eUSCI_A1 module according to schematics.
   * don't worry about it's value */

  P2SEL1 |= (BIT5 | BIT6);  /* P2.5,6 = USCI_A1 TXD/RXD */
  P2SEL0 &= ~(BIT5| BIT6);

  /* RS232 */
  UCA1CTLW0 |= UCSWRST;            /* Hold peripheral in reset state */
  UCA1CTLW0 |= UCSSEL__SMCLK;      /* CLK = SMCLK */

  /* Asynchronous mode, No parity, 1 stop bit,
   * 8 bit character select, UART mode */
  UCA1CTLW0 &= ~(UCSYNC + UCPEN + UCSPB + UC7BIT + UCMODE_3);

  /* Reset UCRXIE, UCBRKIE, UCDORM, UCTXADDR, UCTXBRK */
  UCA1CTLW0 &= ~(UCRXEIE + UCBRKIE + UCDORM + UCTXADDR + UCTXBRK);

  const uart_params *uparams = find_uart_settings(baud);

  UCA1BRW = uparams->ucaxbrw;                /* Set UCBRx */
  UCA1MCTLW = uparams->ucaxmctl;             /* Set UCBRSx, UCBRFx, UCOS16 */

  /* XXX Clear pending interrupts before enable */
  UCA1IE &= ~UCRXIFG;
  UCA1IE &= ~UCTXIFG;

  UCA1CTLW0 &= ~UCSWRST;                   /* Initialize USCI state machine **before** enabling interrupts */
  UCA1IE |= UCRXIE;                        /* Enable UCA1 RX interrupt */

#if RX_WITH_DMA
  UCA1IE &= ~UCRXIE; /* disable USART1 RX interrupt  */
  /* UART1_RX trigger */
  DMACTL0 = DMA0TSEL_20;

  /* source address = RXBUF1 */
  DMA0SA = (unsigned int)&UCA1RXBUF;
  DMA0DA = (unsigned int)&rxbuf;
  DMA0SZ = RXBUFSIZE;
  last_size = RXBUFSIZE;
  DMA0CTL = DMADT_4 + DMASBDB + DMADSTINCR_3 + DMAEN + DMAREQ;

  msp430_add_lpm_req(MSP430_REQUIRE_LPM1);
#endif /* RX_WITH_DMA */
}
/*---------------------------------------------------------------------------*/
#if !RX_WITH_DMA
ISR(USCI_A1, uart1_rx_interrupt)
{
  uint8_t c;

  ENERGEST_ON(ENERGEST_TYPE_IRQ);
  if(UCA1IV == 2) {
    if(UCA1STATW & UCRXERR) {
      c = UCA1RXBUF;   /* Clear error flags by forcing a dummy read. */
    } else {
      c = UCA1RXBUF;
      if(uart1_input_handler != NULL) {
        if(uart1_input_handler(c)) {
          LPM4_EXIT;
        }
      }
    }
  }
  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}
#endif /* !RX_WITH_DMA */
/*---------------------------------------------------------------------------*/
