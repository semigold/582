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
 *
 */

#include "contiki.h"
#include <stdio.h>
#include <string.h>

#include "dev/button-sensor.h"
#include "dev/leds.h"
#include "dev/serial-line.h"
#include "dev/slip.h"
#include "dev/uart.h"
#include "dev/watchdog.h"
#include "dev/xmem.h"
#include "dev/adc.h"
#include "lib/random.h"
#include "net/netstack.h"
#include "net/mac/frame802154.h"

#if NETSTACK_CONF_WITH_IPV6
#include "net/ipv6/uip-ds6.h"
#endif /* NETSTACK_CONF_WITH_IPV6 */

#include "net/rime/rime.h"

#include "sys/node-id.h"
#include "sys/autostart.h"

#if UIP_CONF_ROUTER

#ifndef UIP_ROUTER_MODULE
#ifdef UIP_CONF_ROUTER_MODULE
#define UIP_ROUTER_MODULE UIP_CONF_ROUTER_MODULE
#else /* UIP_CONF_ROUTER_MODULE */
#define UIP_ROUTER_MODULE rimeroute
#endif /* UIP_CONF_ROUTER_MODULE */
#endif /* UIP_ROUTER_MODULE */

extern const struct uip_router UIP_ROUTER_MODULE;
#endif /* UIP_CONF_ROUTER */

#ifndef NETSTACK_CONF_WITH_IPV4
#define NETSTACK_CONF_WITH_IPV4 0
#endif

#if NETSTACK_CONF_WITH_IPV4
#include "net/ip/uip.h"
#include "net/ipv4/uip-fw.h"
#include "net/ipv4/uip-fw-drv.h"
#include "net/ipv4/uip-over-mesh.h"
static struct uip_fw_netif slipif =
  {UIP_FW_NETIF(192,168,1,2, 255,255,255,255, slip_send)};
static struct uip_fw_netif meshif =
  {UIP_FW_NETIF(172,16,0,0, 255,255,0,0, uip_over_mesh_send)};

#endif /* NETSTACK_CONF_WITH_IPV4 */

#define UIP_OVER_MESH_CHANNEL 8
#if NETSTACK_CONF_WITH_IPV4
static uint8_t is_gateway;
#endif /* NETSTACK_CONF_WITH_IPV4 */

#ifdef EXPERIMENT_SETUP
#include "experiment-setup.h"
#endif

void init_platform(void);

void uip_log(char *msg) { puts(msg); }
/*---------------------------------------------------------------------------*/
#ifndef RF_CHANNEL
#define RF_CHANNEL              26
#endif
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
#ifndef NODE_ID
#define NODE_ID 0x03
#endif /* NODE_ID */
/*---------------------------------------------------------------------------*/
#if 0

static void
print_processes(struct process * const processes[])
{
  /*  const struct process * const * p = processes;*/
  printf("Starting");
  while(*processes != NULL) {
    //printf(" %s", (*processes)->name);
    processes++;
  }
  printf("\r\n");
}

#endif /* !PROCESS_CONF_NO_PROCESS_NAMES */
/*--------------------------------------------------------------------------*/
#if NETSTACK_CONF_WITH_IPV4
#endif /* NETSTACK_CONF_WITH_IPV4 */
/*---------------------------------------------------------------------------*/
#if defined(__MSP430_HEADER_VERSION__) && __MSP430_HEADER_VERSION__ < 1074
int
putchar(int c) {
    uart1_writeb(c);
    return c;
}
#endif

SENSORS(&button_sensor, &button_sensor2);

#define ADC_MONITOR_THRESHOLD   3.0
#define ADC_MONITOR_FREQUENCY   8000

#define MCLK_FREQUENCY          8000000
#define SMCLK_FREQUENCY         8000000

extern void initAdcMonitor(void);
extern void stopAdcMonitor(void);

