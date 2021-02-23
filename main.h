/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Assignment 3
 *****************************************************************************/


#include "score_list.h"

/*Order command line arguments are expected*/

#define SCORELIST 1
#define DICTIONARY 2


#define NUMARGS 3

enum commands {
    CI_HELP,
    CI_ADD,
    CI_DELETE,
    CI_SAVE,
    CI_ERROR
};
enum commands process_command(char * command, char * return_word);
void print_help(void);
