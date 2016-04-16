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

/******************************************************************************
 *                          Reusable MSP430 printf()
 *
 * Description: This printf function was written by oPossum and originally
 *              posted on the 43oh.com forums. For more information on this
 *              code, please see the link below.
 *
 *              http://www.43oh.com/forum/viewtopic.php?f=10&t=1732
 *
 *              A big thanks to oPossum for sharing such great code!
 *
 * Author:  oPossum
 * Source:  http://www.43oh.com/forum/viewtopic.php?f=10&t=1732
 * Date:    10-17-11
 *
 * Note: This comment section was written by Nicholas J. Conn on 06-07-2012
 *       for use on NJC's MSP430 LaunchPad Blog.
 ******************************************************************************/

#include "uart_printf.h"

void
uputs(void (*output)(unsigned char), char *s)
{
  char c;

  // Loops through each character in string 's'
  while ((c = *s++)) {
    output(c);
  }
}

void
uputc(void (*output)(unsigned char), unsigned b)
{
  output(b);
}

static const unsigned long dv[] = {
//  4294967296      // 32 bit unsigned max
    1000000000,// +0
    100000000, // +1
    10000000, // +2
    1000000, // +3
    100000, // +4
//       65535      // 16 bit unsigned max
    10000, // +5
    1000, // +6
    100, // +7
    10, // +8
    1, // +9
};

static void
xtoa(void (*output)(unsigned char), unsigned long x, const unsigned long *dp)
{
  char c;
  unsigned long d;
  if (x) {
    while (x < *dp)
      ++dp;
    do {
      d = *dp++;
      c = '0';
      while (x >= d)
        ++c, x -= d;
      uputc(output, c);
    } while (!(d & 1));
  } else
    uputc(output, '0');
}

static void
uputh(void (*output)(unsigned char), unsigned n)
{
  static const char hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
      '9', 'A', 'B', 'C', 'D', 'E', 'F' };
  uputc(output, hex[n & 15]);
}

void
uart_printf(void (*output)(unsigned char), char *format, ...)
{
  char c;
  int i;
  long n;

  va_list a;
  va_start(a, format);
  while((c = *format++)) {
    if(c == '%') {
      switch((c = *format++)) {
        case 's': // String
          uputs(output, va_arg(a, char*));
          break;
        case 'c':// Char
          uputc(output, va_arg(a, int));
        break;
        case 'd':
        case 'i':// 16 bit Integer
        case 'u':// 16 bit Unsigned
          i = va_arg(a, int);
          if(c == 'i' && i < 0) i = -i, uputc(output, '-');
          xtoa(output, (unsigned)i, dv + 5);
        break;
        case 'l':// 32 bit Long
        case 'n':// 32 bit uNsigned loNg
          n = va_arg(a, long);
          if(c == 'l' && n < 0) n = -n, uputc(output, '-');
          xtoa(output, (unsigned long)n, dv);
        break;
        case 'x':// 16 bit heXadecimal
          i = va_arg(a, int);
          uputh(output, i >> 12);
          uputh(output, i >> 8);
          uputh(output, i >> 4);
          uputh(output, i);
        break;
        case 0: return;
        default: goto bad_fmt;
      }
    } else
      bad_fmt: uputc(output, c);
  }
  va_end(a);
}
