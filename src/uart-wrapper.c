#include <avr/io.h>
#include <stdio.h>
#include "../lib/andygock_avr-uart/uart.h"

int uart0_getchar(FILE *stream)
{
    (void) stream;

    //  Error handling
    if (uart0_peek() == UART_NO_DATA) {
        return 0;
    }

    return (char) uart0_getc();
}
int uart0_putchar(char c, FILE *stream)
{
    (void) stream;

    // Add Windows line endings
    if (c == '\n') {
        uart0_putc('\r');
    }

    uart0_putc(c);
    return 0;
}
int uart3_putchar(char c, FILE *stream)
{
    (void) stream;

    // Add Windows line endings
    if (c == '\n') {
        uart3_putc('\r');
    }

    uart3_putc(c);
    return 0;
}