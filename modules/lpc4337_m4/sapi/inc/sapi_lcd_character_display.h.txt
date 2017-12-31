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

/* Date: 2017-12-05 */

#ifndef _SAPI_LCD_H_
#define _SAPI_LCD_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"        // <= Biblioteca sAPI

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

// LCD Char Display pins

#define LCD_CHAR_RS                 LCDRS // Define MCU pin connected to LCD
                                          // RS. RS = 0 to select command 
                                          // register, RS = 1 to select  
                                          // data register.

#define LCD_CHAR_EN                 LCDEN // Define MCU pin connected to LCD RS
                                          // Enable.

#define LCD_CHAR_RW                 0     // Define MCU pin connected to LCD
                                          // R/W. R/W = 0 for write, R/W = 1
                                          // for read. Must Connect to GND in 
                                          // 3.3V MCUs.

#define LCD_CHAR_D0                 0     // Define MCU pin connected to LCD D0.
                                          // Not used in 4-bit mode.
#define LCD_CHAR_D1                 0     // Define MCU pin connected to LCD D1.
                                          // Not used in 4-bit mode.
#define LCD_CHAR_D2                 0     // Define MCU pin connected to LCD D2.
                                          // Not used in 4-bit mode.
#define LCD_CHAR_D3                 0     // Define MCU pin connected to LCD D3.
                                          // Not used in 4-bit mode.

#define LCD_CHAR_D4                 LCD1  // Define MCU pin connected to LCD D4.
#define LCD_CHAR_D5                 LCD2  // Define MCU pin connected to LCD D5.
#define LCD_CHAR_D6                 LCD3  // Define MCU pin connected to LCD D6.
#define LCD_CHAR_D7                 LCD4  // Define MCU pin connected to LCD D7.


#define LDP  configLCD_DATA_PORT	    // Define MCU port connected to LCD data pins
#define LCP  configLCD_CONTROL_PORT	 // Define MCU port connected to LCD control pins
#define LDDR configLCD_DATA_REG	    // Define MCU direction register for port connected to LCD data pins
#define LCDR configLCD_CONTROL_REG	 // Define MCU direction register for port connected to LCD control pins





// Reading:
#define LCD_BUSY            7   // DB7: LCD is busy
#define LCD_LINES           4   // visible lines
#define LCD_LINE_LENGTH		20	  // line length (in characters)

// Cursor position to DDRAM mapping
#define LCD_LINE0_DDRAMADDR		0x00
#define LCD_LINE1_DDRAMADDR		0x40
#define LCD_LINE2_DDRAMADDR		0x14
#define LCD_LINE3_DDRAMADDR		0x54

// Progress bar defines
#define LCD_CHAR_PROG_PIXELS        6     // PROGRESSPIXELS_PER_CHAR 


// LCD Char Display delay Times

#define LCD_CHAR_EN_PULSE_WAIT_US   25    // 25 us
#define LCD_CHAR_LOW_WAIT_US        25    // 25 us
#define LCD_CHAR_HIGH_WAIT_US       100   // 100 us

#define LCD_CHAR_CMD_WAIT_US        45    // Wait time for every command 45 us, except:
#define LCD_CHAR_CLR_DISP_WAIT_MS   2     // - Clear Display 1.52 ms
#define LCD_CHAR_RET_HOME_WAIT_MS   2     // - Return Home  1.52 ms
                                          // - Read Busy flag and address 0 us

#define LCD_STARTUP_WAIT_MS    3000  // 3000 ms

// LCD delay HAL
#define lcdDelay_ms(duration)       delay(duration)
#define lcdDelay_us(duration)       delayInaccurateUs(duration) //delayUs(duration)
#define lcdCommandDelay()           lcdDelay_us(LCD_CMD_WAIT_US)
#define lcdConfigPinAsOutput(pin)   gpioConfig( (pin), GPIO_OUTPUT );
#define lcdPinWrite( pin, value )   gpioWrite( (pin), (value) )

/*==================[typedef]================================================*/

