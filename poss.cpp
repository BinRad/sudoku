#include "rank.h"
#include "board.h"
#include "poss.h"
#include <iostream>

namespace sudoku_one {
  poss(sudoku_one::board &lev, sudoku_one::rank &sim){
    lev.reset();
    for(int a = 0; a <81; a++){
      for(int b = 0; b <9; b++){
        data[a][b] = finder(a,b, lev, finder(i,j,lev)+b);
      }
      num[a] = 0;
    }
  }
  ~poss(){}
  int finder(int i, int j, sudoku_one::board &lev, int entry){
    if(lev.read(i,j) != 0){
      return lev.read(i,j);
    }
    for (int k = 0; k < 9; k++) {
        //std::cout <<entry<< "      ";
        if (lev.read(i, k) == entry) {
            //std::cout << lev.read(i, k) << "==" << entry << std::endl;
            entry++;
            k = 0;
        }
        if (lev.read(k, j) == entry) {
            //std::cout << lev.read(k, j) << "==" << entry << std::endl;
            entry++;
            k = 0;
        }
        //SECTION CHECKER
        //std::cout << "point: " << i << "," << j << "    entry: " << entry << std::endl;
        if (k < 3) {
            if (i < 3) { //Section 1
                if (j < 3) {// section 1,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 1,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 1,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 1,k
            if (i > 2 && i < 6) {//section 2, k
                if (j < 3) {// section 2,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 2,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 2,3
                    for (int a = 6; a < 9; a++){
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 2,k
            if (i > 5 && i < 9) {//section 3,k
                if (j < 3) {// section 3,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 3,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 3,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 3,k
        }// end section checker
    }//end k
    if (entry > 9) {
        return 0;
    } else {
        return entry;
    }
  }
  sudoku_one::board next(sudoku_one::board& lev, sudoku_one::rank &sim){
    if(data[ans][num[ans] + 1] != 0 ){//try the next possibility for the current
        num[ans]++;
    }
      else{
          ans++;
      }
      for(int a = 0; a <81; a++){
          lev.mod(a/9, a%9, num[a]);
      }
      return lev;
  }
}
