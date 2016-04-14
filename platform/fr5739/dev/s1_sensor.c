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
const struct sensors_sensor button_sensor2;

static struct timer debouncetimer1;
static struct timer debouncetimer2;
static int status_s1(int type);
static int status_s2(int type);

HWCONF_PIN(S1, 4, 0);
HWCONF_IRQ(S1, 4, 0);
HWCONF_PIN(S2, 4, 1);
HWCONF_IRQ(S2, 4, 1);

/*---------------------------------------------------------------------------*/
ISR(PORT4, irq_p4)
{
  ENERGEST_ON(ENERGEST_TYPE_IRQ);

  if(S1_CHECK_IRQ() && timer_expired(&debouncetimer1)) {
    timer_set(&debouncetimer1, CLOCK_SECOND / 4);
    sensors_changed(&button_sensor);
    P3OUT ^= BIT4;
    LPM4_EXIT;
    S1_IRQ_CLEAR();
  }

  if(S2_CHECK_IRQ() && timer_expired(&debouncetimer2)) {
    timer_set(&debouncetimer2, CLOCK_SECOND / 4);
    sensors_changed(&button_sensor2);
    P3OUT ^= BIT5;
    LPM4_EXIT;
    S2_IRQ_CLEAR();
  }
  

  ENERGEST_OFF(ENERGEST_TYPE_IRQ);
}
/*---------------------------------------------------------------------------*/
static int
value_s1(int type)
{
  return S1_READ() || !timer_expired(&debouncetimer1);
}

static int
value_s2(int type)
{
  return S2_READ() || !timer_expired(&debouncetimer2);
}
/*---------------------------------------------------------------------------*/
static int
configure_s1(int type, int value)
{
  
  if(type == SENSORS_ACTIVE) {
    if(value == 0) {
      /* Deactivate button sensor */
      S1_DISABLE_IRQ();
    } else {
      /* Activate button sensor */
      if(!status_s1(SENSORS_ACTIVE)) {
        timer_set(&debouncetimer1, 0);

        P4SEL0 &= ~(1 << 0);
        P4SEL1 &= ~(1 << 0);
        // S1 on Launchpad board -- P4.0
        /* Port Resistor Enable Register */
        P4REN |= BIT0;   // set pullup on
        // input pin
        P4DIR &= ~BIT0;
        /* Set output to 1 for pullup resestor */
        P4OUT |= BIT0;
        /* Port Interrupt Edge Select Register */
        S1_IRQ_EDGE_SELECTD();
        /* Port clear Interrupt Flag Register */
        P4IFG &= ~BIT0;
        /* Port Interrupt Enable Register */
        S1_ENABLE_IRQ();
      }
    }
    return 1;
  }
  return 0;
}

static int
configure_s2(int type, int value)
{
  
  if(type == SENSORS_ACTIVE) {
    if(value == 0) {
      /* Deactivate button sensor */
      S2_DISABLE_IRQ();
    } else {
      /* Activate button sensor */
      if(!status_s2(SENSORS_ACTIVE)) {
        timer_set(&debouncetimer2, 0);

        P4SEL0 &= ~(1 << 1);
        P4SEL1 &= ~(1 << 1);
        // S1 on Launchpad board -- P4.1
        /* Port Resistor Enable Register */
        P4REN |= BIT1;   // set pullup on
        // input pin
        P4DIR &= ~BIT1;
        /* Set output to 1 for pullup resestor */
        P4OUT |= BIT1;
        /* Port Interrupt Edge Select Register */
        S2_IRQ_EDGE_SELECTD();
        /* Port clear Interrupt Flag Register */
        P4IFG &= ~BIT1;
        /* Port Interrupt Enable Register */
        S2_ENABLE_IRQ();
      }
    }
    return 1;
  }
  return 0;
}
/*---------------------------------------------------------------------------*/
static int
status_s1(int type)
{
  switch(type) {
  case SENSORS_ACTIVE:
  case SENSORS_READY:
    return S1_IRQ_ENABLED();
  default:
    return 0;
  }
}

static int
status_s2(int type)
{
  switch(type) {
  case SENSORS_ACTIVE:
  case SENSORS_READY:
    return S2_IRQ_ENABLED();
  default:
    return 0;
  }
}
/*---------------------------------------------------------------------------*/
SENSORS_SENSOR(button_sensor, BUTTON_SENSOR,
           value_s1, configure_s1, status_s1);

SENSORS_SENSOR(button_sensor2, BUTTON_SENSOR,
           value_s2, configure_s2, status_s2);

