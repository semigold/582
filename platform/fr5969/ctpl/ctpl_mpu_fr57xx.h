/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_MPU_FR57XX_H_
#define CTPL_MPU_FR57XX_H_

//******************************************************************************
//
//! \addtogroup ctpl_mpu_fr57xx_api
//! Compute Through Power Loss FR57xx MPU Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>
#include <stdlib.h>

//******************************************************************************
//
//! Length of FRAM storage for the FR57xx MPU peripheral registers in 16-bit words.
//
//******************************************************************************
#define CTPL_MPU_FR57XX_STORAGE_LENGTH         3

//******************************************************************************
//
//! Save function for the FR57xx MPU peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_MPU_FR57XX_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Restore function for the FR57xx MPU peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_MPU_FR57XX_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Epilogue function for the FR57xx MPU peripheral.
//
//******************************************************************************
#define ctpl_MPU_FR57XX_epilogue               NULL

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_MPU_FR57XX_H_ */
