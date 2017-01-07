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

#define GPIO_SPEED(n)      ( (n) << 4 )
#define GPIO_STRENGTH(n)   ( (n) << 7 )

/*==================[typedef]================================================*/

/* GPIO configuration struct */
typedef uint16_t gpioConfig_t;

/* GPIO struct */
typedef struct{
   gpioConfig_t config;
   Callback_t eventCallback;
} Gpio_t;

#define GPIO_NULL { 0, { 0, 0 } }

/*
   config
      mode;
      speed;
      power;
      value;
      event;

   eventCallback; //struct

p event  spe   mode
1 11111
5 43210 987 654 3210
P FRAEL 00s 00s OPPI
o aisde   p   t p /
w lsygv   e   r eDUO
e linee   e   e nop
r inc l   d   n  w
  ngh         g dn
  g r         h r
             t
000000 000 000 0000 val

*/

/* GPIO Config Struct */
typedef enum{
   GPIO_INPUT             = 1,
      GPIO_NOPULL         = 0, // default value with GPIO_INPUT
      GPIO_PULLUP         = (1<<1),
      GPIO_PULLDOWN       = (1<<2),
      GPIO_PULLUPDOWN     = GPIO_PULLUP | GPIO_PULLDOWN,
   GPIO_OUTPUT            = 0,
      GPIO_PUSHPULL       = 0, // default value with GPIO_OUTPUT
      GPIO_OPENCOLLECTOR  = (1<<3),
      GPIO_OPENDRAIN      = GPIO_OPENCOLLECTOR,
   GPIO_LEVEL             = (1<<10),
      GPIO_LEVEL_HIGH     = (1<<13),
      GPIO_LEVEL_LOW      = (1<<14),
   GPIO_EDGE              = (1<<11),
   GPIO_ASYNCHRONOUS_EDGE = (1<<12),
      GPIO_EDGE_RISING    = GPIO_LEVEL_HIGH,
      GPIO_EDGE_FALLING   = GPIO_LEVEL_LOW,
   GPIO_POWER_ON          = (1<<15),
   GPIO_POWER_OFF         = (0<<15),
} gpioConfig_t;


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/* Properties getters and setters */

// mode
void gpioSetMode( gpioMap_t gpioNumber, gpioConfig_t mode );
gpioConfig_t gpioGetMode( gpioMap_t gpioNumber );
// speed
void gpioSetSpeed( gpioMap_t gpioNumber, gpioConfig_t speed );
gpioConfig_t gpioGetSpeed( gpioMap_t gpioNumber );
// power
void gpioSetPower( gpioMap_t gpioNumber, gpioConfig_t power );
gpioConfig_t gpioGetPower( gpioMap_t gpioNumber );

// event
void gpioSetEvent( gpioMap_t gpioNumber, gpioConfig_t event );
gpioConfig_t gpioGetEvent( gpioMap_t gpioNumber );
// eventCallback
void gpioSetEventCallback( gpioMap_t gpioNumber, Callback_t callback );
Callback_t gpioGetEventCallback( gpioMap_t gpioNumber );

// value
void gpioSetValue( gpioMap_t gpioNumber, bool_t value );
bool_t gpioGetValue( gpioMap_t gpioNumber );


/* Methods */

bool_t gpioConfig( gpioMap_t gpioNumber, gpioConfig_t config );
bool_t gpioRead( gpioMap_t gpioNumber );
void gpioWrite( gpioMap_t gpioNumber, bool_t value );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_GPIO_H_ */
