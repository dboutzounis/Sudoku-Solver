# Sudoku-Solver

![](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExbDZxYXQ5aDA4bzh5b2cyamc1eHc2M2R2dm5rYnFtdXN6bWh3c3B5NyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/l41Yy6jvn3BXYDRu0/giphy.gif)

## Definition

A puzzle in which a grid consisting of several regions is to be filled with numbers so that every row, column, and region contains only one instance of each number. The most common format is a grid of nine rows and columns that are divided into nine smaller regions of three rows and three columns into which the numbers 1 through 9 must be placed.

## Implementation

This project is using the Dancing Links(DLX) technique by Donald E. Knuth (https://arxiv.org/pdf/cs/0011047.pdf) for adding and deleting a node from a circular doubly linked list, which is very efficiently for implementing Knuth's Algorithm X for the Exact Cover problem.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/37/Dancing_links.svg/1920px-Dancing_links.svg.png)

Algorithm X is a recursive, nondeterministic, depth-first, backtracking algorithm that finds all solutions to the exact cover problem. Some of the better-known exact cover problems include tiling, the n queens problem, and Sudoku.

1. If A is empty, the problem is solved; terminate successfully.
2. Otherwise choose a column, c (deterministically).
3. Choose a row, r, such that A[r, c] = 1 (nondeterministically).
4. Include r in the partial solution.
5. For each j such that A[r, j] = 1,
   delete column j from matrix A;
   for each i such that A[i, j] = 1,
   delete row i from matrix A.

6. Repeat this algorithm recursively on the reduced matrix A.

The solver begins by transforming the Sudoku grid into an Exact Cover Problem Matrix using the following constraints:

-   Row-Column: Each intersection of a row and column, i.e, each cell, must contain exactly one number.
-   Row-Number: Each row must contain each number exactly once.
-   Column-Number: Each column must contain each number exactly once.
-   Box-Number: Each box must contain each number exactly once.

Then it selects the rows in the constraint matrix of the cells that are already present in the given Sudoku grid and make sure they are in the final solution.

Finally it solves the Exact Cover Problem for the constraint matrix with the selected rows using the Algorithm X and converts the Exact Cover matrix into a Sudoku grid.

## Compile and Run

-   For compiling the Sudoku-Solver Project:

    ```
    $ make
    ```

-   For removing the objective and executable files

    ```
    $ make clean
    ```

-   For running the Sudoku-Solver

    ```
    $ ./sudoku
    ```

    Τhe program will request the Sudoku grid size, which can be 4, 9 or 16. Then it will ask for the Sudoku grid's values. The assigned values are represented with numbers from '1' to '4' for 4x4 Sudokus, '1' to '9' for 9x9 Sudokus and '1' to '9' and 'A' to 'G' for 16x16 Sudokus. The unassigned values are reprsented with '.' . In the data/ folder there are 4x4, 9x9, 16x16 Sudokus for testing. Finally, it will print the original and solved Sudoku (gives all solutions but Sudokus must only have one) based on the above information.
