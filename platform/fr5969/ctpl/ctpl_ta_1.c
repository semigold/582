#include <stdint.h>

#define __MSP430_HAS_TxA7__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_ta_1.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_TA_1_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[4] = HWREG16(baseAddress + OFS_TAxCCTL1);
    storage[3] = HWREG16(baseAddress + OFS_TAxCCR1);
    storage[2] = HWREG16(baseAddress + OFS_TAxCCR0);
    storage[1] = HWREG16(baseAddress + OFS_TAxCTL);
    storage[0] = HWREG16(baseAddress + OFS_TAxR);

    /* Disable interrupts if entering shutdown mode. */
    if (mode == CTPL_MODE_SHUTDOWN) {
        HWREG16(baseAddress + OFS_TAxCTL) &= ~MC_3;
    }

    return;
}

void ctpl_TA_1_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_TAxR)     = storage[0];
    HWREG16(baseAddress + OFS_TAxCTL)   = storage[1];
    HWREG16(baseAddress + OFS_TAxCCR0)  = storage[2];
    HWREG16(baseAddress + OFS_TAxCCR1)  = storage[3]; 
    HWREG16(baseAddress + OFS_TAxCCTL1) = storage[4];
    return;
}


