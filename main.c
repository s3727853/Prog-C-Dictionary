/******************************************************************************
 * Student Name    :    Jack Edwards
 * RMIT Student ID :    S3727853
 *
 * Assignment 3
 *****************************************************************************/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "word_list.h"
#include "io.h"

int main(int argc, char *argv[]) {

    clock_t start, end;
    double score_time, dictionary_time;
    struct score_list *letters;
    struct word_list *words;
    char *user_input[MAX_STRING_LENGTH + EXTRA_CHARS];
    char user_word[WORD_LENGTH + EXTRA_CHARS];
    enum input_result result = IR_FAILURE;

    *user_input = NULL;
    /*Allocate mem for word list and initilise it*/
    words = malloc(sizeof(struct word_list));
    if (!words) {
        perror("Memory allocation failed");
        return EXIT_FAILURE;
    }
    list_init(words);

    /*Check correct amount of command line arguments passed in*/
    if (argc != NUMARGS) {
        printf(
            "\nError, incorrect number of commandline arguments "
            "passed in\n");
        return EXIT_FAILURE;
    }
    /*start timer for loading scores*/
    start = clock();
    letters = load_scores(argv[SCORELIST]);
    if (letters == NULL) {
        return EXIT_FAILURE;
    }
    end = clock();
    score_time = ((double)end - start) / CLOCKS_PER_SEC;

    /* Load in words list */
    start = clock();
    if (!load_dictionary(argv[DICTIONARY], words)) {
        printf("\nError loading word file\n");
        return EXIT_FAILURE;
    }

    end = clock();
    dictionary_time = ((double)end - start) / CLOCKS_PER_SEC;

    printf(
        "\nWelcome to Wuzzle spellchecker\n"
        "--------------------------------\n");

    printf(
        "Loading in score list took %f seconds.\n"
        "Loading in dictionary took %f seconds.\n\n",
        score_time, dictionary_time);

    /*Get word List load time and display here*/

    printf(
        "Please enter the word to check the spelling of"
        " (or :help for help)|");
    /*Call io function for input*/

    /* Main input loop */
    while (result != IR_EOF) {
        result = read_string_keyboard(user_input);

        /*If input contained a semicolon at the start parse it as a command*/
        if (result == IR_COMMAND) {
            enum commands command_result;
            command_result = process_command(*user_input, user_word);
            switch (command_result) {
                case CI_HELP:
                    print_help();
                    free(*user_input);
                    break;
                case CI_ADD:
                    if (list_add(words, user_word)) {
                        printf("\nWord added to dictionary.\n");
                    }
                    free(*user_input);
                    break;
                case CI_DELETE:
                    if (list_delete(words, user_word)) {
                        printf("\n'%s' was deleted from the dictionary.\n",
                               user_word);
                    }
                    free(*user_input);
                    break;
                case CI_SAVE:
                    if (save_out(words, user_word)) {
                        printf("\nDictionary saved to file '%s'\n", user_word);
                    }
                    free(*user_input);
                    break;
                case CI_ERROR:
                    printf(
                        "\nError, please check that the word you entered "
                        "contains valid characters only(letters)\n");
                    break;
            }
        }
        if (result == IR_SUCCESS) {
            to_upper(*user_input);
            if (is_in_dictionary(words, *user_input)) {
                printf("\nThe word '%s' is in the dictionary.\n", *user_input);
            }
            free(*user_input);
        }
    }
    /*Save the file that was loaded*/
    save_out(words, argv[DICTIONARY]);

    /*Test list - Print function*/
    /*print_list(words);*/

    /*Free the linked list*/
    list_free(words);

    free(words);
    free(letters);
    return EXIT_SUCCESS;
}

/*This function validates commands, if a command is passed in with a second
 * word (delete or add) this word is copied into the return_words location
 * for caller to pass to required word list function*/

enum commands process_command(char *command, char *return_word) {
    char *token;
    char command_word[WORD_LENGTH + EXTRA_CHARS];
    char action_word[WORD_LENGTH + EXTRA_CHARS];
    BOOLEAN action_word_present = FALSE;
    int i = 0;

    /*Get the first part of the string read in (the command) and convert to
     * uppercase. Strtok is used to split on space, the first half is ignored
     * (the command) and the second half is saved*/

    token = strtok(command, " ");

    while (token != NULL) {
        if (i == 0) {
            strcpy(command_word, token);
        }
        if (i == 1) {
            strcpy(action_word, token);
            action_word_present = TRUE;
        }
        token = strtok(NULL, " ");
        i++;
    }

    /*Check command has valid letters*/
    if (!is_alpha(command_word)) {
        printf("\nError: command is invalid.");
        return CI_ERROR;
    }

    /*Check if command is any of the single word commands*/
    to_upper(command_word);
    if (strcmp(command_word, "HELP") == 0) {
        return CI_HELP;
    }

    /*If save command we don't wanto validate save name as it may be a
     * complete file path*/
    if (strcmp(command_word, "SAVE") == 0) {
        strcpy(return_word, action_word);
        return CI_SAVE;
    }

    /*check second part of command is present and letters valid*/
    if (!action_word_present || !is_alpha(action_word)) {
        return CI_ERROR;
    }

    to_upper(action_word);

    /*Check word against commands TODO don't hardcode this */

    if (strcmp(command_word, "ADD") == 0) {
        strcpy(return_word, action_word);
        return CI_ADD;
    }
    if (strcmp(command_word, "DELETE") == 0) {
        strcpy(return_word, action_word);
        return CI_DELETE;
    }

    printf("\nError: unrecognised command.\n");
    return CI_ERROR;
}

void print_help(void) {
    printf(
        "\n------------------ Spellchecker Help -------------------------"
        "\nTo check a words spelling is correct simply type the word and "
        "press enter.\nTo exit press enter on an emptyline or CTRL-D"
        "\n---------------------- Commands -----------------------------\n"
        "To add word to dictionary type :add word\n"
        "To delete a word from dictionary type :delete word\n"
        "To save the dictionary type :save filename\n"
        "To access this help info again type :help\n");
}
