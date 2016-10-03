#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
//#define __ASSERT_USE_STDERR
#include <assert.h>
#include "hmi_msg.h"
#include "uart.h"
#include "print_helper.h"

#define BLINK_DELAY_MS 1000

int main (void)
{
    /* set pin 3 of PORTB for output*/
    DDRA |= _BV(DDA3);
    /* Init error console as stderr in UART3 and print user code info */
    uart0_init();
    uart3_init();
    stdout = stdin = &uart0_io;
    stderr = &uart3_out;
    fprintf(stderr, "Version: %s built on: %s %s\n",
            GIT_DESCR, __DATE__, __TIME__);
    fprintf(stderr, "avr-libc version: %s\n", __AVR_LIBC_VERSION_STRING__);
    /*End UART3 init and info print */

    fprintf(stdout, STUD_NAME "\n");

    /* PRINT ASCII */
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};
    for (unsigned char i = 0; i < sizeof(ascii); i++) {
        ascii[i] = i;
    }
    /* PRINT FOR HUMAN */
    print_for_human(stdout, ascii, sizeof(ascii));

    while(1) {

		char input;
		fprintf(stdout, "Enter Month name first letter >");
		fscanf(stdin, "%c", &input);
		fprintf(stdout, "%c\n", input);

		for (int i = 0; i < 12; i++) {
			if (!strncmp(strupr(&input), MONTHS[i], 1)) {
				fprintf(stdout, "%s\n", MONTHS[i]);
			}
		}

        /* set pin 3 high to turn led on */
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);

        /* set pin 3 low to turn led off */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
	}
}
