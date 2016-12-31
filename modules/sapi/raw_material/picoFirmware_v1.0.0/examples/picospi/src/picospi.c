#include "picoapi.h"

/*
 * Read FSTEST, PTEST, AGCTEST, TEST2 and TEST1 registers
 * from CC1101 transceiver connected to SPI0.
 * Use P6_13 as slave select pin.
 */

/* header burst flag */
#define CC1101_BURST      (0x40)

/* register read flag */
#define CC1101_READ       (0x80)

/* starting address */
#define CC1101_REG_FSTEST (0x29)

int main(void)
{
	/* set slave select pin */
	picoConfigDigitalOutput(P6_13, 1);

	/* init SPI0 at 100kbps */
	picoSPIInit(SPI0, 100000);

	/* set transmit and receive buffers */
	uint8_t tx[6] = {0,0,0,0,0,0};
	uint8_t rx[6] = {0,0,0,0,0,0};

	/* read registers in burst mode starting from FSTEST */
	tx[0] = CC1101_READ | CC1101_BURST | CC1101_REG_FSTEST;
	tx[1] = tx[2] = 0;

	/* send and receive data */
	picoSPITransfer(SPI0, P6_13, tx, rx, 6);

	/* print results */
	printString("\r\nCC1101 Test:\r\n");
	printString("Status  : "); printInteger(rx[0]); printString("\r\n");
	printString("FSTEST  : "); printInteger(rx[1]); printString("\r\n");
	printString("PTEST   : "); printInteger(rx[2]); printString("\r\n");
	printString("AGCTEST : "); printInteger(rx[3]); printString("\r\n");
	printString("TEST2   : "); printInteger(rx[4]); printString("\r\n");
	printString("TEST1   : "); printInteger(rx[5]); printString("\r\n");

	while (1) {
		/* toggle blue LED */
		picoDigitalToggle(LED_B);
		/* wait 500 milliseconds */
		pausems(500);
	}
}
