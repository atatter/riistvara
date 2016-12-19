#include "../lib/matejx_avr_lib/mfrc522.h"

#ifndef _RFID_HELPER_H
#define _RFID_HELPER_H

typedef struct card {
    uint8_t size;
    uint8_t uid[10];
    char *name;
    struct card *next; /* pointer to next card in the list */
} card_t;

extern card_t* rfid_get_card_with_uid(Uid *uid);
extern card_t* rfid_find_card(card_t *input);
extern void rfid_add_card(Uid *uid, const char *name);
extern void rfid_remove_card(const char *name);
extern void rfid_print_cards();

#endif /* _RFID_HELPER_H */