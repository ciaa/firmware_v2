#include "picoapi.h"

int main(void)
{
	while (1) {
		/* toggle blue LED */
		picoDigitalToggle(LED_B);
		/* wait 500 milliseconds */
		pausems(500);
	}
}
