/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_WDT_A__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_wdt_a.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_WDT_A_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[0] = HWREG16(baseAddress + OFS_WDTCTL);

    /* Halt WDT. */
    HWREG16(baseAddress + OFS_WDTCTL) = WDTPW | WDTHOLD;

    return;
}

void ctpl_WDT_A_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Do nothing here. */
    return;
}

void ctpl_WDT_A_epilogue(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_WDTCTL) = (storage[0] & 0x00ff) | WDTPW;

    return;
}
