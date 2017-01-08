/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
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
 
#ifndef CIAAUART_H_
#define CIAAUART_H_

#include "chip.h"
#include "string.h"

typedef enum _ciaaUarts_e
{
	CIAA_UART_485 = 0,
	CIAA_UART_USB = 1,
	CIAA_UART_232 = 2
}ciaaUART_e;

#define rs485Print(x) uartSend(0, (uint8_t *)(x), strlen(x))
#define dbgPrint(x)   uartSend(1, (uint8_t *)(x), strlen(x))
#define rs232Print(x) uartSend(2, (uint8_t *)(x), strlen(x))

#define UART_BUF_SIZE	512
#define UART_RX_FIFO_SIZE 16

typedef struct _uartData
{
	LPC_USART_T * uart;
	RINGBUFF_T * rrb;
	RINGBUFF_T * trb;
}uartData_t;

void ciaaUARTInit(void);
int uartSend(ciaaUART_e nUART, void * data, int datalen);
int uartRecv(ciaaUART_e nUART, void * data, int datalen);

#endif /* CIAAUART_H_ */
