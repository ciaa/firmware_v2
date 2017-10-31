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

#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>

#include "chip.h"
#include "sapi_stdioBuffer.h"

/*==================[macros and definitions]=================================*/

#ifdef errno
#undef errno
#endif

#ifndef STDOUT_UART
#define STDOUT_UART 2
#endif

#ifndef STDERR_UART
#define STDERR_UART 2
#endif

#ifndef STDIN_UART
#define STDIN_UART 2
#endif

#ifdef lpc4337_m4
#define LPC_UART2 LPC_USART2
#endif

#ifdef lpc54102_m4
#define LPC_UART2 LPC_USART2
#endif

#ifdef lpc11u68
#define LPC_UART2 LPC_USART2
#endif

#if STDIN_UART == 1
	 #define MYSTDIN UART1
#elif STDIN_UART == 2
	 #define MYSTDIN LPC_UART2
#elif STDIN_UART == 3
	 #define MYSTDIN UART3
#else
	 #error "You defined STDIN_UART wrong!"
#endif

#if STDOUT_UART == 1
	 #define MYSTDOUT UART1
#elif STDOUT_UART == 2
	 #define MYSTDOUT LPC_UART2
#elif STDOUT_UART == 3
	 #define MYSTDOUT UART3
#else
	 #error "You defined STDOUT_UART wrong!"
#endif

#if STDERR_UART == 1
	 #define MYSTDERR UART1
#elif STDERR_UART == 2
	 #define MYSTDERR LPC_UART2
#elif STDERR_UART == 3
	 #define MYSTDERR UART3
#else
	 #error "You defined STDERR_UART wrong!"
#endif



/*==================[internal data declaration]==============================*/

static char StdioStubBuffer [STDIO_BUFFER_MAX_SIZE];
static int StdioStubBufferIndex = 0;

extern int errno;

/*==================[internal functions declaration]=========================*/

int 	_close	(int file);
void 	_exit	(int status);
int 	_fstat	(int file, struct stat *st);
int 	_isatty	(int file);
int 	_link	(char *old, char *new);
int 	_lseek	(int file, int ptr, int dir);
int 	_read	(int file, char *ptr, int len);
caddr_t _sbrk	(int incr);
int 	_stat	(const char *filepath, struct stat *st);
clock_t _times	(struct tms *buf);
int 	_unlink	(char *name);
int 	_wait	(int *status);
int 	_write	(int file, char *ptr, int len);

/*==================[internal data definition]===============================*/

void _exit(int status) {
	_write(1, "exit", 4);
	while (1) {
		;
	}
}

int _close(int file) {
	return -1;
}

/*
 fstat
 Status of an open file. For consistency with other minimal implementations in these examples,
 all files are regarded as character special devices.
 The `sys/stat.h' header file required is distributed in the `include' subdirectory for this C library.
 */
int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*
 isatty
 Query whether output stream is a terminal. For consistency with the other minimal implementations,
 */
int _isatty(int file) {
	switch (file){
	case STDOUT_FILENO:
	case STDERR_FILENO:
	case STDIN_FILENO:
		return 1;
	default:
		//errno = ENOTTY;
		errno = EBADF;
		return 0;
	}
}


/*
 link
 Establish a new name for an existing file. Minimal implementation:
 */

int _link(char *old, char *new) {
	errno = EMLINK;
	return -1;
}

/*
 lseek
 Set position in a file. Minimal implementation:
 */
int _lseek(int file, int ptr, int dir) {
	return 0;
}

/*
 sbrk
 Increase program data space.
 Malloc and related functions depend on this
 */
caddr_t _sbrk(int incr) {

	extern char _ebss; // Defined by the linker
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0) {
		heap_end = &_ebss;
	}
	prev_heap_end = heap_end;

	char *stack = (char*) __get_MSP();
	if (heap_end + incr >  stack)
	{
		_write (STDERR_FILENO, "Heap and stack collision\n", 25);
		errno = ENOMEM;
		return  (caddr_t) -1;
	}

	heap_end += incr;
	return (caddr_t) prev_heap_end;
}

