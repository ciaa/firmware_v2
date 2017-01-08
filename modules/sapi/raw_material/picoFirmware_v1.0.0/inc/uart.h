/* Copyright 2016, Pablo Ridolfi
 * Copyright 2016, VICDA Argentina
 * All rights reserved.
 *
 * This file is part of picoAPI.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _UART_H_
#define _UART_H_

/** @addtogroup SerialCom
 * UART communication
 *
 * @{
 */
/*==================[inclusions]=============================================*/

#include "picoapi.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/** Available UARTs */
typedef enum picoUART_e {
	UART1=1,/**< UART1 */
	UART2,  /**< UART2 */
	UART3   /**< UART3 */
}picoUART_e;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** initialize USART0 using ring buffers
 */
void debugInit(void);

/** send data through debug interface (USART0)
 *
 * @param data pointer to data
 * @param len data length in bytes
 * @return number of bytes placed in tx buffer
 */
uint32_t debugSend(void * data, size_t len);

/** receive data from debug interface (USART0)
 *
 * @param data buffer to store data
 * @param len buffer size
 * @return number of bytes readed from rx buffer
 */
uint32_t debugRecv(void * data, size_t len);

/** send a string through debug interface
 *
 * @param string null-terminated string to send
 */
void printString(char * string);

/** convert integer to decimal string and send through debug interface
 *
 * @param number integer to convert and send
 */
void printInteger(int32_t number);

/** convert integer to hexadecimal string and send through debug interface
 *
 * @param number integer to convert and send
 */
void printHex(uint32_t number);

/** initialize UART
 *
 * @param u        @ref picoUART_e UART number (@ref UART1, @ref UART2 or @ref UART3)
 * @param txpin    TXD pin to use, see @ref picoPin_e
 * @param rxpin    RXD pin to use, see @ref picoPin_e
 * @param baudrate integer baudrate (i.e. 9600, 19200, 115200, etc.)
 */
void picoUARTInit(picoUART_e u, picoPin_e txpin, picoPin_e rxpin, uint32_t baudrate);

/** send data through UART
 *
 * @param u    @ref picoUART_e UART number (@ref UART1, @ref UART2 or @ref UART3)
 * @param data pointer to data
 * @param len  data length in bytes
 * @return number of bytes placed in tx buffer
 */
uint32_t picoUARTSend(picoUART_e u, void * data, size_t len);

/** receive data from UART
 *
 * @param u    @ref picoUART_e UART number (@ref UART1, @ref UART2 or @ref UART3)
 * @param data buffer to store data
 * @param len  buffer size
 * @return number of bytes readed from rx buffer
 */
uint32_t picoUARTRecv(picoUART_e u, void * data, size_t len);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} */

/*==================[end of file]============================================*/
#endif /* #ifndef _UART_H_ */
