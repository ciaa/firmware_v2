#include "picoapi.h"

int main(void)
{
	picoConfigAnalogInput(P2_6);
	picoConfigAnalogInput(P2_4);

	while (1) {
		printString("AP2_6: "); printInteger(picoAnalogRead(P2_6));
		printString(" AP2_4: "); printInteger(picoAnalogRead(P2_4));
		printString("\r\n");
		pausems(200);
	}
}
