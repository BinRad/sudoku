#include "poss.h"
#include "rank.h"
#include "board.h"
#include <iostream>
#include "assert.h"

namespace sudoku_one {
    poss::poss(sudoku_one::board &lev, sudoku_one::rank &sim) {
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
              violator[a][b] = 0;
                for (int c = 0; c < 9; c++) {
                    for (int d = 0; d < 9; d++) {
                        matrics[a][b][c][d] = 0;
                    }
                }
                loop[a][b] = 0;
            }
        }
    }

    poss::~poss() {}

    int poss::finder(int i, int j, sudoku_one::board &lev, int entry) {
        if (lev.read(i, j) != 0) {
            return 0;
        }
        for (int k = 0; k < 9; k++) {
            //std::cout <<entry<< "      ";
            if (lev.read(i, k) == entry) {
                //std::cout << lev.read(i, k) << "==" << entry << std::endl;
                entry++;
                if (lev.read_ini(i, k) == 0) {
                    matrics[i][j][i][k] = 1;
                }
                k = 0;
            }
            if (lev.read(k, j) == entry) {
                //std::cout << lev.read(k, j) << "==" << entry << std::endl;
                entry++;
                if (lev.read_ini(k, j) == 0) {
                    matrics[i][j][k][j] = 1;
                }
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
                                if (lev.read_ini(k, a) == 0) {
                                    matrics[i][j][k][a] = 1;
                                }
                                k = 0;
                                a = -1;
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 1,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k, a) == entry) {
                                //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k, a) == 0) {
                                    matrics[i][j][k][a] = 1;
                                }
                                k = 0;
                                a = 2;

                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 1,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k, a) == entry) {
                                //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k, a) == 0) {
                                    matrics[i][j][k][a] = 1;
                                }
                                k = 0;
                                a = 5;
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
                                if (lev.read_ini(k + 3, a) == 0) {
                                    matrics[i][j][k + 3][a] = 1;
                                }
                                k = 0;
                                a = -1;
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 2,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k + 3, a) == 0) {
                                    matrics[i][j][k + 3][a] = 1;
                                }
                                k = 0;
                                a = 2;
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 2,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k + 3, a) == 0) {
                                    matrics[i][j][k + 3][a] = 1;
                                }
                                k = 0;
                                a = 5;
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
                                if (lev.read_ini(k + 6, a) == 0) {
                                    matrics[i][j][k + 6][a] = 1;
                                }
                                k = 0;
                                a = -1;
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 3,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k + 6, a) == 0) {
                                    matrics[i][j][k + 6][a] = 1;
                                }
                                k = 0;
                                a = 2;
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 3,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                                entry++;
                                if (lev.read_ini(k + 6, a) == 0) {
                                    matrics[i][j][k + 6][a] = 1;
                                }
                                k = 0;
                                a = 5;
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
         if (entry > 9 || entry < 0) {
        //     old_i = i;
        //     old_j = j;
             return 0;
         } else {return entry;}
    }

    bool poss::anti_loop(int i, int j, sudoku_one::board &lev) {
        if (loop[i][j] == 200) {//tolerance
            return false;
        } else {
            loop[i][j]++;
            return false;
        }
    }

    void poss::violation(int i, int j, sudoku_one::board &lev) {
      for (int c = 0; c < 9; c++) {
          for (int d = 0; d < 9; d++) {
              if (matrics[i][j][c][d] != 0){
              lev.mod(c,d, 0);
            }
          }
        }
        int entry, ans;
        entry = finder(i,j,lev);
        ans = finder(i,j,lev, entry +violator[i][j]);
        if(ans!= 0){
          lev.mod(i,j,ans);
          for (int c = 0; c < 9; c++) {
              for (int d = 0; d < 9; d++) {
                matrics[c][d][i][j] = 111;
              }
            }
          return;
        }
      violator[i][j]++;
      for(int c = 0; c < 9; c++){
         std::cout << std::endl;
         if( c == 3 || c==6){
           std::cout << std::endl;
         }
         for(int d = 0; d < 9; d++){
             std::cout << violator[c][d] << " ";
             if(d == 2 || d == 5){
               std::cout << "  ";
             }
         }
       }
        int temp = 0;
       // for (int a = 0; a < 9; a++) {
       //     for (int b = 0; b < 9; b++) {
       //         for (int c = 0; c < 9; c++) {
       //             for (int d = 0; d < 9; d++) {
       //                 if (matrics[a][b][c][d] == 2 || matrics[a][b][c][d] ==  3) {
       //                     matrics[a][b][c][d] = 1;
       //                 }
       //             }
       //         }
       //     }
       // }
        while (fix(99, 99, i, j, lev, temp) != true) {
            temp++;
            fix(99, 99, i, j, lev, temp);
        }
    }

    bool poss::fix(int i, int j, int a, int b, sudoku_one::board &lev, int count) {
        //i, j are the old values
        //a, b are the current values
        //std::cout <<i << j<< " " << a << b << std::endl;
        if (lev.read(i, j) != 0) {
          std::cout << "NONONO";
            return false;
        }
        int temp = 0;
        temp = next(a, b, lev, count);
        int x = temp / 9;
        int y = temp % 9;
        if (temp == 99) {
          //   if( i == 99 && j == 99){
          //     for (int c = 0; c < 9; c++) {
          //         for (int d = 0; d < 9; d++) {
          //       if(matrics[a][b][c][d] != 0){
          //         matrics[a][b][c][d] = 1;
          //       }
          //     }
          //   }
          // }
            matrics[i][j][a][b] = 111;

           lev.printout(4);
           for(int c = 0; c < 9; c++){
               std::cout << std::endl;
               if( c == 3 || c==6){
                 std::cout << std::endl;
               }
               for(int d = 0; d < 9; d++){
                   std::cout << matrics[i][j][c][d] << " ";
                   if(d == 2 || d == 5){
                     std::cout << "  ";
                   }
               }
             }

            int entry = finder(a, b, lev);
            if(lev.read(a,b) == entry){
              entry = finder(a, b, lev, entry + 1);}
            if (entry == 0) {
                if (count == 3) {
                    return fix(99, 99, i, j, lev, count);
                }
                if(next(a,b,lev,count) == 99){
                    return fix(i, j, a, b, lev, count + 1);
                }
            } else {
                lev.mod(a, b, entry);
                return true;
            }
        }
        lev.mod(x, y, 0);
        return fix(a, b, x, y, lev, count);
    }

    //if the entry "next" entry is = to count +1 then return it.
    //if the entry has already been used
    int poss::next(int a, int b, sudoku_one::board &lev, int count) {
        for (int c = 0; c < 9; c++) {
            for (int d = 0; d < 9; d++) {
                if (matrics[a][b][c][d] == count + 1) {
                    matrics[a][b][c][d] = count + 2;
                    return (c * 10) + d;
                }
            }
        }
        return 99;
    }
}
