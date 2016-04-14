/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_RC_H_
#define CTPL_RC_H_

//******************************************************************************
//
//! \addtogroup ctpl_rc_api
//! Compute Through Power Loss RC Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>
#include <stdlib.h>

//******************************************************************************
//
//! Length of FRAM storage for the RC peripheral registers in 16-bit words.
//
//******************************************************************************
#define CTPL_RC_STORAGE_LENGTH          1

//******************************************************************************
//
//! Save function for the RC peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_RC_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Restore function for the RC peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_RC_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Save function for the RC peripheral.
//
//******************************************************************************
#define ctpl_RC_epilogue                NULL

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_RC_H_ */
