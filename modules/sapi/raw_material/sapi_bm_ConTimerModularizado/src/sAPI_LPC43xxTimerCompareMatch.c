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

/*
 * For more information about the Timer peripheral, refer to the Chapter 32 of
 * the LPC43xx user manual
 */

/*==================[inclusions]=============================================*/
#include "chip.h"
/* Specific modules used:
   #include "timer_18xx_43xx.h" for Chip_TIMER functions
   #include "rgu_18xx_43xx.h" for Chip_RGU functions
   #include "core_cm4.h" for NVIC functions
*/

#include "sAPI_DataTypes.h"
#include "sAPI_PeripheralMap.h"

#include "sAPI_LPC43xxTimer.h"
#include "sAPI_LPC43xxTimerCompareMatch.h"

/*==================[macros and definitions]=================================*/

#define MAX_SYSCALL_INTERRUPT_PRIORITY 5

/*==================[internal data declaration]==============================*/
typedef struct
{
   LPC_TIMER_T *name;
   uint32_t RGU; /* Reset Generator Unit */
   uint32_t IRQn;

}timerStaticData_t;

typedef struct
{
   voidFunctionPointer_t timerCompareMatchFunctionPointer[4];
}timerDinamicData_t;






extern sAPI_FuncPtr_t timerIRQHandlers[4];

/*
timerIRQHandlers[0] = timer0CompareMatchFuncPtr;
timerIRQHandlers[1] = timer1CompareMatchFuncPtr;
timerIRQHandlers[2] = timer2CompareMatchFuncPtr;
timerIRQHandlers[3] = timer3CompareMatchFuncPtr;
*/




/*==================[internal functions declaration]=========================*/
static void errorOcurred(void);
static void doNothing(void);

/*==================[internal data definition]===============================*/

/*Timers Static Data, given by the uC libraries*/
static const timerStaticData_t timer_sd[4] =
{
   {LPC_TIMER0,RGU_TIMER0_RST,TIMER0_IRQn},
   {LPC_TIMER1,RGU_TIMER1_RST,TIMER1_IRQn},
   {LPC_TIMER2,RGU_TIMER2_RST,TIMER2_IRQn},
   {LPC_TIMER3,RGU_TIMER3_RST,TIMER3_IRQn}
};

/*Timers dynamic data. Function pointers and Compare match frequencies, which can vary.
 * This is the default initialization*/
static timerDinamicData_t timer_dd[4] =
{
   {doNothing,errorOcurred,errorOcurred,errorOcurred},
   {doNothing,errorOcurred,errorOcurred,errorOcurred},
   {doNothing,errorOcurred,errorOcurred,errorOcurred},
   {doNothing,errorOcurred,errorOcurred,errorOcurred}
};


/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/* Causes:
 * User forgot to initialize the functions for the compare match interrupt on Timer_init call
 */
static void errorOcurred(void){
   while(1);
}

static void doNothing(void){
}

/*==================[external functions definition]==========================*/




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
                            voidFunctionPointer_t voidFunctionPointer ){
   /* Source:
   http://docs.lpcware.com/lpcopen/v1.03/lpc18xx__43xx_2examples_2periph_2periph__blinky_2blinky_8c_source.html */

   /*If timer period = CompareMatch0 Period = 0 => ERROR*/
   if (ticks==0)
   {
      errorOcurred();
   }

   /* Enable timer clock and reset it */
   Chip_TIMER_Init(timer_sd[timer].name);
   Chip_RGU_TriggerReset(timer_sd[timer].RGU);
   while (Chip_RGU_InReset(timer_sd[timer].RGU)) {}
   Chip_TIMER_Reset(timer_sd[timer].name);

   /* Update the defalut function pointer name of the Compare match 0*/
   timer_dd[timer].timerCompareMatchFunctionPointer[TIMER_COMPARE_MATCH_0] = voidFunctionPointer;

   /* Initialize compare match with the specified ticks (number of counts needed to clear the match counter) */
   Chip_TIMER_MatchEnableInt(timer_sd[timer].name, TIMER_COMPARE_MATCH_0);
   Chip_TIMER_SetMatch(timer_sd[timer].name, TIMER_COMPARE_MATCH_0, ticks);

   /* Makes Timer Match 0 period the timer period*/
   Chip_TIMER_ResetOnMatchEnable(timer_sd[timer].name, TIMER_COMPARE_MATCH_0);

   /*Enable timer*/
   Chip_TIMER_Enable(timer_sd[timer].name);

   /* Enable timer interrupt */
   NVIC_SetPriority(timer_sd[timer].IRQn, MAX_SYSCALL_INTERRUPT_PRIORITY+1);
   NVIC_EnableIRQ(timer_sd[timer].IRQn);
   NVIC_ClearPendingIRQ(timer_sd[timer].IRQn);
}

