#include "sudoku.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

sudoku::sudoku(std::string _filename)
{
    board = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    std::vector<int> flatboard = buildFlatBoard(_filename);
    buildBoard(flatboard);
}

void sudoku::buildBoard(std::vector<int> flatboard)
{
    int count = 0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            board[i][j] = flatboard[count++];
        }
    }
}

std::vector<int> sudoku::buildFlatBoard(std::string _fileName)
{
    std::vector<int> flatboard = std::vector<int>(81, 0);
    std::ifstream inputFile(_fileName);
    if (!inputFile.is_open())
    {
        throw std::invalid_argument("Error opening file");
    }
    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string fileContents = ss.str();
    int count = 0;
    while (ss.good())
    {
        std::string substr;
        std::getline(ss, substr, ' ');
        flatboard[count++] = std::stoi(substr);
    }

    return flatboard;
}

void sudoku::print()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void sudoku::solveSudoku()
{
    std::array<std::bitset<9>, 9> row_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // 9 sets of 9 bits, 1 means already been used. Now we can you primitive operators to check if a digit has been used
    std::array<std::bitset<9>, 9> col_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::array<std::bitset<9>, 9> cell_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            //mark integers that are already in the board
            if (board[row][col] != 0)
            {
                int digit = board[row][col];
                int digitIdx = digit - 1;
                row_contains[row].set(digitIdx); //given index is true
                col_contains[col].set(digitIdx);
                int cell = get_cell(row, col);
                cell_contains[cell].set(digitIdx);
            }
        }
    }

    bool result = solve(board, 0, 0, row_contains, col_contains, cell_contains);
    std::cout << "Solved: " << result << std::endl;
    int x = 0;
}

bool sudoku::solve(std::vector<std::vector<int>> &board, int const row_start, int const col_start, std::array<std::bitset<9>, 9> &row_contains, std::array<std::bitset<9>, 9> &col_contains, std::array<std::bitset<9>, 9> &cell_contains)
{
    //find the next empty cell
    auto [row, col] = next_empty(board, row_start, col_start);

    if (row == 9)
    {
        return true;
    }
    
    int const cell = get_cell(row, col);
    std::bitset<9> const contains = row_contains[row] | col_contains[col] | cell_contains[cell]; //bitwise OR operator
    if(contains.all()){
        return false;
    }

    for(int digit_idx = 0; digit_idx < 9; ++digit_idx){
        if(!contains[digit_idx]){
            board[row][col] = digit_idx + 1; //put digit on board
            row_contains[row].set(digit_idx); //mark digit as used
            col_contains[col].set(digit_idx);
            cell_contains[cell].set(digit_idx);
            //recursively solve the board
            if (solve(board, row, col, row_contains, col_contains, cell_contains)){
                return true;
            }

            //if solve is false, backtrack
            row_contains[row].reset(digit_idx);
            col_contains[col].reset(digit_idx);
            cell_contains[cell].reset(digit_idx);
        }
    }

    board[row][col] = 0;
    return false;
}

std::pair<int, int> sudoku::next_empty(std::vector<std::vector<int>> &board, int row, int col)
{
    //returns next position or a position off the board (base case)
    while(row != 9){
        if(board[row][col] == 0){
            return {row, col};
        }
        row = get_next_row(row, col);
        col = get_next_col(col);
    }

    return {9, 0};
}

int sudoku::get_cell(int row, int col)
{
    //return the cell index by dividing the row and column by 3
    return (row / 3) * 3 + col / 3;
}

int sudoku::get_next_row(int row, int col){
    //return the next row by adding 1 to the row and dividing the column by 9
    return row + (col + 1) / 9;
}

int sudoku::get_next_col(int col){
    //return the next column by adding 1 to the column and taking the modulus of 9
    return (col + 1) % 9;
}

std::ostream &operator<<(std::ostream &output, const sudoku &sud)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            output << sud.board[i][j] << " ";
        }
        output << std::endl;
    }
    return output;
}
