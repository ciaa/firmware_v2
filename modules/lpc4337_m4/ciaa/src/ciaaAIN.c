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
 
#include "ciaaAIN.h"

uint16_t current_in[4];

void ADC0_IRQHandler(void)
{
	if(Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH1, ADC_DR_DONE_STAT)==SET)
	{
		Chip_ADC_ReadValue(LPC_ADC0, ADC_CH1, current_in);
	}
	if(Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH2, ADC_DR_DONE_STAT)==SET)
	{
		Chip_ADC_ReadValue(LPC_ADC0, ADC_CH2, current_in+1);
	}
	if(Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH3, ADC_DR_DONE_STAT)==SET)
	{
		Chip_ADC_ReadValue(LPC_ADC0, ADC_CH3, current_in+2);
	}
	if(Chip_ADC_ReadStatus(LPC_ADC0, ADC_CH4, ADC_DR_DONE_STAT)==SET)
	{
		Chip_ADC_ReadValue(LPC_ADC0, ADC_CH4, current_in+3);
	}
}

void ciaaAINInit(void)
{
	ADC_CLOCK_SETUP_T clk = {200000, 10, true};

	Chip_ADC_Init(LPC_ADC0, &clk);

	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH2, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH3, ENABLE);
	Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH4, ENABLE);

	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH1, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH2, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH3, ENABLE);
	Chip_ADC_Int_SetChannelCmd(LPC_ADC0, ADC_CH4, ENABLE);

	Chip_ADC_SetBurstCmd(LPC_ADC0, ENABLE);

	NVIC_EnableIRQ(ADC0_IRQn);
}

uint16_t ciaaAINRead(uint8_t input)
{
	if(input > 3) return -1;
	return current_in[input];
}
