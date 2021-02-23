/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Assignment 3
 *****************************************************************************/

#include "shared.h"

#define MAX_STRING_LENGTH 80
#define EXTRA_CHARS 2

enum input_result {
    IR_FAILURE,
    IR_SUCCESS,
    IR_COMMAND,
    IR_EOF = -1
};


enum input_result read_string_keyboard(char *string[]);
char *strdup(const char*);
void to_upper(char * word);
BOOLEAN is_alpha(char * word);
