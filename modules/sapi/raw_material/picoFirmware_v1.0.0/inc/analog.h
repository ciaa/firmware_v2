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

#ifndef _ANALOG_H_
#define _ANALOG_H_

/** @addtogroup Analog-to-Digital
 *  Analog-to-Digital conversion functions.
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

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** init ADC functions
 * @warning Do not call to this function, it is called during
 *          system initialization.
 */
void picoAnalogInit(void);

/** Read analog input
 * @param pin analog pin to read, should be @ref P2_3 to @ref P2_11 or @ref P8_10,
 *            previously configured with @ref picoConfigAnalogInput.
 * @return analog value (12-bits)
 */
uint16_t picoAnalogRead(picoPin_e pin);

/** Write analog output
 * @warning Not supported!!!
 */
void picoAnalogWrite(picoPin_e pin, uint16_t value);

/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _ANALOG_H_ */
