/*
 * Copyright (c) 20016.
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
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki-conf.h"
#include "dev/leds.h"

/*---------------------------------------------------------------------------*/
void
leds_arch_init(void)
{
  // Configure GPIO
  LEDS_GREEN_PXOUT &= ~LEDS_GREEN_BIT;  // Clear P1.0 output latch for a defined power-on state
  LEDS_GREEN_PXDIR |= LEDS_GREEN_BIT;   // Set P1.0 to output direction

  LEDS_RED_PXOUT &= ~LEDS_RED_BIT;      // Clear P4.6 to output latch for a defined power-on state
  LEDS_RED_PXDIR |= LEDS_RED_BIT;       // Set P4.6 to output direction

  // Disable the GPIO power-on default high-impedance mode to activate
  // previously configured port settings. The oscillator should now start...
  PM5CTL0 &= ~LOCKLPM5;
}
/*---------------------------------------------------------------------------*/
unsigned char
leds_arch_get(void)
{
  return (LEDS_GREEN_PXOUT & LEDS_GREEN_BIT) ? LEDS_GREEN: 0 
  | (LEDS_RED_PXOUT & LEDS_RED_BIT) ? LEDS_RED : 0;
}
/*---------------------------------------------------------------------------*/
void
leds_arch_set(unsigned char l)
{
  
  if(l & LEDS_GREEN)
    LEDS_GREEN_PXOUT |= LEDS_GREEN_BIT;  // turn green on
  else
    LEDS_GREEN_PXOUT &= ~LEDS_GREEN_BIT; // turn green off

  if (l & LEDS_RED)
    LEDS_RED_PXOUT |= LEDS_RED_BIT;      // turn red on
  else
    LEDS_RED_PXOUT &= ~LEDS_RED_BIT;     // turn red off

}