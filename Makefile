###############################################################################
# Student Name    : 	Jack Edwards
# RMIT Student ID : 	S3727853
#
# Startup code provided by Paul Miller for use in "Programming in C",
# Assignment 2, study period 4, 2020.
###############################################################################

CC=gcc
CFLAGS=-ansi -Wall -pedantic -g
TARGETS=wuzzle-c
LFLAGS=
HEADERS=*.h
 
all:$(TARGETS)

wuzzle-c:io.o main.o score_list.o word_list.o
	$(CC) $(LFLAGS) io.o main.o score_list.o word_list.o -o wuzzle-c

io.o:io.c io.h word_list.h
	$(CC) $(CFLAGS) -c io.c

main.o:main.c main.h word_list.h io.h
	$(CC) $(CFLAGS) -c main.c

score_list.o:score_list.c score_list.h
	$(CC) $(CFLAGS) -c score_list.c

word_list.o:word_list.c word_list.h score_list.h shared.h
	$(CC) $(CFLAGS) -c word_list.c

.PHONY:clean
clean:
	rm -f *.o wuzzle-c *~
