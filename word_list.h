/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 23, study period 4, 2020.
 *****************************************************************************/
#include "shared.h"
#ifndef WORDLIST_H
#define WORDLIST_H

#define WORD_LENGTH 80
#define EXTRA_CHARS 2

struct word_node {
    struct word_node *next;
    const char *word;
};

struct word_list {
    struct word_node *head;
    long num_words;
};

/**
 * List function prototypes that will be used for the management of the linked
 * list here.
 **/

BOOLEAN load_dictionary(const char *, struct word_list *list);

void list_init(struct word_list *list);

BOOLEAN check_letters(char *ptr);
BOOLEAN list_add(struct word_list *, const char *word);

BOOLEAN list_delete(struct word_list *list, const char *word);
void list_free(struct word_list *);
int word_cmp(const struct word_node *ptr1, const struct word_node *ptr2);
void print_list(struct word_list *);
BOOLEAN save_out(struct word_list *list, char *filename);
BOOLEAN is_in_dictionary(struct word_list *, const char *);
#endif
