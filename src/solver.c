#include "Dancing-Links/dancing-links.h"
#include "sudoku.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definition of the Exact Cover Problem struct */
typedef struct exact_cover {
    Node *head;
    Node **answer;
    Node **original;
    int **matrix;
    int row;
    int col;
    int size;
    int isSolved;
} ExactCover;

/* Function for initializing the Exact Cover Problem */
ExactCover *initExactCover(Sudoku *sudoku) {
    ExactCover *ex_cover = malloc(sizeof(ExactCover));
    ex_cover->head = NULL;
    ex_cover->answer = malloc(500 * sizeof(NodePtr));
    ex_cover->original = malloc(500 * sizeof(NodePtr));
    for (int i = 0; i < 500; i++) {
        ex_cover->answer[i] = NULL;
        ex_cover->original[i] = NULL;
    }
    ex_cover->row = sudoku->size * sudoku->size * sudoku->size;
    ex_cover->col = 4 * sudoku->size * sudoku->size;
    ex_cover->matrix = malloc(ex_cover->row * sizeof(int *));
    for (int i = 0; i < ex_cover->row; i++) {
        ex_cover->matrix[i] = malloc(ex_cover->col * sizeof(int));
        memset(ex_cover->matrix[i], 0, ex_cover->col * sizeof(int));
    }
    ex_cover->size = sudoku->size;
    ex_cover->isSolved = 0;
    return ex_cover;
}

// Function to destroy the ExactCover struct
void destroyExactCover(ExactCover *ex_cover) {
    if (ex_cover == NULL)
        return;

    destroyNode(ex_cover->head);

    for (int i = 0; i < 500; i++) {
        destroyNode(ex_cover->answer[i]);
        destroyNode(ex_cover->original[i]);
    }

    for (int i = 0; i < ex_cover->row; i++)
        free(ex_cover->matrix[i]);
    free(ex_cover->matrix);

    free(ex_cover);
}

/* Function for creating the Sparse Matrix of the Exact Cover Problem */
void makeSparseMatrix(ExactCover *ex_cover) {
    // Row-Column: Each intersection of a row and column, i.e, each cell, must contain exactly one number.
    for (int col = 0; col < ex_cover->size * ex_cover->size; col++)
        for (int row = 0; row < ex_cover->size; row++)
            ex_cover->matrix[row + col * ex_cover->size][col] = 1;

    // Row-Number: Each row must contain each number exactly once.
    int col_offset = ex_cover->size * ex_cover->size;
    for (int col = ex_cover->size * ex_cover->size; col < 2 * ex_cover->size * ex_cover->size; col++) {
        int adjusted_col = col % (ex_cover->size * ex_cover->size);
        int col_block = adjusted_col / ex_cover->size;
        for (int row = 0; row < ex_cover->size; row++) {
            int x = row + (col_block * ex_cover->size) + col_offset;
            int y = adjusted_col * ex_cover->size + row;
            ex_cover->matrix[y][x] = 1;
        }
    }

    // Column-Number: Each column must contain each number exactly once.
    col_offset = 2 * ex_cover->size * ex_cover->size;
    for (int col = 2 * ex_cover->size * ex_cover->size; col < 3 * ex_cover->size * ex_cover->size; col++) {
        int adjusted_col = col % (ex_cover->size * ex_cover->size);
        for (int row = 0; row < ex_cover->size; row++) {
            int x = (row + adjusted_col * ex_cover->size) % (ex_cover->size * ex_cover->size) + col_offset;
            int y = adjusted_col * ex_cover->size + row;
            ex_cover->matrix[y][x] = 1;
        }
    }

    // Box-Number: Each box must contain each number exactly once.
    int s_size = sqrt(ex_cover->size);
    col_offset = 3 * ex_cover->size * ex_cover->size;
    for (int col = 3 * ex_cover->size * ex_cover->size; col < 4 * ex_cover->size * ex_cover->size; col++) {
        int adjusted_col = col % (ex_cover->size * ex_cover->size);
        int col_block = (adjusted_col / s_size) % s_size;
        for (int row = 0; row < ex_cover->size; row++) {
            int x = col_offset + row + (col_block + (adjusted_col / (ex_cover->size * s_size)) * s_size) * ex_cover->size;
            int y = adjusted_col * ex_cover->size + row;
            ex_cover->matrix[y][x] = 1;
        }
    }
}

