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

#ifndef _I2C_H_
#define _I2C_H_

/** @addtogroup I2C
 *  Inter-Integrated Circuit communication API
 *
 *  Available signals and pins:
 *  | picoCIAA | Signal     |
 *  | -------- | ---------- |
 *  | P8_5     | I2C1_SCL   |
 *  | P8_8     | I2C1_SDA   |
 *  | P8_3     | I2C0_SCL   |
 *  | P8_6     | I2C0_SDA   |
 *  | P8_7     | I2C2_SCL   |
 *  | P2_13    | I2C2_SDA   |
 *
 *  @note use I2C1 as default because it has external pull-ups available
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

/** Available I2C ports */
typedef enum picoI2CPort {
	I2C0, /**< I2C0 on pins @ref P8_3 (SCL) and @ref P8_6 (SDA) */
	I2C1, /**< I2C1 on pins @ref P8_5 (SCL) and @ref P8_8 (SDA) with external pull-ups */
	I2C2  /**< I2C2 on pins @ref P8_7 (SCL) and @ref P2_13 (SDA) */
}picoI2CPort;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** initialize I2C port
 *
 * @param p port number, can be @ref I2C0, @ref I2C1 or @ref I2C2.
 */
void picoI2CInit(picoI2CPort p);

/** transmit and receive data to/from I2C port
 *
 * @param p          port number, can be @ref I2C0, @ref I2C1 or @ref I2C2.
 * @param slave_addr slave ID
 * @param txbuf      transmit data buffer
 * @param txlen      transmit data buffer length in bytes
 * @param rxbuf      receive data buffer
 * @param rxlen      receive data buffer length in bytes
 * @return 0 on success, other value in case of I2C error
 */
int32_t picoI2CTransfer(picoI2CPort p, uint8_t slave_addr,
		uint8_t * txbuf, uint16_t txlen,
		uint8_t * rxbuf, uint16_t rxlen);

/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _I2C_H_ */
