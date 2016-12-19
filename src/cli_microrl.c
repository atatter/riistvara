#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "../lib/hd44780_111/hd44780.h"
#include "../lib/andygock_avr-uart/uart.h"
#include "../lib/matejx_avr_lib/mfrc522.h"
#include "hmi_msg.h"
#include "print_helper.h"
#include "cli_microrl.h"
#include "rfid_helper.h"

typedef struct cli_cmd {
    PGM_P cmd;
    PGM_P help;
    void (*func_p)();
    const uint8_t func_argc;
} cli_cmd_t;

const cli_cmd_t cli_cmds[] = {
    {help_cmd, help_help, cli_print_help, 0},
    {ver_cmd, ver_help, cli_print_ver, 0},
    {ascii_cmd, ascii_help, cli_print_ascii_tbls, 0},
    {month_cmd, month_help, cli_handle_month, 1},
    {rfid_read_cmd, rfid_read_help, cli_rfid_read, 0},
    {rfid_add_cmd, rfid_add_help, cli_rfid_add, 1},
    {rfid_remove_cmd, rfid_remove_help, cli_rfid_remove, 1},
    {rfid_list_cmd, rfid_list_help, cli_rfid_list, 0}
};


void cli_print(const char *str)
{
    printf("%s", str);
}


char cli_get_char(void)
{
    if (uart0_peek() != UART_NO_DATA) {
        return uart0_getc() & UART_STATUS_MASK;
    } else {
        return 0x00;
    }
}


void cli_print_help(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    printf_P(PSTR(IMPLEMENTED "\n"));

    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        printf_P(cli_cmds[i].cmd);
        printf_P(PSTR(" : "));
        printf_P(cli_cmds[i].help);
        printf_P(PSTR("\n"));
    }
}


void cli_print_ver(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    // Print versions
    fprintf_P(stdout, PSTR(VER_FW "\n"), PSTR(GIT_DESCR), PSTR(__DATE__),
              PSTR(__TIME__));
    fprintf_P(stdout, PSTR(VER_LIBC "\n"), PSTR(__AVR_LIBC_VERSION_STRING__));
    fprintf_P(stdout, PSTR(VER_GCC "\n"), PSTR(__VERSION__));
}


void cli_print_ascii_tbls(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    // Print ascii table
    print_ascii_tbl(stdout);
    unsigned char ascii[128];

    for (unsigned char i = 0; i < sizeof(ascii); i++) {
        ascii[i] = i;
    }

    print_for_human(stdout, ascii, sizeof(ascii));
}


void cli_handle_month(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    lcd_goto(0x40);

    for (int i = 0; i < 6; i++) {
        if (!strncmp_P(argv[1], (PGM_P)pgm_read_word(&months[i]), strlen(argv[1]))) {
            fprintf_P(stdout, (PGM_P)pgm_read_word(&months[i]));
            fputc('\n', stdout);
            lcd_puts_P((PGM_P)pgm_read_word(&months[i]));
            lcd_putc(' ');
        }
    }

    lcd_puts_P(PSTR(CLEAN_LINE));
}


void cli_rfid_read(const char *const *argv)
{
    (void) argv;
    Uid uid;
    Uid *uid_ptr = &uid;
    printf_P(PSTR("\n"));

    if (PICC_IsNewCardPresent()) {
        printf(UID_SELECTED "\n");
        PICC_ReadCardSerial(uid_ptr);
        printf(UID_SIZE "\n", uid.size);
        printf(UID_SAK "\n", uid.sak);
        printf(UID_MSG);

        for (byte i = 0; i < uid.size; i++) {
            printf("%02X", uid.uidByte[i]);
        }

        printf_P(PSTR("\n"));
        PICC_IsNewCardPresent(); // Fixes the problem, where the next card could not be selected
    }   else {
        printf_P((PSTR(UID_ERROR)));
        printf_P(PSTR("\n"));
    }
}


void cli_rfid_add(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    Uid uid;
    Uid *uid_ptr = &uid;

    if (PICC_IsNewCardPresent()) {
        PICC_ReadCardSerial(uid_ptr);
        rfid_add_card(uid_ptr, argv[1]);
        PICC_IsNewCardPresent(); // Fixes the problem, where the next card could not be selected
    } else {
        printf_P((PSTR(UID_ERROR)));
        printf_P(PSTR("\n"));
    }
}


void cli_rfid_remove(const char *const *argv)
{
    (void) argv;
    printf_P(PSTR("\n"));
    rfid_remove_card(argv[1]);
}

void cli_rfid_list(void)
{
    printf_P(PSTR("\n"));
    rfid_print_cards();
}

void cli_print_cmd_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(NO_COMMAND "\n"));
}


void cli_print_cmd_arg_error(void)
{
    printf_P(PSTR("\n"));
    printf_P(PSTR(ARGUMENTS "\n"));
}


int cli_execute(int argc, const char *const *argv)
{
    for (uint8_t i = 0; i < NUM_ELEMS(cli_cmds); i++) {
        if (!strcmp_P(argv[0], cli_cmds[i].cmd)) {
            // Test do we have correct arguments to run command
            // Function arguments count shall be defined in struct
            if ((argc - 1) != cli_cmds[i].func_argc) {
                cli_print_cmd_arg_error();
                return 0;
            }

            // Hand argv over to function pointer,
            // cross fingers and hope that funcion handles it properly
            cli_cmds[i].func_p (argv);
            return 0;
        }
    }

    cli_print_cmd_error();
    return 0;
}