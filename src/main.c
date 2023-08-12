#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int size;

    printf("WELCOME TO THE SUDOKU SOLVER!\n\n");
    printf("What is the size of the Sudoku grid? ");
    scanf("%d", &size);
    while (size != 4 && size != 9 && size != 16) {
        printf("You gave an uncompatible size.\nSudoku grid sizes must be 4, 9 or 16.\nPlease give the Sudoku grid size again: ");
        scanf("%d", &size);
    }
    printf("\n");

    SudokuPtr sudoku = initSudoku(size);

    printf("Now it's time to give the Sudoku that you want to be solved.\nThe Sudoku's assigned values must be from 1 to %d.\nThe Sudoku's unassigned values must be represented with '.'.\nHere is an input example for a 9x9 Sudoku:\n....8497...5.......4.7..6.3...........217...46...9..3...9.....6.6..21....37..5.9.\nPlease give the Sudoku:\n", size);
    readSudoku(sudoku);
    printf("\n");

    displaySudoku(sudoku);
    printf("\n");

    SudokuSolver(sudoku);

    destroySudoku(sudoku);
    printf("\nProgram exited:)\n");

    return 0;
}