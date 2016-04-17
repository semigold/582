/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_TA_1_H_
#define CTPL_TA_1_H_

//******************************************************************************
//
//! \addtogroup ctpl_TA_1_api
//! Compute Through Power Loss TA_1 Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>
#include <stdlib.h>

//******************************************************************************
//
//! Length of FRAM storage for the TA_1 peripheral registers in 16-bit words.
//
//******************************************************************************
#define CTPL_TA_1_STORAGE_LENGTH       5

//******************************************************************************
//
//! Save function for the TA_1 peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_TA_1_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Restore function for the TA_1 peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_TA_1_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Save function for the TA_1 peripheral.
//
//******************************************************************************
#define ctpl_TA_1_epilogue             NULL

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_TA_1_H_ */
