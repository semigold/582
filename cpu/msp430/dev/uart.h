/*
 * Copyright (c) 2016
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
 *
 */

/**
 * \file
 *         UART Generic header file for MSP430FRXXXX MCU
 * \author
 *         Clyde Byrd III <clydebyrdiii@yahoo.com>
 */


#ifndef UART_H_
#define UART_H_

/* struct for UART Baud rate related registers */
struct uart_parameters {
  unsigned int ucaxbrw;   /* eUSCI_Ax Baud Rate Control Word Register; Holds UCBRx */
  unsigned int ucaxmctl   /* eUSCI_Ax Modulation Control Word Register; Holds UCBRSx, UCBRFx, UCOS16 */
  unsigned long baud_rate; /* baud rate for the connection */
};
typedef uart_parameters uart_params;


#if F_CPU == 8000000uL
/* Table taken from http://www.ti.com/lit/ug/slau272c/slau272c.pdf
   the family guide for MSP430 FR57XX family. It's similar to the FR59XX family
*/
#define CRYSTAL_SETTINGS_LEN 7
extern uart_params crystal_settings[CRYSTAL_SETTINGS_LEN] =
{
  {0x34, 0x49 << 8 | 1  << 4 | 1, 9600  },
  {0x18, 0xB6 << 8 | 0  << 4 | 1, 19200 },
  {0x0D, 0x84 << 8 | 0  << 4 | 1, 38400 },
  {0x08, 0xF7 << 8 | 10 << 4 | 1, 57600 },
  {0x04, 0x55 << 8 | 5  << 4 | 1, 115200},
  {0x02, 0xBB << 8 | 2  << 4 | 1, 230400},
  {0x11, 0x4A << 8 | 0  << 4 | 0, 460800},
};

/* find the uart settings in the crystal_settings table using binary search */
extern uart_params* find_uart_settings(unsigned long ubr);

#else  /* F_CPU == 8000000uL */
#error Please add a baudrate/crystal settings table for your F_CPU from the link in platform-conf.h
#endif

#endif /* UART_H_ */