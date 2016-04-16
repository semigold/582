/* --COPYRIGHT--,FRAM-Utilities
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
 * Visit http://www.ti.com/msp-fram-utilities for software information and
 * download.
 * --/COPYRIGHT--*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "msp430.h"
#include "ctpl.h"
#include "ctpl_benchmark.h"
#include "ctpl_low_level.h"
#include "ctpl_peripherals.h"
extern volatile uint16_t ctpl_mode;
extern void ctpl_saveCpuStackEnterLpm(uint16_t timeout);
static void ctpl_saveEnterLpmRestore(uint16_t mode, bool restoreOnReset, uint16_t timeout);
/*
 * Save peripheral, stack and cpu context and enter into LPM3.5.
 */
void ctpl_enterLpm35(bool restoreOnReset)
{
    ctpl_saveEnterLpmRestore(CTPL_MODE_LPM35, restoreOnReset, 0);
    return;
}
/*
 * Save peripheral, stack and cpu context and enter into LPM4.5.
 */
void ctpl_enterLpm45(bool restoreOnReset)
{
    ctpl_saveEnterLpmRestore(CTPL_MODE_LPM45, restoreOnReset, 0);
    return;
}
/*
 * Save peripheral, stack and cpu context and wait for SVS to put the device
 * into BOR. There is no argument for restoreOnReset, the state is always
 * restored in the event of a power loss.
 */
void ctpl_enterShutdown(uint16_t timeout)
{
    ctpl_saveEnterLpmRestore(CTPL_MODE_SHUTDOWN, CTPL_ENABLE_RESTORE_ON_RESET, timeout);
    return;
}
/*
 * Save peripheral, stack and cpu context and enter into the specified low
 * power mode. Peripheral context saved is defined by the ctpl_peripherals
 * array in the device abstraction.
 */
static void ctpl_saveEnterLpmRestore(uint16_t mode, bool restoreOnReset, uint16_t timeout)
{
    uint16_t i;
    uint16_t interruptState;
    uint16_t baseAddress;
    uint16_t *storage;
    /* Global disable interrupts until entering LPM4.5 */
    interruptState = __get_interrupt_state();
    __disable_interrupt();
#ifdef CTPL_BENCHMARK
    /* Toggle benchmark pin and set to high while saving state. */
    CTPL_BENCHMARK_DIR |= CTPL_BENCHMARK_PIN;
    CTPL_BENCHMARK_OUT &= ~CTPL_BENCHMARK_PIN;
    CTPL_BENCHMARK_OUT |= CTPL_BENCHMARK_PIN;
#endif
    /* Set mode variable. */
    ctpl_mode = mode;
    if (restoreOnReset) {
        ctpl_mode |= CTPL_MODE_RESTORE_RESET;
    }
    /*
     * Save peripherals in reverse order. The order of the peripheral array
     * determines the order the peripherals are restored where the first
     * peripheral is restored first.
     */
    for (i = ctpl_peripheralsLen; i-- > 0;) {
        baseAddress = ctpl_peripherals[i]->baseAddress;
        storage = ctpl_peripherals[i]->storage;
        ctpl_peripherals[i]->save(baseAddress, storage, mode);
    }
    /*
     * Save CPU state and enter LPM mode. This function will return when the CPU
     * wakes up and the ctpl_init function is called.
     */
    ctpl_saveCpuStackEnterLpm(timeout);
    /*
     * Restore peripherals. The order of the peripheral array determines the
     * order the peripherals are restored where the first peripheral is
     * restored first.
     */
    for (i = 0; i < ctpl_peripheralsLen; i++) {
        baseAddress = ctpl_peripherals[i]->baseAddress;
        storage = ctpl_peripherals[i]->storage;
        ctpl_peripherals[i]->restore(baseAddress, storage, mode);
    }
    /*
     * Disable the GPIO power-on default high-impedance mode to activate
     * previously configured port settings.
     */
    PM5CTL0 &= ~LOCKLPM5;
    /*
     * Call the epilogue functions for any registers that need to be modified
     * after clearing the LOCKLPM5 bit.
     */
    for (i = 0; i < ctpl_peripheralsLen; i++) {
        if (ctpl_peripherals[i]->epilogue) {
            baseAddress = ctpl_peripherals[i]->baseAddress;
            storage = ctpl_peripherals[i]->storage;
            ctpl_peripherals[i]->epilogue(baseAddress, storage, mode);
        }
    }
    /* Reset the CTPL mode to none. */
    ctpl_mode = CTPL_MODE_NONE;
    /* Restore interrupt state. */
    __set_interrupt_state(interruptState);
    return;
}
