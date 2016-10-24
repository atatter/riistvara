#include <avr/pgmspace.h>
#ifndef _HMI_MSG_H
#define _HMI_MSG_H

const char MONTHS[6][9] PROGMEM = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
      };

const char STUD_NAME[] PROGMEM = "Aleks, Tatter";
const char VER_FW[]  PROGMEM = "Version: %s built on: %s %s\n";
const char VER_LIBC[] PROGMEM = "avr-libc version: %s\n";
const char ENTER_MONTH_LETTER[] PROGMEM = "Enter Month name first letter >";
const char CLEAN_LINE[] PROGMEM = "                ";

#endif /* _HMI_MSG_H */
