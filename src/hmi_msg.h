#include <avr/pgmspace.h>
#ifndef _HMI_MSG_H
#define _HMI_MSG_H

#define STUD_NAME "Aleks Tatter"
#define VER_FW "Version: %S built on: %S %S\n"
#define VER_LIBC "avr-libc version: %S\n"
#define ENTER_MONTH_LETTER "Enter Month name first letter >"
#define CLEAN_LINE "                "
#define UPTIME "Uptime: %lu s"

const char jan[] PROGMEM = "January";
const char feb[] PROGMEM = "February";
const char mar[] PROGMEM = "March";
const char apr[] PROGMEM = "April";
const char may[] PROGMEM = "May";
const char jun[] PROGMEM = "June";

PGM_P const months[] PROGMEM = {jan, feb, mar, apr, may, jun};

#endif /* _HMI_MSG_H */
