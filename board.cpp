#include "board.h"
#include <iostream>

namespace sudoku_one{

    board::board() {
	// matrix that holds restricted data
//	int ini[9][9]
              //matrix that holds general data
        int matrix[9][9];
        for(int i = 0; i<=8; i++){
            for (int j = 0; j <= 8; j++) {
                 init[i][j] = 0;
                 matrix[i][j] = 0;
            }
        }
    }
    board::~board() {//inline function
        delete[] init;
        delete[] matrix;
    }
    // Modification functions
    void board::mod_ini(int x, int y, int &entry) {
                matrix[x][y] = entry;
    }
    void board::mod_perm(int x, int y, int &entry) {
        matrix[x][y] = entry;
    }
    void board::mod_temp(int x, int y, int &entry, bool green) {
        int tempx = x;
        int tempy = y;
        if (green) {
            matrix[x][y] = entry;
        }
    }
    void board::printout() {
        for(int i = 0; i<=8; i++){
            std::cout << "/n";
            for(int j = 0; j <= 8; j++){
                std::cout << matrix[i][j];
            }  }
    }
}
