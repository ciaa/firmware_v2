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

#ifndef SAPI_SERVO_H_
#define SAPI_SERVO_H_

/*==================[inclusions]=============================================*/

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros and definitions]=================================*/

/*==================[typedef]================================================*/

typedef enum{
   DISABLE_SERVO_OUTPUT, ANGULAR_SERVO, CONTINOUS_SERVO
} servoMode_t;

typedef struct{   
   uint8_t servoDO;  /* Servo Digital Output */
   int32_t value;    /* value of servo in microseconds */
   servoMode_t mode; /* ANGULAR_SERVO, CONTINOUS_SERVO or 
                        DISABLE_SERVO_OUTPUT */
   int32_t periodUs; /* Servo PWM period in microseconds, typicaly 20000, 
                        only can define 3 diferent periods, one fore each 
                        physical TIMER (TIMER1 to TIMER3) */
   int32_t minUs;    /* min value ON in microseconds (0° or full speed 
                        counter-clockwise), typicaly 1000 */
   int32_t midUs;    /* mid value ON in microseconds (90° or stop), typicaly
                        1500 */
   int32_t maxUs;    /* max value ON in microseconds (180° or full speed 
                        clockwise), typicaly 2000 */
} servoConfig_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*
 * @Brief: Initializes servo peripheral
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  servoMode_t mode: ANGULAR_SERVO, CONTINOUS_SERVO or DISABLE_SERVO_OUTPUT
 * @return: bool_t: true (1) if config it is ok
 * @IMPORTANT: this function uses Timer 1 (SERVO0 to SERVO2), Timer 2 (SERVO3 
               to SERVO5) and Timer 3 (SERVO6 to SERVO8) to generate the servo 
               signals, so they won't be available to use.
 */
bool_t servoConfig( uint8_t servo, servoMode_t mode );

/*
 * @Brief: Initializes servo peripheral
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  servoConfig_t * servoConfig: servo configuration structure 
 * @return: bool_t: true (1) if config it is ok
 * @IMPORTANT: this function uses Timer 1 (SERVO0 to SERVO2), Timer 2 (SERVO3 
               to SERVO5) and Timer 3 (SERVO6 to SERVO8) to generate the servo 
               signals, so they won't be available to use.
 */
bool_t servoAdvancedConfig( uint8_t servo, servoConfig_t * servoConfig );

/*
 * @brief: Read the value of servo
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @return: int32_t value:  value of servo
 */
int32_t servoRead( uint8_t servo );

/*
 * @brief: Change the value of servo
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  int32_t value:  value of servo 
 * @return: True if the value was successfully changed, False if not.
 */
bool_t servoWrite( uint8_t servo, int32_t value );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/

#endif /* SAPI_SERVO_H_ */
