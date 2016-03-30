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
 */

/*
 * Yet another machine dependent MSP430X UART generic code.
 * IF2, etc. can not be used here... need to abstract to some macros
 * later.
 */
#include "dev/uart.h"

/* Table taken from http://www.ti.com/lit/ug/slau272c/slau272c.pdf
   the family guide for MSP430 FR57XX family. It's similar to the FR59XX family
*/

const uart_params crystal_settings[CRYSTAL_SETTINGS_LEN] =
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

const uart_params*
find_uart_settings(unsigned long ubr)
{
  int low = 0;
  int high = CRYSTAL_SETTINGS_LEN;

  while(low <= high) {

    int mid = low + ((high - low) / 2);
    const uart_params *up = &(crystal_settings[mid]);

    if(ubr ==  up->baud_rate)
      return up;
    else if (ubr > up->baud_rate)
      low = mid + 1;
    else
      high = mid - 1;
  }
  /* if value isn't found use the lowest settings */
  return &(crystal_settings[0]);
}
