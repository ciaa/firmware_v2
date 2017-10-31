/* Copyright 2017, Agustin Bassi.
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

/* Date: 2017-30-10 */

/*==================[inclusions]=============================================*/

#include "sapi.h"     // <= sAPI header
//#include "stdio_printf_and_buffer.h"

/*==================[macros and definitions]=================================*/

#define PI 3.145
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
int32_t contador = 0;
// Puntero al buffer stdio (se puede formatear como printf).
char * stdioBufferPointer;

   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar UART_USB a 115200 baudios */
   uartConfig( UART_USB, 115200 );

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
	   // Se escribe en el buffer stdio la cadena formateada con los parametros pasados.
	   stdioBufferWrite("\n\rContador; %d; PI; %f; PI+Cont; %f\n\r", contador, PI, PI + contador);

	   // Se asigna al puntero la direccion de memoria del buffer stdio formateado previamente.
	   stdioBufferPointer = stdioBufferRead();

	   // Se escribe en la UART_USB el contenido del buffer stdio.
	   // Notar que este buffer, ademas de mandarse por la UART
	   // puede ser utilizado para otros fines. Por ejemplo:
	   // guardar el string formateado en una SD o EEPROM, enviarlo por TCP, etc.
	   uartWriteString(UART_USB, stdioBufferPointer);

	   // Realiza un printf de la cadena por la UART_USB.
	   // La UART_USB podria cambiarse por UART_485 o UART_232
	   uartPrintf(UART_USB, "Printf desde EDU-CIAA NXP. Contador: %d\n\r", contador);

	   contador++;
	   delay(1000);
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
