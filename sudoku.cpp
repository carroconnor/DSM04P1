#include "sudoku.h"
#include <fstream> 
#include <iostream> 
#include <sstream>
#include <string>

sudoku::sudoku(std::string _filename){
    
}

void sudoku::buildFlatBoard(std::string _fileName){
    std::ifstream inputFile(_fileName);
    if(!inputFile.is_open()){
        throw std::invalid_argument( "Error opening file" ); 
    }
    std::stringstream ss;
    ss << inputFile.rdbuf();
    std::string fileContents = ss.str();
    int count = 0;
    while( ss.good() )
    {
        std::string substr;
        std::getline( ss, substr, ',' );
        flatboard[count++] = stoi(substr);
    }
}

void sudoku::print(){

}

void sudoku::solve(){

}

std::ostream& operator<<(std::ostream& output, const sudoku& sud) {
    output << "" << std::endl;
    return output;
}
