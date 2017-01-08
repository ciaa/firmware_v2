/* Copyright 2016, Eric Pernia.
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
 */

/* Date: 2016-08-16 */

/*==================[inclusions]=============================================*/

#include "tasks.h"        /* <= own header */

#include "sapi.h"         /* <= sAPI header */

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* ------------ INICIALIZACION DE TAREAS ------------ */

/* FUNCION que inicializa las tareas. */
void tasksInit(void){

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar GPIOs */
   gpioConfig( 0, GPIO_ENABLE );

   /* Configuración de pines de entrada para Teclas de la CIAA-NXP */
   gpioConfig( TEC1, GPIO_INPUT );
   gpioConfig( TEC2, GPIO_INPUT );
   gpioConfig( TEC3, GPIO_INPUT );
   gpioConfig( TEC4, GPIO_INPUT );

   /* Configuración de pines de salida para Leds de la CIAA-NXP */
   gpioConfig( LEDR, GPIO_OUTPUT );
   gpioConfig( LEDG, GPIO_OUTPUT );
   gpioConfig( LEDB, GPIO_OUTPUT );
   gpioConfig( LED1, GPIO_OUTPUT );
   gpioConfig( LED2, GPIO_OUTPUT );
   gpioConfig( LED3, GPIO_OUTPUT );

}

/* --------------------- TAREAS --------------------- */

/* FUNCION que realiza la tarea 1.
   Esta tarea lee una tecla cada 40ms y escribe su valor
   en LEDB */
void task1(void){

   gpioWrite( LEDB, !gpioRead(TEC1) );

}

/* FUNCION que realiza la tarea 2.
   Esta tarea hace destellar el LED2 (blink) cada
   250ms. */
void task2(void){

   static bool_t led2Status = OFF;

   led2Status = !led2Status;
   gpioWrite( LED2, led2Status );

}

/* FUNCION que realiza la tarea 3.
   Esta tarea hace destellar el LED3 (blink) cada
   500ms. */
void task3(void){

   static bool_t led3Status = OFF;

   led3Status = !led3Status;
   gpioWrite( LED3, led3Status );

}

/*==================[end of file]============================================*/
