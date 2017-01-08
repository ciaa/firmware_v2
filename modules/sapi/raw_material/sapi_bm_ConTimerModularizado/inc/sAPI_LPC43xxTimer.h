/* Copyright 2016, Ian Olivieri.
 * Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/* Date: 2016-05-02 */

#ifndef _SAPI_LPC43XX_TIMER_H_
#define _SAPI_LPC43XX_TIMER_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

typedef void (*voidFunctionPointer_t)(void);

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * @Brief:  Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param:  uint32_t microseconds: Value in microseconds
 * @return: uint32_t Equivalent in Ticks for the LPC4337
 * @note:   Can be used for the second parameter in the Timer_init
 */
uint32_t timerMicrosecondsToTicks( uint32_t microseconds );

/*==================[ISR external functions declaration]=====================*/

/* 0x1c 0x00000070 - Handler for ISR TIMER0 (IRQ 12) */
void TIMER0_IRQHandler(void);

/* 0x1d 0x00000074 - Handler for ISR TIMER1 (IRQ 13) */
void TIMER1_IRQHandler(void);

/* 0x1e 0x00000078 - Handler for ISR TIMER2 (IRQ 14) */
void TIMER2_IRQHandler(void);

/* 0x1f 0x0000007C - Handler for ISR TIMER3 (IRQ 15) */
void TIMER3_IRQHandler(void);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/

#endif /* _SAPI_LPC43XX_TIMER_H_ */