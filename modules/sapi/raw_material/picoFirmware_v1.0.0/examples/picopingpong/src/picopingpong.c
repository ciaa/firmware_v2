#include "picoapi.h"
#include "cc1101.h"

#include <stdio.h>
#include <string.h>

/* define 1 for transmitter (PING), 0 for receiver (PONG) */
#define PING 0

#if PING
#define MY_ADDRESS     1
#define REMOTE_ADDRESS 2
#else
#define PONG           1
#define MY_ADDRESS     2
#define REMOTE_ADDRESS 1
#endif

int main(void)
{
	uint8_t str[64];
	uint8_t size;

	cc1101_Init();
	cc1101_SetAddress(MY_ADDRESS);

	printString("\r\nCC1101 Test\r\n");

#ifdef PONG
	cc1101_SetReceive();
#endif

	while (1) {
#if PING
		sprintf((char*)str, "Hello! %d", size++);
		cc1101_SendData(REMOTE_ADDRESS, str, strlen((char*)str)+1);
		picoDigitalToggle(LED_B);
		printString("Sent: "); printString((char*)str); printString("\r\n");
		pausems(500);
#endif
#if PONG
		if (cc1101_CheckReceiveFlag()) {
			byte status[2];
			size = cc1101_ReceiveData(str, status);
			if (size > 0) {
				printString("Recv: "); printString((char *)str);
				printString(" RSSI: "); printInteger(((int8_t)status[0])/2-74);
				printString("dBm LQI: "); printHex(status[1]);
				printString("\r\n");
				picoDigitalToggle(LED_G);
			}
			cc1101_SetReceive();
		}
#endif
	}
}
