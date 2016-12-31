#include "picoapi.h"

int main(void)
{
	int i = 0;

	while (1) {
		/* print current value of i */
		printString("i: "); 
		/* in decimal format */
		printInteger(i); 
		printString(" "); 
		/* and hexadecimal format */
		printHex(i); 
		printString("\r\n");
		i++;
		pausems(100);
	}
}
