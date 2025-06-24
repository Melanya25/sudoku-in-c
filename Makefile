CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: sudoku

sudoku: sudoku.c
    $(CC) $(CFLAGS) sudoku.c -o sudoku

clean:
    rm -f sudoku