/*
 * @Brief:  Disables timer peripheral
 * @param:  uint8_t timer: TIMER0 to TIMER3
 * @return: nothing
 */
void timerDeInit(uint8_t timer)
{
   NVIC_DisableIRQ(timer_sd[timer].IRQn);
   Chip_TIMER_Disable(timer_sd[timer].name);
   Chip_TIMER_DeInit(timer_sd[timer].name);
}

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
                              voidFunctionPointer_t voidFunctionPointer ){
   
   timer_dd[timer].timerCompareMatchFunctionPointer[compareMatch] = voidFunctionPointer;

   Chip_TIMER_MatchEnableInt(timer_sd[timer].name, compareMatch);
   Chip_TIMER_SetMatch(timer_sd[timer].name, compareMatch, ticks);
}

/*
 * @Brief:  Disables a compare match of a timer
 * @param:  uint8_t timer: TIMER0 to TIMER3
 * @param:  uint8_t compareMatch: TIMER_COMPARE_MATCH_1 to 
 *                                TIMER_COMPARE_MATCH_3
 * @return: None
 */
void timerCompareMatchDisable( uint8_t timer, uint8_t compareMatch ){
   
   timer_dd[timer].timerCompareMatchFunctionPointer[compareMatch] = errorOcurred;

   Chip_TIMER_ClearMatch(timer_sd[timer].name, compareMatch);
   Chip_TIMER_MatchDisableInt(timer_sd[timer].name, compareMatch);
}

/*
 * @Brief:  Allows the user to change the compare value n? 
 *          'compareMatch' of timer 'timer'.
 *          This is specially useful to generate square waves if used in the 
 *          function for the TIMER_COMPARE_MATCH_0 (because that compare match 
 *          resets the timer counter), which will be passed as a parameter 
 *          when initializing a timer.
 * @note:   The selected time (3rd parameter) must be less than 
 *          TIMER_COMPARE_MATCH_0's compareMatchTime_uS for the compare match to 
 *          make the interruption.
 */
void timerCompareMatchSet( uint8_t timer, uint8_t compareMatch,
                           uint32_t ticks ){
   Chip_TIMER_SetMatch(timer_sd[timer].name, compareMatch,ticks);
}

/*==================[ISR external functions definition]======================*/
/*
 * @Brief:   Executes the functions passed by parameter in the Timer_init,
 *   at the chosen frequencies
 */
 
bool_t timer0CompareMatchFuncPtr( void *ptr ){
   
   uint8_t compareMatch = 0;

   for(compareMatch = TIMER_COMPARE_MATCH_0 ; compareMatch <= TIMER_COMPARE_MATCH_3 ; compareMatch++ ){
      if (Chip_TIMER_MatchPending(LPC_TIMER0, compareMatch)){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER0].timerCompareMatchFunctionPointer[compareMatch])();
         Chip_TIMER_ClearMatch(LPC_TIMER0, compareMatch);
      }
   }
   return 1;
}

bool_t timer1CompareMatchFuncPtr( void *ptr ){
   
   uint8_t compareMatch = 0;

   for(compareMatch = TIMER_COMPARE_MATCH_0 ; compareMatch <= TIMER_COMPARE_MATCH_3 ; compareMatch++ ){
      if (Chip_TIMER_MatchPending(LPC_TIMER1, compareMatch)){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER1].timerCompareMatchFunctionPointer[compareMatch])();
         Chip_TIMER_ClearMatch(LPC_TIMER1, compareMatch);
      }
   }
   return 1;
}

bool_t timer2CompareMatchFuncPtr( void *ptr ){
   
   uint8_t compareMatch = 0;

   for(compareMatch = TIMER_COMPARE_MATCH_0 ; compareMatch <= TIMER_COMPARE_MATCH_3 ; compareMatch++ ){
      if (Chip_TIMER_MatchPending(LPC_TIMER2, compareMatch)){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER2].timerCompareMatchFunctionPointer[compareMatch])();
         Chip_TIMER_ClearMatch(LPC_TIMER2, compareMatch);
      }
   }
   return 1;
}

bool_t timer3CompareMatchFuncPtr( void *ptr ){
   
   uint8_t compareMatch = 0;

   for(compareMatch = TIMER_COMPARE_MATCH_0 ; compareMatch <= TIMER_COMPARE_MATCH_3 ; compareMatch++ ){
      if (Chip_TIMER_MatchPending(LPC_TIMER3, compareMatch)){
         /*Run the functions saved in the timer dynamic data structure*/
         (*timer_dd[TIMER3].timerCompareMatchFunctionPointer[compareMatch])();
         Chip_TIMER_ClearMatch(LPC_TIMER3, compareMatch);
      }
   }
   return 1;
}

/*==================[end of file]============================================*/
