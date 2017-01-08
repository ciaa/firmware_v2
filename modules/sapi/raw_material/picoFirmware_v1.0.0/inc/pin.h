/* Copyright 2016, Pablo Ridolfi
 * Copyright 2016, VICDA Argentina
 * All rights reserved.
 *
 * This file is part of picoAPI.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _PIN_H_
#define _PIN_H_

/** @addtogroup DigitalIO
 * Configuration of General Purpose Input/Outputs.
 *
 * @{
 */
/*==================[inclusions]=============================================*/

#include "picoapi.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/** RGB LEDs on picoCIAA use inverted logic */
#define LED_ON  (0)

/** RGB LEDs on picoCIAA use inverted logic */
#define LED_OFF (1)

/*==================[typedef]================================================*/

/** physical pins definitions */
typedef enum {
	P2_1 = 0,      /**< DigitalInOut | UART1_TXD                        */
	P2_2,          /**< DigitalInOut | SPI0_MOSI                        */
	P2_3,          /**< DigitalInOut | AnalogIn   | SPI1_MISO  | PWM1.3 */
	P2_4,          /**< DigitalInOut | AnalogIn   | SPI1_MOSI  | PWM1.2 */
	P2_5,          /**< DigitalInOut | AnalogIn   | SPI1_SCK   | PWM1.2 */
	P2_6,          /**< DigitalInOut | AnalogIn   | SPI1_SSEL0 | PWM1.3 */
	P2_7,          /**< DigitalInOut | AnalogIn   | SPI0_MISO  | PWM0.1 */
	P2_8,          /**< DigitalInOut | AnalogIn   | SPI0_SCK            */
	P2_9,          /**< DigitalInOut | AnalogIn   | SPI1_SSEL3 | PWM1.3 */
	P2_10,         /**< DigitalInOut | AnalogIn                         */
	P2_11,         /**< DigitalInOut | AnalogIn   | UART2_RTS  | PWM3.1 */
	P2_12,         /**< DigitalInOut                                    */
	P2_13,         /**< DigitalInOut | I2C2_SDA   | PWM2.0              */
	P2_14,         /**< DigitalInOut | SPI1_SSEL1 | PWM0.0              */

	P6_1,          /**< DigitalInOut | UART0_RTS  | PWM1.3              */
	P6_2,          /**< DigitalInOut | UART0_CTS                        */
	P6_3,          /**< DigitalInOut | UART1_RXD  | PWM0.0              */
	P6_4,          /**< DigitalInOut | UART0_SCLK | SPI0_SSEL2 | PWM1.2 */
	P6_5,          /**< DigitalInOut | UART1_SCLK | PWM0.2              */
	P6_6,          /**< DigitalInOut | UART1_TXD  | PWM0.1              */
	P6_7,          /**< DigitalInOut | UART2_RXD  | PWM0.3              */
	P6_8,          /**< DigitalInOut | UART1_RTS                        */
	P6_9,          /**< DigitalInOut | UART2_SCLK | PWM3.0              */
	P6_10,         /**< DigitalInOut | UART2_TXD  | SPI0_SSEL0          */
	P6_11,         /**< DigitalInOut | UART1_TXD  | SPI0_MOSI  | PWM2.3 */
	P6_12,         /**< DigitalInOut | UART1_RXD  | SPI0_SCK   | PWM2.1 */
	P6_13,         /**< DigitalInOut | SPI0_SSEL0 | PWM2.1              */
	P6_14,         /**< DigitalInOut | SPI0_MISO  | PWM2.0              */
	P6_15,         /**< DigitalInOut | UART3_TXD  | SPI1_MOSI  | PWM1.1 */
	P6_16,         /**< DigitalInOut | UART3_RXD  | SPI1_SCK   | PWM1.0 */
	P6_17,         /**< DigitalInOut | UART3_TXD  | PWM0.0              */
	P6_18,         /**< DigitalInOut | UART2_RXD  | SPI1_MISO           */
	P6_19,         /**< DigitalInOut | UART3_RXD                        */
	P6_20,         /**< DigitalInOut | UART3_SCLK | PWM0.1              */

	P8_1,          /**< DigitalInOut | UART0_TXD  | PWM3.0              */
	P8_2,          /**< DigitalInOut | SPI1_SSEL0                       */
	P8_3,          /**< DigitalInOut | I2C0_SCL                         */
	P8_4,          /**< DigitalInOut | UART0_RXD  | PWM3.3              */
	P8_5,          /**< DigitalInOut | UART1_CTS  | I2C1_SCL            */
	P8_6,          /**< DigitalInOut | I2C0_SDA   | PWM0.0              */
	P8_7,          /**< DigitalInOut | I2C2_SCL                         */
	P8_8,          /**< DigitalInOut | I2C1_SDA                         */
	P8_9,          /**< GROUND @warning Do not use this pin!!!          */
	P8_10,         /**< DigitalInOut | AnalogIn   | ISP mode   | PWM0.3 */

	LED_B = P8_10, /**< DigitalInOut | LED Blue                         */
	LED_G,         /**< DigitalInOut | LED Green                        */
	LED_R,         /**< DigitalInOut | LED Red                          */

	PICOPIN_COUNT  /**< Pin count for checking                          */
}picoPin_e;

