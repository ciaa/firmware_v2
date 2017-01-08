#include "picoapi.h"

int main(void)
{
	uint32_t duty = 10;

	/* set PWM to 10kHz */
	picoPWMInit(10000);

	while (1) {
		/* set PWM */
		picoPWMSet(P2_8, duty);
		picoPWMSet(P6_13, 100-duty);
		duty += 10;
		if (duty > 100) {
			duty = 0;
		}
		/* toggle blue LED */
		picoDigitalToggle(LED_B);
		/* wait 1 second */
		pausems(1000);
	}
}
