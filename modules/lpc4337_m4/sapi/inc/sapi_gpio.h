/* Copyright 2015-2016, Eric Pernia.
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

/* Date: 2015-09-23 */

#ifndef _SAPI_GPIO_H_
#define _SAPI_GPIO_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"
#include "sapi_peripheral_map.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define GPIO_STRENGTH(n)    ( (n) << 4 )
#define GPIO_SPEED(n)       ( (n) << 7 )

/*==================[typedef]================================================*/

/* GPIO Config enum type */
/*
gpioConfig_t[15:0] bits = power[15], event[14:10], speed[9:7], mode[6:0]

event[14:10] bits = falling[14], rising[13], asynch_edge[12], edge[11], 
                    level[10]

mode[6:0] bits = strength[6:4], open_drain[3], pull_down[2], pull_up[1], 
                 input_output[0]
*/
typedef enum{
   GPIO_INPUT                    = 1,
      GPIO_NOPULL                = 0, // default value with GPIO_INPUT
      GPIO_PULLUP                = (1<<1),
      GPIO_PULLDOWN              = (1<<2),
      GPIO_PULLUPDOWN            = GPIO_PULLUP | GPIO_PULLDOWN,
         GPIO_INPUT_PULLUP       = GPIO_INPUT | GPIO_PULLUP,
         GPIO_INPUT_PULLDOWN     = GPIO_INPUT | GPIO_PULLDOWN,
         GPIO_INPUT_PULL_UP_DOWN = GPIO_INPUT | GPIO_PULLUP | GPIO_PULLDOWN,
   GPIO_OUTPUT                   = 0,
      GPIO_PUSHPULL              = 0, // default value with GPIO_OUTPUT
      GPIO_OPENDRAIN             = (1<<3),
      GPIO_OPENCOLLECTOR         = GPIO_OPENDRAIN,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH1 = 128,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH2 = 256,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH3 = 384,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH4 = 512,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH5 = 640,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH6 = 768,
         GPIO_OUTPUT_GPIO_PUSHPULL_GPIO_STRENGTH7 = 896,
         GPIO_OUTPUT_OPENDRAIN_PULLUP = GPIO_OUTPUT|GPIO_OPENDRAIN|GPIO_PULLUP,
   GPIO_LEVEL                    = (1<<10),
      GPIO_LEVEL_HIGH            = (1<<13),
      GPIO_LEVEL_LOW             = (1<<14),
   GPIO_EDGE                     = (1<<11),
   GPIO_ASYNCHRONOUS_EDGE        = (1<<12),
      GPIO_EDGE_RISING           = GPIO_LEVEL_HIGH,
      GPIO_EDGE_FALLING          = GPIO_LEVEL_LOW,
   GPIO_POWER_ON                 = (1<<15),
   GPIO_POWER_OFF                = (0<<15)
} gpioConfig_t;


/* GPIO instance struct type */
typedef struct{
   gpioConfig_t config;
   Callback_t   eventCallback;
} Gpio_t;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/* ----------------- Initialize method ----------------- */

void gpioInitialize( void );

/* ------ Properties getters and setters methods ------- */

// mode
void gpioSetMode( gpioName_t gpioName, gpioConfig_t mode );
gpioConfig_t gpioGetMode( gpioName_t gpioName );
// speed
void gpioSetSpeed( gpioName_t gpioName, gpioConfig_t speed );
gpioConfig_t gpioGetSpeed( gpioName_t gpioName );
// power
void gpioSetPower( gpioName_t gpioName, gpioConfig_t power );
gpioConfig_t gpioGetPower( gpioName_t gpioName );

// event
void gpioSetEvent( gpioName_t gpioName, gpioConfig_t event );
gpioConfig_t gpioGetEvent( gpioName_t gpioName );
// eventCallback
void gpioSetEventCallback( gpioName_t gpioName, Callback_t callback );
//Callback_t gpioGetEventCallback( gpioName_t gpioName );

// value
void gpioSetValue( gpioName_t gpioName, bool_t value );
bool_t gpioGetValue( gpioName_t gpioName );


/* ------------------- Action methods ------------------ */

// Config
void gpioConfig( gpioName_t gpioName, gpioConfig_t config );

// Group of GPIOs Config
void gpioGroupConfig( gpioName_t* gpioNames, 
                      uint8_t gpioNamesSize, 
                      gpioConfig_t config );

// Write a GPIO
void gpioWrite( gpioName_t gpioName, bool_t value );

// Read a GPIO
bool_t gpioRead( gpioName_t gpioName );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_GPIO_H_ */
