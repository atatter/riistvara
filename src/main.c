#include <stdio.h>
#include <string.h>
#include <time.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "hmi_msg.h"
#include "../lib/andygock_avr-uart/uart.h"
#include "uart-wrapper.h"
#include "print_helper.h"
#include "../lib/hd44780_111/hd44780.h"

#define BAUDRATE 9600

static inline void init_system_clock(void)
{
    TCCR5A = 0; // Clear control register A
    TCCR5B = 0; // Clear control register B
    TCCR5B |= _BV(WGM52) | _BV(CS52); // CTC and fCPU/256
    OCR5A = 62549; // 1 s
    TIMSK5 |= _BV(OCIE5A); // Output Compare A Match Interrupt Enable
}

static inline void init (void)
{
    // Set pin 25 as led output
    DDRA |= _BV(DDA3);
    // Initialize and clear lcd
    lcd_init();
    lcd_clrscr();
    // Initiaize system clock
    init_system_clock();
    // Enable interrupts
    sei();
    // Initialize uart
    uart0_init(UART_BAUD_SELECT(BAUDRATE, F_CPU));
    uart3_init(UART_BAUD_SELECT(BAUDRATE, F_CPU));
    stdout = stdin = &uart0_io;
    stderr = &uart3_out;
}

static inline void print_info (void)
{
    // Print versions
    fprintf_P(stderr, PSTR(VER_FW), PSTR(GIT_DESCR), PSTR(__DATE__),
              PSTR(__TIME__));
    fprintf_P(stderr, PSTR(VER_LIBC), PSTR(__AVR_LIBC_VERSION_STRING__));
    // Print student name to lcd and uart0
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    lcd_puts_P(PSTR(STUD_NAME));
    // Print ascii table
    print_ascii_tbl(stdout);
    unsigned char ascii[128];

    for (unsigned char i = 0; i < sizeof(ascii); i++) {
        ascii[i] = i;
    }

    print_for_human(stdout, ascii, sizeof(ascii));
    // Print info text
    fprintf_P(stdout, PSTR(ENTER_MONTH_LETTER));
}

static inline void heartbeat (void)
{
    // Previous time
    static time_t previous_time;
    // Get current system time
    time_t current_time = time(NULL);

    if (current_time <= previous_time) {
        return;
    }

    // Update previous time and print info to uart3
    previous_time = current_time;
    fprintf_P(stderr, PSTR(UPTIME "\n"), current_time);
    // Toggle led
    PORTA ^= _BV(PORTA3);
}

static inline void search (char input)
{
    fprintf(stdout, "%c\n", input);
    lcd_goto(0x40);

    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(&input, (PGM_P)pgm_read_word(&months[i]), 1)) {
            fprintf_P(stdout, (PGM_P)pgm_read_word(&months[i]));
            fputc('\n', stdout);
            lcd_puts_P((PGM_P)pgm_read_word(&months[i]));
            lcd_putc(' ');
        }
    }

    lcd_puts_P(PSTR(CLEAN_LINE));
    fprintf_P(stdout, PSTR(ENTER_MONTH_LETTER));
}

int main (void)
{
    init();
    print_info();

    while (1) {
        heartbeat();
        char i = uart0_getchar(stdin);

        if (i != 0) {
            search(i);
        }
    }
}

// System clock
ISR(TIMER5_COMPA_vect)
{
    system_tick();
}
