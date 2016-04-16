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

#include <msp430.h>

#include "ctpl_peripherals.h"

#ifndef __MSP430FR6989__
#error This file is only to be used with msp430fr6989, please replace this and the linker files with the correct device files.
#endif

/*
 * Comment out a line below if you would not like to save the peripheral. The
 * remainder of the file should not be modified.
 */
#define CTPL_SAVE_MPU
#define CTPL_SAVE_PORTA
#define CTPL_SAVE_PORTB
#define CTPL_SAVE_PORTC
#define CTPL_SAVE_PORTD
#define CTPL_SAVE_PORTE
#define CTPL_SAVE_PORTJ
#define CTPL_SAVE_FRAM
#define CTPL_SAVE_PMM
#define CTPL_SAVE_SYS
#define CTPL_SAVE_RTC_C
#define CTPL_SAVE_MPY32
#define CTPL_SAVE_CS
#define CTPL_SAVE_WDT_A

/*****************************************************/
/*                                                   */
/* !!! DO NOT MODIFY ANYTHING BELOW THIS COMMENT !!! */
/*                                                   */
/*****************************************************/

#ifdef CTPL_SAVE_MPU
uint16_t ctpl_MPU_storage[CTPL_MPU_STORAGE_LENGTH];

const ctpl_peripheral ctpl_MPU = {
    __MSP430_BASEADDRESS_MPU__,
    ctpl_MPU_storage,
    ctpl_MPU_save,
    ctpl_MPU_restore,
    ctpl_MPU_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTA
uint16_t ctpl_PORTA_storage[CTPL_PORT_INT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTA = {
    __MSP430_BASEADDRESS_PORTA_R__,
    ctpl_PORTA_storage,
    ctpl_PORT_INT_save,
    ctpl_PORT_INT_restore,
    ctpl_PORT_INT_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTB
uint16_t ctpl_PORTB_storage[CTPL_PORT_INT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTB = {
    __MSP430_BASEADDRESS_PORTB_R__,
    ctpl_PORTB_storage,
    ctpl_PORT_INT_save,
    ctpl_PORT_INT_restore,
    ctpl_PORT_INT_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTC
uint16_t ctpl_PORTC_storage[CTPL_PORT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTC = {
    __MSP430_BASEADDRESS_PORTC_R__,
    ctpl_PORTC_storage,
    ctpl_PORT_save,
    ctpl_PORT_restore,
    ctpl_PORT_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTD
uint16_t ctpl_PORTD_storage[CTPL_PORT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTD = {
    __MSP430_BASEADDRESS_PORTD_R__,
    ctpl_PORTD_storage,
    ctpl_PORT_save,
    ctpl_PORT_restore,
    ctpl_PORT_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTE
uint16_t ctpl_PORTE_storage[CTPL_PORT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTE = {
    __MSP430_BASEADDRESS_PORTE_R__,
    ctpl_PORTE_storage,
    ctpl_PORT_save,
    ctpl_PORT_restore,
    ctpl_PORT_epilogue
};
#endif

#ifdef CTPL_SAVE_PORTJ
uint16_t ctpl_PORTJ_storage[CTPL_PORT_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PORTJ = {
    __MSP430_BASEADDRESS_PORTJ_R__,
    ctpl_PORTJ_storage,
    ctpl_PORT_save,
    ctpl_PORT_restore,
    ctpl_PORT_epilogue
};
#endif

#ifdef CTPL_SAVE_FRAM
uint16_t ctpl_FRAM_storage[CTPL_FRAM_STORAGE_LENGTH];

const ctpl_peripheral ctpl_FRAM = {
    __MSP430_BASEADDRESS_FRAM__,
    ctpl_FRAM_storage,
    ctpl_FRAM_save,
    ctpl_FRAM_restore,
    ctpl_FRAM_epilogue
};
#endif

#ifdef CTPL_SAVE_PMM
uint16_t ctpl_PMM_storage[CTPL_PMM_STORAGE_LENGTH];

const ctpl_peripheral ctpl_PMM = {
    __MSP430_BASEADDRESS_PMM_FRAM__,
    ctpl_PMM_storage,
    ctpl_PMM_save,
    ctpl_PMM_restore,
    ctpl_PMM_epilogue
};
#endif

#ifdef CTPL_SAVE_SYS
uint16_t ctpl_SYS_storage[CTPL_SYS_STORAGE_LENGTH];

const ctpl_peripheral ctpl_SYS = {
    __MSP430_BASEADDRESS_SYS__,
    ctpl_SYS_storage,
    ctpl_SYS_save,
    ctpl_SYS_restore,
    ctpl_SYS_epilogue
};
#endif

#ifdef CTPL_SAVE_RTC_C
uint16_t ctpl_RTC_C_storage[CTPL_RTC_C_STORAGE_LENGTH];

const ctpl_peripheral ctpl_RTC_C = {
    __MSP430_BASEADDRESS_RTC_C__,
    ctpl_RTC_C_storage,
    ctpl_RTC_C_save,
    ctpl_RTC_C_restore,
    ctpl_RTC_C_epilogue
};
#endif

#ifdef CTPL_SAVE_MPY32
uint16_t ctpl_MPY32_storage[CTPL_MPY32_STORAGE_LENGTH];

const ctpl_peripheral ctpl_MPY32 = {
    __MSP430_BASEADDRESS_MPY32__,
    ctpl_MPY32_storage,
    ctpl_MPY32_save,
    ctpl_MPY32_restore,
    ctpl_MPY32_epilogue
};
#endif

#ifdef CTPL_SAVE_CS
uint16_t ctpl_CS_storage[CTPL_CS_STORAGE_LENGTH];

const ctpl_peripheral ctpl_CS = {
    __MSP430_BASEADDRESS_CS__,
    ctpl_CS_storage,
    ctpl_CS_save,
    ctpl_CS_restore,
    ctpl_CS_epilogue
};
#endif

#ifdef CTPL_SAVE_WDT_A
uint16_t ctpl_WDT_A_storage[CTPL_WDT_A_STORAGE_LENGTH];

const ctpl_peripheral ctpl_WDT_A = {
    __MSP430_BASEADDRESS_WDT_A__,
    ctpl_WDT_A_storage,
    ctpl_WDT_A_save,
    ctpl_WDT_A_restore,
    ctpl_WDT_A_epilogue
};
#endif

const ctpl_peripheral *ctpl_peripherals[] = {
#ifdef CTPL_SAVE_MPU
    &ctpl_MPU,
#endif
#ifdef CTPL_SAVE_PORTA
    &ctpl_PORTA,
#endif
#ifdef CTPL_SAVE_PORTB
    &ctpl_PORTB,
#endif
#ifdef CTPL_SAVE_PORTC
    &ctpl_PORTC,
#endif
#ifdef CTPL_SAVE_PORTD
    &ctpl_PORTD,
#endif
#ifdef CTPL_SAVE_PORTE
    &ctpl_PORTE,
#endif
#ifdef CTPL_SAVE_PORTJ
    &ctpl_PORTJ,
#endif
#ifdef CTPL_SAVE_FRAM
    &ctpl_FRAM,
#endif
#ifdef CTPL_SAVE_PMM
    &ctpl_PMM,
#endif
#ifdef CTPL_SAVE_SYS
    &ctpl_SYS,
#endif
#ifdef CTPL_SAVE_RTC_C
    &ctpl_RTC_C,
#endif
#ifdef CTPL_SAVE_MPY32
    &ctpl_MPY32,
#endif
#ifdef CTPL_SAVE_CS
    &ctpl_CS,
#endif
#ifdef CTPL_SAVE_WDT_A
    &ctpl_WDT_A,
#endif
};

const uint16_t ctpl_peripheralsLen = (sizeof(ctpl_peripherals)/sizeof(ctpl_peripherals[0]));
