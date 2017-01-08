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

#ifndef _SAPI_LPC43XX_TIMER_COMPARE_MATCH_H_
#define _SAPI_LPC43XX_TIMER_COMPARE_MATCH_H_

/*==================[inclusions]=============================================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

typedef void (*voidFunctionPointer_t)(void);

typedef enum{
   TIMER_COMPARE_MATCH_0,
   TIMER_COMPARE_MATCH_1,
   TIMER_COMPARE_MATCH_2, 
   TIMER_COMPARE_MATCH_3
} timerCompareMatch_t;


/*



typedef struct{
   uint8_t timer;
   timerMode_t mode;   
} timerConfig_t;
*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

//*****************************************************************************
// PASAR a LOC43xxTimer -v
//*****************************************************************************


/*
 * @Brief:  Initialize Timer peripheral
 * @param:  uint8_t  timer: TIMER0 to TIMER3
 * @param:  uint32_t ticks: Number of ticks required to finish the cycle.
 * @param:  voidFunctionPointer: function to be executed at the end of the 
 *                               timer cycle
 * @return: nothing
 * @note:   For the 'ticks' parameter, see function Timer_microsecondsToTicks
 */
void timerInit( uint8_t timer, uint32_t ticks, 
                voidFunctionPointer_t voidFunctionPointer );

/*
 * @Brief:  Disables timer peripheral
 * @param:  uint8_t timer: TIMER0 to TIMER3
 * @return: nothing
 */
void timerDeInit( uint8_t timer );

//*****************************************************************************
// PASAR a LOC43xxTimer -^
//*****************************************************************************

/*
 * @Brief:  Enables a compare match in a timer
 * @param:  uint8_t timer: TIMER0 to TIMER3
 * @param:  uint8_t compareMatch: TIMER_COMPARE_MATCH_1 to 
 *                                TIMER_COMPARE_MATCH_3 
 * @param:  uint32_t ticks: Number of ticks required to reach the compare 
 *                          match.
 * @param   voidFunctionPointer: function to be executed when the compare 
 *                               match is reached
 * @return: None
 * @note:   For the 'ticks' parameter, see function Timer_microsecondsToTicks
 */
void timerCompareMatchEnable( uint8_t timer, uint8_t compareMatch, 
                              uint32_t ticks, 
                              voidFunctionPointer_t voidFunctionPointer );

/*
 * @Brief:  Disables a compare match of a timer
 * @param:  uint8_t timer: TIMER0 to TIMER3
 * @param:  uint8_t compareMatch: TIMER_COMPARE_MATCH_1 to 
 *                                TIMER_COMPARE_MATCH_3
 * @return: None
 */
void timerCompareMatchDisable( uint8_t timer, uint8_t compareMatch );

/*
 * @Brief:  Allows the user to change the compare value n? 
 *          'compareMatchNumber' of timer 'timerNumber'.
 *          This is specially useful to generate square waves if used in the 
 *          function for the TIMERCOMPAREMATCH0 (because that compare match 
 *          resets the timer counter), which will be passed as a parameter 
 *          when initializing a timer.
 * @note:   The selected time (3rd parameter) must be less than 
 *          TIMERCOMPAREMATCH0's compareMatchTime_uS for the compare match to 
 *          make the interruption.
 */
void timerCompareMatchSet( uint8_t timer, uint8_t compareMatch,
                           uint32_t ticks );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/

#endif /* _SAPI_LPC43XX_TIMER_COMPARE_MATCH_H_ */
