/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_EUSCI_A_X_H_
#define CTPL_EUSCI_A_X_H_

//******************************************************************************
//
//! \addtogroup ctpl_EUSCI_A_X_api
//! Compute Through Power Loss EUSCI_A_X Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>
#include <stdlib.h>

//******************************************************************************
//
//! Length of FRAM storage for the EUSCI_A_X peripheral registers in 16-bit words.
//
//******************************************************************************
#define CTPL_EUSCI_A_X_STORAGE_LENGTH       4

//******************************************************************************
//
//! Save function for the EUSCI_A_X peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_EUSCI_A_X_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Restore function for the EUSCI_A_X peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_EUSCI_A_X_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Epilogue function for the EUSCI_A_X peripheral.
//
//******************************************************************************
void ctpl_EUSCI_A_X_epilogue(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_EUSCI_A_X_H_ */
