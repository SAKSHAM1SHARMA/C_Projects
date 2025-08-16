#include <stdio.h>

int puzzle[9][9] = {
    {3,0,0,0,2,0,0,7,0},
    {9,0,0,5,0,0,0,1,4},
    {0,1,6,3,7,0,0,0,8},
    {2,0,0,8,0,0,0,0,1},
    {5,0,0,0,4,1,8,0,0},
    {0,8,9,0,0,0,0,5,0},
    {0,0,5,0,1,0,2,8,0},
    {0,4,0,0,0,6,0,9,3},
    {7,3,1,0,8,2,0,0,0},
};

int fixed[9][9];  // Will store which cells are fixed

// Function declarations
void print_puzzle(int puzzle[9][9]);
int valid_puzzle(int puzzle[9][9], int row, int column, int val);
int sudoku_solver(int puzzle[9][9], int fixed[9][9], int row, int column);
int is_given_puzzle_valid(int puzzle[9][9]);

int main() {
    // Check if initial puzzle is valid
    if (!is_given_puzzle_valid(puzzle)) {
        printf("The provided Sudoku puzzle is INVALID!\n");
        return 1;
    }

    // Mark fixed (non-zero) cells
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            fixed[i][j] = (puzzle[i][j] != 0);
        }
    }

    printf("Welcome to SUDOKU Solver!!");
    printf("\nOriginal Puzzle:");
    print_puzzle(puzzle);

    if (sudoku_solver(puzzle, fixed, 0, 0)) {
        printf("\nSolved Puzzle:");
        print_puzzle(puzzle);
    } else {
        printf("\nNo solution exists for this puzzle.\n");
    }

    return 0;
}

int is_given_puzzle_valid(int puzzle[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int val = puzzle[i][j];
            if (val < 0 || val > 9) {
                return 0; // Invalid number
            }
            if (val != 0) {
                puzzle[i][j] = 0;  // Temporarily clear the cell
                if (!valid_puzzle(puzzle, i, j, val)) {
                    puzzle[i][j] = val;  // Restore
                    return 0; // Violates Sudoku rules
                }
                puzzle[i][j] = val;  // Restore
            }
        }
    }
    return 1;
}

int valid_puzzle(int puzzle[9][9], int row, int column, int val) {
    // Check row
    for(int i = 0; i < 9; i++) {
        if(puzzle[row][i] == val) {
            return 0;
        }
    }

    // Check column
    for(int i = 0; i < 9; i++) {
        if(puzzle[i][column] == val) {
            return 0;
        }
    }

    // Check 3x3 grid
    int r = row - row % 3;
    int c = column - column % 3;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(puzzle[r + i][c + j] == val) {
                return 0;
            }
        }
    }

    return 1;
}

int sudoku_solver(int puzzle[9][9], int fixed[9][9], int row, int column) {
    if(row == 9) return 1;
    if(column == 9) return sudoku_solver(puzzle, fixed, row + 1, 0);

    if(fixed[row][column]) {
        return sudoku_solver(puzzle, fixed, row, column + 1);
    }

    for(int num = 1; num <= 9; num++) {
        if(valid_puzzle(puzzle, row, column, num)) {
            puzzle[row][column] = num;

            if(sudoku_solver(puzzle, fixed, row, column + 1)) {
                return 1;
            }

            puzzle[row][column] = 0;  // Backtrack
        }
    }

    return 0;  // Trigger backtracking
}

void print_puzzle(int puzzle[9][9]) {
    printf("\n\n+-------+-------+-------+");
    for(int row = 0; row < 9; row++) {
        if(row % 3 == 0 && row != 0) {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");
        for(int column = 0; column < 9; column++) {
            if(column % 3 == 0) {
                printf("| ");
            }
            if(puzzle[row][column] == 0)
                printf(". ");
            else
                printf("%d ", puzzle[row][column]);
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}
