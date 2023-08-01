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