#include "sudoku.h"

/* Program name: sudoku.cpp
* Author: Carr O'Connor
* Date last updated: 6/25/2024
* Purpose: Solve a sudoku puzzle using backtracking
*/

int main(){
    sudoku sud("sudoku.txt");
    sud.print();
    sud.solveSudoku();
    sud.print();
    return 0;
}
