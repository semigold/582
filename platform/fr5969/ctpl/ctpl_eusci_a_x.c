#include <stdint.h>

#define __MSP430_HAS_EUSCI_Ax__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_eusci_a_x.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_EUSCI_A_X_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[3] = HWREG16(baseAddress + OFS_UCAxIE);
    storage[2] = HWREG16(baseAddress + OFS_UCAxBRW);
    storage[1] = HWREG16(baseAddress + OFS_UCAxMCTLW);
    storage[0] = HWREG16(baseAddress + OFS_UCAxCTLW0);

    /* Disable interrupts if entering shutdown mode. */
    if (mode == CTPL_MODE_SHUTDOWN) {
        HWREG16(baseAddress + OFS_UCAxIE) = 0;
    }
    return;
}

void ctpl_EUSCI_A_X_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG16(baseAddress + OFS_UCAxCTLW0)  = storage[0];
    HWREG16(baseAddress + OFS_UCAxMCTLW)  = storage[1]; 
    HWREG16(baseAddress + OFS_UCAxBRW)    = storage[2];
    HWREG16(baseAddress + OFS_UCAxIE)     = storage[3];
    return;
}

void ctpl_EUSCI_A_X_epilogue(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Clear the interrupt flags if not waking up from LPMx5. */
    if (!(mode & CTPL_MODE_LPMX5_WAKEUP)) {
        HWREG16(baseAddress + OFS_UCAxIE) = ~UCRXIFG;
        HWREG16(baseAddress + OFS_UCAxIE) = ~UCTXIFG;
    }

    return;
}
