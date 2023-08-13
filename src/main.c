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

    if (size == 4)
        printf("Now it's time to give the Sudoku that you want to be solved.\nThe Sudoku's assigned values must be from '1' to '4'.\nThe Sudoku's unassigned values must be represented with '.'.\nHere is an input example for a 4x4 Sudoku:\n3......24....1..\nPlease give the Sudoku:\n");
    else if (size == 9)
        printf("Now it's time to give the Sudoku that you want to be solved.\nThe Sudoku's assigned values must be from '1' to '9'.\nThe Sudoku's unassigned values must be represented with '.'.\nHere is an input example for a 9x9 Sudoku:\n....8497...5.......4.7..6.3...........217...46...9..3...9.....6.6..21....37..5.9.\nPlease give the Sudoku:\n");
    else
        printf("Now it's time to give the Sudoku that you want to be solved.\nThe Sudoku's assigned values must be from '1' to '9' and from 'A' to 'G'.\nThe Sudoku's unassigned values must be represented with '.'.\nHere is an input example for a 16x16 Sudoku:\n....6........D.16.A.....9.1C.E.4G.FD2A1.4......C.1.4......6..7A.1.....F..5.......AGBD...7.46.9..E..F....G.81..53..4.1..6...37G.A..3....7.9.AB..G..75.D.2C....8....CEAF43..2....9.F.8B......5A.7....C5....GEF..6.D..9.BA.8....4....2.4....A..C.D......G.F2DB.9...\nPlease give the Sudoku:\n");

    readSudoku(sudoku);
    printf("\n");

    displaySudoku(sudoku);
    printf("\n");

    SudokuSolver(sudoku);

    destroySudoku(sudoku);
    printf("\nProgram exited:)\n");

    return 0;
}