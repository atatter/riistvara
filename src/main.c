#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
//#define __ASSERT_USE_STDERR
#include <assert.h>
#include "hmi_msg.h"
#include "uart.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"

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
    lcd_init();
    lcd_clrscr();
    /* Print version info to stderr */
    fprintf_P(stderr, VER_FW, GIT_DESCR, __DATE__, __TIME__);
    fprintf_P(stderr, VER_LIBC, __AVR_LIBC_VERSION_STRING__);
    /* End version print */
    lcd_puts_P(STUD_NAME);
    /* PRINT ASCII */
    print_ascii_tbl(stdout);
    unsigned char ascii[128] = {0};

    for (unsigned char i = 0; i < sizeof(ascii); i++) {
        ascii[i] = i;
    }

    /* PRINT FOR HUMAN */
    print_for_human(stdout, ascii, sizeof(ascii));

    while (1) {
        char input;
        fprintf_P(stdout, ENTER_MONTH_LETTER);
        fscanf(stdin, "%c", &input);
        fprintf(stdout, "%c\n", input);
        lcd_goto(0x40);

        for (int i = 0; i < 6; i++) {
            if (!strncmp_P(&input, MONTHS[i], 1)) {
                fprintf_P(stdout, MONTHS[i]);
                fputc('\n', stdout);
                lcd_puts_P(MONTHS[i]);
                lcd_putc(' ');
            }
        }

        lcd_puts_P(CLEAN_LINE);
        /* set pin 3 high to turn led on */
        PORTA |= _BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
        /* set pin 3 low to turn led off */
        PORTA &= ~_BV(PORTA3);
        _delay_ms(BLINK_DELAY_MS);
    }
}
