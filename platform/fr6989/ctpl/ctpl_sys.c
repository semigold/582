/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_SYS__
#define __MSP430_HAS_SFR__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_sys.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_SYS_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[3] = HWREG16(baseAddress + OFS_SYSJMBC);
    storage[2] = HWREG16(baseAddress + OFS_SYSCTL);
    storage[1] = HWREG16(baseAddress + OFS_SFRRPCR);
    storage[0] = HWREG16(baseAddress + OFS_SFRIE1);

    return;
}

void ctpl_SYS_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_SFRIE1) = storage[0];
    HWREG16(baseAddress + OFS_SFRRPCR) = storage[1];
    HWREG16(baseAddress + OFS_SYSCTL) = storage[2];
    HWREG16(baseAddress + OFS_SYSJMBC) = storage[3];

    /* Clear pending reset IFG's all modes. */
    HWREG16(baseAddress + OFS_SYSRSTIV) = 0;

    return;
}