int main(void)
{

  /* Halt the watchdog timer */
  WDTCTL = WDTPW | WDTHOLD;

  /* Initialize the GPIO, clock system and the ADC monitor. */
  msp430_cpu_init();
  clock_init();
  leds_init();

  clock_wait(2);

  uart0_init(115200); /* Must come before first printf */

  /* set the uart function that will write a byte to the uart module */
  set_uart_out(uart0_writeb);

  clock_wait(1);

  rtimer_init();

  initAdcMonitor();

  /*
   * Hardware initialization done!
   */

  process_init();
  process_start(&etimer_process, NULL);

  ctimer_init();

  process_start(&sensors_process, NULL);

  //uart0_set_input(serial_line_input_byte);
  //serial_line_init();

  // energest_init();
  // ENERGEST_ON(ENERGEST_TYPE_CPU);
  printf("Main Initialization finished\r\n");
  autostart_start(autostart_processes);

  //leds_on(LEDS_GREEN);


  watchdog_start();
  watchdog_stop(); /* Stop the wdt... */

  while (1) {
    int r;
    do {
      /* Reset watchdog. */
      watchdog_periodic();
      r = process_run();
    } while(r > 0);
  }
}

void initAdcMonitor(void)
{   
    __disable_interrupt();
    /* Initialize timer for ADC trigger. */
    TA0CCR0 = (SMCLK_FREQUENCY/ADC_MONITOR_FREQUENCY);
    TA0CCR1 = TA0CCR0/2;
    TA0CCTL1 = OUTMOD_3;
    TA0CTL = TASSEL__SMCLK | MC__UP;

    /* Configure internal 2.0V reference. */
    while(REFCTL0 & REFGENBUSY);
    REFCTL0 |= REFVSEL_1 | REFON;
    while(!(REFCTL0 & REFGENRDY));

    /*
     * Initialize ADC12_B window comparator using the battery monitor.
     * The monitor will first enable the high side to the monitor voltage plus
     * 0.1v to make sure the voltage is sufficiently above the threshold. When
     * the high side is triggered the interrupt service routine will switch to
     * the low side and wait for the voltage to drop below the threshold. When
     * the voltage drops below the threshold voltage the device will invoke the
     * compute through power loss shutdown function to save the application
     * state and enter complete device shutdown.
     */
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
    ADC12CTL1 = ADC12SHS_1 | ADC12SSEL_0 | ADC12CONSEQ_2 | ADC12SHP;
    ADC12CTL3 = ADC12BATMAP;
    ADC12MCTL0 = ADC12INCH_31 | ADC12VRSEL_1 | ADC12WINC;
    ADC12HI = (uint16_t)(4096*((ADC_MONITOR_THRESHOLD+0.1)/2)/(2.0));
    ADC12LO = (uint16_t)(4096*(ADC_MONITOR_THRESHOLD/2)/(2.0));
    ADC12IFGR2 &= ~(ADC12HIIFG | ADC12LOIFG);
    ADC12IER2 = ADC12HIIE;
    ADC12CTL0 |= ADC12ENC;
    __enable_interrupt();
}

void stopAdcMonitor(void)
{
    /* Stop the timer, reference and ADC. */
    TA0CTL &= ~MC_3;
    REFCTL0 &= ~REFON;
    ADC12CTL0 &= ~(ADC12ENC | ADC12ON);
}

ISR(ADC12, power)
{
    switch(__even_in_range(ADC12IV, ADC12IV_ADC12LOIFG)) {
        case ADC12IV_NONE:        break;        // Vector  0: No interrupt
        case ADC12IV_ADC12OVIFG:  break;        // Vector  2: ADC12MEMx Overflow
        case ADC12IV_ADC12TOVIFG: break;        // Vector  4: Conversion time overflow
        case ADC12IV_ADC12HIIFG:                // Vector  6: Window comparator high side
            /* Disable the high side and enable the low side interrupt. */
            ADC12IER2 &= ~ADC12HIIE;
            ADC12IER2 |= ADC12LOIE;
            ADC12IFGR2 &= ~ADC12LOIFG;
            break;
        case ADC12IV_ADC12LOIFG:                // Vector  8: Window comparator low side
            /* Stop the ADC monitor and enter device shutdown with 64ms timeout. */
            stopAdcMonitor();
            ctpl_enterShutdown(CTPL_SHUTDOWN_TIMEOUT_64_MS);

            /* Reinitialize the ADC monitor since the ADC state is not retained. */
            initAdcMonitor();
            uart0_init(115200);
            set_uart_out(uart0_writeb);

            break;
        default: break;
    }
}

