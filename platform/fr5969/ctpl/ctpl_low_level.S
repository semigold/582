; --COPYRIGHT--,FRAM-Utilities
;  Copyright (c) 2015, Texas Instruments Incorporated
;  All rights reserved.
; 
;  This source code is part of FRAM Utilities for MSP430 FRAM Microcontrollers.
;  Visit http://www.ti.com/msp-fram-utilities for software information and
;  download.
; --/COPYRIGHT--
#include <msp430.h> 
#include "ctpl_benchmark.h" 
#include "ctpl_low_level.h"

#define PC R0                   
#define SP R1
#define SR R2
.arch msp430fr5969
.cpu 430xv2

; Return statement for different code models
.macro retx
#ifdef __MSP430X_LARGE__
        reta
#else
        ret
#endif
        .endm

; Macro for setting DCO to 8MHz
.macro setDco8Mhz
#if defined(__MSP430FR57XX_FAMILY__)
            mov.w   #DCOFSEL_3,&CSCTL1                  ; Set DCO 8MHz
#elif defined(__MSP430FR5XX_6XX_FAMILY__)
            mov.w   #DCOFSEL_6,&CSCTL1                  ; Set DCO 8MHz
#endif
            .endm
            
; Macro for toggling the CTPL benchmark pin.
.macro benchmark
#if defined(CTPL_BENCHMARK)
            xor.b   #CTPL_BENCHMARK_PIN,&CTPL_BENCHMARK_OUT
#endif
            .endm

; State keys
.equ CTPL_STATE_VALID, 0xa596
.equ CTPL_STATE_INVALID, 0x0000

.global ctpl_mode

; FRAM stack copy
    .lcomm ctpl_stackCopy, CTPL_STACK_SIZE

; Low level state variables
    .lcomm ctpl_mode, 2
    .lcomm ctpl_state, 2
    .lcomm ctpl_stackUsage, 2

    .global __stack

    .sect ".text:ctpl_low_level" 
; Declare functions globally
    .global ctpl_init
    .global ctpl_saveCpuStackEnterLpm

ctpl_init:
    cmpx.w  #CTPL_STATE_VALID,&ctpl_state       ; Valid ctpl state?
    jne     ctpl_initReturn                     ; No, return
    bicx.w  #0xff00,&ctpl_mode                  ; Clear the status flags of the mode
    bitx.w  #CTPL_MODE_SHUTDOWN,&ctpl_mode      ; Shutdown mode?
    jnz     ctpl_wakeup                         ; Yes, jump to wakeup (always restore)
    bit.w   #PMMRSTIFG, &PMMIFG                 ; Was there a RST/NMI?
    jnz     ctpl_initResetPowerup               ; Yes, jump to reset/powerup routine
ctpl_initNonReset:
    bit.w   #PMMLPM5IFG, &PMMIFG                ; Was reset due to LPMx.5 wakeup?
    jz      ctpl_initResetPowerup               ; No, jump to reset/powerup routine
    bisx.w  #CTPL_MODE_LPMX5_WAKEUP,&ctpl_mode  ; Yes, set the LPMx.5 wakeup status flag
    jmp     ctpl_wakeup                         ; Jump to wakeup
ctpl_initResetPowerup:
    bitx.w  #CTPL_MODE_RESTORE_RESET,&ctpl_mode ; Allow wakeup from reset/powerup?
    jnz     ctpl_wakeup                         ; Yes, jump to wakeup
ctpl_initReturn:
    movx.w  #CTPL_MODE_NONE,&ctpl_mode          ; Reset the mode to none
    movx.w  #CTPL_STATE_INVALID,&ctpl_state     ; Mark the state as invalid
    retx                                        ; Return

ctpl_saveCpuStackEnterLpm:
    pushx.a SR                                  ; Save SR to stack
    dint                                        ; disable interrupts
    nop                                         ; disable interrupts
    pushm.a #12,R15                             ; Save R4-R15 to stack
    movx.a  #__stack, R4                        ; Calculate stack usage
    subx.a  SP,R4                               ; Calculate stack usage
    movx.w  R4,&ctpl_stackUsage                 ; Save stack usage
    movx.a  #ctpl_stackCopy,R6                  ; dest ptr
    movx.a  SP,R5                               ; src ptr
                                                ; copy the stack
