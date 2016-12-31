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

#include "ciaaIO.h"

#ifdef edu_ciaa_nxp
ciaaPin_t inputs[4] = { {0,4},{0,8},{0,9},{1,9} };
ciaaPin_t outputs[6] = { {5,0},{5,1},{5,2},{0,14},{1,11},{1,12} };
#elif defined(ciaa_nxp)
ciaaPin_t inputs[8] = { {2,0},{2,1},{2,2},{2,3},{3,11},{3,12},{3,13},{3,14} };
ciaaPin_t outputs[8] = { {5,1},{2,6},{2,5},{2,4},{5,12},{5,13},{5,14},{1,8} };
#else
#error "please define CIAA_NXP or EDU_CIAA_NXP"
#endif

void ciaaIOInit(void)
{
	Chip_GPIO_Init(LPC_GPIO_PORT);

#if defined(edu_ciaa_nxp)
   /* LEDs */
   Chip_SCU_PinMux(2,0,MD_PUP|MD_EZI,FUNC4);  /* GPIO5[0], LED0R */
   Chip_SCU_PinMux(2,1,MD_PUP|MD_EZI,FUNC4);  /* GPIO5[1], LED0G */
   Chip_SCU_PinMux(2,2,MD_PUP|MD_EZI,FUNC4);  /* GPIO5[2], LED0B */
   Chip_SCU_PinMux(2,10,MD_PUP|MD_EZI,FUNC0); /* GPIO0[14], LED1 */
   Chip_SCU_PinMux(2,11,MD_PUP|MD_EZI,FUNC0); /* GPIO1[11], LED2 */
   Chip_SCU_PinMux(2,12,MD_PUP|MD_EZI,FUNC0); /* GPIO1[12], LED3 */

   Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 0,(1<<14),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<11)|(1<<12),1);

   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<0)|(1<<1)|(1<<2));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 0,(1<<14));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1,(1<<11)|(1<<12));

   /* Switches */
   Chip_SCU_PinMux(1,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[4], SW1 */
   Chip_SCU_PinMux(1,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[8], SW2 */
   Chip_SCU_PinMux(1,2,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO0[9], SW3 */
   Chip_SCU_PinMux(1,6,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO1[9], SW4 */

   Chip_GPIO_SetDir(LPC_GPIO_PORT, 0,(1<<4)|(1<<8)|(1<<9),0);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<9),0);
#elif defined(ciaa_nxp)
	/* Inputs */
   Chip_SCU_PinMux(4,0,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO2[0]  */
   Chip_SCU_PinMux(4,1,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO2[1]  */
   Chip_SCU_PinMux(4,2,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO2[2]  */
   Chip_SCU_PinMux(4,3,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO2[3]  */
   Chip_SCU_PinMux(7,3,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO3[11] */
   Chip_SCU_PinMux(7,4,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO3[12] */
   Chip_SCU_PinMux(7,5,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO3[13] */
   Chip_SCU_PinMux(7,6,MD_PUP|MD_EZI|MD_ZI,FUNC0); /* GPIO3[14] */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 2,0xF, 0);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 3, 0xF<<11, 0);

   /* MOSFETs */
   Chip_SCU_PinMux(4,8,MD_PUP|MD_EZI,FUNC4);  /* GPIO5[12] */
   Chip_SCU_PinMux(4,9,MD_PUP|MD_EZI,FUNC4);  /* GPIO5[13] */
   Chip_SCU_PinMux(4,10,MD_PUP|MD_EZI,FUNC4); /* GPIO5[14] */
   Chip_SCU_PinMux(1,5,MD_PUP|MD_EZI,FUNC0);  /* GPIO1[8]  */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<12)|(1<<13)|(1<<14),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 1,(1<<8),1);
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<12)|(1<<13)|(1<<14));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 1,(1<<8));

   /* Relays */
   Chip_SCU_PinMux(4,4,MD_PUP|MD_EZI,FUNC0); /* GPIO2[4] */
	Chip_SCU_PinMux(4,5,MD_PUP|MD_EZI,FUNC0); /* GPIO2[5] */
	Chip_SCU_PinMux(4,6,MD_PUP|MD_EZI,FUNC0); /* GPIO2[6] */
	Chip_SCU_PinMux(2,1,MD_PUP|MD_EZI,FUNC4); /* GPIO5[1] */
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 2,(1<<4)|(1<<5)|(1<<6),1);
   Chip_GPIO_SetDir(LPC_GPIO_PORT, 5,(1<<1),1);
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 2,(1<<4)|(1<<5)|(1<<6));
   Chip_GPIO_ClearValue(LPC_GPIO_PORT, 5,(1<<1));
#endif
}

uint32_t ciaaReadInput(uint32_t inputNumber)
{
	return Chip_GPIO_ReadPortBit(LPC_GPIO_PORT,
			inputs[inputNumber].port,
			inputs[inputNumber].bit);
}

uint32_t ciaaWriteOutput(uint32_t outputNumber, uint32_t value)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,
			outputs[outputNumber].port,
			outputs[outputNumber].bit,
			value);
	return 0;
}

void ciaaToggleOutput(uint32_t outputNumber)
{
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT,
			outputs[outputNumber].port,
			outputs[outputNumber].bit);
}
