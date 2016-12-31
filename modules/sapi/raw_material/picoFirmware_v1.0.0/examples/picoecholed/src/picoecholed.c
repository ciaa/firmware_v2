#include "picoapi.h"

int main(void)
{
	char mychar;
	printString("Type something!\r\n");
	while (1) {
		if (debugRecv(&mychar, 1) > 0) {
			picoDigitalWrite(LED_R, mychar & 1);
			picoDigitalWrite(LED_G, mychar & 2);
			picoDigitalWrite(LED_B, mychar & 4);
			debugSend(&mychar, 1);
		}
	}
}
