/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_FRAM__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_fram.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_FRAM_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[1] = HWREG16(baseAddress + OFS_GCCTL0);
    storage[0] = HWREG16(baseAddress + OFS_FRCTL0);

    return;
}

void ctpl_FRAM_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_FRCTL0) = (storage[0] & 0x00ff) | FRCTLPW;
    HWREG16(baseAddress + OFS_GCCTL0) = storage[1];
    HWREG8(baseAddress + OFS_FRCTL0_L) = 0;

    return;
}
