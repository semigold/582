/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_RTC_B__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_rtc_b.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_RTC_B_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[2] = HWREG16(baseAddress + OFS_RTCCTL01);
    storage[1] = HWREG16(baseAddress + OFS_RTCPS1CTL);
    storage[0] = HWREG16(baseAddress + OFS_RTCPS0CTL);

    /* Disable interrupts if entering shutdown mode. */
    if (mode == CTPL_MODE_SHUTDOWN) {
        HWREG8(baseAddress + OFS_RTCCTL01_L) = 0;
    }

    return;
}

void ctpl_RTC_B_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_RTCPS0CTL) = storage[0];
    HWREG16(baseAddress + OFS_RTCPS1CTL) = storage[1];
    HWREG16(baseAddress + OFS_RTCCTL01) = storage[2];

    return;
}
