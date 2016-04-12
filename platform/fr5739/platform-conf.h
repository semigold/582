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
 *         Platform configuration for the MSP430FR5739 platform
 * \author
 *         Clyde Byrd III
 */

#ifndef PLATFORM_CONF_H_
#define PLATFORM_CONF_H_

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */
#define MSP430_FR5739 1  /* Enric */

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
typedef unsigned long off_t;

/*
 * Definitions below are dictated by the hardware and not really
 * changeable!
 */

/* LED ports */

/* all are blue */

/* LED 1, 2, 3, 4 share the same Port */
#define LEDS_1234_PXDIR PJDIR
#define LEDS_1234_PXOUT PJOUT

/* LED1 on PJ.0 */
#define LEDS_1_BIT   BIT0

/* LED2 on PJ.1 */
#define LEDS_2_BIT   BIT1

/* LED3 on PJ.2 */
#define LEDS_3_BIT   BIT2

/* LED4 on PJ.3 */
#define LEDS_4_BIT   BIT3

/* LEDS 5, 6, 7, 8 share the same Port */
#define LEDS_5678_PXDIR P3DIR
#define LEDS_5678_PXOUT P3OUT

/* LED5 on P3.4 */
#define LEDS_5_BIT   BIT4

/* LED6 on P3.5 */
#define LEDS_6_BIT   BIT5

/* LED7 on P3.6 */
#define LEDS_7_BIT   BIT6

/* LED8 on P3.7 */
#define LEDS_8_BIT   BIT7

#define LEDS_1    BIT0
#define LEDS_2    BIT1
#define LEDS_3    BIT2
#define LEDS_4    BIT3
#define LEDS_5    BIT4
#define LEDS_6    BIT5
#define LEDS_7    BIT6
#define LEDS_8    BIT7

/* redefine contiki LED colors since all LEDS are blue; and we have 8 LEDS */

#define LEDS_GREEN    BIT0

#define LEDS_YELLOW   BIT1

#define LEDS_RED      BIT2

#define LEDS_CONF_ALL (BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7)


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
