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
 
#include "ciaaNVM.h"

void ciaaNVMInit(void)
{
	ciaaI2CInit();
}

void mem48Read(uint8_t addr, void * buffer, int len)
{
	int i;

	/* Primero escribo dirección: 1 byte */
	ciaaI2CWrite(0x51, &addr, 1);

	//tiempo de establecimiento de la memoria
	//for(i=0; i<0xFFFF; i++);

	/* Leo byte (lectura propiamente dicha) */
	ciaaI2CRead(0x51, buffer, len);

	//tiempo de establecimiento de la memoria
	for(i=0; i<0xFFFF; i++);
}

void mem48Write(uint8_t addr, void * buffer, int len)
{
	uint8_t * pdatos = (uint8_t *)buffer;
	uint8_t buf[34];
	int i;

	while(len>0)
	{
		buf[0] = addr;

		for(i=0; i < ( len > 32 ? 32 : len ); i++)
			buf[i+1] = pdatos[i];

		ciaaI2CWrite(0x51, buf, len > 32 ? 34 : len+2);
		//tiempo de establecimiento de la memoria
		for(i=0; i<0xFFFF; i++);

		addr += 32;
		len -= 32;
		pdatos+=32;
	}
}

void memRead(uint16_t addr, void * buffer, int len)
{
	unsigned char txbuf[2];
	int i;

	txbuf[0] = addr >> 8;
	txbuf[1] = addr & 0xFF;

	/* Primero escribo dirección: 2 bytes */
	ciaaI2CWrite(0x50, txbuf, 2);

	//tiempo de establecimiento de la memoria
	//for(i=0; i<0xFFFF; i++);

	/* Leo byte (lectura propiamente dicha) */
	ciaaI2CRead(0x50, buffer, len);

	//tiempo de establecimiento de la memoria
	for(i=0; i<0xFFFF; i++);
}

void memWrite(uint16_t addr, void * buffer, int len)
{
	uint8_t * pdatos = (uint8_t *)buffer;
	uint8_t buf[34];
	int i;

	while(len>0)
	{
		buf[0] = addr >> 8;
		buf[1] = addr & 0xFF;

		for(i=0; i < ( len > 32 ? 32 : len ); i++)
			buf[i+2] = pdatos[i];

		ciaaI2CWrite(0x50, buf, len > 32 ? 34 : len+2);
		//tiempo de establecimiento de la memoria
		for(i=0; i<0xFFFF; i++);

		addr += 32;
		len -= 32;
		pdatos+=32;
	}
}
