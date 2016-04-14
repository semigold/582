/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#ifndef CTPL_BENCHMARK_H_
#define CTPL_BENCHMARK_H_

//******************************************************************************
//
//! \addtogroup ctpl_benchmark_api
//! @{
//
//******************************************************************************

#if defined(CTPL_BENCHMARK)

#include <msp430.h>

//******************************************************************************
//
//! Benchmark pin used when CTPL_BENCHMARK is defined in the compiler settings
//! (-DCTPL_BENCHMARK).
//
//******************************************************************************
#define CTPL_BENCHMARK_PIN      BIT6

//******************************************************************************
//
//! Benchmark port direction register used when CTPL_BENCHMARK is defined in the
//! compiler settings (-DCTPL_BENCHMARK).
//
//******************************************************************************
#define CTPL_BENCHMARK_DIR      P4DIR

//******************************************************************************
//
//! Benchmark port output register used when CTPL_BENCHMARK is defined in the
//! compiler settings (-DCTPL_BENCHMARK).
//
//******************************************************************************
#define CTPL_BENCHMARK_OUT      P4OUT

#endif

//******************************************************************************
//
// Close the Doxygen group.
//! @}
//
//******************************************************************************

#endif /* CTPL_BENCHMARK_H_ */
