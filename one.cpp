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

    //This is the first solver::SOLVER ONE
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
          //double for loops goes through the board
        int answ = 1;
        //default entry when not specified is 1
        if(lev.read(i,j) == 0){
            for(int k = 0; k < 9; k++){
              //this goes throught the row and column of each
              //entry and incrments if # is already in column
              // then set k =0 so that it can check all the
              //entrys against the new answer
              if(lev.read(i,k) == answ){
                answ++;
                k = 0;
                std::cout << lev.read(i,k) << "==? " << answ-1 << "\n";
              }
              if(lev.read(k,j) == answ){
                  answ++;
                  k = 0;
              }
              if(k < 3){
                for(int z = 0; z < 3; z++){
                  if(lev.read(k, j) == answ){
                    answ++;
                    k = 0;
                  }
                }
              }
            }
        lev.mod(i,j, answ);

        if(answ > 9){std::cout << "Error!!       ";}
        }
        }
      }
lev.printout();



    return 0;
}

#include "board.cpp"
