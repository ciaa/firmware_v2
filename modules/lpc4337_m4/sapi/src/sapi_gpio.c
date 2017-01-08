/* Copyright 2015-2016, Eric Pernia.
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

/* Date: 2015-09-23 */

/*==================[inclusions]=============================================*/

#include "sapi_gpio.h"

/*==================[macros and definitions]=================================*/

#define GPIO_MODE_MASK    0x7F
#define GPIO_SPEED_MASK   0x380
#define GPIO_EVENT_MASK   0x7C00
#define GPIO_POWER_MASK   0x8000

#define GPIO_SET_CONFIG_PROPERTY( gpioName, property , mask ) gpioInstances[(gpioName)].config = (gpioInstances[(gpioName)].config & ~(mask)) | ((property) & (mask)) 

#define GPIO_GET_CONFIG_PROPERTY( gpioName, mask ) gpioInstances[(gpioName)].config & (mask)

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

static Gpio_t gpioInstances[GPIO_INSTANCES_SIZE];

// EDU-CIAA-NXP
static const pinConfigGpioLpc4337_t gpioPinsConfig[] = {

 // LPC4337 internal:
 // { {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }

 /* ------------------------------------------------------------------ */
 /*                             EDU-CIAA-NXP                           */
 /* -----------------------------+--------+-----------+--------------- */
 /*      LPC4337 internal        |  sAPI  | Connector | Serigraphy     */
 /* -----------------------------+--------+-----------+--------------- */
   { {6, 1}, FUNC0, {3, 0} },   //  GPIO0 | CON2_29   |  GPIO0
   { {6, 4}, FUNC0, {3, 3} },   //  GPIO1 | CON2_32   |  GPIO1
   { {6, 5}, FUNC0, {3, 4} },   //  GPIO2 | CON2_31   |  GPIO2
   { {6, 7}, FUNC4, {5,15} },   //  GPIO3 | CON2_34   |  GPIO3
   { {6, 8}, FUNC4, {5,16} },   //  GPIO4 | CON2_33   |  GPIO4
   { {6, 9}, FUNC0, {3, 5} },   //  GPIO5 | CON2_36   |  GPIO5
   { {6,10}, FUNC0, {3, 6} },   //  GPIO6 | CON2_35   |  GPIO6
   { {6,11}, FUNC0, {3, 7} },   //  GPIO7 | CON2_38   |  GPIO7
   { {6,12}, FUNC0, {2, 8} },   //  GPIO8 | CON2_40   |  GPIO8
                                //        |           |  
   { {4, 4}, FUNC0, {2, 4} },   //  GPIO9 | CON2_30   |  LCD1
   { {4, 5}, FUNC0, {2, 5} },   // GPIO10 | CON2_28   |  LCD2
   { {4, 6}, FUNC0, {2, 6} },   // GPIO11 | CON2_26   |  LCD3
   { {4,10}, FUNC4, {5,14} },   // GPIO12 | CON2_22   |  LCD4
   { {4, 8}, FUNC4, {5,12} },   // GPIO13 | CON2_24   |  LCDRS
   { {4, 9}, FUNC4, {5,13} },   // GPIO14 | CON2_23   |  LCDEN
                                //        |           |  
   { {0, 0}, FUNC0, {0, 0} },   // GPIO15 | CON2_04   |  ENET_RXD1
   { {0, 1}, FUNC0, {0, 1} },   // GPIO16 | CON2_06   |  ENET_TXEN
   { {7, 7}, FUNC0, {3,15} },   // GPIO17 | CON2_08   |  ENET_MDC
   { {1,15}, FUNC0, {0, 2} },   // GPIO18 | CON2_09   |  ENET_RXD0
   { {1,16}, FUNC0, {0, 3} },   // GPIO19 | CON2_10   |  ENET_CRS_DV
   { {1,17}, FUNC0, {0,12} },   // GPIO20 | CON2_12   |  ENET_MDIO
   { {1,18}, FUNC0, {0,13} },   // GPIO21 | CON2_14   |  ENET_TXD0
   { {1,20}, FUNC0, {0,15} },   // GPIO22 | CON2_16   |  ENET_TXD1
                                //        |           |  
   { {1, 3}, FUNC0, {0,10} },   // GPIO23 | CON2_18   |  SPI_MISO
   { {1, 4}, FUNC0, {0,11} },   // GPIO24 | CON2_21   |  SPI_MOSI
                                //        |           |  
                                //        |           |  
   { {2, 4}, FUNC4, {5, 4} },   // GPIO25 | CON1_23   |  RS232_RXD
   { {2, 3}, FUNC4, {5, 3} },   // GPIO26 | CON1_25   |  RS232_TXD
                                //        |           |  
   { {3, 1}, FUNC4, {5, 8} },   // GPIO27 | CON1_27   |  CAN_RD
   { {3, 2}, FUNC4, {5, 9} },   // GPIO28 | CON1_29   |  CAN_TD
                                //        |           |  
   { {4, 0}, FUNC0, {2, 0} },   // GPIO29 | CON1_33   |  T_FIL0
   { {4, 1}, FUNC0, {2, 1} },   // GPIO30 | CON1_36   |  T_FIL1
   { {4, 2}, FUNC0, {2, 2} },   // GPIO31 | CON1_37   |  T_FIL2
   { {4, 3}, FUNC0, {2, 3} },   // GPIO32 | CON1_35   |  T_FIL3
   { {1, 5}, FUNC0, {1, 8} },   // GPIO33 | CON1_39   |  T_COL0
   { {7, 4}, FUNC0, {3,12} },   // GPIO34 | CON1_31   |  T_COL1
   { {7, 5}, FUNC0, {3,13} },   // GPIO35 | CON1_34   |  T_COL2
                                //        |           |  
                                //        |           |  
   { {1, 0}, FUNC0, {0, 4} },   // GPIO36 | TEC1      |  TEC1
   { {1, 1}, FUNC0, {0, 8} },   // GPIO37 | TEC2      |  TEC2
   { {1, 2}, FUNC0, {0, 9} },   // GPIO38 | TEC3      |  TEC3
   { {1, 6}, FUNC0, {1, 9} },   // GPIO39 | TEC4      |  TEC4
                                //        |           |  
   { {2,10}, FUNC0, {0,14} },   // GPIO40 | LED1      |  LED1
   { {2,11}, FUNC0, {1,11} },   // GPIO41 | LED2      |  LED2
   { {2,12}, FUNC0, {1,12} },   // GPIO42 | LED3      |  LED3
   { {2, 0}, FUNC4, {5, 0} },   // GPIO43 | LEDR      |  LEDR
   { {2, 1}, FUNC4, {5, 1} },   // GPIO44 | LEDG      |  LEDG
   { {2, 2}, FUNC4, {5, 2} }    // GPIO45 | LEDB      |  LEDB
};


