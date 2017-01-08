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

/*==================[inclusions]=============================================*/

#include "cc1101.h"
#include <string.h>

/*==================[macros and definitions]=================================*/

#define WRITE_BURST     0x40
#define READ_SINGLE     0x80
#define READ_BURST      0xC0
#define BYTES_IN_RXFIFO 0x7F

/** CC1101 Register addresses */
#define CC1101_IOCFG2       0x00        // GDO2 output pin configuration
#define CC1101_IOCFG1       0x01        // GDO1 output pin configuration
#define CC1101_IOCFG0       0x02        // GDO0 output pin configuration
#define CC1101_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CC1101_SYNC1        0x04        // Sync word, high INT8U
#define CC1101_SYNC0        0x05        // Sync word, low INT8U
#define CC1101_PKTLEN       0x06        // Packet length
#define CC1101_PKTCTRL1     0x07        // Packet automation control
#define CC1101_PKTCTRL0     0x08        // Packet automation control
#define CC1101_ADDR         0x09        // Device address
#define CC1101_CHANNR       0x0A        // Channel number
#define CC1101_FSCTRL1      0x0B        // Frequency synthesizer control
#define CC1101_FSCTRL0      0x0C        // Frequency synthesizer control
#define CC1101_FREQ2        0x0D        // Frequency control word, high INT8U
#define CC1101_FREQ1        0x0E        // Frequency control word, middle INT8U
#define CC1101_FREQ0        0x0F        // Frequency control word, low INT8U
#define CC1101_MDMCFG4      0x10        // Modem configuration
#define CC1101_MDMCFG3      0x11        // Modem configuration
#define CC1101_MDMCFG2      0x12        // Modem configuration
#define CC1101_MDMCFG1      0x13        // Modem configuration
#define CC1101_MDMCFG0      0x14        // Modem configuration
#define CC1101_DEVIATN      0x15        // Modem deviation setting
#define CC1101_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1A        // Bit Synchronization configuration
#define CC1101_AGCCTRL2     0x1B        // AGC control
#define CC1101_AGCCTRL1     0x1C        // AGC control
#define CC1101_AGCCTRL0     0x1D        // AGC control
#define CC1101_WOREVT1      0x1E        // High INT8U Event 0 timeout
#define CC1101_WOREVT0      0x1F        // Low INT8U Event 0 timeout
#define CC1101_WORCTRL      0x20        // Wake On Radio control
#define CC1101_FREND1       0x21        // Front end RX configuration
#define CC1101_FREND0       0x22        // Front end TX configuration
#define CC1101_FSCAL3       0x23        // Frequency synthesizer calibration
#define CC1101_FSCAL2       0x24        // Frequency synthesizer calibration
#define CC1101_FSCAL1       0x25        // Frequency synthesizer calibration
#define CC1101_FSCAL0       0x26        // Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x27        // RC oscillator configuration
#define CC1101_RCCTRL0      0x28        // RC oscillator configuration
#define CC1101_FSTEST       0x29        // Frequency synthesizer calibration control
#define CC1101_PTEST        0x2A        // Production test
#define CC1101_AGCTEST      0x2B        // AGC test
#define CC1101_TEST2        0x2C        // Various test settings
#define CC1101_TEST1        0x2D        // Various test settings
#define CC1101_TEST0        0x2E        // Various test settings

/** CC1101 Strobe commands */
#define CC1101_SRES         0x30        // Reset chip.
#define CC1101_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32        // Turn off crystal oscillator.
#define CC1101_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CC1101_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C        // Reset real time clock.
#define CC1101_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.
/** CC1101 Status registers */
#define CC1101_PARTNUM      0x30
#define CC1101_VERSION      0x31
#define CC1101_FREQEST      0x32
#define CC1101_LQI          0x33
#define CC1101_RSSI         0x34
#define CC1101_MARCSTATE    0x35
#define CC1101_WORTIME1     0x36
#define CC1101_WORTIME0     0x37
#define CC1101_PKTSTATUS    0x38
#define CC1101_VCO_VC_DAC   0x39
#define CC1101_TXBYTES      0x3A
#define CC1101_RXBYTES      0x3B

/** CC1101 PATABLE,TXFIFO,RXFIFO */
#define CC1101_PATABLE      0x3E
#define CC1101_TXFIFO       0x3F
#define CC1101_RXFIFO       0x3F

