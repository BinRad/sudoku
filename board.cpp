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
                 rank[i][j] = 0;
            }
        }
    }
    board::~board() {//inline function}
  }// i tried making a real destructor but it caused the matrices to be deleted prematurely
    // Modification functions
    void board::mod_ini(int x, int y, int entry) {
                matrix[x][y] = entry;
                init[x][y] = entry;
    }
    void board::mod(int x, int y, int entry) {
        matrix[x][y] = entry;
    }
    void board::modrank(int x, int y, int entry) {
        rank[x][y] = entry;
    }
    void const board::printout(int m) {
      if(m == 0 || m == 1){
      std::cout << "\n initial board:";
      for(int i = 0; i < 9; i++){
          std::cout << std::endl;
          if( i == 3 || i==6){
            std::cout << std::endl;
          }
          for(int j = 0; j < 9; j++){
              std::cout << init[i][j] << " ";
              if(j == 2 || j == 5){
                std::cout << "  ";
              }
          }
        }
      }
        std::cout << std::endl;
        if(m == 0 || m == 2){
        std::cout << "\n current board:";
        for(int i = 0; i < 9; i++){
            std::cout << std::endl;
            if( i == 3 || i==6){
              std::cout << std::endl;
            }
            for(int j = 0; j < 9; j++){
                std::cout << matrix[i][j] << " ";
                if(j == 2 || j == 5){
                  std::cout << "  ";
                }
            }
          }
        }
          std::cout << std::endl;
          if(m == 3){
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
    if(m == 4){
    std::cout << "\n Difference:";
    for(int i = 0; i < 9; i++){
        std::cout << std::endl;
        if( i == 3 || i==6){
          std::cout << std::endl;
        }
        for(int j = 0; j < 9; j++){
          if(init[i][j] == matrix[i][j]){
            std::cout << "  ";
          }
          else{
            std::cout << matrix[i][j] << " ";
          }

            if(j == 2 || j == 5){
              std::cout << "  ";
            }
        }
      }
    }
      std::cout << std::endl;
  }
    void board::clearrank(){
      for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            rank[i][j] = 0;
          }
        }
      }
    void board::reset(){
      for(int i = 0; i < 9; i++){
          for(int j = 0; j < 9; j++){
               matrix[i][j] = init[i][j];
           }
       }
       board::clearrank();
    }
    int const board::read(int x, int y){
      return matrix[x][y];
    }
    int const board::read_ini(int x, int y){
      return init[x][y];
    }
    int const board::readrank(int x, int y){
      return rank[x][y];
    }
}
