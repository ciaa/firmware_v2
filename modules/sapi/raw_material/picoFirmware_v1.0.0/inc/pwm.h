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

#ifndef _PWM_H_
#define _PWM_H_

/** @addtogroup PWM
 *  PWM functions
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

/** configure PWM engine frequency
 *
 * @param frequency desired frequency in Hertz
 */
void picoPWMInit(uint32_t frequency);

/** set PWM output pin and duty cycle
 *
 * @param pin  pwm pin to set, can be @ref P2_1, @ref P2_7, @ref P2_8,
 * @ref P2_9, @ref P2_10, @ref P6_18, @ref P6_3, @ref P6_5, @ref P6_7,
 * @ref P6_9, @ref P6_10, @ref P6_13, @ref P6_14, @ref P6_17, @ref P6_20
 * or @ref P8_2.
 * @param duty duty cycle in percent (0~100%)
 * @return 0 in case of success, -1 if pin doesn't have pwm function
 */
int32_t picoPWMSet(picoPin_e pin, uint32_t duty);

/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _PWM_H_ */
