/*
 * @brief NXP LPCXpresso 11U68 Sysinit file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

 #include "board.h"
 #include "string.h"

/* The System initialization code is called prior to the application and
   initializes the board for run-time operation. Board initialization
   includes clock setup and default pin muxing configuration. */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* Pin muxing table, only items that need changing from their default pin
   state are in this table. Not every pin is mapped. */
STATIC const PINMUX_GRP_T pinmuxing[] = {
	/* LPCXpresso pin			- Base board function		- Mapped function */
	/* RESET-PIO0_0				- PIO/RESET (pin 4)			- Reset */
	/* PIO0_1-ISP_EN			- PIO (pin 51)				- GPIO input */
	/* PIO0_2-SSP0_SSEL			- PIO/SSEL (pin 8)			- GPIO output for SSP0 CS */
	/* PIO0_3-VBUS				-                           - USB VBUS */
	{0, 3,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_4-I2C_SCL			- PIO/I2C-SCL (pin 41)		- I2C0 SCL */
	{0, 4,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_5-I2C_SDA			- PIO/I2C-SDA (pin 40)		- I2C0 SDA */
	{0, 5,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_6					-                           - GPIO */
	/* PIO0_7					- PIO (pin 11)				- GPIO */
	/* PIO0_8-SSP0_MISO			- PIO/MISO (pin 6)			- SSP0 MISO */
	{0, 8,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_9-SSP0_MOSI			- PIO/MOSI (pin 5)			- SSP0 MOSI */
	{0, 9,  (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* SWCLK-PIO0_10			-                           - SWCLK */
	/* PIO0_11-ADC_9			- PIO/AD5 (pin 20)			- ADC_9 */
	{0, 11, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_12-ADC_8			- PIO/AD4/SWDIO (pin 19)	- ADC_8 */
	{0, 12, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_13-ADC_7			- PIO/AD3 (pin 18)			- ADC_7 */
	{0, 13, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_14-ADC_6			- PIO/AD2 (pin 17)			- ADC_6 */
	{0, 14, (IOCON_FUNC2 | IOCON_MODE_INACT)},
	/* PIO0_16-WAKEUP			-                           - GPIO input */
	/* PIO0_17					- PIO (pin 12)				- GPIO */
	/* TO_MUX_PIO0_18-ISP_RX	- PIO/RXD (pin 10)			- UART0 RX */
	{0, 18, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_19-ISP_TX			- PIO/TXD (pin 9)			- UART0 TX */
	{0, 19, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO0_20					- PIO (pin 13)				- GPIO */
	/* PIO0_21					- PIO (pin 14)				- GPIO */
	/* PIO0_22					- PIO (pin 21)				- GPIO */
	/* PIO0_23-ADC_1			- PIO/AD1 (pin 16)			- ADC_1 */
	{0, 23, (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO1_0					- PIO (pin 22)				- GPIO */
	/* PIO1_1					- PIO/USB_CONNECT (pin 23)	- GPIO */
	/* PIO1_2					- PIO/SWCLK (pin 24)		- SWCLK */
	/* PIO1_3					- PIO (pin 25)				- GPIO */
	/* PIO1_4					- PIO (pin 26)				- GPIO */
	/* PIO1_5					- PIO (pin 27)				- GPIO */
	/* PIO1_6					- PIO (pin 53)				- GPIO */
	/* PIO1_7					- PIO (pin 52)				- GPIO */
	/* PIO1_8					- PIO (pin 50)				- GPIO */
	/* PIO1_9-ADC_0				- PIO/AD0 (pin 15)			- ADC_0 */
	{1, 9,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO1_10					- PIO (pin 49)				- GPIO */
	/* PIO1_11-I2C1_SCL			-                           - I2C1 SCL */
	{1, 11, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_12					- PIO/USB_VBUS (pin 39)		- GPIO input */
	/* PIO1_13					- PIO (pin 38)				- GPIO output */
	/* PIO1_14-I2C_SDA			-                           - I2C SDA */
	{1, 14, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_15					- PIO (pin 48)				- GPIO */
	/* PIO1_16					-                           - GPIO */
	/* PIO1_17					-                           - GPIO */
	/* PIO1_18					-                           - GPIO input, with pullup */
	/* PIO1_19					-                           - GPIO */
	/* PIO1_20-SSP1_SCK			-                           - SSP1 CLK */
	{1, 20, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_21-SSP1_MISO		-                           - SSP1 MISO */
	{1, 21, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_22-SSP1_MOSI		-                           - SSP1 MOSI */
	{1, 22, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_23-SSP1_SSEL		-                           - SSP1 SSEL */
	{1, 23, (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_24-CT32B0_MAT0		-                           - GPIO input, with pullup */
	/* PIO1_25					-                           - GPIO */
	/* PIO1_26-CT32B0_MAT2		-                           - CT32B0_MAT2 */
	{1, 26, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_27-CT32B0_MAT3		-                           - CT32B0_MAT3 */
	{1, 27, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_28					-                           - GPIO */
	/* PIO1_29-SSP0_SCK			- PIO/SCK (pin 7)			- SSP0 CLK */
	{1, 29, (IOCON_FUNC1 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO1_30					-                           - GPIO */
	/* PIO1_31					-                           - GPIO */
	/* PIO2_0					-                           - XTALIN */
	{2, 0,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO2_1					-                           - XTALOUT */
	{2, 1,  (IOCON_FUNC1 | IOCON_MODE_INACT)},
	/* PIO2_2-SCT0_OUT1			- PIO (pin 46)				- GPIO */
	/* PIO2_3-CT32B0_MAT1		-                           - CT32B0_MAT1 */
	{2, 3,  (IOCON_FUNC2 | IOCON_MODE_INACT | IOCON_DIGMODE_EN)},
	/* PIO2_4					-                           - GPIO */
	/* PIO2_5					-                           - GPIO */
	/* PIO2_6					-                           - GPIO */
	/* PIO2_7-SCT0_OUT2			- PIO (pin 47)				- GPIO */
	/* PIO2_8					-                           - GPIO */
	/* PIO2_9					-                           - GPIO */
	/* PIO2_10					-                           - GPIO */
	/* PIO2_11					-                           - GPIO */
	/* PIO2_12					-                           - GPIO */
	/* PIO2_13					-                           - GPIO */
	/* PIO2_14					-                           - GPIO */
	/* PIO2_15					-                           - GPIO */
	/* PIO2_16-SCT1_OUT0		- PIO/MAT=PWM (pin 42)		- LED1 GREEN */
	/* PIO2_17-SCT1_OUT1		- PIO/MAT=PWM (pin 43)		- LED0 RED */
	/* PIO2_18-SCT1_OUT2		- PIO (pin 44)				- LED2 BLUE */
	/* PIO2_19-SCT1_OUT3		- PIO (pin 45)				- GPIO */
	/* PIO2_20					-                           - GPIO */
	/* PIO2_21					-                           - GPIO */
	/* PIO2_22					-                           - GPIO */
	/* PIO2_23					-                           - GPIO */
};

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Sets up system pin muxing */
void Board_SetupMuxing(void)
{
	/* Enable IOCON clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);

	Chip_IOCON_SetPinMuxing(LPC_IOCON, pinmuxing, sizeof(pinmuxing) / sizeof(PINMUX_GRP_T));
}

/* Set up and initialize clocking prior to call to main */
void Board_SetupClocking(void)
{
	Chip_SetupXtalClocking();
}

/* Set up and initialize hardware prior to call to main */
void Board_SystemInit(void)
{
	/* Setup system clocking and muxing */
	Board_SetupMuxing();/* Muxing first as it sets up ext oscillator pins */
	Board_SetupClocking();
}
