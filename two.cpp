// two.cpp uses the ranking system to choose which
// number to find the answer to first that is most
// likely to be the most accurate using the what
// numbers are in the rows and columns and subsquare
// with it.
#include <iostream>
#include "board.h"
int* ranker(sudoku_one::board& lev);

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
  p = ranker(lev);
    while(*p != 99){
      //std::cout << *p;
      //<< "," << *(p+1) << "";
      int i = *p;//x coordiante of entry
      int j = *(p+1); //  y coordinate of entry
//copied from ONE.CPP
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
                  //std::cout << lev.read(i,k) << "==? " << answ-1 << "\n";
              }
              if(lev.read(k,j) == answ){
                  answ++;
                  k = 0;
              }
              if (k < 3) {
                  if (i < 3) { //Section 1
                      if (j < 3) {// section 1,1
                          for (int a = 0; a < 3; a++) {
                              //std::cout << k << "," << a <<std::endl;
                              if (lev.read(k, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 0;
                              }
                          }
                      }
                      if (j > 2 && j < 6) {//section 1,2
                          for (int a = 3; a < 6; a++) {
                              //std::cout << k << "," << a <<std::endl;
                              if (lev.read(k, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 3;
                              }
                          }
                      }
                      if (j > 5 && j < 9) {//section 1,3
                          for (int a = 6; a < 9; a++) {
                              //std::cout << k << "," << a <<std::endl;
                              if (lev.read(k, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 6;
                              }
                          }
                      }
                  }//end section 1,k
                  if (i > 2 && i < 6) {//section 2, k
                      if (j < 3) {// section 2,1
                          for (int a = 0; a < 3; a++) {
                              //std::cout << k + 3 << "," << a <<std::endl;
                              if (lev.read(k + 3, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 0;
                              }
                          }
                      }
                      if (j > 2 && j < 6) {//section 2,2
                          for (int a = 3; a < 6; a++) {
                              //std::cout << k + 3 << "," << a <<std::endl;
                              if (lev.read(k + 3, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 3;
                              }
                          }
                      }
                      if (j > 5 && j < 9) {//section 2,3
                          for (int a = 6; a < 9; a++){
                              //std::cout << k + 3 << "," << a <<std::endl;
                              if (lev.read(k + 3, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 6;
                              }
                          }
                      }
                  }//end section 2,k
                  if (i > 5 && i < 9) {//section 3,k
                      if (j < 3) {// section 3,1
                          for (int a = 0; a < 3; a++) {
                              //std::cout << k + 6 << "," << a <<std::endl;
                              if (lev.read(k + 6, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 0;
                              }
                          }
                      }
                      if (j > 2 && j < 6) {//section 3,2
                          for (int a = 3; a < 6; a++) {
                              //std::cout << k + 6 << "," << a <<std::endl;
                              if (lev.read(k + 6, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 3;
                              }
                          }
                      }
                      if (j > 5 && j < 9) {//section 3,3
                          for (int a = 6; a < 9; a++) {
                              //std::cout << k + 6 << "," << a <<std::endl;
                              if (lev.read(k + 6, a) == answ) {
                                  answ++;
                                  k = 0;
                                  a = 6;
                              }
                          }
                      }
                  }//end section 3,k
              }// end section checker
          }
      lev.mod(i,j, answ);//this will also take the entry out of the rankings
      if(answ > 9){std::cout << "Error!!       ";}
      }
      p = ranker(lev);//gets coordinates of easiest entry
    }
    lev.printout();
      return 0;
}

//FUNCTION RANKER
int* ranker(sudoku_one::board& lev){
  lev.clearrank();
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
    //rows
    int row = 0;
    for(int i = 0; i < 9; i++){ //rows
      row = 0;
      for(int j = 0; j < 9; j++){ //column
        if(lev.read(i,j) != 0){
          row++; // store how many values are in the row
        }
      }
      for(int q = 0; q < 9; q++){
        if(lev.readrank(i,q) != 0){
          lev.modrank(i, q, lev.readrank(i,q) + row);
        }
      }
    }
    //columns
    int col = 0;
    for(int j = 0; j < 9; j++){ //columna
      col = 0;
      for(int i = 0; i < 9; i++){ //rows
        if(lev.read(i,j) != 0){
          col++; // store how many values are in the row
        }
      }
      for(int q = 0; q < 9; q++){
        if(lev.readrank(q,j) != 0){
          lev.modrank(q, j, lev.readrank(q,j) + col);
        }
      }
    }
   int* soln = new int[2];
    soln[0] = 99;
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
      if(temp == 0){
        soln[0] = 99;
      }
    int *p = soln;
    return p;
}
#include "board.cpp"
