#include "picoapi.h"
#include <string.h>

#define STRING   "This is a test.\n"
#define FILENAME "test.txt"

int main(void)
{
	char buffer[100];

	/* fill buffer with zeroes */
	bzero(buffer, 100);

	/* init SD card connected to SPI0 */
	picoSDInit();

	/* write test */
	if (picoSDWriteAll(FILENAME, STRING, strlen(STRING)) > 0) {
		printString("Write to SD OK\r\n");
		picoDigitalWrite(LED_G, LED_ON);
	}
	else {
		printString("Error writing file.\r\n");
	}

	/* read test */
	if (picoSDReadAll(FILENAME, buffer, 100) > 0) {
		printString("Read from SD: ");
		printString(buffer);
		printString("\r\n");
	}
	else {
		printString("Error reading file.\r\n");
	}

	/* append test */
	if (picoSDAppendAll(FILENAME, STRING, strlen(STRING)) > 0) {
		printString("Append to file OK\r\n");
	}
	else {
		printString("Error appending data to file.\r\n");
	}

	while (1) {
		/* toggle blue LED */
		picoDigitalToggle(LED_B);
		/* wait 500 milliseconds */
		pausems(500);
	}
}
