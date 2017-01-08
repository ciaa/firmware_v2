/* Copyright 2015, Eric Pernia.
 * Copyright 2016, Ian Olivieri.
 * Copyright 2016, Eric Pernia.
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

#ifndef _SAPI_PERIPHERALMAP_BOARD_H_
#define _SAPI_PERIPHERALMAP_BOARD_H_

/*==================[inclusions]=============================================*/

#include "sapi_datatypes.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/* ------- Begin EDU-CIAA-NXP Peripheral Map ------ */

/* Defined for sapi_gpio.h */

typedef enum{
   /* EDU-CIAA-NXP */

   // P2 header
// GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8,
   LCD1 = 9, LCD2, LCD3, LCD4, LCDRS, LCDEN,
   ENET_RXD1, ENET_TXEN, ENET_MDC, ENET_RXD0, 
   ENET_CRS_DV, ENET_MDIO, ENET_TXD0, ENET_TXD1,
   SPI_MISO, SPI_MOSI,
   
   // P1 header
   RS232_RXD, RS232_TXD,
   CAN_RD, CAN_TD,
   TFIL0, TFIL1, TFIL2, TFIL3, TCOL0, TCOL1, TCOL2,
   
   // Switches
   // 36     37     38     39
   TEC1,  TEC2,  TEC3,  TEC4,

   // Leds
   // 40     41     42     43     44     45
   LED1,  LED2,  LED3,  LEDR,  LEDG,  LEDB,
}  gpioMapBoard_t;




/* Defined for sapi_adc.h */
typedef enum{
/* 62         63       64        65       */
   AI3 = 62, AI2 = 63, AI1 = 64, AI0 = 65,
             CH3 = 63, CH2 = 64, CH1 = 65
/*  46        47   48  49 */
// AI2 = 46, AI1, AI0, AO
} adcMap_t;

/* Defined for sapi_dac.h */
typedef enum{
/* 66 */
   AO = 66,
   DAC = 66
} dacMap_t;

/* Defined for sapi_uart.h */
typedef enum{
   UART_USB, UART_232, UART_485
} uartMap_t;

/*Defined for sapi_timer.h*/
//NOTE: if servo is enable (servoConfig used) the only available timer to use
// is TIMER0
typedef enum{
   TIMER0, TIMER1, TIMER2, TIMER3
} timerMap_t;
typedef enum{
   TIMERCOMPAREMATCH0, TIMERCOMPAREMATCH1,
   TIMERCOMPAREMATCH2, TIMERCOMPAREMATCH3
} timerCompareMatch_t;

/*Defined for sapi_sct.h*/
// NOTE: CTOUT11 has no SCT mode associated, so it can't be used!
// NOTE: if pwm is enable (pwmConfig used) there will be no sct channels
// available
typedef enum{
   CTOUT0,  CTOUT1,  CTOUT2,  CTOUT3,  CTOUT4,  CTOUT5,  CTOUT6,  CTOUT7,
   CTOUT8,  CTOUT9, CTOUT10, CTOUT11, CTOUT12, CTOUT13
} sctMap_t;

/*Defined for sapi_pwm.h*/
typedef enum{
   PWM0, PWM1, PWM2, PWM3, PWM4, PWM5, PWM6, PWM7, PWM8, PWM9, PWM10
} pwmMap_t;

/*Defined for sapi_servo.h*/
typedef enum{
   SERVO0, SERVO1, SERVO2, SERVO3, SERVO4, SERVO5, SERVO6, SERVO7, SERVO8
} servoMap_t;

/*Defined for sapi_i2c.h*/
/* Comment because already defined in "i2c_18xx_43xx.h"*/
/*
typedef enum{
   I2C0 // TODO: Add support for I2C1
} i2cMap_t;
*/
typedef uint8_t i2cMap_t;



/* ------- Begin CIAA-NXP Peripheral Map ------ */
/*
typedef enum{ 
 // 46     47     48     49     50     51     52     53
   DI0,   DI1,   DI2,   DI3,   DI4,   DI5,   DI6,   DI7,
 // 54     55     56     57     58     59     60     61
   DO0,   DO1,   DO2,   DO3,   DO4,   DO5,   DO6,   DO7
} gpioMapBoard_t;
*/




/* ------- End EDU-CIAA-NXP Peripheral Map -------- */

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_PERIPHERALMAP_BOARD_H_ */
