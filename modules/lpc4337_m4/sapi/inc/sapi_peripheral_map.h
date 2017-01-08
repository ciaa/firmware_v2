/* Copyright 2015, Eric Pernia.
 * Copyright 2016, Ian Olivieri.
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

#ifndef _SAPI_PERIPHERALMAP_H_
#define _SAPI_PERIPHERALMAP_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"
#include "sapi_peripheral_map_soc.h"
#include "sapi_peripheral_map_board.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros & typedef]=======================================*/

/* ---------------------- GPIO Map --------------------- */

/* GPIO instances size */
#define GPIO_INSTANCES_SIZE 64

/* GPIO name enum type */
typedef enum{
    GPIO0,  GPIO1,  GPIO2,  GPIO3,  GPIO4,  GPIO5,  GPIO6,  GPIO7,
    GPIO8,  GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15,
   GPIO16, GPIO17, GPIO18, GPIO19, GPIO20, GPIO21, GPIO22, GPIO23,
   GPIO24, GPIO25, GPIO26, GPIO27, GPIO28, GPIO29, GPIO30, GPIO31,
   GPIO32, GPIO33, GPIO34, GPIO35, GPIO36, GPIO37, GPIO38, GPIO39,
   GPIO40, GPIO41, GPIO42, GPIO43, GPIO44, GPIO45, GPIO46, GPIO47,
   GPIO48, GPIO49, GPIO50, GPIO51, GPIO52, GPIO53, GPIO54, GPIO55,
   GPIO56, GPIO57, GPIO58, GPIO59, GPIO60, GPIO61, GPIO62, GPIO63, 
} gpioName_t;


/* ---------------------- UART Map --------------------- */

/* UART instances size */
#define UART_INSTANCES_SIZE 8

/* UART name enum type */
typedef enum{
   UART0, UART1, UART2, UART3, UART4, UART5, UART6, UART7
} uartName_t;


/* --------------------- TIMER Map --------------------- */

/* TIMER instances size */
#define TIMER_INSTANCES_SIZE 8

/* TIMER name enum type */
typedef enum{
   TIMER0, TIMER1, TIMER2, TIMER3, TIMER4, TIMER5, TIMER6, TIMER7
} timerName_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_PERIPHERALMAP_H_ */
