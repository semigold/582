/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_RTC_C__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_rtc_c.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_RTC_C_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[5] = HWREG16(baseAddress + OFS_RTCCTL0);
    storage[4] = HWREG16(baseAddress + OFS_RTCCTL13);
    storage[3] = HWREG16(baseAddress + OFS_RTCPS0CTL);
    storage[2] = HWREG16(baseAddress + OFS_RTCPS1CTL);
    storage[1] = HWREG16(baseAddress + OFS_BIN2BCD);
    storage[0] = HWREG16(baseAddress + OFS_BCD2BIN);

    /* Disable interrupts if entering shutdown mode. */
    if (mode == CTPL_MODE_SHUTDOWN) {
        HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
        HWREG16(baseAddress + OFS_RTCCTL0) = 0;
    }

    return;
}

void ctpl_RTC_C_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Calculate BCD2BIN and BIN2BCD registers. */
    HWREG16(baseAddress + OFS_BIN2BCD) = storage[0];
    uint16_t calcBCD2BIN = HWREG16(baseAddress + OFS_BIN2BCD);
    HWREG16(baseAddress + OFS_BCD2BIN) = storage[1];
    uint16_t calcBIN2BCD = HWREG16(baseAddress + OFS_BCD2BIN);
    
    /* Restore register context from non-volatile storage. */
    HWREG8(baseAddress + OFS_RTCCTL0_H) = RTCKEY_H;
    HWREG16(baseAddress + OFS_BCD2BIN) = calcBCD2BIN;
    HWREG16(baseAddress + OFS_BIN2BCD) = calcBIN2BCD;
    HWREG16(baseAddress + OFS_RTCPS1CTL) = storage[2];
    HWREG16(baseAddress + OFS_RTCPS0CTL) = storage[3];
    HWREG16(baseAddress + OFS_RTCCTL13) = storage[4];
    HWREG8(baseAddress + OFS_RTCCTL0_L) = storage[5] & 0x00ff;
    HWREG8(baseAddress + OFS_RTCCTL0_H) = 0;

    return;
}
