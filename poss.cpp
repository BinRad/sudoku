#include "poss.h"
#include "rank.h"
#include "board.h"
#include <iostream>
#include "assert.h"

namespace sudoku_one {
  poss::poss(sudoku_one::board &lev, sudoku_one::rank &sim){
    lev.reset();
    for(int a = 0; a <81; a++){
      for(int b = 1; b < 9; b++){
        data[a][b] = finder(a,b, lev, finder(a,b,lev)+b -1);
        std::cout << data[a][b] << std::endl;
      }
      data[a][0] = 0;
      num[a] = 0;
    }
    sim.advance();
  }
  poss::~poss(){}
  int poss::finder(int i, int j, sudoku_one::board &lev, int entry){
    if(lev.read(i,j) != 0){
      return 0;
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
    if (entry > 9 || entry < 0) {
        return 0;
    } else {
        return entry;
    }
  }
//  bool poss::checker(i ,j,  )
  void poss::next(sudoku_one::board& lev, sudoku_one::rank &sim){
    if(data[ans][num[ans] + 1] != 0){//try the next possibility for the current
        num[ans]++;
    }
      else{
          ans++;
          sim.advance();
          assert(ans < 81);
      }
      for(int a = 0; a <81; a++){
        if(data[a][num[a]]!=0){
          lev.mod(a/9, a%9, data[a][num[a]]);
      }
    }
  }
}
