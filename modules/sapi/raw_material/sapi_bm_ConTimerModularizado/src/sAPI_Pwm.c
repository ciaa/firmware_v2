/* Copyright 2016, Eric Pernia.
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

/* Date: 2016-02-10 */

/* TODO: hacer una forma de buscar las funciones que tocan el modulo siguiente
 * All functions relative to the microcontroller */

/*==================[inclusions]=============================================*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_Pwm.h"

#include "sAPI_Timer.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
 * @Brief: Initializes pwm peripheral
 * @param: uint8_t  pwm: PWM0 to PWM10
 * @param: uint8_t  mode:
 * @param: uint8_t  dutyCycle: 0 to 100.
 * @param: uint32_t frequency: value in Hz
 * @return bool_t true (1) if config it is ok
 */
bool_t pwmConfig( uint8_t pwm, uint8_t mode, uint8_t dutyCycle,
                  uint32_t frequency ){

   timerPwm_t pwmConfig = { pwm, mode, dutyCycle, frequency };

   return timerConfig( SCT, PWM, &pwmConfig );
}

/*
 * @brief:  Read the value of pwm
 * @param:  uint8_t pwm: PWM0 to PWM10
 * @return: uint8_t dutyCycle: dutyCycle of the pwm in the pin (0 to 100).
 */
uint8_t pwmRead( uint8_t pwm ){

   timerPwm_t pwmToRead = { pwm, 0, 0, 0 };

   timerRead( SCT, PWM, &pwmToRead );

   return pwmToRead.dutyCycle;
}

/*
 * @brief:  Change the value of pwm
 * @param:  uint8_t pwm: PWM0 to PWM10
 * @param:  uint8_t dutyCycle: 0 to 100 (percent)
 * @return: True if the value was successfully changed, False if not.
 */
bool_t pwmWrite( uint8_t pwm, uint8_t dutyCycle ){

   timerPwm_t pwmToWrite = { pwm, 0, dutyCycle, 0 };

   return timerWrite( SCT, PWM, &pwmToWrite );
}

/*==================[end of file]============================================*/
