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

SudokuPtr initSudoku(int);
void readSudoku(SudokuPtr);
void displaySudoku(SudokuPtr);
void SudokuSolver(SudokuPtr);
void destroySudoku(SudokuPtr);

#endif // CODE_SUDOKU_H