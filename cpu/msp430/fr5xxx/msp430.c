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
 * This file is part of the Contiki operating system.
 */
#include "contiki.h"
#include "dev/watchdog.h"

/* dco_required set to 1 will cause the CPU not to go into
   sleep modes where the DCO clock stopped */
int msp430_dco_required;

#if defined(__MSP430__) && defined(__GNUC__)
#define asmv(arg) __asm__ __volatile__(arg)
#endif
/*---------------------------------------------------------------------------*/
void
msp430_init_dco(void)
{
#ifdef __IAR_SYSTEMS_ICC__
  __bis_SR_register(SCG0);
#else
  asmv("bis %0, r2" : : "i" (SCG0));
#endif

  // Setup GPIO for XT1 Clock

  PJSEL0 |= BIT4 | BIT5;                    // For XT1

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings

  PM5CTL0 &= ~LOCKLPM5;

  // Clock System Setup
  CSCTL0_H = CSKEY >> 8;                    // Unlock CS registers

  #ifdef __MSP430FR5739
  CSCTL1 |= DCOFSEL0 + DCOFSEL1;             // Set DCO to 8MHz
  #elif __MSP430FR5969
  CSCTL1 |= DCOFSEL_6;                       // Set DCO to 8MHz
  #elif
  #error "Set the DCO speed for your MCU family"
  #endif

  /*
  *  SELA_0 differs on platforms, but 5969 it expands to
  *  SELA__LFXTCLK; 5739 it expands to SELA__XT1CLK
  */

  CSCTL2 = SELA_0 | SELS__DCOCLK | SELM__DCOCLK;       // Set SMCLK=MCLK=DCO
                                                       // ACLK=XT1
  CSCTL3 = DIVA_0 | DIVS_0 | DIVM_0;                   // Set all dividers

  #ifdef __MSP430FR5739
  CSCTL4 |= XT1DRIVE_1;                   /* Set XT1 oscillator operating
                                             range to 8 MHz to 16 MHz. */
  CSCTL4 &= ~XT1OFF;                      /* Set XT1 to be on  */
  #elif __MSP430FR5969
  CSCTL4 &= ~LFXTOFF;                     /* Set LFXT1 to be on */
  #elif
  #error "Set CSCTL4 for your MCU family"
  #endif

  do
  {

    #ifdef __MSP430FR5739
    CSCTL5 &= ~XT1OFFG;                   // Clear XT1 fault flag
    #elif __MSP430FR5969
    CSCTL5 &= ~LFXTOFFG;                  // Clear LFXT1 fault flag
    #elif
    #error "Clear XT1 fault flag for your MCU family"
    #endif

    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG);                // Test oscillator fault flag
  CSCTL0_H = 0;                             // Lock CS registers

#ifdef __IAR_SYSTEMS_ICC__
  __bic_SR_register(SCG0);
#else
  asmv("bic %0, r2" : : "i" (SCG0));
#endif
}
/*---------------------------------------------------------------------------*/

