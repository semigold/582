/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_MPY32__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_mpy32.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_MPY32_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[8] = HWREG16(baseAddress + OFS_MPY32CTL0);
    storage[7] = HWREG16(baseAddress + OFS_RES3);
    storage[6] = HWREG16(baseAddress + OFS_RES2);
    storage[5] = HWREG16(baseAddress + OFS_RES1);
    storage[4] = HWREG16(baseAddress + OFS_RES0);
    storage[3] = HWREG16(baseAddress + OFS_MPY32H);
    storage[2] = HWREG16(baseAddress + OFS_MPY32L);
    storage[1] = HWREG16(baseAddress + OFS_OP2H);
    storage[0] = HWREG16(baseAddress + OFS_OP2L);

    return;
}

void ctpl_MPY32_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_OP2L) = storage[0];
    HWREG16(baseAddress + OFS_OP2H) = storage[1];
    HWREG16(baseAddress + OFS_MPY32L) = storage[2];
    HWREG16(baseAddress + OFS_MPY32H) = storage[3];
    HWREG16(baseAddress + OFS_RES0) = storage[4];
    HWREG16(baseAddress + OFS_RES1) = storage[5];
    HWREG16(baseAddress + OFS_RES2) = storage[6];
    HWREG16(baseAddress + OFS_RES3) = storage[7];
    HWREG16(baseAddress + OFS_MPY32CTL0) = storage[8];

    return;
}
