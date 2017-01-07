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

/* GPIO struct */
typedef struct{
   mode;
   speed;
   power;
   value;
   event;
   eventCallback;
} gpio_t;

/* Pin modes */
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
      GPIO_EDGE_FALLING   = GPIO_LEVEL_LOW
} gpioConfig_t;

/*

       str spd mode
111111
543210 987 654 3210
xFRAEL 00s 00s OPPI
 aisde   t   p p /
 lsygv   r   e eDUO
 linee   e   e nop
 inc l   n   d  w
 ngh     g     dn
 g r     h     r
000000 000 000 0000 val

*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

bool_t gpioConfig( gpioMap_t pin, gpioConfig_t config );
bool_t gpioRead( gpioMap_t pin );
bool_t gpioWrite( gpioMap_t pin, bool_t value );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_GPIO_H_ */
