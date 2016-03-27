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
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Led arch specific file to control leds on the fr5969 platform
 * \author
 *         Clyde Byrd III <clydebyrdiii@yahoo.com>
 */

#include "contiki-conf.h"
#include "dev/leds.h"

/*---------------------------------------------------------------------------*/
void
leds_arch_init(void)
{
  // Configure GPIO
  LEDS_1_PXOUT &= ~LEDS_1_BIT;      // Clear PJ.0 output latch for a defined power-on state
  LEDS_1_PXDIR |= LEDS_1_BIT;       // Set PJ.0 to output direction

  LEDS_2_PXOUT &= ~LEDS_2_BIT;      // Clear PJ.1 to output latch for a defined power-on state
  LEDS_2_PXDIR |= LEDS_2_BIT;       // Set PJ.1 to output direction

  LEDS_3_PXOUT &= ~LEDS_3_BIT;      // Clear PJ.2 output latch for a defined power-on state
  LEDS_3_PXDIR |= LEDS_3_BIT;       // Set PJ.2 to output direction

  LEDS_4_PXOUT &= ~LEDS_4_BIT;      // Clear PJ.3 to output latch for a defined power-on state
  LEDS_4_PXDIR |= LEDS_4_BIT;       // Set PJ.3 to output direction

  LEDS_5_PXOUT &= ~LEDS_5_BIT;      // Clear P3.4 output latch for a defined power-on state
  LEDS_5_PXDIR |= LEDS_5_BIT;       // Set P3.4 to output direction

  LEDS_6_PXOUT &= ~LEDS_6_BIT;      // Clear P3.5 to output latch for a defined power-on state
  LEDS_6_PXDIR |= LEDS_6_BIT;       // Set P3.5 to output direction

  LEDS_7_PXOUT &= ~LEDS_7_BIT;      // Clear P3.6 output latch for a defined power-on state
  LEDS_7_PXDIR |= LEDS_7_BIT;       // Set P3.6 to output direction

  LEDS_8_PXOUT &= ~LEDS_8_BIT;      // Clear P3.7 to output latch for a defined power-on state
  LEDS_8_PXDIR |= LEDS_8_BIT;       // Set P3.7 to output direction

}
/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
  unsigned char ledv = 0;
  if(LEDS_1_PXOUT & LEDS_1)
    ledv |= LEDS_1_BIT;
  
  if(LEDS_2_PXOUT & LEDS_2)
    ledv |= LEDS_2_BIT;

  if(LEDS_3_PXOUT & LEDS_3)
    ledv |= LEDS_3_BIT;
  
  if(LEDS_4_PXOUT & LEDS_4)
    ledv |= LEDS_4_BIT;
  
  if(LEDS_5_PXOUT & LEDS_5)
    ledv |= LEDS_5_BIT;
  
  if(LEDS_6_PXOUT & LEDS_6)
    ledv |= LEDS_6_BIT;
  
  if(LEDS_7_PXOUT & LEDS_7)
    ledv |= LEDS_7_BIT;
  
  if(LEDS_8_PXOUT & LEDS_8)
    ledv |= LEDS_8_BIT;
  
  return ledv;
}
/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char l)
{
  
  /* code checks each bit to see if it is 1 or 0 
  *  if it is 1 it turns that corresponding LED on;
  *  off otherwise
  */
  if(l & LEDS_1)
    LEDS_1_PXOUT |= LEDS_1_BIT;  // turn LED on
  else
    LEDS_1_PXOUT &= ~LEDS_1_BIT; // turn LED off

  if(l & LEDS_2)
    LEDS_2_PXOUT |= LEDS_2_BIT;
  else
    LEDS_2_PXOUT &= ~LEDS_2_BIT;

  if(l & LEDS_3)
    LEDS_3_PXOUT |= LEDS_3_BIT;
  else
    LEDS_3_PXOUT &= ~LEDS_3_BIT;

  if(l & LEDS_4)
    LEDS_4_PXOUT |= LEDS_4_BIT;
  else
    LEDS_4_PXOUT &= ~LEDS_4_BIT;

  if(l & LEDS_5)
    LEDS_5_PXOUT |= LEDS_5_BIT;
  else
    LEDS_5_PXOUT &= ~LEDS_5_BIT;

  if(l & LEDS_6)
    LEDS_6_PXOUT |= LEDS_6_BIT;
  else
    LEDS_6_PXOUT &= ~LEDS_6_BIT;

  if(l & LEDS_7)
    LEDS_7_PXOUT |= LEDS_7_BIT;
  else
    LEDS_7_PXOUT &= ~LEDS_7_BIT;

  if(l & LEDS_8)
    LEDS_8_PXOUT |= LEDS_8_BIT;
  else
    LEDS_8_PXOUT &= ~LEDS_8_BIT;

}
