#ifndef UART_WRAPPER_H
#define UART_WRAPPER_H

int uart0_putchar(char c, FILE *stream);
int uart3_putchar(char c, FILE *stream);

FILE uart0_out = FDEV_SETUP_STREAM(uart0_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart3_out = FDEV_SETUP_STREAM(uart3_putchar, NULL, _FDEV_SETUP_WRITE);

#endif /* UART_WRAPPER_H */
