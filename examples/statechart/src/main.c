/* Copyright 2016, Pablo Ridolfi
 * All rights reserved.
 *
 * This file is part of Workspace.
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
 
/** @brief This is a simple statechart example using Yakindu Statechart Tool
 * Plug-in (update site: http://updates.yakindu.org/sct/mars/releases/).
 */

/** \addtogroup statechart Simple UML Statechart example.
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"
#include "board.h"

/* Include statechart header file. Be sure you run the statechart C code
 * generation tool!
 */
#include "Idleblink.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/** statechart instance */
static Idleblink statechart;

/*==================[internal functions declaration]=========================*/

/** @brief hardware initialization function
 *	@return none
 */
static void initHardware(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/** clock and peripherals initialization */
static void initHardware(void)
{
	Board_Init();
	Board_Buttons_Init();
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
}

/*==================[external functions definition]==========================*/

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param onoff state machine operation parameter
 */
void idleblinkIface_opLED(Idleblink* handle, const sc_boolean onoff)
{
	Board_LED_Set(LED, onoff);
}

/** SysTick interrupt handler */
void SysTick_Handler(void)
{
	/* send evTick event to state machine every 1ms */
	idleblinkIface_raise_evTick(&statechart);

	/* update state machine every 1ms */
	idleblink_runCycle(&statechart);
}

/** main function, application entry point */
int main(void)
{
	/* init and reset state machine */
	idleblink_init(&statechart);
	idleblink_enter(&statechart);

	initHardware();

	while (1) {
		if (Buttons_GetStatus() != NO_BUTTON_PRESSED) {
			/* if a button is pressed, send evButton to state machine */
			idleblinkIface_raise_evButton(&statechart);

			/* wait until button is released */
			while (Buttons_GetStatus() != NO_BUTTON_PRESSED) {
				__WFI(); /* wait for interrupt */
			}
		}
	}
}

/** @} doxygen end group definition */

/*==================[end of file]============================================*/