/* Function for creating the Torodial Double Linked List from the Sparse Matrix */
void makeTorodialDList(ExactCover *ex_cover) {
    NodePtr head = malloc(sizeof(Node));
    head->left = head;
    head->right = head;
    head->up = head;
    head->down = head;
    head->size = -1;
    head->colHead = head;

    NodePtr temp = head;

    for (int i = 0; i < ex_cover->col; i++) {
        NodePtr node = malloc(sizeof(Node));
        node->left = temp;
        node->right = head;
        node->up = node;
        node->down = node;
        node->colHead = node;
        node->size = 0;
        temp->right = node;
        temp = node;
    }

    int id[3] = {0, 1, 1};

    for (int i = 0; i < ex_cover->row; i++) {
        NodePtr cur = head->right, prev = NULL;

        if (i != 0 && i % (ex_cover->size * ex_cover->size) == 0) {
            id[0] -= ex_cover->size - 1;
            id[1]++;
            id[2] -= ex_cover->size - 1;
        } else if (i != 0 && i % ex_cover->size == 0) {
            id[0] -= ex_cover->size - 1;
            id[2]++;
        } else {
            id[0]++;
        }

        for (int j = 0; j < ex_cover->col; j++, cur = cur->right) {
            if (ex_cover->matrix[i][j]) {
                NodePtr node = malloc(sizeof(Node));
                node->id[0] = id[0];
                node->id[1] = id[1];
                node->id[2] = id[2];
                if (prev == NULL) {
                    prev = node;
                    prev->right = node;
                }
                node->left = prev;
                node->right = prev->right;
                node->right->left = node;
                prev->right = node;
                node->up = cur->up;
                node->down = cur;
                node->colHead = cur;
                cur->up->down = node;
                (cur->size)++;
                cur->up = node;
                if (cur->down == cur)
                    cur->down = node;
                prev = node;
            }
        }
    }

    ex_cover->head = head;
}

/* Function for transforming the Torodial Double Linked List based on the Sudoku Grid */
void transformTorodialDList(ExactCover *ex_cover, Sudoku *sudoku) {
    int pos = 0;

    for (int i = 0; i < sudoku->size; i++) {
        for (int j = 0; j < sudoku->size; j++) {
            if (sudoku->grid[i][j] != 0) {
                NodePtr col = NULL;
                NodePtr temp = NULL;
                int flag = 0;
                for (col = ex_cover->head->right; col != ex_cover->head; col = col->right) {
                    for (temp = col->down; temp != col; temp = temp->down)
                        if (temp->id[0] == sudoku->grid[i][j] && temp->id[1] - 1 == i && temp->id[2] - 1 == j) {
                            flag = 1;
                            break;
                        }
                    if (flag)
                        break;
                }
                if (flag) {
                    cover(col);
                    ex_cover->original[pos++] = temp;
                    for (NodePtr node = temp->right; node != temp; node = node->right)
                        cover(node->colHead);
                }
            }
        }
    }
}

/* Function for mapping the answer of the Exact Cover Problem to the Sudoku Grid */
void MapAnswer(ExactCover *ex_cover, Sudoku *sudoku) {
    for (int i = 0; ex_cover->answer[i] != NULL; i++)
        sudoku->grid[ex_cover->answer[i]->id[1] - 1][ex_cover->answer[i]->id[2] - 1] = ex_cover->answer[i]->id[0];

    for (int i = 0; ex_cover->original[i] != NULL; i++)
        sudoku->grid[ex_cover->original[i]->id[1] - 1][ex_cover->original[i]->id[2] - 1] = ex_cover->original[i]->id[0];
}

/* Algorithm X of Donald Knuth */
/* Function for searching the solution of the Exact Cover Problem */
void search(ExactCover *ex_cover, Sudoku *sudoku, int k) {
    if (ex_cover->head == ex_cover->head->right) {
        SudokuPtr copy = initSudoku(sudoku->size);
        MapAnswer(ex_cover, copy);
        displaySudoku(copy);
        destroySudoku(copy);
        ex_cover->isSolved = 1;
        return;
    }

    NodePtr col = chooseColumn(ex_cover->head);
    cover(col);

    for (NodePtr i = col->down; i != col; i = i->down) {
        ex_cover->answer[k] = i;
        for (NodePtr j = i->right; j != i; j = j->right)
            cover(j->colHead);
        search(ex_cover, sudoku, k + 1);
        i = ex_cover->answer[k];
        ex_cover->answer[k] = NULL;
        col = i->colHead;
        for (NodePtr j = i->left; j != i; j = j->left)
            uncover(j->colHead);
    }
    uncover(col);
}

/* Function for solving the Sudoku */
void SudokuSolver(SudokuPtr sudoku) {
    ExactCover *ex_cover = initExactCover(sudoku);
    makeSparseMatrix(ex_cover);
    makeTorodialDList(ex_cover);
    transformTorodialDList(ex_cover, sudoku);
    search(ex_cover, sudoku, 0);
    if (!ex_cover->isSolved)
        printf("No solution found.\n");
    // destroyExactCover(ex_cover);
}