/** Used pins */
#define SCK_PIN   P6_12
#define MISO_PIN  P6_14
#define MOSI_PIN  P6_11
#define SS_PIN    P6_13
#define GDO0	  P6_9
#define GDO2	  P6_10

/** logic states for pins */
#define LOW  0
#define HIGH 1

/*==================[internal data declaration]==============================*/

static byte PaTable[8] = {0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60 ,0x60};
static byte myAddress;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

static void cc1101_SpiInit(void)
{
	picoConfigDigitalOutput(SS_PIN, 1);
	picoSPIInit(SPI0, 1000000);
}

static void cc1101_GDO_Set(void)
{
	picoConfigDigitalInput(GDO0);
	picoConfigDigitalInput(GDO2);
}

static void cc1101_Reset(void)
{
	picoDigitalWrite(SS_PIN, LOW);
	pausems(1);
	picoDigitalWrite(SS_PIN, HIGH);
	pausems(1);
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[1] = {CC1101_SRES};
	byte rxbuf[1] = {0};
	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, 1);

	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);
	picoDigitalWrite(SS_PIN, HIGH);
}

static void cc1101_SpiWriteReg(byte addr, byte value)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[2] = {addr, value};
	byte rxbuf[2] = {0, 0};

	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, 2);

	picoDigitalWrite(SS_PIN, HIGH);
}

static void cc1101_SpiWriteBurstReg(byte addr, byte *buffer, byte num)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[num+1];
	byte rxbuf[num+1];

	txbuf[0] = addr | WRITE_BURST;
	memcpy(txbuf+1, buffer, num);
	bzero(rxbuf, num+1);
	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, num+1);

	picoDigitalWrite(SS_PIN, HIGH);
}

static void cc1101_SpiStrobe(byte strobe)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[1] = {strobe};
	byte rxbuf[1] = {0};

	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, 1);

	picoDigitalWrite(SS_PIN, HIGH);
}

static byte cc1101_SpiReadReg(byte addr)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[2] = {addr|READ_SINGLE, 0};
	byte rxbuf[2] = {0, 0};

	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, 2);

	picoDigitalWrite(SS_PIN, HIGH);

	return rxbuf[1];
}

static void cc1101_SpiReadBurstReg(byte addr, byte *buffer, byte num)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[num+1];
	byte rxbuf[num+1];

	bzero(txbuf, num+1);
	bzero(rxbuf, num+1);
	txbuf[0] = addr | READ_BURST;

	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, num+1);

	picoDigitalWrite(SS_PIN, HIGH);

	memcpy(buffer, rxbuf+1, num);
}

static byte cc1101_SpiReadStatus(byte addr)
{
	picoDigitalWrite(SS_PIN, LOW);
	picoConfigDigitalInput(MISO_PIN);
	while(picoDigitalRead(MISO_PIN));
	picoConfigSPI(MISO_PIN);

	byte txbuf[2] = {addr|READ_BURST, 0};
	byte rxbuf[2] = {0,0};
	picoSPITransfer(SPI0, PICOPIN_COUNT, txbuf, rxbuf, 2);

	picoDigitalWrite(SS_PIN, HIGH);

	return rxbuf[0]; /* o rxbuf[1] ???? */
}

