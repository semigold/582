/*
 * Copyright (c) 2016.
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

/**
 * \file
 *         Platform configuration for the MSP430fr5969 platform
 * \author
 *         Clyde Byrd III
 */

#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */
#define MSP430_FR5969 1  /* Enric */

/* Delay between GO signal and SFD: radio fixed delay + 4Bytes preample + 1B SFD -- 1Byte time is 32us
 * ~327us + 129preample = 456 us */
#define RADIO_DELAY_BEFORE_TX ((unsigned)US_TO_RTIMERTICKS(456))
/* Delay between GO signal and start listening
 * ~50us delay + 129preample + ?? = 183 us */
#define RADIO_DELAY_BEFORE_RX ((unsigned)US_TO_RTIMERTICKS(183))
/* Delay between the SFD finishes arriving and it is detected in software */
#define RADIO_DELAY_BEFORE_DETECT 0

#define PLATFORM_HAS_LEDS    1
#define PLATFORM_HAS_BUTTON  1
#define PLATFORM_HAS_RADIO   0
#define PLATFORM_HAS_BATTERY 0

/* CPU target speed in Hz */
#define F_CPU 8000000uL /* 8MHz by default */

/* Our clock resolution, this is the same as Unix HZ. */
#define CLOCK_CONF_SECOND 128UL

#define BAUD2UBR(baud) ((F_CPU / baud))

#define CCIF
#define CLIF

#define HAVE_STDINT_H
#include "msp430def.h"
#include "dev/uart_printf.h"

/* reduce code size by using custom uart_printf */
#define printf uart_printf

/* XXX Temporary place for defines that are lacking in mspgcc4's gpio.h */
#ifdef __IAR_SYSTEMS_ICC__
#ifndef P1SEL2_
#define P1SEL2_              (0x0041u)  /* Port 1 Selection 2*/
DEFC(P1SEL2, P1SEL2_)
#endif
#else /* __IAR_SYSTEMS_ICC__ */
#ifdef __GNUC__
#ifndef P1SEL2_
#define P1SEL2_             0x0041    /* Port 1 Selection 2*/
sfrb(P1SEL2, P1SEL2_);
#endif
#endif /* __GNUC__ */
#endif /* __IAR_SYSTEMS_ICC__ */

/* Types for clocks and uip_stats */
typedef unsigned short uip_stats_t;
typedef unsigned long clock_time_t;
#define off_t unsigned long

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */

/* LED ports */

 /* Green LED is LED2  on P1.0 */
#define LEDS_GREEN_BIT   BIT0
#define LEDS_GREEN_PXDIR P1DIR
#define LEDS_GREEN_PXOUT P1OUT

/* RED LED is LED1  on P4.6 */
#define LEDS_RED_BIT     BIT6
#define LEDS_RED_PXDIR   P4DIR
#define LEDS_RED_PXOUT   P4OUT

/* Button ports */

/* DCO speed resynchronization for more robust UART, etc. */
#define DCOSYNCH_CONF_ENABLED 0
#define DCOSYNCH_CONF_PERIOD 30

#define ROM_ERASE_UNIT_SIZE  512
#define XMEM_ERASE_UNIT_SIZE (64 * 1024L)

#define CFS_CONF_OFFSET_TYPE    long

/* Use the first 64k of external flash for node configuration */
#define NODE_ID_XMEM_OFFSET     (0 * XMEM_ERASE_UNIT_SIZE)

/* Use the second 64k of external flash for codeprop. */
#define EEPROMFS_ADDR_CODEPROP  (1 * XMEM_ERASE_UNIT_SIZE)

#define CFS_XMEM_CONF_OFFSET    (2 * XMEM_ERASE_UNIT_SIZE)
#define CFS_XMEM_CONF_SIZE      (1 * XMEM_ERASE_UNIT_SIZE)

#define CFS_RAM_CONF_SIZE 4096

#endif /* PLATFORM_CONF_H_ */
