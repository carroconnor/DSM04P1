#include "sudoku.h"

/* Program name: sudoku.cpp
* Author: Carr O'Connor
* Date last updated: 6/25/2024
* Purpose: Solve a sudoku puzzle using backtracking
*/

int main(){
    sudoku test("sudoku.txt");
    test.print();
    test.solveSudoku();
    test.print();
    return 0;
}
