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

#include "contiki.h"

/*
 * This is SPI initialization code for the MSP430X architecture.
 *
 */

unsigned char spi_busy = 0;

/*
 * Initialize SPI bus.
 */
void
spi_init(void)
{
  // Configure GPIO

  /* XT1 is already setup in init_dco in msp430.c */

  /* P1DIR is controlled by eUSCI_B0 module.
   * DOn't worry about it */

  P1SEL1 |= BIT6 | BIT7;                 // P1.6,7 UCB0SDA, UCB0SCL
  P1SEL0 &= ~(BIT6 | BIT7);
  P2SEL1 |= BIT2;
  P2SEL0 &= ~BIT2;                       // P2.2 UCB0CLK (don't know if necessary)

  // Initialize ports for communication with SPI units.

  UCB0CTLW0 |=  UCSWRST;                 // **Put state machine in reset**
  UCB0CTLW0 |=  UCSSEL__SMCLK;           // smclk while usci is reset

  /* // MSB-first 8-bit, Master, Synchronous, 3 pin SPI master, no ste,
   watch-out for clock-phase UCCKPH */
  UCB0CTLW0 |= ( UCMSB | UCMST | UCSYNC | UCCKPL); 

  /* Set up SPI bus speed. */
  UCB0BRW = 0x02; // /2

  // Clear pending interrupts before enable!!!
  UCB0IE &= ~UCRXIFG;
  UCB0IE &= ~UCTXIFG;
  UCB0CTLW0 &= ~UCSWRST;         // **Initialize USCI state machine**

  //Enable UCB0 Interrupts
  //UCB0IE |= UCB0TXIE;              // Enable USCI_B0 TX Interrupts
  //UCB0IE |= UCB0RXIE;              // Enable USCI_B0 RX Interrupts
}
