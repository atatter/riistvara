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
#include "../lib/helius_microrl/microrl.h"
#include "cli_microrl.h"

#define BAUDRATE 9600

// Create microrl object and pointer on it
static microrl_t rl;
static microrl_t *prl = &rl;

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
    stdout = &uart0_out;
    stderr = &uart3_out;
}

static inline void print_info (void)
{
    // Print versions
    fprintf_P(stderr, PSTR(VER_FW "\n"), PSTR(GIT_DESCR), PSTR(__DATE__),
              PSTR(__TIME__));
    fprintf_P(stderr, PSTR(VER_LIBC "\n"), PSTR(__AVR_LIBC_VERSION_STRING__));
    fprintf_P(stderr, PSTR(VER_GCC "\n"), PSTR(__VERSION__));
    // Print student name to lcd and uart0
    fprintf_P(stdout, PSTR(STUD_NAME "\n"));
    lcd_puts_P(PSTR(STUD_NAME));
}

static inline void init_microrl(void)
{
    microrl_init (prl, cli_print);
    microrl_set_execute_callback (prl, cli_execute);
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

int main (void)
{
    init();
    print_info();
    init_microrl();

    while (1) {
        heartbeat();
        microrl_insert_char (prl, cli_get_char());
    }
}

// System clock
ISR(TIMER5_COMPA_vect)
{
    system_tick();
}
