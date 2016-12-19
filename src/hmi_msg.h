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
#define RFID_READ_CMD "rfid"
#define RFID_READ_HELP "Card has to be close to the sensor to show info"
#define RFID_ADD_CMD "add"
#define RFID_ADD_HELP "Add a card: add name"
#define RFID_REMOVE_CMD "remove"
#define RFID_REMOVE_HELP "Remove a card: remove name"
#define RFID_LIST_CMD "list"
#define RFID_LIST_HELP "Type list to see all saved cards"
#define UID_ERROR "Unable to select card"
#define UID_SIZE "UID size: 0x%02X"
#define UID_SAK "UID sak: 0x%02X"
#define UID_SELECTED "Card selected!"
#define UID_MSG "Card UID: "
#define ACCESS_DENIED "Access denied"
#define CARD_NOT_ON_LIST "This card is not on the list"
#define CARD_IS_ON_LIST "This card is already on the list"
#define NO_CARDS "No cards on the list"
#define REMOVING "Removing..."

extern PGM_P const months[];
extern const char help_cmd[];
extern const char help_help[];
extern const char ver_cmd[];
extern const char ver_help[];
extern const char ascii_cmd[];
extern const char ascii_help[];
extern const char month_cmd[];
extern const char month_help[];
extern const char rfid_read_cmd[];
extern const char rfid_read_help[];
extern const char rfid_add_cmd[];
extern const char rfid_add_help[];
extern const char rfid_remove_cmd[];
extern const char rfid_remove_help[];
extern const char rfid_list_cmd[];
extern const char rfid_list_help[];

#endif /* _HMI_MSG_H */
