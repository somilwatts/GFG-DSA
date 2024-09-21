#include <iostream>
using namespace std;

const int SIZE = 9;

// Function declare kiya hai
bool solveSudoku(int board[SIZE][SIZE]);
bool solveSudokuRecursive(int board[SIZE][SIZE], int emptyPositions[][2], int emptyCount, int index);
void findEmptyPositions(int board[SIZE][SIZE], int emptyPositions[][2], int &emptyCount);
bool isSafe(int board[SIZE][SIZE], int row, int col, int num);
void printBoard(int board[SIZE][SIZE]);

int main() {
    int board[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        cout << "Sudoku solved successfully!" << endl;
        printBoard(board);
    } else {
        cout << "Unsolvable Sudoku puzzle!" << endl;
    }

    return 0;
}

bool solveSudoku(int board[SIZE][SIZE]) {
    int emptyPositions[SIZE * SIZE][2];
    int emptyCount = 0;
    findEmptyPositions(board, emptyPositions, emptyCount);
    return solveSudokuRecursive(board, emptyPositions, emptyCount, 0);
}

bool solveSudokuRecursive(int board[SIZE][SIZE], int emptyPositions[][2], int emptyCount, int index) {
    if (index == emptyCount) {
        return true;
    }

    int row = emptyPositions[index][0];
    int col = emptyPositions[index][1];

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudokuRecursive(board, emptyPositions, emptyCount, index + 1)) {
                return true;
            }
            board[row][col] = 0;
        }
    }

    return false;
}

void findEmptyPositions(int board[SIZE][SIZE], int emptyPositions[][2], int &emptyCount) {
    emptyCount = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                emptyPositions[emptyCount][0] = row;
                emptyPositions[emptyCount][1] = col;
                emptyCount++;
            }
        }
    }
}

bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num) {
            return false;
        }
    }

    for (int x = 0; x < SIZE; x++) {
        if (board[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

void printBoard(int board[SIZE][SIZE]) {
    for (int r = 0; r < SIZE; r++) {
        for (int d = 0; d < SIZE; d++) {
            cout << board[r][d] << " ";
        }
        cout << endl;
        if ((r + 1) % 3 == 0) {
            cout << endl;
        }
    }
}