/*

// CIAA-NXP
const pinConfigGpioLpc4337_t gpioPinsConfig[] = {

 // LPC4337 internal:
 // { {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }

*/

 /*{ {PinNamePortN ,PinNamePinN}, PinFUNC, {GpioPortN, GpioPinN} }*/
 /* ------------------------------------------------------------------ */
 /*                             CIAA-NXP                               */
 /* -----------------------------+--------+-----------+--------------- */
 /*      LPC4337 internal        |  sAPI  | Connector | Serigraphy     */
 /* -----------------------------+--------+-----------+--------------- */
/*   { {4, 0}, FUNC0, {2, 0} },   //  GPIO0 | BORN_24   |   DIN0
   { {4, 1}, FUNC0, {2, 1} },   //  GPIO1 | BORN_25   |   DIN1
   { {4, 2}, FUNC0, {2, 2} },   //  GPIO2 | BORN_26   |   DIN2
   { {4, 3}, FUNC0, {2, 3} },   //  GPIO3 | BORN_27   |   DIN3
   { {7, 3}, FUNC0, {3,11} },   //  GPIO4 | BORN_28   |   DIN4
   { {7, 4}, FUNC0, {3,12} },   //  GPIO5 | BORN_29   |   DIN5
   { {7, 5}, FUNC0, {3,13} },   //  GPIO6 | BORN_30   |   DIN6
   { {7, 6}, FUNC0, {3,14} },   //  GPIO7 | BORN_31   |   DIN7
                                //        |           |  
   { {2, 1}, FUNC4, {5, 1} },   //  GPIO8 | BORN_14   |   DOUT0
   { {4, 6}, FUNC0, {2, 6} },   //  GPIO9 | BORN_06   |   DOUT1
   { {4, 5}, FUNC0, {2, 5} },   // GPIO10 | BORN_08   |   DOUT2
   { {4, 4}, FUNC0, {2, 4} },   // GPIO10 | BORN_10   |   DOUT3
   { {4, 8}, FUNC4, {5,12} },   // GPIO10 | BORN_14   |   DOUT4
   { {4, 9}, FUNC4, {5,13} },   // GPIO10 | BORN_15   |   DOUT5
   { {4,10}, FUNC4, {5,14} },   // GPIO10 | BORN_16   |   DOUT6
   { {1, 5}, FUNC0, {1, 8} }    // GPIO10 | BORN_17   |   DOUT7
};
*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/* ----------------- Initialize method ----------------- */

void gpioInitialize( void ){

   uint32_t i;

   for( i=0; i<GPIO_INSTANCES_SIZE; i++ ){
      gpioInstances[i].config = GPIO_POWER_MASK;
   }
}

/* ------ Properties getters and setters methods ------- */

