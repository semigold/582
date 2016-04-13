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
 * This file is part of I/O functions for the msp430fr5739 platform for
 * the Contiki operating system.
 *
 *
 * -----------------------------------------------------------------
 *
 * Author  : Clyde Byrd III
 * Created : 2016-11-04
 */

#ifndef UART_PRINTF_H_
#define UART_PRINTF_H_

#include "stdarg.h"

/* functions to support uart output */

/**
 *  uputs() is used by uart_printf() and helper functions 
 *  to display or send a character. 
 *  output is a function that writes a single byte to the uart peripheral 
 *  you choose. uputs will write the entire string passed to it to the uart
 *  chosen.
 **/
void uputs(void (*output)(unsigned char), char *);

/**
 *  uputc() is used by uart_printf() and helper functions 
 *  to display or send a character. 
 *  output is a function that writes a single byte to the uart peripheral 
 *  you choose. uputc will write a single byte to the uart peripheral chosen
 **/
void uputc(void (*output)(unsigned char), unsigned);
/* 
 * This function operates similiar to printf, but only for these 7 types:
 * character,
 * string, 
 * integer, 
 * unsigned integer, 
 * long, 
 * unsigned long, 
 * hexadecimal (16-bit) 
 * 
 * output is a function that writes a single byte to the uart peripheral of your choosing.
 **/
void uart_printf(void (*output)(unsigned char), char *format, ...);

#endif /* UART_PRINTF_H_ */
