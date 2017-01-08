#include "picoapi.h"
#include <string.h>

int main(void)
{
	picoFile myFile;

	printString("Initializing SD card... ");

	if (picoSDInit() != 0) {
		printString("initialization failed!\r\n");
		return -1;
	}

	printString("initialization done.\r\n");

	// open the file.
	myFile = picoSDOpen("test.txt", picoFILE_WRITE);

	// if the file opened okay, write to it:
	if (myFile) {
		printString("Writing to test.txt... ");
		picoSDPrint(myFile, "testing 1, 2, 3.\r\n");
		// close the file:
		picoSDClose(myFile);
		printString("done.\r\n");
	} else {
		// if the file didn't open, print an error:
		printString("error opening test.txt\r\n");
	}

	// re-open the file for reading:
	myFile = picoSDOpen("test.txt", picoFILE_READ);
	if (myFile) {
		printString("test.txt: ");
		char data[10];
		int32_t datalen;
		// read from the file until there's nothing else in it:
		while (!picoSDEndOfFile(myFile)) {
			datalen = picoSDRead(myFile, data, 10);
			debugSend(data, datalen);
		}
		printString("\r\n");
		// close the file:
		picoSDClose(myFile);
	} else {
		// if the file didn't open, print an error:
		printString("error opening test.txt\r\n");
	}

	while (1) {
		/* toggle blue LED */
		picoDigitalToggle(LED_B);
		/* wait 500 milliseconds */
		pausems(500);
	}
}
