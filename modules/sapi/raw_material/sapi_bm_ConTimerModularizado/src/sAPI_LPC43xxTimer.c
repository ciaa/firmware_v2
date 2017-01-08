/* Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/* Date: 2016-02-10 */

/*
 * For more information about the Timer peripheral, refer to the Chapter 32 of
 * the LPC43xx user manual
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
/* Specific modules used:
   #include "timer_18xx_43xx.h" for Chip_TIMER functions
   #include "rgu_18xx_43xx.h" for Chip_RGU functions
   #include "core_cm4.h" for NVIC functions
*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_LPC43xxTimer.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

sAPI_FuncPtr_t timerIRQHandlers[4] = { sAPI_NullFuncPtr,
                                       sAPI_NullFuncPtr,
                                       sAPI_NullFuncPtr,
                                       sAPI_NullFuncPtr
                                     };

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
 * @Brief:  Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param:  uint32_t microseconds: Value in microseconds
 * @return: uint32_t Equivalent in Ticks for the LPC4337
 * @note:   Can be used for the second parameter in the Timer_init
 */
uint32_t timerMicrosecondsToTicks( uint32_t microseconds ){
   return ( microseconds * (SystemCoreClock/1000000) );
}

/*==================[ISR external functions definition]======================*/

__attribute__ ((section(".after_vectors")))

/* 0x1c 0x00000070 - Handler for ISR TIMER0 (IRQ 12) */
void TIMER0_IRQHandler(void){
   (* timerIRQHandlers[0] )( 0 );
}

/* 0x1d 0x00000074 - Handler for ISR TIMER1 (IRQ 13) */
void TIMER1_IRQHandler(void){
   (* timerIRQHandlers[1] )( 0 );
}

/* 0x1e 0x00000078 - Handler for ISR TIMER2 (IRQ 14) */
void TIMER2_IRQHandler(void){
   (* timerIRQHandlers[2] )( 0 );
}

/* 0x1f 0x0000007C - Handler for ISR TIMER3 (IRQ 15) */
void TIMER3_IRQHandler(void){
   (* timerIRQHandlers[3] )( 0 );
}

/*==================[end of file]============================================*/