static void cc1101_RegConfigSettings(void)
{
	cc1101_SpiWriteReg(CC1101_FSCTRL1,  0x08);
	cc1101_SpiWriteReg(CC1101_FSCTRL0,  0x00);
	cc1101_SpiWriteReg(CC1101_FREQ2,    0x10);
	cc1101_SpiWriteReg(CC1101_FREQ1,    0xA7);
	cc1101_SpiWriteReg(CC1101_FREQ0,    0x62);
	cc1101_SpiWriteReg(CC1101_MDMCFG4,  0x5B);
	cc1101_SpiWriteReg(CC1101_MDMCFG3,  0xF8);
	cc1101_SpiWriteReg(CC1101_MDMCFG2,  0x03);
	cc1101_SpiWriteReg(CC1101_MDMCFG1,  0x22);
	cc1101_SpiWriteReg(CC1101_MDMCFG0,  0xF8);
	cc1101_SpiWriteReg(CC1101_CHANNR,   0x00);
	cc1101_SpiWriteReg(CC1101_DEVIATN,  0x47);
	cc1101_SpiWriteReg(CC1101_FREND1,   0xB6);
	cc1101_SpiWriteReg(CC1101_FREND0,   0x10);
	cc1101_SpiWriteReg(CC1101_MCSM0 ,   0x18);
	cc1101_SpiWriteReg(CC1101_FOCCFG,   0x1D);
	cc1101_SpiWriteReg(CC1101_BSCFG,    0x1C);
	cc1101_SpiWriteReg(CC1101_AGCCTRL2, 0xC7);
	cc1101_SpiWriteReg(CC1101_AGCCTRL1, 0x00);
	cc1101_SpiWriteReg(CC1101_AGCCTRL0, 0xB2);
	cc1101_SpiWriteReg(CC1101_FSCAL3,   0xEA);
	cc1101_SpiWriteReg(CC1101_FSCAL2,   0x2A);
	cc1101_SpiWriteReg(CC1101_FSCAL1,   0x00);
	cc1101_SpiWriteReg(CC1101_FSCAL0,   0x11);
	cc1101_SpiWriteReg(CC1101_FSTEST,   0x59);
	cc1101_SpiWriteReg(CC1101_TEST2,    0x81);
	cc1101_SpiWriteReg(CC1101_TEST1,    0x35);
	cc1101_SpiWriteReg(CC1101_TEST0,    0x09);
	cc1101_SpiWriteReg(CC1101_IOCFG2,   0x0B); //serial clock.synchronous to the data in synchronous serial mode
	cc1101_SpiWriteReg(CC1101_IOCFG0,   0x06); //Asserts when sync word has been sent / received, and de-asserts at the end of the packet.
	cc1101_SpiWriteReg(CC1101_PKTCTRL1, 0x04); //two status bytes will be appended to the payload of the packet,including RSSI LQI and CRC OK
	                                           //No address check
	cc1101_SpiWriteReg(CC1101_PKTCTRL0, 0x05); //whitening off;CRC Enable£»variable length packets, packet length configured by the first byte after sync word
	cc1101_SpiWriteReg(CC1101_ADDR,     0x00); //address used for packet filtration.
	cc1101_SpiWriteReg(CC1101_PKTLEN,   0x3D); //61 bytes max length
}

/*==================[external functions definition]==========================*/

void cc1101_Init(void)
{
	cc1101_SpiInit();									//spi initialization
	cc1101_GDO_Set();									//GDO set
	cc1101_Reset();										//CC1101 reset
	cc1101_RegConfigSettings();							//CC1101 register config
	cc1101_SpiWriteBurstReg(CC1101_PATABLE,PaTable,8);	//CC1101 PATABLE config
}

void cc1101_SetAddress(byte address)
{
	cc1101_SpiWriteReg(CC1101_ADDR, address); //address used for packet filtration.
	myAddress = address;
}

void cc1101_SendData(byte address, byte *txBuffer,byte size)
{
	cc1101_SpiStrobe(CC1101_SFTX);						  //flush TXfifo
	cc1101_SpiWriteReg(CC1101_TXFIFO,size+1);
	cc1101_SpiWriteReg(CC1101_TXFIFO,address);
	cc1101_SpiWriteBurstReg(CC1101_TXFIFO,txBuffer,size); //write data to send
	cc1101_SpiStrobe(CC1101_STX);						  //start send
}

void cc1101_SetReceive(void)
{
	cc1101_SpiStrobe(CC1101_SRX);
}

byte cc1101_CheckReceiveFlag(void)
{
	if(picoDigitalRead(GDO0)) {
		while (picoDigitalRead(GDO0));
		return 1;
	}
	else {// no data
		return 0;
	}
}

byte cc1101_ReceiveData(byte rxBuffer[64], byte status[2])
{
	byte size;
	byte address;
	byte bstatus = cc1101_SpiReadStatus(CC1101_RXBYTES) & BYTES_IN_RXFIFO;
	if(bstatus > 0) {
		size=cc1101_SpiReadReg(CC1101_RXFIFO);
		address=cc1101_SpiReadReg(CC1101_RXFIFO);
		cc1101_SpiReadBurstReg(CC1101_RXFIFO,rxBuffer,size-1);
		cc1101_SpiReadBurstReg(CC1101_RXFIFO,status,2);
		cc1101_SpiStrobe(CC1101_SFRX);
		if (address != myAddress) {
			size = 0;
		}
	}
	return size;
}

/*==================[end of file]============================================*/
