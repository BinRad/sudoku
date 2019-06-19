#include "board.h"
#include <iostream>

namespace sudoku_one{

    board::board() {
	// matrix that holds restricted data
//	int ini[9][9]
              //matrix that holds general data
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
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
    void const board::printout(int m) {
      if(m == 0 || m == 1){
      std::cout << "\n initial board:";
      for(int i = 0; i < 9; i++){
          std::cout << std::endl;
          for(int j = 0; j < 9; j++){
              std::cout << init[i][j] << " ";
          }
        }
      }
        std::cout << std::endl;
        if(m == 0 || m == 2){
        std::cout << "\n current board:";
        for(int i = 0; i < 9; i++){
            std::cout << std::endl;
            for(int j = 0; j < 9; j++){
                std::cout << matrix[i][j] << " ";
            }
          }
        }
          std::cout << std::endl;
          if(m == 0 || m == 3){
          std::cout << "\n rank:";
          for(int i = 0; i < 9; i++){
              std::cout << std::endl;
              if( i == 3 || i==6){
                std::cout << std::endl;
              }
              for(int j = 0; j < 9; j++){
                  std::cout << rank[i][j] << " ";
                  if(j == 2 || j == 5){
                    std::cout << "  ";
                  }
              }
            }
            std::cout << "\n";
    }
  }
    void board::clearrank(){
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            rank[i][j] = 0;
          }
        }
      }

    int board::read(int x, int y){
      return matrix[x][y];
    }
    int board::readrank(int x, int y){
      return rank[x][y];
    }
}
