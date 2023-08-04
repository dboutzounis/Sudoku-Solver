#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    SudokuPtr sudoku = initSudoku(9);

    readSudoku(sudoku);

    displaySudoku(sudoku);
    printf("\n");

    SudokuSolver(sudoku);

    destroySudoku(sudoku);
    printf("\n");

    return 0;
}