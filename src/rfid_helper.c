#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "rfid_helper.h"
#include "hmi_msg.h"
#include "../lib/matejx_avr_lib/mfrc522.h"

card_t *head = NULL;

void print(card_t *card)
{
    printf("- ");

    for (uint8_t i = 0; i < card->size; i++) {
        printf("%02X", card->uid[i]);
    }

    printf(" %s", card->name);
    printf("\n");
}

card_t* rfid_find_card(card_t *input)
{
    if (head != NULL) {
        card_t *current;
        current = head;

        while (current != NULL) {
            if (memcmp(current->uid, input->uid, current->size) == 0) {
                return current;
            }

            current = current->next;
        }
    }

    return NULL;
}

card_t* rfid_uid_to_card(Uid *uid)
{
    card_t *new_card;
    new_card = malloc(sizeof(card_t));
    memcpy(new_card->uid, uid->uidByte, uid->size);
    new_card->size = uid->size;
    new_card->name = NULL;
    new_card->next = NULL;
    return new_card;
}

card_t* rfid_get_card_with_uid(Uid *uid)
{
    return rfid_find_card(rfid_uid_to_card(uid));
}

void rfid_add_card(Uid *uid, const char *name)
{
    card_t *new_card;
    new_card = rfid_uid_to_card(uid);
    card_t *search = rfid_find_card(new_card);

    if (search) {
        printf_P(PSTR(CARD_IS_ON_LIST "\n"));
        print(search);
        free(new_card->name);
        free(new_card);
        return;
    }

    char *new_name;
    new_name = malloc(strlen(name) + 1);
    strcpy(new_name, name);
    new_card->name = new_name;

    if (head == NULL) {
        head = new_card;
    } else {
        card_t *current;
        current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = new_card;
    }

    return;
}

void rfid_remove_card(const char *name)
{
    card_t *previous, *current;
    current = head;
    previous = NULL;

    if (head == NULL) {
        printf_P(PSTR(CARD_NOT_ON_LIST "\n"));
        return;
    }

    while (current->next != NULL)  {
        if (strcmp(current->name, name) == 0) {
            break;
        }

        previous = current;
        current = current->next;
    }

    if (strcmp(current->name, name) == 0) {
        printf_P(PSTR(REMOVING "\n"));

        if (previous == NULL && current->next == NULL) {
            free(current->name);
            free(current);
            head = NULL;
            return;
        }

        if (previous == NULL && current->next != NULL) {
            head = current->next;
            free(current->name);
            free(current);
            return;
        }

        if (previous != NULL && current->next == NULL) {
            previous->next = NULL;
            free(current->name);
            free(current);
            return;
        }

        if (previous != NULL && current->next != NULL) {
            previous->next = current->next;
            free(current->name);
            free(current);
            return;
        }
    } else {
        printf_P(PSTR(CARD_NOT_ON_LIST "\n"));
    }
}

void rfid_print_cards()
{
    if (head == NULL) {
        printf_P(PSTR(NO_CARDS "\n"));
    } else {
        card_t *current;
        current = head;

        while (current->next != NULL) {
            print(current);
            current = current->next;
        }

        print(current);
    }
}