static void
init_ports(void)
{
  /* Turn everything off, device drivers enable what is needed. */
  /* All configured for digital I/O */
  #ifdef __MSP430_HAS_P1SEL0__
  P1SEL0 = 0;
  P1SEL1 = 0;

  P1DIR = 0;
  P1OUT = 0;

  P1IE = 0;
  #endif

  #ifdef __MSP430_HAS_P2SEL0__
  P2SEL0 = 0;
  P2SEL1 = 0;

  P2DIR = 0;
  P2OUT = 0;

  P2IE = 0;
  #endif

  #ifdef __MSP430_HAS_P3SEL0__
  P3SEL0 = 0;
  P3SEL1 = 0;

  P3DIR = 0;
  P3OUT = 0;

  P3IE = 0;
  #endif

  #ifdef __MSP430_HAS_P4SEL0__
  P4SEL0 = 0;
  P4SEL1 = 0;

  P4DIR = 0;
  P4OUT = 0;

  P4IE = 0;
  #endif

  #ifdef __MSP430_HAS_P5SEL0__
  P5SEL0 = 0;
  P5SEL1 = 0;

  P5DIR = 0;
  P5OUT = 0;

  P5IE = 0;
  #endif

  #ifdef __MSP430_HAS_P6SEL0__
  P6SEL0 = 0;
  P6SEL1 = 0;

  P6DIR = 0;
  P6OUT = 0;

  P6IE = 0;
  #endif

  #ifdef __MSP430_HAS_P7SEL0__
  P7SEL0 = 0;
  P7SEL1 = 0;

  P7DIR = 0;
  P7OUT = 0;

  P7IE = 0;
  #endif

  #ifdef __MSP430_HAS_P8SEL0__
  P8SEL0 = 0;
  P8SEL1 = 0;

  P8DIR = 0;
  P8OUT = 0;

  P8IE = 0;
  #endif

  #ifdef __MSP430_HAS_P9SEL0__
  P9SEL0 = 0;
  P9SEL1 = 0;

  P9DIR = 0;
  P9OUT = 0;

  P9IE = 0;
  #endif

  #ifdef __MSP430_HAS_P10SEL0__
  P10SEL0 = 0;
  P10SEL1 = 0;

  P10DIR = 0;
  P10OUT = 0;

  P10IE = 0;
  #endif

  #ifdef __MSP430_HAS_PASEL0__
  PASEL0 = 0;
  PASEL1 = 0;

  PADIR = 0;
  PAOUT = 0;

  PAIE = 0;
  #endif

  #ifdef __MSP430_HAS_PBSEL0__
  PBSEL0 = 0;
  PBSEL1 = 0;

  PBDIR = 0;
  PBOUT = 0;

  PBIE = 0;
  #endif

  #ifdef __MSP430_HAS_PCSEL0__
  PCSEL0 = 0;
  PCSEL1 = 0;

  PCDIR = 0;
  PCOUT = 0;

  PCIE = 0;
  #endif

  #ifdef __MSP430_HAS_PDSEL0__
  PDSEL0 = 0;
  PDSEL1 = 0;

  PDDIR = 0;
  PDOUT = 0;

  PDIE = 0;
  #endif

  #ifdef __MSP430_HAS_PESEL0__
  PESEL0 = 0;
  PESEL1 = 0;

  PEDIR = 0;
  PEOUT = 0;

  PEIE = 0;
  #endif

  #ifdef __MSP430_HAS_PFSEL0__
  PFSEL0 = 0;
  PFSEL1 = 0;

  PFDIR = 0;
  PFOUT = 0;

  PFIE = 0;
  #endif

  #ifdef __MSP430_HAS_PJSEL0__
  PJSEL0 = 0;
  PJSEL1 = 0;

  PJDIR = 0;
  PJOUT = 0;

  PJIE = 0;
  #endif

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings

  PM5CTL0 &= ~LOCKLPM5;
}
/*---------------------------------------------------------------------------*/
/* msp430-ld may align _end incorrectly. Workaround in cpu_init. */
#if defined(__MSP430__) && defined(__GNUC__)
extern int _end;		/* Not in sys/unistd.h */
static char *cur_break = (char *)&_end;
#endif

/*---------------------------------------------------------------------------*/
/* add/remove_lpm_req - for requiring a specific LPM mode. currently Contiki */
/* jumps to LPM3 to save power, but DMA will not work if DCO is not clocked  */
/* so some modules might need to enter their LPM requirements                */
/* NOTE: currently only works with LPM1 (e.g. DCO) requirements.             */
/*---------------------------------------------------------------------------*/
void
msp430_add_lpm_req(int req)
{
  if(req <= MSP430_REQUIRE_LPM1) {
    msp430_dco_required++;
  }
}

void
msp430_remove_lpm_req(int req)
{
  if(req <= MSP430_REQUIRE_LPM1) {
    msp430_dco_required--;
  }
}

void
msp430_cpu_init(void)
{
  dint();
  watchdog_init();
  init_ports();
  msp430_init_dco();
  eint();
#if defined(__MSP430__) && defined(__GNUC__)
  if((uintptr_t)cur_break & 1) { /* Workaround for msp430-ld bug! */
    cur_break++;
  }
#endif

  msp430_dco_required = 0;
}
/*---------------------------------------------------------------------------*/

#define STACK_EXTRA 32

/*
 * Allocate memory from the heap. Check that we don't collide with the
 * stack right now (some other routine might later). A watchdog might
 * be used to check if cur_break and the stack pointer meet during
 * runtime.
 */
#if defined(__MSP430__) && defined(__GNUC__)
void *
sbrk(int incr)
{
  char *stack_pointer;

  asmv("mov r1, %0" : "=r" (stack_pointer));
  stack_pointer -= STACK_EXTRA;
  if(incr > (stack_pointer - cur_break))
    return (void *)-1;		/* ENOMEM */

  void *old_break = cur_break;
  cur_break += incr;
  /*
   * If the stack was never here then [old_break .. cur_break] should
   * be filled with zeros.
  */
  return old_break;
}
#endif
/*---------------------------------------------------------------------------*/
/*
 * Mask all interrupts that can be masked.
 */
int
splhigh_(void)
{
  int sr;
  /* Clear the GIE (General Interrupt Enable) flag. */
#ifdef __IAR_SYSTEMS_ICC__
  sr = __get_SR_register();
  __bic_SR_register(GIE);
#else
  asmv("mov r2, %0" : "=r" (sr));
  asmv("bic %0, r2" : : "i" (GIE));
#endif
  return sr & GIE;		/* Ignore other sr bits. */
}
/*---------------------------------------------------------------------------*/
#ifdef __IAR_SYSTEMS_ICC__
int __low_level_init(void)
{
  /* turn off watchdog so that C-init will run */
  WDTCTL = WDTPW + WDTHOLD;
  /*
   * Return value:
   *
   *  1 - Perform data segment initialization.
   *  0 - Skip data segment initialization.
   */
  return 1;
}
#endif
/*---------------------------------------------------------------------------*/
