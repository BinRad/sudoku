#include <iostream>
#include "board.h"

int* rank(sudoku_one::board& lev);

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
    // TODO: SOLVER TWO
    // create a rank system so that it fills out
    // the most obvious entries first
    int *p;
    p  = rank(lev);
    std::cout << *(p+1) << *(p+2) << "\n";
      return 0;
}

int* rank(sudoku_one::board& lev){
  //RANK
  int x = 0;
  int y = 0;
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(lev.read(i, j) != 0){
        lev.modrank(i, j, lev.readrank(i, j) + 1);
      }
    }
  }
  lev.printout();
  // SUM SECTION
  int section[9];
  for(int i = 0; i < 9; i++){
  section[i] = 0;
  }
  for(int k = 0; k < 3; k++){ // goes through each section
  for(int i = 0; i < 3; i++){ //rows
    for(int j = 0; j < 3; j++){ //columns
      section[k] += lev.readrank(i, j + (k*3));
      section[k + 3] += lev.readrank(i + 3, j + (k*3));
      section[k + 6] += lev.readrank(i + 6, j + (k*3));
    }
  }
  }
  // add sum section value to eahc entry in that SECTION
  // if there is an entry there alredy then we rank it 0 which is what
  // the if and else statements do
  for(int k = 0; k < 3; k++){ // goes through each section
    for(int i = 0; i < 3; i++){ //rows
      for(int j = 0; j < 3; j++){ //columns
          if(lev.readrank(i, j + (k*3)) == 0){
            lev.modrank(i, j + (k*3), lev.readrank(i, j + (k*3)) + section[k]);
          }
          else{lev.modrank(i, j + (k*3), 0);}
          if(lev.readrank(i + 3, j + (k*3)) == 0){
            lev.modrank(i + 3, j + (k*3), lev.readrank(i + 3, j + (k*3)) + section[k + 3]);
          }
          else{lev.modrank(3 + i, j + (k*3), 0);}
          if(lev.readrank(i + 6, j + (k*3)) == 0){
            lev.modrank(i + 6, j + (k*3), lev.readrank(i + 6, j + (k*3)) + section[k + 6]);
          }
          else{lev.modrank(i + 6, j + (k*3), 0);}
        }
      }
    }
    lev.printout(3);
    //rows
    int row = 0;
    for(int i = 0; i < 9; i++){ //rows
      row = 0;
      for(int j = 0; j < 9; j++){ //column
        if(lev.read(i,j) != 0){
          row++; // store how many values are in the row
        }
      }
      std::cout << "THIS IS THE ROW VALUE: " << row<< "    line:" << i << "\n";
      for(int q = 0; q < 9; q++){
        if(lev.readrank(i,q) != 0){
          lev.modrank(i, q, lev.readrank(i,q) + row);
        }
      }
    }
    //columns
    lev.printout(3);


    int soln[2];
    soln[0] = 0;
    soln[1] = 0;
    int temp = 0;
      for(int i = 0; i < 9; i++){ //rows
        for(int j = 0; j < 9; j++){ //columns
          if(lev.readrank(i, j) > temp){
            soln[0] = i;
            soln[1] = j;
            temp = lev.readrank(i, j);
          }
        }
      }
      lev.printout(3);
      return soln;

}
