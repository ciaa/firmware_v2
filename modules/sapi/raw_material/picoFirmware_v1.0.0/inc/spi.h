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

#ifndef _SPI_H_
#define _SPI_H_

/** @addtogroup SPI
 *  Serial Peripheral Interface communication API
 *
 *  Available signals and pins:
 *  | picoCIAA | Signal     |
 *  | -------- | ---------- |
 *  | P6_11    | SPI0_MOSI  |
 *  | P6_12    | SPI0_SCK   |
 *  | P6_14    | SPI0_MISO  |
 *  | P6_15    | SPI1_MOSI  |
 *  | P6_16    | SPI1_SCK   |
 *  | P6_18    | SPI1_MISO  |
 *
 *  @warning SD interface uses SPI0, do not use SD API and SPI API with SPI0
 *  at the same time!
 *
 *  @{
 */

/*==================[inclusions]=============================================*/

#include "pin.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/** available SPI ports */
typedef enum picoSPIPort {
	SPI0, /**< SPI0 interface */
	SPI1  /**< SPI1 interface */
}picoSPIPort;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** initialize SPI port
 *
 * @param p          port number, @ref SPI0 or @ref SPI1
 * @param clock_rate SPI clock rate
 */
void picoSPIInit(picoSPIPort p, uint32_t clock_rate);

/** transmit and receive data through SPI port (full-duplex)
 *
 * @param p     port number, @ref SPI0 or @ref SPI1
 * @param ssel  digital output to use as slave select, user must previously configure
 * it with @ref picoConfigDigitalOutput and initial value 1 (logic high). If ssel is
 * set as @ref PICOPIN_COUNT, user must take control of SSEL signal.
 * @param txbuf transmit buffer
 * @param rxbuf receive buffer
 * @param len   transfer length in bytes
 * @return transfer status, -1 on error
 */
int32_t picoSPITransfer(picoSPIPort p, picoPin_e ssel,
		uint8_t * txbuf, uint8_t * rxbuf, int32_t len);

/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SPI_H_ */
