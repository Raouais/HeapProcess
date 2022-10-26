#!/usr/bin/env bash
CC=gcc 
CDFLAGS=-g -Wall -Werror -Wextra -Wwrite-strings -Wshadow -std=c99
PROG = myheap
LDLIBS=-lm

SRC=$(wildcard *.c init/*.c heap/*.c menu/*.c utils/*.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

default: $(PROG)

$(PROG): $(OBJ)
	@echo Compilation: executable sera $(PROG)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(PROG)
%.o: %.c %.h structures/%.h
utils/%.o: utils/%.c utils/%.h
init/%.o: init/%.c init/%.h
heap/%.o: heap/%.c heap/%.h

clean:
	@echo 'suppressions fichiers .o'
	@rm -f $(OBJ)