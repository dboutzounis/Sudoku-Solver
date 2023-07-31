#include "sudoku.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Function for initializing the Sudoku struct */
Sudoku *initSudoku(int size, int missingDigits) {
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
    int i, j, n = sudoku->size * sudoku->size;

    for (i = 0; i < n; i++) {
        if (i % sudoku->size == 0 && i != 0) {
            for (j = 0; j < n + sudoku->size - 1; j++)
                printf("- ");
            printf("\n");
        }
        for (j = 0; j < sudoku->size; j++) {
            if (j % sudoku->size == 0 && j != 0)
                printf("| ");
        }
        printf("%d ", sudoku->grid[i][j]);
    }
    printf("\n");
}
