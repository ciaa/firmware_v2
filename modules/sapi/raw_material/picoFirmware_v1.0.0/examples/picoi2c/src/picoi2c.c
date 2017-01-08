#include "picoapi.h"

/* Si5351 I2C Slave Address */
#define Si5351_ADDR 0x60

int main(void)
{
	/* init i2c1 (P8_5/SCL and P8_8/SDA) */
	picoI2CInit(I2C1);

	/* read register 183 (CRYSTAL_INTERNAL_LOAD_CAPACITANCE) */
	uint8_t txbuf[1] = {183};
	uint8_t rxbuf[1] = {0};
	picoI2CTransfer(I2C1, Si5351_ADDR, txbuf, 1, rxbuf, 1);

	/* print result */
	printString("Si5351 read register 183 (XTAL_CL): ");
	printHex(rxbuf[0]); printString("\r\n");

	while (1) {
		/* toggle blue LED */
		picoDigitalToggle(LED_G);
		/* wait 500 milliseconds */
		pauseus(500000);
	}
}
