/* Copyright 2016, Eric Pernia.
 * Copyright 2016, Ian Olivieri.
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

/* Date: 2016-06-04 */

/*
 * Timers
 * For more information about the Timers peripherals, refer to the Chapter 32
 * of the LPC43xx user manual.
 */

/* The SCT (State Configurable Timer) is a feature included in some of LPC's 
 * microcontrollers that provides a high resolution PWM (or just another timer).
 * It's like a normal timer but with multiple Compare Match values (16),
 * and can be therefore used to generate several PWM signals with THE SAME 
 * PERIOD. For more information about the STCPWM peripheral, refer to the 
 * Chapter 39 of the LPC43xx user manual.
 */

/*==================[inclusions]=============================================*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_Timer.h"

#include "sAPI_LPC43xxSctPwm.h"
#include "sAPI_LPC43xxTimerCompareMatch.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/


/* 
HACER UN VECTOR "TIMER CAPABILITIES" QUE TENGA FLAGS SEGUN EL MODO QUE
SOPORTA CADA TIMER. ESTO ES PARA DAR ERROR CORRECTO SI NO SOPORTA CIERTO
MODO
*/
typedef struct{
   bool_t countToOverflowMode;
   bool_t countToMatchMode;
   bool_t inputPulseCaptureMode;
   bool_t outputSignalGeneratorMode;
   bool_t pwmMode;
} timerCapabilities_t;


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
bool_t timerConfig( uint8_t timer, uint8_t mode, void *configValues ){

   bool_t ret_val = 1;

   switch(mode){

      /* Timer reset on counter overflow */
      case COUNT_TO_OVERFLOW:
         ret_val = 0;
      break;

      /* Clear timer on compare match */
      case COUNT_TO_MATCH:
         switch(timer){
            case TIMER0:
               ret_val = 0;
            case TIMER1:            
            case TIMER2:            
            case TIMER3:
               
               ret_val = 0;
            break;
            case SCT:
               ret_val = 0;
            break;
            default:
               ret_val = 0;
            break;
         }
      break;
      
      /* Pulse count */
      case INPUT_PULSE_CAPTURE:
         ret_val = 0;
      break;
      
      /* Waveform generator */
      case OUTPUT_SIGNAL_GENERATOR:
         ret_val = 0;
      break;
      
      /* Generate a Pulse Width Modulation output */
      case PWM:
         switch(timer){
            case TIMER0:
            case TIMER1:
            case TIMER2:
            case TIMER3:
               ret_val = 0;
            break;
            case SCT:
   
               sctPwmInit( ((timerPwm_t *)configValues)->frequency );

               switch( ((timerPwm_t *)configValues)->mode ){
                  case PWM_OUTPUT_ENABLE:
                     sctPwmEnable( ((timerPwm_t *)configValues)->pwm );
                     sctPwmSetDutyCycle(
                                         ((timerPwm_t *)configValues)->pwm, 
                                         ((timerPwm_t *)configValues)->dutyCycle 
                                       );
                  break;
                  case PWM_OUTPUT_DISABLE:
                     sctPwmDisable( ((timerPwm_t *)configValues)->pwm );
                  break;
                  default:
                     ret_val = 0;
                  break;
               }             
            break;            
            default:
               ret_val = 0;
            break;
         }
      break;
      
      /* Turn Off a Timers */
      case DISABLE_TIMER:
         ret_val = 0;
      break;
      
      
      default:
         ret_val = 0;
      break;
   }

   return ret_val;
}

/*
 * @brief: Read Timer in readInValues
 * @param:  uint8_t timer: TIMER0, TIMER1, TIMER2, TIMER3 or SCT
 * @param:  uint8_t mode: DISABLE_TIMER, COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
                          INPUT_PULSE_CAPTURE, OUTPUT_SIGNAL_GENERATOR, PWM
 * @param:  void * readInValues: strurcture to save read values
 * @return: bool_t.
 */
