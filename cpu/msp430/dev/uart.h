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

#include "contiki.h"

/* struct for UART Baud rate related registers */
struct uart_parameters {
  unsigned int ucaxbrw;   /* eUSCI_Ax Baud Rate Control Word Register; Holds UCBRx */
  unsigned int ucaxmctl;   /* eUSCI_Ax Modulation Control Word Register; Holds UCBRSx, UCBRFx, UCOS16 */
  unsigned long baud_rate; /* baud rate for the connection */
};

typedef struct uart_parameters uart_params;


#if F_CPU == 8000000uL

/* find the uart settings in the crystal_settings table using binary search */
const uart_params* find_uart_settings(unsigned long ubr);

#else  /* F_CPU == 8000000uL */
#error Please add a baudrate/crystal settings table to uart.c for your F_CPU from the link in uart.h
#endif

#endif /* UART_H_ */