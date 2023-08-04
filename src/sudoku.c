#include "sudoku.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function for initializing the Sudoku struct */
SudokuPtr initSudoku(int size) {
    // Allocating memory for the Sudoku struct
    SudokuPtr sudoku = malloc(sizeof(Sudoku));
    assert(sudoku);

    // Initializing the fields of the Sudoku struct
    sudoku->size = size;
    sudoku->squareRootOfSize = (int)sqrt(size);

    // Allocating memory for the Sudoku grid and initializing it to zero
    sudoku->grid = malloc(size * sizeof(int *));
    assert(sudoku->grid);
    for (int i = 0; i < size; i++) {
        sudoku->grid[i] = malloc(size * sizeof(int));
        memset(sudoku->grid[i], 0, size * sizeof(int));
    }

    return sudoku;
}

/* Function for reading a new Sudoku from the user */
void readSudoku(SudokuPtr sudoku) {
    if (sudoku == NULL) {
        fprintf(stderr, "Can't assign values to a Sudoku that is uninitialized...\n");
        exit(EXIT_FAILURE);
    }

    int buf[1000] = {0}, size, count = 0, val = 0;
    char ch;

    ch = getchar();
    while (ch != EOF && ch != '\n') {
        if (ch >= '1' && ch <= '9') {
            if (ch == '1' && sudoku->size > 9) {
                val = 10 * val + (ch - '0');
                ch = getchar();
                char limit = '0' + (sudoku->size - 10);
                if (ch >= '0' && ch <= limit) {
                    val = 10 * val + ch;
                    buf[count++] = val;
                } else {
                    ungetc(ch, stdin);
                }
                val = 0;
            } else {
                buf[count++] = ch - '0';
            }
        } else if (ch == '.') {
            buf[count++] = 0;
        } else {
            fprintf(stderr, "Sudoku's cells with assigned values must have numbers between '1' and the size of the Sudoku\nand cells with unassigned must have '.'\n");
            exit(EXIT_FAILURE);
        }
        ch = getchar();
    }

    size = count;
    count = 0;
    if (sudoku->size * sudoku->size != size) {
        fprintf(stderr, "Error - The Sudoku grid has %d cells and you gave %d values\n", sudoku->size * sudoku->size, size);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sudoku->size; i++) {
        for (int j = 0; j < sudoku->size; j++) {
            sudoku->grid[i][j] = buf[count++];
        }
    }
}

/* Function for displaying the Sudoku grid*/
void displaySudoku(SudokuPtr sudoku) {
    int size = sudoku->size, block_size = sudoku->squareRootOfSize, flag = 1;

    printf("+");
    for (int i = 0; i < size; i++) {
        if (i % block_size == 0 && i != 0) {
            printf("--");
        }
        printf("--");
    }
    printf("-+\n");

    for (int i = 0; i < size; i++) {
        if (i % block_size == 0 && i != 0) {
            printf("|");
            for (int k = 0; k < size + block_size - 1; k++) {
                printf("--");
            }
            printf("-|\n");
        }
        flag = 1;
        printf("|");
        for (int j = 0; j < size; j++) {
            if (j % block_size == 0 && j != 0) {
                printf("| ");
            }
            if (flag) {
                printf(" %d ", sudoku->grid[i][j]);
                flag = 0;
            } else {
                printf("%d ", sudoku->grid[i][j]);
            }
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < size; i++) {
        if (i % block_size == 0 && i != 0) {
            printf("--");
        }
        printf("--");
    }
    printf("-+\n");
}

/* Function for deallocating the memory of a Sudoku */
void destroySudoku(SudokuPtr sudoku) {
    if (sudoku == NULL)
        return;

    if (sudoku->grid != NULL) {
        for (int i = 0; i < sudoku->size; i++)
            free(sudoku->grid[i]);
        free(sudoku->grid);
    }
    free(sudoku);
}