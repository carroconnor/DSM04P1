#ifndef SUDOKU_H
#define SUDOKU_H
#pragma once
#include <string>
#include <iostream>

class sudoku {
    public:
        sudoku(std::string);
        void print();
        void solve();
        friend std::ostream& operator<<(std::ostream&, const sudoku&);
    private:
        int board [9][9];
        std::string filename;
        int flatboard[81] = {};
};

#endif