/** user callback for pin interrupts */
typedef void (*picoPinIntHandler)(void);

/** pin interrupt edge type */
typedef enum {
	PICOPININT_EDGE_FALLING, /**< interrupt request on falling edge */
	PICOPININT_EDGE_RISING   /**< interrupt request on rising edge */
}picoPinIntEdgeType_e;

/** pin interrupt request channel */
typedef enum {
	PICOPININT_IRQ0, /**< channel 0 */
	PICOPININT_IRQ1, /**< channel 1 */
	PICOPININT_IRQ2, /**< channel 2 */
	PICOPININT_IRQ3, /**< channel 3 */
	PICOPININT_IRQ4, /**< channel 4 */
	PICOPININT_IRQ5, /**< channel 5 */
	PICOPININT_IRQ6, /**< channel 6 */
	PICOPININT_IRQ7  /**< channel 7 */
}picoPinIntRequest_e;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** Config pin as Digital Input, specifying mode bits (IOCON_*)
 * @param pin  @ref picoPin_e to configure
 * @param mode mode bits (OR'ed values or type IOCON_*)
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigDigitalInputExt(picoPin_e pin, uint16_t mode);

/** Config pin as Digital Input with default settings
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigDigitalInput(picoPin_e pin);

/** Config pin as Digital Output
 *
 * @param pin @ref picoPin_e to configure
 * @param initialValue initial value, 0 (low) or 1 (high)
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigDigitalOutput(picoPin_e pin, bool initialValue);

/** config pin as analog input
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigAnalogInput(picoPin_e pin);

/** config pin as analog output
 *
 * @warning Not supported yet!
 * @param pin @ref picoPin_e to configure
 * @return -1, not supported
 */
int32_t picoConfigAnalogOutput(picoPin_e pin);

/** config pin as UART function
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigUART(picoPin_e pin);

/** config pin as I2C function
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigI2C(picoPin_e pin);

/** config pin as SPI function
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigSPI(picoPin_e pin);

/** config pin as Timer Match Output function (for PWM)
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigMatchOutput(picoPin_e pin);

/** config pin as Timer Capture Input function
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigCaptureInput(picoPin_e pin);

/** config pin as State-Configurable Timer Output function (for PWM)
 *
 * @param pin @ref picoPin_e to configure
 * @return 0 if config was successful, -1 if invalid pin
 */
int32_t picoConfigSCTOutput(picoPin_e pin);

/** read Digital Input
 *
 * @param pin @ref picoPin_e to read
 * @return 0 if input low, 1 if input high
 */
int32_t picoDigitalRead(picoPin_e pin);

/** write digital output
 *
 * @param pin @ref picoPin_e to write
 * @param value 0/false (low) or 1/true (high)
 * @return 0 if set was successful, -1 if invalid pin
 */
int32_t picoDigitalWrite(picoPin_e pin, bool value);

/** toggle digital output
 *
 * @param pin @ref picoPin_e to toggle
 * @return 0 if set was successful, -1 if invalid pin
 */
int32_t picoDigitalToggle(picoPin_e pin);

/** attach interrupt handler to pin and set edge type
 *
 * @param pin     pin to configure as interrupt input (@ref picoPin_e)
 * @param irq     interrupt request channel number (@ref picoPinIntRequest_e)
 * @param edge    edge type (@ref picoPinIntEdgeType_e)
 * @param handler irq handler function (@ref picoPinIntHandler)
 */
void picoAttachPinInterrupt(picoPin_e pin, picoPinIntRequest_e irq, picoPinIntEdgeType_e edge, picoPinIntHandler handler);

/** detach interrupt from pin and disable irq
 *
 * @param irq interrupt request channel number (@ref picoPinIntRequest_e)
 */
void picoDetachPinInterrupt(picoPinIntRequest_e irq);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/** @} */

/*==================[end of file]============================================*/
#endif /* _PIN_H_ */
