/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_PORT1_R__
#define __MSP430_HAS_PORT2_R__
#define __MSP430_HAS_PORTA_R__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_port_int.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_PORT_INT_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[6] = HWREG16(baseAddress + OFS_PAIE);
    storage[5] = HWREG16(baseAddress + OFS_PAIES);
    storage[4] = HWREG16(baseAddress + OFS_PASEL1);
    storage[3] = HWREG16(baseAddress + OFS_PASEL0);
    storage[2] = HWREG16(baseAddress + OFS_PAREN);
    storage[1] = HWREG16(baseAddress + OFS_PADIR);
    storage[0] = HWREG16(baseAddress + OFS_PAOUT);

    /* Disable interrupts if entering shutdown mode. */
    if (mode == CTPL_MODE_SHUTDOWN) {
        HWREG16(baseAddress + OFS_PAIE) = 0;
    }

    return;
}

void ctpl_PORT_INT_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_PAOUT) = storage[0];
    HWREG16(baseAddress + OFS_PADIR) = storage[1];
    HWREG16(baseAddress + OFS_PAREN) = storage[2];
    HWREG16(baseAddress + OFS_PASEL0) = storage[3];
    HWREG16(baseAddress + OFS_PASEL1) = storage[4];
    HWREG16(baseAddress + OFS_PAIES) = storage[5];
    HWREG16(baseAddress + OFS_PAIE) = storage[6];

    return;
}

void ctpl_PORT_INT_epilogue(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Clear the interrupt flags if not waking up from LPMx5. */
    if (!(mode & CTPL_MODE_LPMX5_WAKEUP)) {
        HWREG16(baseAddress + OFS_PAIFG) = 0;
    }

    return;
}
