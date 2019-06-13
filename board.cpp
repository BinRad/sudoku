#include "board.h"
#include <iostream>

namespace sudoku_one{

    board::board() {
	// matrix that holds restricted data
//	int ini[9][9]
              //matrix that holds general data
        for(int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++) {
                 init[i][j] = 0;
                 matrix[i][j] = 0;
            }
        }
    }
    board::~board() {//inline function}
    }
    // Modification functions
    void board::mod_ini(int x, int y, int entry) {
                matrix[x][y] = entry;
                init[x][y] = entry;
    }
    void board::mod(int x, int y, int entry) {
        matrix[x][y] = entry;
    }
    void board::mod_temp(int x, int y, int entry, bool green) {
        int tempx = x;
        int tempy = y;
        if (green) {
            matrix[x][y] = entry;
        }
    }
    void const board::printout() {
      for(int i = 0; i < 9; i++){
          std::cout << std::endl;
          for(int j = 0; j < 9; j++){
              std::cout << init[i][j] << " ";
          }
        }
        std::cout << std::endl;
        for(int i = 0; i < 9; i++){
            std::cout << std::endl;
            for(int j = 0; j < 9; j++){
                std::cout << matrix[i][j] << " ";
            }
          }
        std::cout << std::endl;
    }
}
