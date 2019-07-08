a #include "rank.h"
#include "board.h"
#include <iostream>

namespace sudoku_one {
  four(sudoku_one::board &lev, sudoku_one::rank &sim){
        i = sim.getrow(0);
        j = sim.getcol(0);
        issue_x = 99;
        issue y = 99;
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                for (int c = 0; c < 9; c++) {
                    for (int d = 0; d < 9; d++) {
                        prob_row[a][b][c]= 0;
                        prob_col[a][b][c] = 0;
                        answers[a][b][c] = 0;
                        current_prob[a][b] = 0;
                        last_prob[a][b][c] = 0;
                        current_ans[a][b] = 0;
                        last_ans[a][b][c] = 0;
                        bad_entry_row[a][b][c] = 0;
                        bad_entry_col[a][b][c] = 0;
                        freed[a][b][c][d] = 0;
                    }
                }
            }
        }
        find_poss_entries(lev);
        solve(lev);
    }
  ~four(){}
  //modification functions
  void solve(sudoku_one::board &lev){
      entry = finder(lev);
      lev.mod(i, j, entry);
      sim.advance();
      i = sim.getrow();
      j = sim.getcol();
      solve(lev);
    }
  int finder(sudoku_one::board &lev){
      entry = answers[i][j][current_ans[i][j]];
      //while loop can be skipped if current ans is correct
      while(!finder_checker){
          entry = answers[i][j][current_ans[i][j]];
          if(entry == 99){
              entry = free_entry(lev);
              // free_entry will update current_ans
          }
          else{
              current_ans[i][j]++;
            }
      }
      return entry;
   }
  bool finder_checker(sudoku_one::board &lev){
      for (int k = 0; k < 9; k++) {
          if(lev.read(i, k) == entry){
              issue_x = i;
              issue_y = k;
              mark_bad(lev);
              return false;
           }
           if( lev.read(k, j) == entry)){
               issue_x = k;
               issue_y = j;
               mark_bad(lev);
               return false;
           }
          //SECTION CHECKER
          //std::cout << "point: " << i << "," << j << "    entry: " << entry << std::endl;
          if (k < 3) {
              if (i < 3) { //Section 1
                  if (j < 3) {// section 1,1
                      for (int a = 0; a < 3; a++) {
                          if (lev.read(k, a) == entry) {
                              issue_x = k;
                              issue_y = a;
                              mark_bad(lev);
                              return false;
                            }
                        }
                    }
                  if (j > 2 && j < 6) {//section 1,2
                      for (int a = 3; a < 6; a++) {
                          if (lev.read(k, a) == entry) {
                              return false;
                          }
                      }
                  }
                  if (j > 5 && j < 9) {//section 1,3
                      for (int a = 6; a < 9; a++) {
                          if (lev.read(k, a) == entry) {
                              issue_x = k;
                              issue_y = a;
                              mark_bad(lev);
                              return false;
                          }
                      }
                  }
              }//end section 1,k
              if (i > 2 && i < 6) {//section 2, k
                  if (j < 3) {// section 2,1
                      for (int a = 0; a < 3; a++) {
                          if (lev.read(k + 3, a) == entry) {
                              issue_x = k+3;
                              issue_y = a;
                              mark_bad(lev);
                             return false;
                          }
                      }
                  }
                  if (j > 2 && j < 6) {//section 2,2
                      for (int a = 3; a < 6; a++) {
                          if (lev.read(k + 3, a) == entry) {
                              issue_x = k+3;
                              issue_y = a;
                              mark_bad(lev);
                             return false;
                          }
                      }
                  }
                  if (j > 5 && j < 9) {//section 2,3
                      for (int a = 6; a < 9; a++) {
                          if (lev.read(k + 3, a) == entry) {
                              issue_x = k+3;
                              issue_y = a;
                              mark_bad(lev);
                              return false;
                          }
                      }
                  }
              }//end section 2,k
              if (i > 5 && i < 9) {//section 3,k
                  if (j < 3) {// section 3,1
                      for (int a = 0; a < 3; a++) {
                          if (lev.read(k + 6, a) == entry) {
                              issue_x = k+6;
                              issue_y = a;
                              mark_bad(lev);
                            return false;
                          }
                      }
                  }
                  if (j > 2 && j < 6) {//section 3,2
                      for (int a = 3; a < 6; a++) {
                          if (lev.read(k + 6, a) == entry) {
                              issue_x = k+6;
                              issue_y = a;
                              mark_bad(lev);
                              return false;
                            }
                        }
                    }
                  if (j > 5 && j < 9) {//section 3,3
                      for (int a = 6; a < 9; a++) {
                          if (lev.read(k + 6, a) == entry) {
                              issue_x = k+6;
                              issue_y = a;
                              mark_bad(lev);
                             return false;
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
        return true;
  }
  int mark_bad(sudoku_one::board &lev){

  }
  void find_poss_entries(sudoku_one::board &lev){
      int c = 0;
      for (int a = 0; a < 9; a++) {
          for (int b = 0; b < 9; b++) {
              c = 0;
                  for (int d = 1; d < 9; d++) {
                      if(poss_entry_checker(a,b, d, lev)){
                          answers[a][b][c] = d;
                          c++;
                        }
                    }
                    while(c < 9){
                        answers[a][b][c] = 99;
                        c++;
                    }
            }
        }
    }
  bool poss_entry_checker(int a, int b, int d, sudoku_one::board &lev){
      for (int k = 0; k < 9; k++) {
          if(lev.read_ini(a, k) == d){

              return false;
           }
           if( lev.read_ini(k, b) == d)){
               return false;
           }
          //SECTION CHECKER
          if (k < 3) {
              if (a< 3) { //Section 1
                  if (b < 3) {// section 1,1
                      for (int z = 0; z < 3; z++) {
                          if (lev.read_ini(k, z) == d) {
                              return false;
                            }
                        }
                    }
                  if (b > 2 && b < 6) {//section 1,2
                      for (int z = 3; z < 6; z++) {
                          if (lev.read_ini(k, z) == d) {
                              return false;
                          }
                      }
                  }
                  if (b > 5 && b < 9) {//section 1,3
                      for (int z = 6; z < 9; z++) {
                          if (lev.read_ini(k, z) == d) {
                              return false;
                          }
                      }
                  }
              }//end section 1,k
              if (a> 2 && a< 6) {//section 2, k
                  if (b < 3) {// section 2,1
                      for (int z = 0; z < 3; z++) {
                          if (lev.read_ini(k + 3, z) == d) {
                             return false;
                          }
                      }
                  }
                  if (b > 2 && b < 6) {//section 2,2
                      for (int z = 3; z < 6; z++) {
                          if (lev.read_ini(k + 3, z) == d) {
                             return false;
                          }
                      }
                  }
                  if (b > 5 && b < 9) {//section 2,3
                      for (int z = 6; z < 9; z++) {
                          if (lev.read_ini(k + 3, z) == d) {
                              return false;
                          }
                      }
                  }
              }//end section 2,k
              if (a> 5 && a< 9) {//section 3,k
                  if (b < 3) {// section 3,1
                      for (int z = 0; z < 3; z++) {
                          if (lev.read_ini(k + 6, z) == d) {
                            return false;
                          }
                      }
                  }
                  if (b > 2 && b < 6) {//section 3,2
                      for (int z = 3; z < 6; z++) {
                          if (lev.read_ini(k + 6, z) == d) {
                              return false;
                            }
                        }
                    }
                  if (b > 5 && b < 9) {//section 3,3
                      for (int z = 6; z < 9; z++) {
                          if (lev.read_ini(k + 6, z) == d) {
                             return false;
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
        return true;
  }
 
  int free_entry(sudoku_one::board &lev);
  bool free_entry_helper(int a, int b, sudoku_one::board &lev);