bool_t timerRead( uint8_t timer, uint8_t mode, void *readInValues ){

   bool_t ret_val = 1;

	/* HACER UN VECTOR "TIMER CAPABILITIES" QUE TENGA FLAGS SEGUN EL MODO QUE
	   SOPORTA CADA TIMER. ESTO ES PARA DAR ERROR CORRECTO SI NO SOPORTA CIERTO
		MODO */

   switch(mode){

      /* Timer reset on counter overflow */
      case COUNT_TO_OVERFLOW:
         ret_val = 0;
      break;

      /* Clear timer on compare match */
      case COUNT_TO_MATCH:
         switch(timer){
            case TIMER0:
               ret_val = 0;
            case TIMER1:            
            case TIMER2:            
            case TIMER3:
               
               ret_val = 0;
            break;
            case SCT:
               ret_val = 0;
            break;
            default:
               ret_val = 0;
            break;
         }
      break;
      
      /* Pulse count */
      case INPUT_PULSE_CAPTURE:
         ret_val = 0;
      break;
      
      /* Waveform generator */
      case OUTPUT_SIGNAL_GENERATOR:
         ret_val = 0;
      break;
      
      /* Generate a Pulse Width Modulation output */
      case PWM:
         switch(timer){
            case TIMER0:
            case TIMER1:
            case TIMER2:
            case TIMER3:
               ret_val = 0;
            break;
            case SCT:
               ((timerPwm_t *)readInValues)->dutyCycle = 
                  sctPwmGetDutyCycle( ((timerPwm_t *)readInValues)->pwm );               
            break;            
            default:
               ret_val = 0;
            break;
         }
      break;
      
      default:
         ret_val = 0;
      break;
   }

   return ret_val;
}

/*
 * @brief: Write Timer from writeInValues
 * @param:  uint8_t timer: TIMER0, TIMER1, TIMER2, TIMER3 or SCT
 * @param:  uint8_t mode: DISABLE_TIMER, COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
                          INPUT_PULSE_CAPTURE, OUTPUT_SIGNAL_GENERATOR, PWM
 * @param:  void * writeInValues: strurcture to load values
 * @return: bool_t.
 */
bool_t timerWrite( uint8_t timer, uint8_t mode, void *writeInValues ){

   bool_t ret_val = 1;

	/* HACER UN VECTOR "TIMER CAPABILITIES" QUE TENGA FLAGS SEGUN EL MODO QUE
	   SOPORTA CADA TIMER. ESTO ES PARA DAR ERROR CORRECTO SI NO SOPORTA CIERTO
		MODO */

   switch(mode){

      /* Timer reset on counter overflow */
      case COUNT_TO_OVERFLOW:
         ret_val = 0;
      break;

      /* Clear timer on compare match */
      case COUNT_TO_MATCH:
         switch(timer){
            case TIMER0:
               ret_val = 0;
            case TIMER1:            
            case TIMER2:            
            case TIMER3:
               
               ret_val = 0;
            break;
            case SCT:
               ret_val = 0;
            break;
            default:
               ret_val = 0;
            break;
         }
      break;
      
      /* Pulse count */
      case INPUT_PULSE_CAPTURE:
         ret_val = 0;
      break;
      
      /* Waveform generator */
      case OUTPUT_SIGNAL_GENERATOR:
         ret_val = 0;
      break;
      
      /* Generate a Pulse Width Modulation output */
      case PWM:
         switch(timer){
            case TIMER0:
            case TIMER1:
            case TIMER2:
            case TIMER3:
               ret_val = 0;
            break;
            case SCT: 
               ret_val = sctPwmSetDutyCycle( 
                           ((timerPwm_t *)writeInValues)->pwm, 
                           ((timerPwm_t *)writeInValues)->dutyCycle
                                           );   
            break;            
            default:
               ret_val = 0;
            break;
         }
      break;      
      
      default:
         ret_val = 0;
      break;
   }

   return ret_val;
}

/*==================[end of file]============================================*/
