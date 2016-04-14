/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_SYS_H_
#define CTPL_SYS_H_

//******************************************************************************
//
//! \addtogroup ctpl_sys_api
//! Compute Through Power Loss SYS Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>
#include <stdlib.h>

//******************************************************************************
//
//! Length of FRAM storage for the SYS peripheral registers in 16-bit words.
//
//******************************************************************************
#define CTPL_SYS_STORAGE_LENGTH         4

//******************************************************************************
//
//! Save function for the SYS peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_SYS_save(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Restore function for the SYS peripheral.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     FRAM storage to save registers to.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
void ctpl_SYS_restore(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Epilogue function for the SYS peripheral.
//
//******************************************************************************
#define ctpl_SYS_epilogue               NULL

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_SYS_H_ */
