/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_PERIPHERALS_H_
#define CTPL_PERIPHERALS_H_

#include <stdint.h>

#include "ctpl_cs.h"
#include "ctpl_fram.h"
#include "ctpl_mpu.h"
#include "ctpl_mpu_fr57xx.h"
#include "ctpl_mpy32.h"
#include "ctpl_pmm.h"
#include "ctpl_port.h"
#include "ctpl_port_int.h"
#include "ctpl_rc.h"
#include "ctpl_rtc_b.h"
#include "ctpl_rtc_c.h"
#include "ctpl_sys.h"
#include "ctpl_wdt_a.h"

//******************************************************************************
//
//! \addtogroup ctpl_peripherals_api
//! @{
//
//******************************************************************************

//******************************************************************************
//
//! \brief  Function prototype for peripheral save, restore and epilogue functions.
//!
//! \param  baseAddress Peripheral base address.
//! \param  storage     Peripheral non-volatile register storage.
//! \param  mode        CTPL mode used.
//!
//! \return none
//
//******************************************************************************
typedef void (*ctpl_tFunction)(uint16_t baseAddress, uint16_t *storage, uint16_t mode);

//******************************************************************************
//
//! Structure defining how to save and restore a peripherals context. These
//! structures are provided for each device in the included device-specific
//! ctpl_*.c file required when using the utility.
//
//******************************************************************************
typedef struct ctpl_peripheral {
    uint16_t baseAddress;       //!< Peripheral base address.
    uint16_t *storage;          //!< Peripheral non-volatile storage.
    ctpl_tFunction save;        //!< Function to save peripheral context.
    ctpl_tFunction restore;     //!< Function to restore peripheral context.
    ctpl_tFunction epilogue;    //!< Optional function to run after clearing the
                                //!  LOCKLPM5 bit. If this function pointer is
                                //!  null the function will not be called.
} ctpl_peripheral;

//******************************************************************************
//
//! Abstracted symbol for the length of the ctpl_peripherals array. This symbol
//! is defined in the device-specific ctpl_*.c file required when using the
//! library.
//
//******************************************************************************
extern const uint16_t ctpl_peripheralsLen;

//******************************************************************************
//
//! The device specific array of peripherals to save and restore. This symbol is
//! defined in the device-specific ctpl_*.c file included with the library.
//
//******************************************************************************
extern const ctpl_peripheral *ctpl_peripherals[];

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_PERIPHERALS_H_ */
