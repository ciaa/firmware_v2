/* Copyright 2015, Mariano Cerdeiro.
 * Copyright 2015, Eric Pernia.
 * Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia.
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

/* Date: 2015-09-23 */

#ifndef _SAPI_ISRS_H_
#define _SAPI_ISRS_H_
/** \brief Bare Metal example header file
 **
 ** This is a mini example of the CIAA Firmware
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup CIAA Firmware
 ** @{ */
/** \addtogroup CIAA Firmware header file
 ** @{ */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[ISR external functions definition]======================*/

/*==================[external functions definition]==========================*/

/** \brief Reset ISR
 **
 ** ResetISR is defined in cr_startup_lpc43xx.c
 **
 ** \remark the definition is in
 **         externals/drivers/cortexM4/lpc43xx/src/cr_startup_lpc43xx.c
 **/
extern void ResetISR(void);

/** \brief Stack Top address
 **
 ** External declaration for the pointer to the stack top from the Linker Script
 **
 ** \remark only a declaration is needed, there is no definition, the address
 **         is set in the linker script:
 **         externals/base/cortexM4/lpc43xx/linker/ciaa_lpc4337.ld.
 **/
extern void _vStackTop(void);

/** \brief System Tick Handler
 **
 ** System Tick Handler is defined in sAPI_Tick.c
 **
 ** \remark the definition is in
 **         modules/sapi/sAPI_Tick.c
 **/
extern void SysTick_Handler(void);

/** \brief ADC0 IRQ Handler
 **
 ** ADC0 IRQ Handler is defined in sAPI_AnalogIO.c
 **
 ** \remark the definition is in
 **         modules/sapi/sAPI_AnalogIO.c
 **/
/*extern void ADC0_IRQHandler(void);*/

/** \brief Timer IRQ Handlers
 **
 ** TIMER0,1,2 and 3 IRQ Handlers are defined in sAPI_Timer.c
 **
 ** \remark the definition is in
 **         modules/sapi/sAPI_Timer.c
 **/
extern void TIMER0_IRQHandler(void);
extern void TIMER1_IRQHandler(void);
extern void TIMER2_IRQHandler(void);
extern void TIMER3_IRQHandler(void);

/** \brief UART IRQ Handlers
 **
 ** System Tick Handler is defined in sAPI_Uart.c
 **
 ** \remark the definition is in
 **         modules/sapi/sAPI_Uart.c
 **/
extern void UART0_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void UART3_IRQHandler(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_ISRS_H_ */
