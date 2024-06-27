#ifndef SUDOKU_H
#define SUDOKU_H
#pragma once
#include <array>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>

class sudoku {
    public:
        sudoku(std::string);
        void print();
        void solveSudoku();
        friend std::ostream& operator<<(std::ostream&, const sudoku&);
    private:        
        std::string filename;
        std::vector<std::vector<int>> board;
        void buildBoard(std::string _filename);
        int get_cell(int, int);
        std::pair<int, int> next_empty(std::vector<std::vector<int>> &board, int row_start, int col_start);
        int get_next_row(int row, int col);
        int get_next_col(int col);
        bool solve(std::vector<std::vector<int>> &board, int const row_start, int const col_start, std::array<std::bitset<9>,9>& row_contains, std::array<std::bitset<9>,9>& col_contains, std::array<std::bitset<9>,9>& cell_contains);
};

#endif
