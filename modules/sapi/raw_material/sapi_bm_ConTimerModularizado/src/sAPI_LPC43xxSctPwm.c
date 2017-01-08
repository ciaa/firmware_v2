/* Copyright 2016, Ian Olivieri
 * Copyright 2016, Eric Pernia
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

/*The SCT (State Configurable Timer) is a feature included in some of LPC's 
 * microcontrollers that provides a high resolution PWM (or just another 
 * timer).
 * It's like a normal timer but with multiple Compare Match values (16),
 * and can be therefore used to generate several PWM signals with THE SAME 
 * PERIOD. 
 * For more information about the STCPWM peripheral, refer to the Chapter 39
 * of the LPC43xx user manual
 */


/*==================[inclusions]=============================================*/
#include "chip.h"
/* Specific modules used:
   #include "scu_18xx_43xx.h" for Chip_SCU funtions
   #include "sct_pwm_18xx_43xx.h" for Chip_SCTPWM funtions
*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_LPC43xxSctPwm.h"


/*==================[macros and definitions]=================================*/

/* Because all pins have their CTOUT in the FUNC1 there is no need to
   save the same number for every pin in this case. */
#define CTOUT_FUNC   FUNC1

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/* Enter a pwm number, get a sct number
 * Since this module works with pwm numbers, but uses sct channels to generate
 * the signal, its necessary to connect pwm number with the SctMap_t.
 * This way the user sets "pwms", while using the sct peripheral internally.
 */
static const uint8_t pwmToSctCtout[] ={   
   /*  PWM0 */  CTOUT6,  /* GPIO2  */
   /*  PWM1 */  CTOUT7,  /* GPIO8  */
   
   /*  PWM2 */  CTOUT13, /* T_COL1 */
   /*  PWM3 */  CTOUT3,  /* T_FIL3 */
   /*  PWM4 */  CTOUT0,  /* T_FIL2 */   
   /*  PWM5 */  CTOUT10, /* T_COL0 */
   /*  PWM6 */  CTOUT12, /* T_COL2 */
   /*  PWM7 */  CTOUT1,  /* T_FIL1 */
   
   /*  PWM8 */  CTOUT2,  /* LED1   */
   /*  PWM9 */  CTOUT5,  /* LED2   */
   /* PWM10 */  CTOUT4   /* LED3   */
};

/*
 * List of ports and pins corresponding to the sct channels.
 * Each channel is asociated with a CTOUT number. Some pins, like
 * LED 1 and LCD1, have the same channel, so you can only generate 1 signal
 * for both. Because of that only one of them will be used.
 */
static pinConfigLpc4337_t SCTdataList[] ={
   /*  Sct n°   port | pin | name in board          */
   /*  CTOUT0 */ { 4,  2 }, /* T_FIL2               */
   /*  CTOUT1 */ { 4,  1 }, /* T_FIL1               */
   /*  CTOUT2 */ { 2, 10 }, /* LED1 (also for LCD1) */
   /*  CTOUT3 */ { 4,  3 }, /* T_FIL3               */
   /*  CTOUT4 */ { 2, 12 }, /* LED3 (also for LCD3) */
   /*  CTOUT5 */ { 2, 11 }, /* LED2 (also for LCD2) */
   /*  CTOUT6 */ { 6,  5 }, /* GPIO2                */
   /*  CTOUT7 */ { 6, 12 }, /* GPIO8                */
   /*  CTOUT8 */ { 1,  3 }, /* MDC / SPI_MISO       */
   /*  CTOUT9 */ { 1,  4 }, /* SPI_MOSI             */
   /* CTOUT10 */ { 1,  5 }, /* T_COL0               */
   /* CTOUT11 */ { 0,  0 }, /* DO NOT USE           */
   /* CTOUT12 */ { 7,  5 }, /* T_COL2               */
   /* CTOUT13 */ { 7,  4 }  /* T_COL1               */
};

