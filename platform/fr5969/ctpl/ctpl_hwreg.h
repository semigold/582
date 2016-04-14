/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_HWREG_H_
#define CTPL_HWREG_H_

//******************************************************************************
//
//! \addtogroup ctpl_hwreg_api
//! Compute Through Power Loss CS Peripheral Definition
//! @{
//
//******************************************************************************

#include <stdint.h>

//******************************************************************************
//
//! Macro for 8-bit hardware register access.
//
//******************************************************************************
#define HWREG8(x)     (*((volatile uint8_t*)((uintptr_t)x)))

//******************************************************************************
//
//! Macro for 16-bit hardware register access.
//
//******************************************************************************
#define HWREG16(x)     (*((volatile uint16_t*)((uintptr_t)x)))

//******************************************************************************
//
//! Macro for 32-bit hardware register access.
//
//******************************************************************************
#define HWREG32(x)     (*((volatile uint32_t*)((uintptr_t)x)))

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_HWREG_H_ */
