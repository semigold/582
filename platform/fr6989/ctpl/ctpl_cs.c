/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_CS__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_cs.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_CS_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[5] = HWREG16(baseAddress + OFS_CSCTL6);
    storage[4] = HWREG16(baseAddress + OFS_CSCTL5);
    storage[3] = HWREG16(baseAddress + OFS_CSCTL4);
    storage[2] = HWREG16(baseAddress + OFS_CSCTL3);
    storage[1] = HWREG16(baseAddress + OFS_CSCTL2);
    storage[0] = HWREG16(baseAddress + OFS_CSCTL1);

    return;
}

void ctpl_CS_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG8(baseAddress + OFS_CSCTL0_H) = CSKEY_H;
    HWREG16(baseAddress + OFS_CSCTL1) = storage[0];
    HWREG16(baseAddress + OFS_CSCTL2) = storage[1];
    HWREG16(baseAddress + OFS_CSCTL3) = storage[2];
    HWREG16(baseAddress + OFS_CSCTL4) = storage[3];
    HWREG16(baseAddress + OFS_CSCTL5) = storage[4];
    HWREG16(baseAddress + OFS_CSCTL6) = storage[5];
    HWREG8(baseAddress + OFS_CSCTL0_H) = 0;

    return;
}
