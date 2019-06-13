// TODO: Make a sudoku game
//Just checking to make sure everything is working
#include <iostream>
#include "board.h"



int main(){
    sudoku_one::board lev;
    for(int i = 0; i < 9; i++){
      std::cout << "start line: " << i + 1 << "\n";
        for(int j = 0; j < 9; j++){
            int q = 0;
            std::cin >> q;
            lev.mod_ini(i , j, q);
        }
      std::cout << "end line: " << i + 1 << "\n";
      if( i > 8){
        std::cout << "all done here, good luck \n";

      }
    }
    std::cout << "Finished the for loop \n";
    lev.printout();
    return 0;
}
