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

#include "sapi_log.h"
#include "sapi_stdioBuffer.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

static LogLevel_t LogLevel = LOG_ERROR;
static uartMap_t LogUart;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/**
 * Configura el log global del sistema.
 * @param logLevel en nivel de los a setear.
 * @param logUart la uart por donde se van a logear los datos.
 * @param baudRate velocidad de transmision de logUart
 * @return TRUE si salio ok. FALSE caso contrario.
 */
bool_t 	logConfig	( LogLevel_t logLevel, uartMap_t logUart, uint32_t baudRate ){
	LogLevel = logLevel;
	LogUart = logUart;
	uartConfig(LogUart, baudRate);
	return TRUE;
}

/**
 * Escribe en LogUart el mensaje formateado recibido como argumento.
 * @param logLevel el nivel de log del mensaje.
 * @param functionCalling es la funcion la cual invoca el log.
 * @param fmt string formateado como printf para logear.
 * Dentro de esta funcion tambien se llama a la funcion uartWriteString
 * pasandole como parametro el bufferStdio dentro de buffer_stdio.c
 */
void 	logWrite	( LogLevel_t logLevel, const char * functionCalling, const char *fmt, ... ){
int c, flag = 0, next_int;
double next_float;
char *next_string;
va_list arg_addr;

	// Si el nivel de log esta permitido a imprimir por la UART.
	if (logLevel <= LogLevel){
		//Obtiene la lista de argumentos
		va_start(arg_addr, fmt);
		//Resetea el indice del arreglo a formatear
		stdioBufferConfig(STDIO_BUFFER_INIT);
		//Imprime el nivel de log.
		printf ("\n\r%d - %s - ", (int)logLevel, functionCalling);
		//Mientras el char a formatear no sea caracter nulo...
		while ( (c=*fmt++) != '\0' ){
			if (c == '%'){
				flag += 1;
			}
			if (flag == 1){
				if (c == 'd'){
					next_int = va_arg(arg_addr, int);
					printf("%d", next_int);
					flag = 0;
				} else if (c == 'f') {
					next_float = va_arg(arg_addr, double);
					printf("%lf", next_float);
					flag = 0;
				} else if (c == 's') {
					next_string = va_arg(arg_addr, char*);
					printf("%s", next_string);
					flag = 0;
				}
			} else {
				printf("%c", c);
			}
		}
		uartWriteString(LogUart, stdioBufferRead());
	}
}

void logRead (char * arrayToSaveLastLog){
	char * pointerToLogArray = stdioBufferRead();

	while (*pointerToLogArray != '\0'){
		*arrayToSaveLastLog = *pointerToLogArray;
		arrayToSaveLastLog++;
		pointerToLogArray++;
	}
	*arrayToSaveLastLog = '\0';

//	strcpy(arrayToSaveLastLog, (const char *)stdioBufferRead());
}

/*==================[end of file]============================================*/
