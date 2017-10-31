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
//#include "log.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){
LogLevel_t logLevel = LOG_ERROR;
char logMessage [100];

	/* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* Inicializar log con LOG_DEBUG, por UART_USB a 115200 baudios */
   logConfig(logLevel, UART_USB, 115200);
   gpioWrite(LEDB, ON);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
	   // Escribe mensajes en el log con distintos niveles de importancia.
	   // Si el log esta configurado para mostrar los mensajes mas prioritarios
	   // los menos prioritarios no se mostraran.
	   // Para reconfigurar el log se debe llamar a la funcion logConfig
	   // seleccionando el nivel de debug, la uart y velocidad de comunicacion.
	   logWrite(LOG_ERROR, 	"main", "Mensaje %d con LOG_ERROR", 1);
	   logWrite(LOG_WARNING,"main", "Mensaje %d con LOG_WARNING", 2);
	   logWrite(LOG_NORMAL, "main", "Mensaje %d con LOG_NORMAL", 3);
	   logWrite(LOG_DEBUG, 	"main", "Mensaje %d con LOG_DEBUG", 4);

	   // Mediante la pulsacion de TEC1 se cambia el nivel de log
	   if (!gpioRead(TEC1)){
		   if (++logLevel >= LOG_INVALID){
			   logLevel = LOG_ERROR;
		   }

		   // Reconfigura el nivel de log y la uart por donde saca los mensajes.
		   // Notar que aca se podria cambiar tambien la uart por la que saca
		   // los mensajes.
		   logConfig(logLevel, UART_USB, 115200);

		   // El nivel es informado con los LEDs de la placa
		   gpioWrite(LEDB, OFF);
		   gpioWrite(LED1, OFF);
		   gpioWrite(LED2, OFF);
		   gpioWrite(LED3, OFF);
		   if 		(logLevel == LOG_ERROR)		gpioWrite(LEDB, ON);
		   else if 	(logLevel == LOG_WARNING)	gpioWrite(LED1, ON);
		   else if 	(logLevel == LOG_NORMAL)	gpioWrite(LED2, ON);
		   else if 	(logLevel == LOG_DEBUG)		gpioWrite(LED3, ON);
	   }

	   // Si se presiona TEC2 se puede leer el ultimo mensaje del log
	   if (!gpioRead(TEC2)){
		   logWrite(LOG_ERROR, 	"main", "Mensaje de lectura del log");
		   logRead(logMessage);
		   uartPrintf(UART_USB, "\n\rEl ultimo mensaje del log es:\n\r%s", logMessage);
		   delay(5000);
	   }
	   delay(1000);
   }

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
