// TODO: Make a sudoku game
//Just checking to make sure everything is working
#include <iostream>
#include "board.h"



int main(){
    sudoku_one::board lev;
    for(int i = 0; i<=8; i++){
        for(int j = 0; j <= 8; j++){
            int q = 0;
            std::cin >> q;
            lev.mod_ini(i , j, q);
        }
    }
    lev.printout();
}