#ifdef __MSP430_HAS_DMAX_3__
    clr.b   &DMA0CTL_L                          ; sw trigger, channel 0
    movx.a  R5,&DMA0SA                          ; set src address
    movx.a  R6,&DMA0DA                          ; set dst address
    rra.w   R4                                  ; divide length by 2
    mov.w   R4, &DMA0SZ                         ; set copy size
    mov.w   #DMASWDW+DMADT_1+DMASRCINCR_3+DMADSTINCR_3+DMAEN+DMAREQ,&DMA0CTL    ; trigger DMA copy
#else
    ctpl_copyLoop:
            movx.w  @R5+, 0(R6)                 ; copy stack word and increment src ptr
            addx.a  #2, R6                      ; increment dst ptr
            subx.a  #2, R4                      ; decrement stack usage
            jnz     ctpl_copyLoop               ; loop if usage > 0
#endif
ctpl_setStateValid:
    movx.w  #CTPL_STATE_VALID,&ctpl_state       ; Mark the state as valid
    bitx.w  #CTPL_MODE_SHUTDOWN,&ctpl_mode      ; Check for shutdown mode and disable SVSH
    jz      ctpl_enterLpm                       ; No, jump to ctpl_enterLpm
ctpl_enterShutdownWithTimeout:
    mov.b   #CSKEY_H,&CSCTL0_H                  ; Unlock CS registers
    mov.w   #DIVM__32+DIVS__32,&CSCTL3          ; Set maximum dividers
    setDco8Mhz                                  ; Reconfigure DCO to 8MHz
    mov.w   #SELM_3+SELS_3,&CSCTL2              ; Source MCLK and SMCLK from DCO
    mov.b   R12,&CSCTL3_L                       ; Set timeout dividers
    clr.b   &CSCTL0_H                           ; Lock CS registers
    bic.w   #255,R12                            ; Clear lower bytes
    swpb    R12                                 ; Swap bytes
    add.w   #WDTPW+WDTCNTCL,R12                 ; Set WDT timeout
    mov.w   R12,&WDTCTL                         ; Set WDT timeout
    mov.b   #PMMPW_H,&PMMCTL0_H                 ; open PMM
    bis.b   #SVSHE,&PMMCTL0_L                   ; enable SVSH
    mov.b   #0,&PMMCTL0_H                       ; close PMM
ctpl_shutdownWaitForSvs:
    benchmark                                   ; Toggle the CTPL benchmark pin
    jmp     ctpl_shutdownWaitForSvs             ; Wait for SVSH to put device into BOR
ctpl_enterLpm:
    benchmark                                   ; Toggle the CTPL benchmark pin
    mov.b   #PMMPW_H,&PMMCTL0_H                 ; Set LPMx.5 bit
    mov.b   #PMMREGOFF,&PMMCTL0_L               ; Set LPMx.5 bit
    bis.w   #LPM4,SR                            ; Enter LPMx.5 mode
    nop                                         ; nop
ctpl_wakeup:
    mov.w   #WDTPW+WDTHOLD,&WDTCTL              ; stop WDT
    mov.b   #CSKEY_H,&CSCTL0_H                  ; unlock CS registers
    mov.w   #DIVM__2,&CSCTL3                    ; set DCO to 4MHz (maximum boot freq)
    clr.b   &CSCTL0_H                           ; lock CS registers
    movx.a  #__stack,SP                         ; Reset stack pointer
    movx.w  &ctpl_stackUsage,R4                 ; loop counter
    subx.a  R4,SP                               ; Reset stack pointer
    movx.a  SP,R6                               ; dest ptr
    movx.a  #ctpl_stackCopy,R5                  ; src ptr
                                                ; copy the stack
#ifdef __MSP430_HAS_DMAX_3__
    clr.b   &DMA0CTL_L                         ; sw trigger, channel 0
    movx.a  R5,&DMA0SA                         ; set src address
    movx.a  R6,&DMA0DA                         ; set dst address
    rra.w   R4                                 ; divide length by 2
    mov.w   R4, &DMA0SZ                        ; set copy size
    mov.w   #DMASWDW+DMADT_1+DMASRCINCR_3+DMADSTINCR_3+DMAEN+DMAREQ,&DMA0CTL    ; trigger DMA copy
#else
    ctpl_copyLoopy:
            movx.w  @R5+, 0(R6)   ; copy stack word and increment src ptr
            addx.a  #2, R6          ; increment dst ptr
            subx.a  #2, R4          ; decrement stack usage
            jnz     ctpl_copyLoopy  ; loop if usage > 0
#endif
    popm.a  #12,R15                             ; Restore R4-R15 from stack
    popx.a  SR                                  ; Restore interrupts
    movx.w  #CTPL_STATE_INVALID,&ctpl_state     ; Mark the state as invalid
    retx                                        ; Return
