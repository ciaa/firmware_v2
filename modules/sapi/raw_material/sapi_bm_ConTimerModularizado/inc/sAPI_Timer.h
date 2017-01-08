/* Copyright 2016, Ian Olivieri.
 * Copyright 2016, Eric Pernia.
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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

/* Date: 2016-05-02 */

#ifndef _SAPI_TIMER_H_
#define _SAPI_TIMER_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/* TIMER */
typedef enum{
   DISABLE_TIMER,
   COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
   INPUT_PULSE_CAPTURE, 
   OUTPUT_SIGNAL_GENERATOR, PWM
} timerMode_t;

typedef struct{
   uint8_t timer;    /* TIMER0 to TIMER3 or SCT */
   timerMode_t mode; /* COUNT_TO_OVERFLOW, COUNT_TO_MATCH, INPUT_PULSE_CAPTURE, 
                        OUTPUT_SIGNAL_GENERATOR, PWM, DISABLE_TIMER */
} timerConfig_t;

/* PWM */
typedef enum{
   PWM_OUTPUT_DISABLE, PWM_OUTPUT_ENABLE
} timerPwmMode_t;

typedef struct{
   uint8_t  pwm;
   uint8_t  mode;
   uint8_t  dutyCycle;
   uint32_t frequency;
}timerPwm_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * @brief: Configure Timer with configValues
 * @param:  uint8_t timer: TIMER0, TIMER1, TIMER2, TIMER3 or SCT
 * @param:  uint8_t mode: DISABLE_TIMER, COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
                          INPUT_PULSE_CAPTURE, OUTPUT_SIGNAL_GENERATOR, PWM
 * @param:  void * configValues: timer configuration Structure, the actual 
 *                               type depends of mode:
 *                               * timerPwm_t for PWM mode.
 *                               * timerCompareMatch_t for COUNT_TO_MATCH mode.
 * @return: bool_t.
 */
bool_t timerConfig( uint8_t timer, uint8_t mode, void *configValues );

/*
 * @brief: Read Timer in readInValues
 * @param:  uint8_t timer: TIMER0, TIMER1, TIMER2, TIMER3 or SCT
 * @param:  uint8_t mode: DISABLE_TIMER, COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
                          INPUT_PULSE_CAPTURE, OUTPUT_SIGNAL_GENERATOR, PWM
 * @param:  void * readInValues: strurcture to save read values
 * @return: bool_t.
 */
bool_t timerRead( uint8_t timer, uint8_t mode, void *readInValues );

/*
 * @brief: Write Timer from writeInValues
 * @param:  uint8_t timer: TIMER0, TIMER1, TIMER2, TIMER3 or SCT
 * @param:  uint8_t mode: DISABLE_TIMER, COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
                          INPUT_PULSE_CAPTURE, OUTPUT_SIGNAL_GENERATOR, PWM
 * @param:  void * writeInValues: strurcture to load values
 * @return: bool_t.
 */
bool_t timerWrite( uint8_t timer, uint8_t mode, void *writeInValues );

/*==================[ISR external functions declaration]=====================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/


#endif /* SAPI_TIMER_H_ */