/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>

#define __MSP430_HAS_MPU__
#include <msp430fr5xx_6xxgeneric.h>

#include "ctpl_mpu.h"
#include "ctpl_hwreg.h"
#include "ctpl_low_level.h"

void ctpl_MPU_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Save register context to non-volatile storage. */
    storage[6] = HWREG16(baseAddress + OFS_MPUCTL0);
    storage[5] = HWREG16(baseAddress + OFS_MPUIPC0);
    storage[4] = HWREG16(baseAddress + OFS_MPUIPSEGB1);
    storage[3] = HWREG16(baseAddress + OFS_MPUIPSEGB2);
    storage[2] = HWREG16(baseAddress + OFS_MPUSAM);
    storage[1] = HWREG16(baseAddress + OFS_MPUSEGB1);
    storage[0] = HWREG16(baseAddress + OFS_MPUSEGB2);

    return;
}

void ctpl_MPU_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode)
{
    /* Restore register context from non-volatile storage. */
    HWREG8(baseAddress + OFS_MPUCTL0_H) = MPUPW_H;
    HWREG16(baseAddress + OFS_MPUSEGB2) = storage[0];
    HWREG16(baseAddress + OFS_MPUSEGB1) = storage[1];
    HWREG16(baseAddress + OFS_MPUSAM) = storage[2];
    HWREG16(baseAddress + OFS_MPUIPSEGB2) = storage[3];
    HWREG16(baseAddress + OFS_MPUIPSEGB1) = storage[4];
    HWREG16(baseAddress + OFS_MPUIPC0) = storage[5];
    HWREG8(baseAddress + OFS_MPUCTL0_L) = storage[6] & 0x00ff;
    HWREG8(baseAddress + OFS_MPUCTL0_H) = 0;

    return;
}