// int
// main(int argc, char **argv)
// {
//   /*
//    * Initalize hardware.
//    */

//   msp430_cpu_init();
//   clock_init();
//   leds_init();

//   clock_wait(2);

//   uart0_init(115200); /* Must come before first printf */
//   set_uart_out(uart0_writeb);
//   clock_wait(1);

//   //rtimer_init();

//   /*
//    * Hardware initialization done!
//    */

//   //process_init();
//   //process_start(&etimer_process, NULL);

//   ctimer_init();
  
//   //process_start(&sensors_process, NULL);

//   uart0_set_input(serial_line_input_byte);
//   serial_line_init();

  
//   initAdcMonitor();

//   energest_init();
//   ENERGEST_ON(ENERGEST_TYPE_CPU);

//   //print_processes(autostart_processes);
//   //autostart_start(autostart_processes);

//   //leds_on(LEDS_GREEN);
//   printf("Main Initialization finished\r\n");
//   /*
//    * This is the scheduler loop.
//    */
//   watchdog_start();
//   watchdog_stop(); /* Stop the wdt... */
//   //while(1) {
 
//       P1DIR |= BIT0;
//   P1OUT &= ~BIT0;
//   while (1) {
//       for (int i = 1; i < 5; i++) {
//           for (int j = i; j > 0; j--) {
//               /* Blink the LED for 0.1s and delay for 0.2s */
//               P1OUT |= BIT0;
//               __delay_cycles(F_CPU/8);
//               P1OUT &= ~BIT0;
//               __delay_cycles(F_CPU/8);
//           }
//           /* Delay 1 second between counts. */
//           __delay_cycles(F_CPU);
//       }
//   }
//     /*
//      * Idle processing.
//      */
//     // int s = splhigh();          /* Disable interrupts. */
//     // /* uart1_active is for avoiding LPM3 when still sending or receiving */
//     // if(process_nevents() != 0 || uart0_active()) {
//     //   splx(s);                  /* Re-enable interrupts. */
//     // } else {
//     //   static unsigned long irq_energest = 0;

//     //   /* Re-enable interrupts and go to sleep atomically. */
//     //   ENERGEST_SWITCH(ENERGEST_TYPE_CPU, ENERGEST_TYPE_LPM);
//     //   /* We only want to measure the processing done in IRQs when we
//     //      are asleep, so we discard the processing time done when we
//     //      were awake. */
//     //   energest_type_set(ENERGEST_TYPE_IRQ, irq_energest);
//     //   watchdog_stop();
//     //   _BIS_SR(GIE | SCG0 | SCG1 | CPUOFF); /* LPM3 sleep. This
//     //                                           statement will block
//     //                                           until the CPU is
//     //                                           woken up by an
//     //                                           interrupt that sets
//     //                                           the wake up flag. */

//     //   /* We get the current processing time for interrupts that was
//     //      done during the LPM and store it for next time around.  */
//     //   dint();
//     //   irq_energest = energest_type_time(ENERGEST_TYPE_IRQ);
//     //   eint();
//     //   watchdog_start();
//     //   ENERGEST_SWITCH(ENERGEST_TYPE_LPM, ENERGEST_TYPE_CPU);
//     // }
//   //}
//   return 0;
// }
// /*---------------------------------------------------------------------------*/
// #if LOG_CONF_ENABLED
// void
// log_message(char *m1, char *m2)
// {
//   printf("%s%s\n", m1, m2);
// }
// #endif /* LOG_CONF_ENABLED */
