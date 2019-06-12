// TODO: Make a sudoku game
//Just checking to make sure everything is working
#include <iostream>
#include "board.h"



int main(){
    sudoku_one::board lev;
    for(int i = 0; i<9; i++){
      std::cout << "start line: " << i + 1 << "\n";
        for(int j = 0; j < 9; j++){
            int q = 0;
            std::cin >> q;
            if(q == 10 && j == 0){
              for(int r = 0; r < 9; r++){
              q = 0;
              lev.mod_ini(i, j+r, q);
            }
              j = 0;
              i++;
            }
            else{
              lev.mod_ini(i , j, q);
            }
        }
      std::cout << "end line: " << i + 1 << "\n";
    }
    lev.printout();
}
