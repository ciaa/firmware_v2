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
 
/*==================[inclusions]=============================================*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_DigitalIO.h"
#include "sAPI_Timer.h"

#include "sAPI_Servo.h"

/*==================[macros and definitions]=================================*/

#define TOTAL_SERVOS 9

/*==================[internal data declaration]==============================*/


/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/

/* Servo Structure */
static servoConfig_t servos[ TOTAL_SERVOS ] = {
                {  DIO4, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO17, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO18, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO19, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO24, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO31, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO32, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO33, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 },
                { DIO35, 500, DISABLE_SERVO_OUTPUT, 20000, 500, 1250, 2000 }
             };

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*
 * @Brief: Initializes servo peripheral
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  servoMode_t mode: ANGULAR_SERVO, CONTINOUS_SERVO or 
 *                            DISABLE_SERVO_OUTPUT
 * @return: bool_t: true (1) if config it is ok
 * @IMPORTANT: this function uses Timer 1 (SERVO0 to SERVO2), Timer 2 (SERVO3 
               to SERVO5) and Timer 3 (SERVO6 to SERVO8) to generate the servo 
               signals, so they won't be available to use.
 */
bool_t servoConfig( uint8_t servo, servoMode_t mode ){
   
   servoConfig_t servoConfiguration = {
                               255,   /* Servo Digital Output */
                               500,   /* value of servo in microseconds */
                               mode,  /* ANGULAR_SERVO, CONTINOUS_SERVO or 
                                         DISABLE_SERVO_OUTPUT */
                               20000, /* Servo PWM period in microseconds */
                               500,   /* min value ON in microseconds */
                               1250,  /* mid value ON in microseconds */
                               2000   /* max value ON in microseconds */
                            };
   
   return servoAdvancedConfig( servo, &servoConfiguration );
}

/*
 * @Brief: Initializes servo peripheral
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  servoConfig_t * servoConfig: servo configuration structure 
 * @return: bool_t: true (1) if config it is ok
 * @IMPORTANT: this function uses Timer 1 (SERVO0 to SERVO2), Timer 2 (SERVO3 
               to SERVO5) and Timer 3 (SERVO6 to SERVO8) to generate the servo 
               signals, so they won't be available to use.
 */
bool_t servoAdvancedConfig( uint8_t servo, servoConfig_t * servoConfig ){

   bool_t ret_val = 1;
   
   if( servos[servo].servoDO != 255 )
      servos[servo].servoDO  = servoConfig->servoDO;
   
   servos[servo].value    = servoConfig->value;
   servos[servo].mode     = servoConfig->mode;
   servos[servo].periodUs = servoConfig->periodUs;
   servos[servo].minUs    = servoConfig->minUs;
   servos[servo].midUs    = servoConfig->midUs;
   servos[servo].maxUs    = servoConfig->maxUs;
   
   /*
   servoInitTimers();
   ret_val = servoAttach( servoNumber );
   ret_val = servoDetach( servoNumber );
   
   */
   
   switch( servos[servo].mode ){

      case ANGULAR_SERVO:
         digitalWrite(LEDB,1);
         
         //ret_val = servoAttach( servoNumber );
      break;

      case CONTINOUS_SERVO:
         digitalWrite(LEDR,1);
      
         //ret_val = servoDetach( servoNumber );
      break;

      case DISABLE_SERVO_OUTPUT:
         digitalWrite(LEDB,0);
         digitalWrite(LEDR,0);
      
         //ret_val = servoDetach( servoNumber );
      break;

      default:
         ret_val = 0;
      break;
   }

   return ret_val;
}

/*
 * @brief: Read the value of servo
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @return: int32_t value:  value of servo
 */
int32_t servoRead( uint8_t servo ){
   
   return servos[servo].value;
}

/*
 * @brief: Change the value of servo
 * @param:  uint8_t servo: SERVO0 to SERVO8
 * @param:  int32_t value:  value of servo 
 * @return: True if the value was successfully changed, False if not.
 */
bool_t servoWrite( uint8_t servo, int32_t value ){

   bool_t ret_val = 1;
   
   if( servos[servo].mode == 0 ){
      digitalWrite(LED1,1);
      digitalWrite(LED2,0);
      digitalWrite(LED3,0);
   }
   
   if( value == 0 ){
      digitalWrite(LED1,1);
      digitalWrite(LED2,0);
      digitalWrite(LED3,0);
   }
   
   if( value == 90 ){
      digitalWrite(LED1,0);
      digitalWrite(LED2,1);
      digitalWrite(LED3,0);
   }
   
   if( value == 180 ){
      digitalWrite(LED1,0);
      digitalWrite(LED2,0);
      digitalWrite(LED3,1);
   }
   
   
   switch( servos[servo].mode ){

      /* value is an angle between 0 and 180 degree */
      case ANGULAR_SERVO:
         if( value>=0 && value<=180 ){
            servos[servo].value = (value )/180; //Ver conversion
         }
         else{
            ret_val = 0;
         }
      break;

      /* value is a speed -100 vMax counter clock-wise, 
         0 and 100 vMax clock-wise */
      case CONTINOUS_SERVO:
         if( value>=-100 && value<=100 ){
            if( value== 0 )
               servos[servo].value = servos[servo].midUs;
            servos[servo].value = (value )/100; //Ver conversion
         }
         else{
            ret_val = 0;
         }
      break;

      case DISABLE_SERVO_OUTPUT:
      default:
         ret_val = 0;
      break;
   }

   return ret_val;
}

/*==================[end of file]============================================*/
