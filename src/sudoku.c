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
        fprintf(stderr, "Can't assign values to a Sudoku that is uninitialized.\n");
        exit(EXIT_FAILURE);
    }

    char *str = malloc(256 * sizeof(char));
    scanf("%s", str);
    int len = strlen(str), count = 0;

    if (len != 16 && len != 81 && len != 256) {
        fprintf(stderr, "-- Error --\nThe Sudoku grid has %d cells and you gave %d values.\n", sudoku->size * sudoku->size, len);
        exit(EXIT_FAILURE);
    }

    if (len == 16 || len == 81) {
        for (int i = 0; i < sudoku->size; i++) {
            for (int j = 0; j < sudoku->size; j++) {
                if (str[count] == '.') {
                    sudoku->grid[i][j] = 0;
                    count++;
                } else if (str[count] >= '1' && str[count] <= '9') {
                    sudoku->grid[i][j] = str[count++] - '0';
                } else {
                    fprintf(stderr, "-- Error --\nSudoku's cells with assigned values must have numbers between '1' and '%d'.\nSudoku's cells with unassigned values must have '.'.\n", sudoku->size);
                    exit(EXIT_FAILURE);
                }
            }
        }
    } else {
        for (int i = 0; i < sudoku->size; i++) {
            for (int j = 0; j < sudoku->size; j++) {
                if (str[count] == '.') {
                    sudoku->grid[i][j] = 0;
                    count++;
                } else if (str[count] >= '1' && str[count] <= '9') {
                    sudoku->grid[i][j] = str[count++] - '0';
                } else if (str[count] >= 'A' && str[count] <= 'G') {
                    sudoku->grid[i][j] = str[count++] - 55;
                } else {
                    fprintf(stderr, "-- Error --\nSudoku's cells with assigned values must have numbers between '1' and '9' and 'A' to 'G'.\nSudoku's cells with unassigned values must have '.'.\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    free(str);
}

/* Function for displaying the Sudoku grid */
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
                if (sudoku->grid[i][j] > 9)
                    printf(" %c ", sudoku->grid[i][j] + 55);
                else
                    printf(" %d ", sudoku->grid[i][j]);

                flag = 0;
            } else {
                if (sudoku->grid[i][j] > 9)
                    printf("%c ", sudoku->grid[i][j] + 55);
                else
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