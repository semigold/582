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

#include "lib/sensors.h"
#include "dev/hwconf.h"
#include "dev/button-sensor.h"
#include "isr_compat.h"
#include "dev/leds.h"

const struct sensors_sensor button_sensor;

static struct timer debouncetimer;
static int status(int type);

HWCONF_PIN(BUTTON, 1, 1);
HWCONF_IRQ(BUTTON, 1, 1);
//HWCONF_PIN(BUTTON, 4, 5);
//HWCONF_IRQ(BUTTON, 4, 5);

/*---------------------------------------------------------------------------*/
ISR(PORT1, irq_p1)
{
  ENERGEST_ON(ENERGEST_TYPE_IRQ);

  
  if(BUTTON_CHECK_IRQ() && timer_expired(&debouncetimer)) {
    timer_set(&debouncetimer, CLOCK_SECOND / 4);
    //leds_toggle(LEDS_RED);
    sensors_changed(&button_sensor);
    LPM4_EXIT;
  }
  //leds_toggle(LEDS_GREEN);
  P1IFG = 0x00;
  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}
/*---------------------------------------------------------------------------*/
static int
value(int type)
{
  return BUTTON_READ() || !timer_expired(&debouncetimer);
}
/*---------------------------------------------------------------------------*/
static int
configure(int type, int value)
{
  
  if(type == SENSORS_ACTIVE) {
    if(value == 0) {
      /* Deactivate button sensor */
      BUTTON_DISABLE_IRQ();
    } else {
      /* Activate button sensor */
      if(!status(SENSORS_ACTIVE)) {
        timer_set(&debouncetimer, 0);
        BUTTON_IRQ_EDGE_SELECTD();

        P1SEL0 &= ~(1 << 1);
        P1SEL1 &= ~(1 << 1);
        // S1 on Launchpad board -- P4.5
        /* Port Resistor Enable Register */
        P1REN |= BIT1;   // set pullup on
        // input pin
        P1DIR &= ~BIT1;
        /* Set output to 1 for pullup resestor */
        P1OUT |= BIT1;
        /* Port Interrupt Edge Select Register */
        //P4IES |= BIT5;   // set for HI -> LOW transition
        /* Port clear Interrupt Flag Register */
        P1IFG = 0;
        /* Port Interrupt Enable Register */
       // P4IE |= BIT5;
        //BUTTON_SELECT();
        //BUTTON_MAKE_INPUT();

        BUTTON_ENABLE_IRQ();
      }
    }
    return 1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
status(int type)
{
  switch(type) {
  case SENSORS_ACTIVE:
  case SENSORS_READY:
    return BUTTON_IRQ_ENABLED();
  default:
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(button_sensor, BUTTON_SENSOR,
           value, configure, status);

