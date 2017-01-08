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

#include "ciaaUART.h"

uint8_t rxbuf[3][UART_BUF_SIZE];
uint8_t txbuf[3][UART_BUF_SIZE];

RINGBUFF_T rrb[3];
RINGBUFF_T trb[3];

uartData_t uarts[3] =
{
		{ LPC_USART0, &(rrb[0]), &(trb[0]) },
		{ LPC_USART2, &(rrb[1]), &(trb[1]) },
		{ LPC_USART3, &(rrb[2]), &(trb[2]) },
};

void ciaaUARTInit(void)
{
	/* UART0 (RS485/Profibus) */
	Chip_UART_Init(LPC_USART0);
	Chip_UART_SetBaud(LPC_USART0, 115200);

	Chip_UART_TXEnable(LPC_USART0);

	Chip_SCU_PinMux(9, 5, MD_PDN, FUNC7);              /* P9_5: UART0_TXD */
	Chip_SCU_PinMux(9, 6, MD_PLN|MD_EZI|MD_ZI, FUNC7); /* P9_6: UART0_RXD */

	Chip_UART_SetRS485Flags(LPC_USART0, UART_RS485CTRL_DCTRL_EN | UART_RS485CTRL_OINV_1);

	Chip_SCU_PinMux(6, 2, MD_PDN, FUNC2);              /* P6_2: UART0_DIR */

	/* Restart FIFOS: set Enable, Reset content, set trigger level */
	Chip_UART_SetupFIFOS(LPC_USART0, UART_FCR_FIFO_EN | UART_FCR_TX_RS | UART_FCR_RX_RS | UART_FCR_TRG_LEV0);
	/* dummy read */
	Chip_UART_ReadByte(LPC_USART0);
	/* enable rx interrupt */
	Chip_UART_IntEnable(LPC_USART0, UART_IER_RBRINT);

	NVIC_EnableIRQ(USART0_IRQn);

	RingBuffer_Init(uarts[0].rrb, rxbuf[0], 1, UART_BUF_SIZE);
	RingBuffer_Init(uarts[0].trb, txbuf[0], 1, UART_BUF_SIZE);

	/* UART2 (USB-UART) */
	Chip_UART_Init(LPC_USART2);
	Chip_UART_SetBaud(LPC_USART2, 115200);

	Chip_UART_TXEnable(LPC_USART2);

	Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
	Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */

	Chip_UART_IntEnable(LPC_USART2, UART_IER_RBRINT);
	NVIC_EnableIRQ(USART2_IRQn);

	RingBuffer_Init(uarts[1].rrb, rxbuf[1], 1, UART_BUF_SIZE);
	RingBuffer_Init(uarts[1].trb, txbuf[1], 1, UART_BUF_SIZE);

	/* UART3 (RS232) */
	Chip_UART_Init(LPC_USART3);
	Chip_UART_SetBaud(LPC_USART3, 115200);

	Chip_UART_TXEnable(LPC_USART3);

	Chip_SCU_PinMux(2, 3, MD_PDN, FUNC2);              /* P2_3: UART3_TXD */
	Chip_SCU_PinMux(2, 4, MD_PLN|MD_EZI|MD_ZI, FUNC2); /* P2_4: UART3_RXD */

	Chip_UART_IntEnable(LPC_USART3, UART_IER_RBRINT);
	NVIC_EnableIRQ(USART3_IRQn);

	RingBuffer_Init(uarts[2].rrb, rxbuf[2], 1, UART_BUF_SIZE);
	RingBuffer_Init(uarts[2].trb, txbuf[2], 1, UART_BUF_SIZE);
}

void uart_irq(ciaaUART_e n)
{
	uartData_t * u = &(uarts[n]);

	Chip_UART_IRQRBHandler(u->uart, u->rrb, u->trb);
}

void UART0_IRQHandler(void)
{
	uart_irq(CIAA_UART_485);
}

void UART2_IRQHandler(void)
{
	uart_irq(CIAA_UART_USB);
}

void UART3_IRQHandler(void)
{
	uart_irq(CIAA_UART_232);
}

int uartSend(ciaaUART_e nUART, void * data, int datalen)
{
	uartData_t * u = &(uarts[nUART]);

	return Chip_UART_SendRB(u->uart, u->trb, data, datalen);
}

int uartRecv(ciaaUART_e nUART, void * data, int datalen)
{
	uartData_t * u = &(uarts[nUART]);

	return Chip_UART_ReadRB(u->uart, u->rrb, data, datalen);
}