// Enumeration defining the HD44780 commands
typedef enum{
   // Clear display. 
   // Clears entire display and sets DDRAM address 0 in address counter.
	LCD_CHAR_CMD_CLEAR_DISPLAY          = 0x01,
   
   // Return home.
   // Sets DDRAM address 0 in address counter. Also returns display from being
   // shifted to original position. DDRAM contents remain unchanged.
	LCD_CHAR_CMD_RETURN_HOME            = 0x02,
   
   // Entry mode set.
   // Sets cursor move direction and specifies display shift. These operations
   // are performed during data write and read.
	LCD_CHAR_CMD_ENTRY_MODE_SET         = 0x04,
	LCD_CHAR_CMD_ENTRY_MODE_SET_INC     = (1<<1),   // Increment
	LCD_CHAR_CMD_ENTRY_MODE_SET_DEC     = (0<<1),   // Decrement
	LCD_CHAR_CMD_ENTRY_MODE_SET_SHIFT   = (1<<0),   // Accompanies display shift
   
   // Display on/off control.
   // Sets entire display (D) on/off, cursor on/off (C), and blinking of cursor
   // position character (B).
	LCD_CHAR_CMD_DISP_ON_OFF_CTRL       = 0x08,
	LCD_CHAR_CMD_DISP_ON_OFF_CTRL_D     = (1<<2),   // Display on
	LCD_CHAR_CMD_DISP_ON_OFF_CTRL_C     = (1<<1),   // Cursor on
	LCD_CHAR_CMD_DISP_ON_OFF_CTRL_B     = (1<<0),   // Blinking of cursor
   
   // Cursor or display shift.
   // Moves cursor and shifts display without changing DDRAM contents.
	LCD_CHAR_CMD_CURSOR_DISPLAY_SHIFT   = 0x10,
	LCD_CHAR_CMD_CURSOR_DISPLAY_SHIFT_D = (1<<3),   // Display shift
	LCD_CHAR_CMD_CURSOR_DISPLAY_SHIFT_C = (0<<3),   // Cursor move
	LCD_CHAR_CMD_CURSOR_DISPLAY_SHIFT_R = (1<<2),   // Shift to the right
	LCD_CHAR_CMD_CURSOR_DISPLAY_SHIFT_L = (0<<2),   // Shift to the left
   
   // Function set.
   // Sets interface data length (DL), number of display lines (N), and
   // character font (F).
	LCD_CHAR_CMD_FUNCTION_SET           = 0x20,
	LCD_CHAR_CMD_FUNCTION_SET_DL_8      = (1<<4),   // DL=1: 8 bits
	LCD_CHAR_CMD_FUNCTION_SET_DL_4      = (0<<4),   // DL=0: 4 bits
	LCD_CHAR_CMD_FUNCTION_SET_N_2       = (1<<3),   // N=1: 2 lines
	LCD_CHAR_CMD_FUNCTION_SET_N_1       = (0<<3),   // N=0: 1 line
	LCD_CHAR_CMD_FUNCTION_SET_F_5X10    = (1<<2),   // F=1: 5x10 dots
	LCD_CHAR_CMD_FUNCTION_SET_F_5X8     = (0<<2),   // F=0: 5x8 dots
   
#define LCD_FUNCTION_8BIT   4      // DB4: set 8BIT mode (0->4BIT mode)
#define LCD_FUNCTION_2LINES 3      // DB3: two lines (0->one line)
#define LCD_FUNCTION_10DOTS 2      // DB2: 5x10 font (0->5x7 font)
   
	LCD_CHAR_CMD_SET_CGRAM_ADDR       = 0x40,   // DB6: set CG RAM address.
	LCD_CHAR_CMD_SET_DDRAM_ADDR       = 0x80    // DB7: set DD RAM address.
}lcdCharDisplayCommands_t;


#define LCD_ON_CTRL         3      // DB3: turn lcd/cursor on
#define LCD_ON_DISPLAY      2      // DB2: turn display on
#define LCD_ON_CURSOR       1      // DB1: turn cursor on
#define LCD_ON_BLINK        0      // DB0: blinking cursor

