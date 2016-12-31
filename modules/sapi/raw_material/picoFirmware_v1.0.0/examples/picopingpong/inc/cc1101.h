/* Copyright 2016, Pablo Ridolfi
 * Based on ELECHOUSE CC1101 module library.
 * Copyright (c) 2010 Michael, <www.elechouse.com>
 * All rights reserved.
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
#ifndef _CC1101_H_
#define _CC1101_H_

/*==================[inclusions]=============================================*/

#include "picoapi.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/** byte type definition */
typedef uint8_t byte;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/** hardware initialization */
void cc1101_Init(void);

/** set device address
 *
 * @param address address to set
 */
void cc1101_SetAddress(byte address);

/** send packet
 *
 * @param address  receiver address
 * @param txBuffer data buffer
 * @param size     data size in bytes
 */
void cc1101_SendData(byte address, byte *txBuffer,byte size);

/** set receive mode */
void cc1101_SetReceive(void);

/** check if data received
 *
 * @return 1 if data received, 0 otherwise
 */
byte cc1101_CheckReceiveFlag(void);

/** get received data
 *
 * @param rxBuffer buffer to store received data
 * @param status   status bytes (RSSI and LQI)
 * @return data size, 0 otherwise
 */
byte cc1101_ReceiveData(byte rxBuffer[64], byte status[2]);


/*==================[cplusplus]==============================================*/

/** @} */

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _CC1101_H_ */
