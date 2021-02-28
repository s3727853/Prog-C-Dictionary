/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 3, study period 4, 2020.
 *****************************************************************************/
#include "word_list.h"
#include "score_list.h"

#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/* create the functions for the management of the linked list in this file */
BOOLEAN load_dictionary(const char *filename, struct word_list *list) {
    FILE *fp;
    char line[WORD_LENGTH + EXTRA_CHARS];
    char word[WORD_LENGTH + EXTRA_CHARS];
    char temp_word[WORD_LENGTH + EXTRA_CHARS];
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL) {

        return FALSE;
    }

    /*Iterate through file for words*/
    while (fgets(line, WORD_LENGTH + EXTRA_CHARS, fp) != NULL) {
        char *token;

        /*Remove newline from word read in*/
        line[strlen(line) - 1] = 0;

        /*split on newline*/
        token = strtok(line, "\n");

        if (token == NULL) {
            printf("\nError: Empytline detected in word file\n");
            break;
        }

        if (!check_letters(token)) {
            printf("\nError, word has invalid characters\n");
            return FALSE;
        }

        /*Convert word to uppercase and copy to malloc'd memory space*/

        for (i = 0; i < strlen(token); i++) {
            temp_word[i] = toupper(token[i]);
        }
        temp_word[strlen(token)] = '\0';

        strcpy(word, temp_word);

        if (!list_add(list, word)) {
            printf("\nError adding word to list.\n");
            return FALSE;
        }

        /*Get next token*/
        token = strtok(NULL, "\n");
    }

    fclose(fp);

    return TRUE;
}

/*Check words characters are valid*/

BOOLEAN check_letters(char *token) {
    int i;
    for (i = 0; i < strlen(token); i++) {
        char temp;
        temp = toupper(token[i]);

        /*Defined in score_list.h ASCI values for uppercase alphabet start/end*/
        if (temp < START_LETTER_VALUE || temp > END_LETTER_VALUE) {
            printf("\nInvalid character: %c in word: %s ", token[i], token);
            return FALSE;
        }
    }
    return TRUE;
}

/******************************************************************************
* CODE REFERENCE
* Linked List is based on code provided by Paul Miller in the week 7 & 8
* tutorial sessions.
******************************************************************************/

/* Initialise a new list*/
void list_init(struct word_list *list) {
    assert(list);
    /*Zero it*/
    memset(list, 0, sizeof(struct word_list));
}

int word_cmp(const struct word_node *first, const struct word_node *second) {
    int cmp;

    /*Positive if first->word is later in the sort order then second->word*/
    /*Negative if first->word is earlier in the sort order then second->word*/

    cmp = strcmp(first->word, second->word);
    return cmp;
}
/*Function to add words to list*/

BOOLEAN list_add(struct word_list *list, const char *word) {
    struct word_node *current, *previous = NULL;
    struct word_node *new;
    char *word_alloc;

    /*Check pointers are valid*/
    assert(list && word);

    /*Allocate memory for node*/
    new = malloc(sizeof(struct word_node));
    if (!new) {
        perror("Mem allocation failed");
        return FALSE;
    }
    /*zero it*/
    memset(new, 0, sizeof(struct word_node));

    /*Allocate memory for word and copy it in*/
    word_alloc = (char *)malloc((WORD_LENGTH + EXTRA_CHARS) * sizeof(char));
    if (!word) {
        perror("Memory allocation failed");
        return FALSE;
    }
    strcpy(word_alloc, word);

    /*set the word pointer in the struct to point to the word. The word */
    new->word = word_alloc;
    new->next = NULL;

    /*If at start of word add this new node in */
    if (list->head == NULL) {
        list->head = new;
        list->num_words++;
        return TRUE;
    }
    /*If items in list use compare function to find the insertion point*/
    current = list->head;

    while (current != NULL && word_cmp(current, new) < 0) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        new->next = list->head;
        list->head = new;
    } else if (!current) {
        previous->next = new;
    } else {
        previous->next = new;
        new->next = current;
    }
    list->num_words++;
    return TRUE;
}

/*Delete an element (word) from the list*/
BOOLEAN list_delete(struct word_list *list, const char *word) {
    struct word_node *current, *previous = NULL;

    if (list->num_words == 0) {
        printf("\nError: List is empty\n");
        return FALSE;
    }
    for (current = list->head; current && strcmp(current->word, word) != 0;
         previous = current, current = current->next) {
        ;
    }
    if (!current) {
        printf("\nError: Word not found\n");
        return FALSE;
    }

    /*The element to delete is the first node*/
    if (!previous) {
        list->head = list->head->next;
    } else {
        previous->next = current->next;
    }
    /*Need to free pointers in current before freeing the structure*/
    free((void *)current->word);
    free(current);
    list->num_words--;
    return TRUE;
}

/*free the memory allocated to the list*/
void list_free(struct word_list *list) {
    struct word_node *current, *next;
    current = list->head;

    while (current != NULL) {
        /*Free the nodes & data*/
        next = current->next;
        free((char *)current->word);
        free(current);
        current = next;
    }
}

/*Print Dictionary feature, utilised for testing*/
void print_list(struct word_list *list) {
    struct word_node *current = list->head;
    int i = 1;

    printf("\n### Printing Linked List ###\n");
    printf("List has %li entries\n\n", list->num_words);

    while (current != NULL) {
        printf("Word %d: %s\n", i, current->word);
        i++;
        current = current->next;
    }
}

BOOLEAN save_out(struct word_list *list, char *filename) {
    FILE *fp;
    struct word_node *current = list->head;
    /*Open the file for writing*/
    fp = fopen(filename, "w");

    /*Check file opened correctly*/
    if (fp == NULL) {
        printf("\nError: Problem writing to file. check filename.\n");
        return FALSE;
    }

    /*Iterate trough list and write each entry*/

    while (current != NULL) {
        fputs(current->word, fp);
        fputs("\n", fp);
        current = current->next;
    }

    fclose(fp);
    return TRUE;
}

/**
 * tests whether the word specified is in the word_list and therefore a valid
 * spelling. Please see the assignment specification for further details.
 **/
BOOLEAN is_in_dictionary(struct word_list *thelist, const char *word) {
    struct word_node *current = NULL;

    if (thelist->num_words == 0) {
        printf("\nError: List is empty\n");
        return FALSE;
    }
    for (current = thelist->head; current && strcmp(current->word, word) != 0;
         current = current->next) {
        ;
    }
    if (!current) {
        printf("\nError: Word not found.\n");
        return FALSE;
    }

    return TRUE;
}
