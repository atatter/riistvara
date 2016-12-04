#ifndef _HMI_MSG_H
#define _HMI_MSG_H

#define STUD_NAME "Aleks Tatter"
#define VER_FW "Version: %S built on: %S %S"
#define VER_LIBC "avr-libc version: %S"
#define VER_GCC "avr-gcc version: %S"
#define CLEAN_LINE "                "
#define UPTIME "Uptime: %lu s"
#define HELP_CMD "help"
#define HELP_HELP "Get help"
#define VER_CMD "version"
#define VER_HELP "Print FW version"
#define ASCII_CMD "ascii"
#define ASCII_HELP "print ASCII tables"
#define MONTH_CMD "month"
#define MONTH_HELP "Find matching month from lookup list. Usage: month <string>"
#define IMPLEMENTED "Implemented commands:"
#define NO_COMMAND "Command not implemented.\n Use <help> to get help."
#define ARGUMENTS "To few or to many arguments for this command\nUse <help>"

extern PGM_P const months[];
extern const char help_cmd[];
extern const char help_help[];
extern const char ver_cmd[];
extern const char ver_help[];
extern const char ascii_cmd[];
extern const char ascii_help[];
extern const char month_cmd[];
extern const char month_help[];

#endif /* _HMI_MSG_H */
