#include <avr/pgmspace.h>
#include "hmi_msg.h"

const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";

const char help_cmd[] PROGMEM = HELP_CMD;
const char help_help[] PROGMEM = HELP_HELP;
const char ver_cmd[] PROGMEM = VER_CMD;
const char ver_help[] PROGMEM = VER_HELP;
const char ascii_cmd[] PROGMEM = ASCII_CMD;
const char ascii_help[] PROGMEM = ASCII_HELP;
const char month_cmd[] PROGMEM = MONTH_CMD;
const char month_help[] PROGMEM = MONTH_HELP;
const char rfid_read_cmd[] PROGMEM = RFID_READ_CMD;
const char rfid_read_help[] PROGMEM = RFID_READ_HELP;
const char rfid_add_cmd[] PROGMEM = RFID_ADD_CMD;
const char rfid_add_help[] PROGMEM = RFID_ADD_HELP;
const char rfid_remove_cmd[] PROGMEM = RFID_REMOVE_CMD;
const char rfid_remove_help[] PROGMEM = RFID_REMOVE_HELP;
const char rfid_list_cmd[] PROGMEM = RFID_LIST_CMD;
const char rfid_list_help[] PROGMEM = RFID_LIST_HELP;

PGM_P const months[] PROGMEM = {jan, feb, mar, apr, may, jun};