// mode
void gpioSetMode( gpioName_t gpioName, gpioConfig_t mode ){

   int8_t pinNamePort = gpioPinsConfig[gpioName].pinName.port;
   int8_t pinNamePin  = gpioPinsConfig[gpioName].pinName.pin;

   int8_t func        = gpioPinsConfig[gpioName].func;

   int8_t gpioPort    = gpioPinsConfig[gpioName].gpio.port;
   int8_t gpioPin     = gpioPinsConfig[gpioName].gpio.pin;

   GPIO_SET_CONFIG_PROPERTY( gpioName, mode, GPIO_MODE_MASK );
   
   switch( mode & GPIO_MODE_MASK ){

      case GPIO_INPUT:
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), 0 );
      break;

      case (GPIO_INPUT | GPIO_PULLUP):
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), 0 );
      break;

      case (GPIO_INPUT | GPIO_PULLDOWN):
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_PULLDOWN | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), 0 );
      break;
      case (GPIO_INPUT | GPIO_PULLUP | GPIO_PULLDOWN):
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_REPEATER | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), 0 );
      break;

      case GPIO_OUTPUT:
      //case (GPIO_OUTPUT | GPIO_PUSHPULL):
      //case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(0)):
      // TODO: Set stenght in real board
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(1)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(2)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(3)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(4)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(5)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(6)):
      case (GPIO_OUTPUT | GPIO_PUSHPULL | GPIO_STRENGTH(7)):
      case (GPIO_OUTPUT | GPIO_OPENDRAIN): // TODO: Set in real board
      case (GPIO_OUTPUT | GPIO_OPENDRAIN | GPIO_PULLUP): // TODO: Set in real board
         Chip_SCU_PinMux(
            pinNamePort,
            pinNamePin,
            SCU_MODE_INACT | SCU_MODE_ZIF_DIS,
            func
         );
         Chip_GPIO_SetDir( LPC_GPIO_PORT, gpioPort, ( 1 << gpioPin ), 1 );
         Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, 0);
      break;

      default:
         while(1); // Error de configuración
      break;
   }

}

gpioConfig_t gpioGetMode( gpioName_t gpioName ){
   return GPIO_GET_CONFIG_PROPERTY( gpioName, GPIO_MODE_MASK );
}

// speed
void gpioSetSpeed( gpioName_t gpioName, gpioConfig_t speed ){
   GPIO_SET_CONFIG_PROPERTY( gpioName, speed, GPIO_SPEED_MASK );
   // TODO: Set in real board
}

gpioConfig_t gpioGetSpeed( gpioName_t gpioName ){
   return GPIO_GET_CONFIG_PROPERTY( gpioName, GPIO_SPEED_MASK );
}

// power
void gpioSetPower( gpioName_t gpioName, gpioConfig_t power ){
   GPIO_SET_CONFIG_PROPERTY( gpioName, power, GPIO_POWER_MASK );
   // TODO: Set in real board
}

gpioConfig_t gpioGetPower( gpioName_t gpioName ){
   return GPIO_GET_CONFIG_PROPERTY( gpioName, GPIO_POWER_MASK );
}

// event
void gpioSetEvent( gpioName_t gpioName, gpioConfig_t event ){
   GPIO_SET_CONFIG_PROPERTY( gpioName, event, GPIO_EVENT_MASK );
   // TODO: Set in real board
}

gpioConfig_t gpioGetEvent( gpioName_t gpioName ){
   return GPIO_GET_CONFIG_PROPERTY( gpioName, GPIO_EVENT_MASK );
}

// eventCallback
void gpioSetEventCallback( gpioName_t gpioName, Callback_t callback ){
   

   // TODO: Set in real board
}

/*
Callback_t gpioGetEventCallback( gpioName_t gpioName ){
   return 0;
}*/


// value
void gpioSetValue( gpioName_t gpioName, bool_t value ){

   int8_t gpioPort    = gpioPinsConfig[gpioName].gpio.port;
   int8_t gpioPin     = gpioPinsConfig[gpioName].gpio.pin;

   Chip_GPIO_SetPinState( LPC_GPIO_PORT, gpioPort, gpioPin, value);
}

bool_t gpioGetValue( gpioName_t gpioName ){

   bool_t ret_val     = OFF;

   int8_t gpioPort    = gpioPinsConfig[gpioName].gpio.port;
   int8_t gpioPin     = gpioPinsConfig[gpioName].gpio.pin;

   ret_val = (bool_t) Chip_GPIO_ReadPortBit( LPC_GPIO_PORT, gpioPort, gpioPin );

   return ret_val;
}


/* ------------------- Action methods ------------------ */

// Config
void gpioConfig( gpioName_t gpioName, gpioConfig_t config ){

   gpioSetMode( gpioName, config );
   gpioSetSpeed( gpioName, config );
   //gpioSetPower( gpioName, config );
}

// Group of GPIOs Config
void gpioGroupConfig( gpioName_t* gpioNames, 
                      uint8_t gpioNamesSize, 
                      gpioConfig_t config ){

   uint32_t i;

   for( i=0; i<gpioNamesSize; i++ )
      gpioConfig( gpioNames[i], config );
}

// Write a GPIO
void gpioWrite( gpioName_t gpioName, bool_t value ){
   gpioSetValue( gpioName, value );
}

// Read a GPIO
bool_t gpioRead( gpioName_t gpioName ){
   return gpioGetValue( gpioName );
}

/*==================[end of file]============================================*/