/*Configuration data for LCD1, LCD2 and LCD3:
 CTOUT_2 { 4 , 4 }, LCD1
 CTOUT_5 { 4 , 5 }, LCD2
 CTOUT_4 { 4 , 6 }, LCD3
 */

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
/*
 * @brief:   Initialize the SCT peripheral with the given frequency
 * @param:   frequency:   value in Hz
 * @note:   there can only be 1 frequency in all the SCT peripheral.
 */
void sctPwmInit( uint32_t frequency ){
   
   static bool_t sctPwmIsInitialized = 0;
    
   if( !sctPwmIsInitialized ){     
      sctPwmIsInitialized = 1;
      /* Source: https://www.lpcware.com/content/faq/how-use-sct-standard-pwm-using-lpcopen */
      /* Initialize the SCT as PWM and set frequency */
      Chip_SCTPWM_Init(LPC_SCT);
      Chip_SCTPWM_SetRate(LPC_SCT, frequency);

      Chip_SCTPWM_Start(LPC_SCT);
   } 
}

/*
 * @brief	Enables pwm function for the given pin
 * @param	pwm: pin where the pwm signal will be generated
 * @return: true (1) if is correct configured
 */
bool_t sctPwmEnable( uint8_t pwm ){
   
   uint8_t sct = pwmToSctCtout[pwm];
   
   /*Enable SCT function on pin*/
   Chip_SCU_PinMux( SCTdataList[sct].port, 
                    SCTdataList[sct].pin, 
                    SCU_MODE_INACT , CTOUT_FUNC
                  );
   /* Sets pin as PWM output and gives it an index 
      (SCTdataList[sctNumber].mode+1)*/
   Chip_SCTPWM_SetOutPin( LPC_SCT, sct+1, sct );

   /* Start with 0% duty cycle */
   return sctPwmSetDutyCycle( sct, Chip_SCTPWM_PercentageToTicks(LPC_SCT,0) );
}

/*
 * @brief	Disable pwm function for the given pin
 * @param	pwm: pin where the pwm signal will be generated
 * @return: true (1) if is correct configured
 */
bool_t sctPwmDisable( uint8_t pwm ){
   
   bool_t  ret_val = 1;
   //uint8_t sct = pwmToSctCtout[pwm];
   
   /* To do */

   return ret_val;
}

/*
 * @brief  Converts a value in microseconds (uS = 1x10^-6 sec) to ticks
 * @param  value: 0 to 100
 * @return Equivalent in Ticks for the LPC4337
 */
uint32_t sctPwmUint8ToTicks(uint8_t value){
   return ( (Chip_SCTPWM_GetTicksPerCycle(LPC_SCT) * value) / 100 );
}

/*
 * @brief: Sets the pwm duty cycle
 * @param: pwm:   pin where the pwm signal is generated
 * @param  value: 0 to 100
 * @note   For the 'ticks' parameter, see function sctPwmUint8ToTicks
 */
bool_t sctPwmSetDutyCycle( uint8_t pwm, uint8_t value ){
   
   bool_t  ret_val = 1;
   uint8_t sct = pwmToSctCtout[pwm];
   
   if( value<0 || value>100 ){
      ret_val = 0;      
   }
   else{
      Chip_SCTPWM_SetDutyCycle( LPC_SCT,
                                sct+1,
                                sctPwmUint8ToTicks(value)
                              );
   }

   return ret_val;   
}

/*
 * @brief:  Gets the pwm duty cycle
 * @param:  sctNumber:   pin where the pwm signal is generated
 * @return: duty cycle of the channel, from 0 to 100
 */
 /* TODO: function not tested */
uint8_t sctPwmGetDutyCycle( uint8_t pwm ){
   
   uint8_t sct = pwmToSctCtout[pwm];   
   uint8_t value = 0;

   value = (uint8_t) ( 
                        ( Chip_SCTPWM_GetDutyCycle( LPC_SCT, sct+1 )
                        * 100) / 
                        Chip_SCTPWM_GetTicksPerCycle( LPC_SCT ) 
                     );

   return value;
}

/*==================[end of file]============================================*/
