/* Copyright 2017, Eric Pernia.
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

/* Date: 2017-01-08 */

#ifndef _SAPI_TIMER_H_
#define _SAPI_TIMER_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define timer_STRENGTH(n)    ( (n) << 4 )
#define timer_SPEED(n)       ( (n) << 7 )

/*==================[typedef]================================================*/

/* timer Config enum type */
/*
timerConfig_t[15:0] bits = power[15], event[14:10], speed[9:7], mode[6:0]

event[14:10] bits = falling[14], rising[13], asynch_edge[12], edge[11], 
                    level[10]

mode[6:0] bits = strength[6:4], open_drain[3], pull_down[2], pull_up[1], 
                 input_output[0]
*/
typedef enum{
   timer_INPUT                    = 1,
      timer_NOPULL                = 0, // default value with timer_INPUT
      timer_PULLUP                = (1<<1),
      timer_PULLDOWN              = (1<<2),
      timer_PULLUPDOWN            = timer_PULLUP | timer_PULLDOWN,
         timer_INPUT_PULLUP       = timer_INPUT | timer_PULLUP,
         timer_INPUT_PULLDOWN     = timer_INPUT | timer_PULLDOWN,
         timer_INPUT_PULL_UP_DOWN = timer_INPUT | timer_PULLUP | timer_PULLDOWN,
   timer_OUTPUT                   = 0,
      timer_PUSHPULL              = 0, // default value with timer_OUTPUT
      timer_OPENDRAIN             = (1<<3),
      timer_OPENCOLLECTOR         = timer_OPENDRAIN,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH1 = 128,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH2 = 256,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH3 = 384,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH4 = 512,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH5 = 640,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH6 = 768,
         timer_OUTPUT_timer_PUSHPULL_timer_STRENGTH7 = 896,
         timer_OUTPUT_OPENDRAIN_PULLUP = timer_OUTPUT|timer_OPENDRAIN|timer_PULLUP,
   timer_LEVEL                    = (1<<10),
      timer_LEVEL_HIGH            = (1<<13),
      timer_LEVEL_LOW             = (1<<14),
   timer_EDGE                     = (1<<11),
   timer_ASYNCHRONOUS_EDGE        = (1<<12),
      timer_EDGE_RISING           = timer_LEVEL_HIGH,
      timer_EDGE_FALLING          = timer_LEVEL_LOW,
   timer_POWER_ON                 = (1<<15),
   timer_POWER_OFF                = (0<<15),

   COUNT_TO_OVERFLOW, COUNT_TO_MATCH,
   INPUT_PULSE_CAPTURE, 
   OUTPUT_SIGNAL_GENERATOR, PWM

} timerConfig_t;


/* timer instance struct type */
typedef struct{
   timerConfig_t config;
   Callback_t   eventCallback;
} Timer_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/* ----------------- Initialize method ----------------- */

void timerInitialize( void );

/* ------ Properties getters and setters methods ------- */

// mode
void timerSetMode( timerName_t timerName, timerConfig_t mode );
timerConfig_t timerGetMode( timerName_t timerName );
// speed
void timerSetSpeed( timerName_t timerName, timerConfig_t speed );
timerConfig_t timerGetSpeed( timerName_t timerName );
// power
void timerSetPower( timerName_t timerName, timerConfig_t power );
timerConfig_t timerGetPower( timerName_t timerName );

// event
void timerSetEvent( timerName_t timerName, timerConfig_t event );
timerConfig_t timerGetEvent( timerName_t timerName );
// eventCallback
void timerSetEventCallback( timerName_t timerName, Callback_t callback );
//Callback_t timerGetEventCallback( timerName_t timerName );

// value
void timerSetValue( timerName_t timerName, bool_t value );
bool_t timerGetValue( timerName_t timerName );


/* ------------------- Action methods ------------------ */

// Config
void timerConfig( timerName_t timerName, timerConfig_t config );

// Group of timers Config
void timerGroupConfig( timerName_t* timerNames, 
                      uint8_t timerNamesSize, 
                      timerConfig_t config );

// Write a timer
void timerWrite( timerName_t timerName, bool_t value );

// Read a timer
bool_t timerRead( timerName_t timerName );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_TIMER_H_ */
