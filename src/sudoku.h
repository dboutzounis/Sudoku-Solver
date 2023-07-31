/* This file includes the struct and the functions for Sudoku */

#pragma once

#ifndef CODE_SUDOKU_H
#define CODE_SUDOKU_H

/* Decalring the Sudoku struct */
typedef struct sudoku {
    int **grid;
    int size;
    int squareRootOfSize;
} Sudoku;

typedef Sudoku *SudokuPtr;

Sudoku *initSudoku(int, int);
void displaySudoku(SudokuPtr);
int **getGrid(SudokuPtr);
int getSize(SudokuPtr);
int getSquareRootOfSize(SudokuPtr);
int getMissingDigits(SudokuPtr);

#endif // CODE_SUDOKU_H