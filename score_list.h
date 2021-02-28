/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/

/**
 * a letter score is a combination of the letter itself, its score and its count
 **/

#include "shared.h"

struct score {
    int letter, score, count;
};

#define MAXWIDTH 100
#define EXTRASPACES 2
#define NUM_SCORES 26

/* 65 - 90 For A-Z (Uppercase). 97 - 122 for a-z (lowercase) */
#define START_LETTER_VALUE 65
#define END_LETTER_VALUE 90

#define LETTER_LENGTH 1
#define SCORE_LENGTH 2
#define COUNT_LENGTH 2
/**
 * the scores list that contains the scores for all letters and doubles as the
 * 'deck' from which letters are dealt. This is also the structure used by each
 * player to represent their hand.
 **/
struct score_list {
    struct score scores[NUM_SCORES];
    int num_scores;
    int total_count;
};

int random_letter_index(struct score_list *scorelist);
int char_to_int(char *ptr);
int char_to_int_letter(char *ptr, int *array_ptr);
int *init_validation_list();
BOOLEAN scorelist_add_item(struct score_list *ptr, struct score item);

struct score_list *load_scores(const char *);
void deal_letters(struct score_list *, struct score_list *);
