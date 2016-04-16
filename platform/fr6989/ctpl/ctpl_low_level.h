/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_LOW_LEVEL_H_
#define CTPL_LOW_LEVEL_H_

//******************************************************************************
//
//! \addtogroup ctpl_low_level_api
//! @{
//
//******************************************************************************

#ifndef CTPL_STACK_SIZE
#error CTPL: You must define the stack size being used (--define=CTPL_STACK_SIZE=160)
#endif

//******************************************************************************
//
//! Bits that define no CTPL mode.
//
//******************************************************************************
#define CTPL_MODE_NONE              0x0000

//******************************************************************************
//
//! Bits that define the LPM3.5 CTPL mode.
//
//******************************************************************************
#define CTPL_MODE_LPM35             0x0001

//******************************************************************************
//
//! Bits that define the LPM4.5 mode.
//
//******************************************************************************
#define CTPL_MODE_LPM45             0x0002

//******************************************************************************
//
//! Bits that define the shutdown CTPL mode.
//
//******************************************************************************
#define CTPL_MODE_SHUTDOWN          0x0004

//******************************************************************************
//
//! Bits that define the optional restoreOnReset flag.
//
//******************************************************************************
#define CTPL_MODE_RESTORE_RESET     0x0010

//******************************************************************************
//
//! Bits that define the LPM3.5 and LPM4.5 wakeup flags.
//
//******************************************************************************
#define CTPL_MODE_LPMX5_WAKEUP      0x0100

#ifndef __IAR_SYSTEMS_ASM__

//******************************************************************************
//
//! CTPL mode variable set by the utility and used to determine the mode before
//! low-power mode or shutdown as well as the flags set for the wakeup source.
//
//******************************************************************************

//******************************************************************************
//
//! \brief Low level assembly function used to save the state and enter LPM.
//!
//! This assembly function saves the CPU state and stack into non-volatile FRAM
//! before setting the state as valid and entering into the low-power mode
//! defined by ctpl_mode. On device reset with a valid state ctpl_init will jump
//! back to this function which restores the CPU state and stack from the FRAM
//! copy. After restoring the state the function returns to the higher-level
//! CTPL function that was invoked by the main application.
//!
//! This function is only intended to be called from within the library code,
//! the user does not need to invoke this function manually.
//!
//! \param  timeout Configurable timeout for a reset if device does not enter
//!                 BOR.
//!                 Valid values are:
//!                     - \b CTPL_POWERLOSS_TIMEOUT_1_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_2_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_4_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_8_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_16_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_32_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_64_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_128_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_256_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_512_MS
//!                     - \b CTPL_POWERLOSS_TIMEOUT_1024_MS
//!
//! \return none.
//
//******************************************************************************

#endif /* __IAR_SYSTEMS_ASM__ */

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_LOW_LEVEL_H_ */