/*
 read
 Read a character to a file. `libc' subroutines will use this system routine for input from all files, including stdin
 Returns -1 on error or blocks until the number of characters have been read.
 */


int _read(int file, char *ptr, int len) {
	int n;
	int num = 0;
	switch (file) {
	case STDIN_FILENO:
		for (n = 0; n < len; n++) {
//			char c;
//#if (!defined(lpc11u68))
//			Chip_UART_ReadBlocking(MYSTDIN, &c, 1);
//#else
//			Chip_UARTN_ReadBlocking(MYSTDIN, &c, 1);
//#endif
//			*ptr++ = c;
			num++;
		}
		break;
	default:
		errno = EBADF;
		return -1;
	}
	return num;
}

/*
 stat
 Status of a file (by name). Minimal implementation:
 int    _EXFUN(stat,( const char *__path, struct stat *__sbuf ));
 */

int _stat(const char *filepath, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*
 times
 Timing information for current process. Minimal implementation:
 */

clock_t _times(struct tms *buf) {
	return -1;
}

/*
 unlink
 Remove a file's directory entry. Minimal implementation:
 */
int _unlink(char *name) {
	errno = ENOENT;
	return -1;
}

/*
 wait
 Wait for a child process. Minimal implementation:
 */
int _wait(int *status) {
	errno = ECHILD;
	return -1;
}

/*
 write
 Write a character to a file. `libc' subroutines will use this system routine for output to all files, including stdout
 Returns -1 on error or number of bytes sent
 */
int _write(int file, char *ptr, int len) {
	int n;

	switch (file) {
	case STDERR_FILENO: /* stderr */
	case STDOUT_FILENO: /*stdout*/
		for (n = 0; n < len; n++) {
			//Si llega al maximo tamanio pone el terminador nulo.
			if (StdioStubBufferIndex < STDIO_BUFFER_MAX_SIZE){
				StdioStubBuffer[StdioStubBufferIndex] = *ptr;
				StdioStubBufferIndex++;
			} else {
				StdioStubBuffer[StdioStubBufferIndex] = '\0';
			}
			//#if (!defined(lpc11u68))
			//			Chip_UART_SendBlocking(MYSTDOUT, ptr, 1);
			//#else
			//			Chip_UARTN_SendBlocking(MYSTDOUT, ptr, 1);
			//#endif
			ptr++;
		}
		break;
	default:
		errno = EBADF;
		return -1;
	}
	return len;
}

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/**
 * Devuelve un puntero al array previamente formateado.
 * El puntero que devuelve pertenece a un array estatico
 * declarado en este archivo.
 * El tamanio del array es ARRAY_FORMATTED_MAX_SIZE
 * y puede cambiarse en el archivo sapi_stdioStubs.h
 * @return un puntero al primer elemento del arreglo formateado.
 */
char * stdioBufferRead (void){
	return StdioStubBuffer;
}

/**
 * Formatea un arreglo de la misma manera que un printf.
 * @param fmt es una cadena al string formateado.
 * Ademas de eso se recibe una lista de argumentos variables
 * que son los que le otorgan los valores al string formateado.
 */
void stdioBufferWrite (const char *fmt, ...){
int c, flag = 0, next_int;
double next_float;
char *next_string;
va_list arg_addr;

	//Obtiene la lista de argumentos
	va_start(arg_addr, fmt);
	//Resetea el indice del arreglo a formatear
//	ArrayFormattedIndex = 0;
	stdioBufferConfig(STDIO_BUFFER_INIT);
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
}

/**
 * Configura el buffer a formatear bajo el formato de printf.
 * @param config el tipo de configuracion a realizar sobre el buffer.
 * Actualmente el unico argumento valido es STDIO_BUFFER_INIT
 * @return TRUE si se configura correctamente. FALSE caso contrario.
 */
bool_t	stdioBufferConfig (stdioBufferConfig_t config){
	bool_t state = FALSE;
	if (config == STDIO_BUFFER_INIT){
		//Resetea el indice del arreglo a formatear
		StdioStubBufferIndex = 0;
		bzero(StdioStubBuffer, STDIO_BUFFER_MAX_SIZE);
		state = TRUE;
	}
	return state;
}

/*==================[end of file]============================================*/

