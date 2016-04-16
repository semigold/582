/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_PMM_FRAM__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_pmm.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_PMM_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[0] = HWREG16(baseAddress + OFS_PMMCTL0);

    return;
}

void ctpl_PMM_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_PMMCTL0) = (storage[0] & 0x00ff) | PMMPW;
    HWREG8(baseAddress + OFS_PMMCTL0_H) = 0;

    return;
}
