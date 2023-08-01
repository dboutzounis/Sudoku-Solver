#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    SudokuPtr sudoku = initSudoku(9);
    int grid[9][9] = {{6, 0, 0, 0, 2, 0, 0, 0, 0},
                      {4, 0, 0, 0, 0, 0, 1, 0, 0},
                      {0, 3, 0, 6, 0, 7, 0, 0, 9},

                      {0, 2, 0, 0, 9, 0, 0, 0, 0},
                      {0, 0, 0, 0, 8, 0, 0, 0, 5},
                      {3, 0, 0, 2, 0, 5, 0, 4, 0},

                      {0, 6, 0, 5, 0, 3, 0, 0, 7},
                      {0, 0, 0, 0, 0, 8, 0, 0, 0},
                      {0, 0, 7, 0, 0, 0, 0, 9, 0}};

    for (int i = 0; i < sudoku->size; i++) {
        for (int j = 0; j < sudoku->size; j++) {
            sudoku->grid[i][j] = grid[i][j];
        }
    }
    displaySudoku(sudoku);
    printf("\n");
    SudokuSolver(sudoku);

    return 0;
}