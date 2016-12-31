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

#include "ciaaI2C.h"


void ciaaI2CInit(void)
{
	//configuro i2c y lo activo
	Chip_I2C_Init(I2C0);
	Chip_I2C_SetClockRate(I2C0, 100000);
	Chip_SCU_I2C0PinConfig(I2C0_STANDARD_FAST_MODE);

}

Status ciaaI2CWrite(uint8_t sl_addr, uint8_t * buffer, int len)
{
	I2CM_XFER_T xfer;

	xfer.slaveAddr = sl_addr;
	xfer.txBuff = buffer;
	xfer.txSz = len;
	xfer.rxBuff = 0;
	xfer.rxSz = 0;
	xfer.options = 0;
	xfer.status = 0;

	Chip_I2CM_XferBlocking(LPC_I2C0, &xfer);

	if(xfer.status == I2CM_STATUS_OK) return SUCCESS;
	else return ERROR;

}

Status ciaaI2CRead(uint8_t sl_addr, uint8_t * buffer, int len)
{
	I2CM_XFER_T xfer;

	xfer.slaveAddr = sl_addr;
	xfer.txBuff = 0;
	xfer.txSz = 0;
	xfer.rxBuff = buffer;
	xfer.rxSz = len;
	xfer.options = 0;
	xfer.status = 0;

	Chip_I2CM_XferBlocking(LPC_I2C0, &xfer);

	if(xfer.status == I2CM_STATUS_OK) return SUCCESS;
	else return ERROR;
}