#define LCD_MOVE            4      // DB4: move cursor/display
#define LCD_MOVE_DISP       3      // DB3: move display (0-> move cursor)
#define LCD_MOVE_RIGHT      2      // DB2: move right (0-> left)



// Enumeration defining the HD44780 available cursor modes
typedef enum{
	LCD_CHAR_CURSOR_OFF               = 0x00,
	LCD_CHAR_CURSOR_ON                = 0x02,
	LCD_CHAR_CURSOR_ON_BLINK          = 0x03
}lcdCharDisplayCursorModes_t;


/*
 * Flex_LCD420_CIAA.h
 *
 *  Created on: 5 de jul. de 2016
 *      Author: benitezjuandedios
 */

// These are the line addresses for most 4x20 LCDs.
/*
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x40
#define LCD_LINE_3_ADDRESS 0x14
#define LCD_LINE_4_ADDRESS 0x54
*/

// These are the line addresses for LCD's which use
// the Hitachi HD66712U controller chip.
/*
#define LCD_LINE_1_ADDRESS 0x00
#define LCD_LINE_2_ADDRESS 0x20
#define LCD_LINE_3_ADDRESS 0x40
#define LCD_LINE_4_ADDRESS 0x60
*/


//*****************************************************************************
//
// File Name	: 'lcd_lib.h'
// Title		: 8 and 4 bit LCd interface
// Author		: Scienceprog.com - Copyright (C) 2007
// Created		: 2007-03-29
// Revised		: 2007-08-08
// Version		: 1.0
// Target MCU	: Atmel AVR series
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t);//copies flash string to LCD at x,y
void LCDdefinechar(const uint8_t *,uint8_t);//write char to LCD CGRAM
void LCDshiftRight(uint8_t);	//shift by n characters Right
void LCDshiftLeft(uint8_t);	//shift by n characters Left
void LCDcursorOn(void);		//Underline cursor ON
void LCDcursorOnBlink(void);	//Underline blinking cursor ON
void LCDcursorOFF(void);		//Cursor OFF
void LCDblank(void);			//LCD blank but not cleared
void LCDvisible(void);			//LCD visible
void LCDcursorLeft(uint8_t);	//Shift cursor left by n
void LCDcursorRight(uint8_t);	//shif cursor right by n

// displays a horizontal progress bar at the current cursor location
// <progress> is the value the bargraph should indicate
// <maxprogress> is the value at the end of the bargraph
// <length> is the number of LCD characters that the bargraph should cover
//adapted from AVRLIB - displays progress only for 8 bit variables
void LCDprogressBar(uint8_t progress, uint8_t maxprogress, uint8_t length);


// ------------------ LCD commands ------------------

void lcdCharDisplayCommand( uint8_t cmd );

void lcdCharDisplayData( uint8_t data );

// Initializes LCD
void lcdCharDisplayInit( uint16_t lineWidth, uint16_t amountOfLines,
                         uint16_t charWidth, uint16_t charHeight );


// ------------------ LCD commands ------------------


void lcdCharDisplaySendStringRaw( char* str );

void lcdCharDisplayCreateChar( uint8_t charnum, const char* chardata );



void LCDsendChar( uint8_t );           // Forms data ready to send to LCD
void LCDstring( uint8_t*, uint8_t );   // Outputs string to LCD
void LCDsendCommand(uint8_t);          // Forms data ready to send to LCD

// ------------------ LCD commands ------------------

// Clears LCD
void lcdCharDisplayClear( void );

// LCD cursor home
void lcdCharDisplayHome( void );

// Cursor to X Y position
void lcdCharDisplayGoToXY( uint8_t x, uint8_t y );



// ------------------ LCD commands ------------------

/*
char* itoa(int value, char* result, int base);    // convierte de un int a un cadena de char

char* ftoa(float f_number,char *buffer, uint8_t places);     // convierte de un float a una cadena de char
*/

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _SAPI_LCD_H_ */
