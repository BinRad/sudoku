#include "rank.h"
#include "board.h"
#include <iostream>

namespace sudoku_one {
  four::four(sudoku_one::board &lev, sudoku_one::rank &sim){
        i = sim.getrow(0);
        j = sim.getcol(0);
        issue_x = 99;
        issue y = 99;
        entry = 0;
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                for (int c = 0; c < 9; c++) {
                    for (int d = 0; d < 9; d++) {
                        prob_row[a][b][c]= 99;
                        prob_col[a][b][c] = 99;
                        answers[a][b][c] = 0;
                        current_prob[a][b] = 0;
                        last_prob[a][b] = 0;
                        current_ans[a][b] = 0;
                        last_ans[a][b][c] = 0;
                        bad_entry_row[a][b][c] = 0;
                        bad_entry_col[a][b][c] = 0;
                        bad_ans[a][b][c] = 99;
                        freed[a][b][c][d] = 0;
                        current_free[a][b] = 0;
                    }
                }
            }
        }
        find_poss_entries(lev);
        i = sim.getrow();
        j = sim.getcol();
        solve(lev);
    }
  ~four(){}
  //modification functions
  void four::solve(sudoku_one::board &lev){
      entry = finder(lev);
      lev.mod(i, j, entry);
      sim.advance(i,j);
      i = sim.getrow();
      j = sim.getcol();
      solve(lev);
    }
  int four::finder(sudoku_one::board &lev){
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
  bool four::finder_checker(sudoku_one::board &lev){
      //possible issue that entry is being checked against
      //itself since k does nto skip over the value that it is supposed to be
      //iterating through
      //may cause ti to passover a valid answer. easy fix if necessary
      //just if statement when k == j when applicable etc...
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
  void four::mark_bad(sudoku_one::board &lev){
      //take entry out of answers array
      int tempans = answers[i][j][current_ans[i][j]];
      int c = current_ans[i][j];
      while(answers[i][j][c+1] != 99){
          answers[i][j][c] = answers[i][j][c + 1]
      }
      last_ans[i][j]--;
      int d = 0;
      while(bad_ans[i][j][d] != 99){
          d++;
      }
      bad_ans[i][j][d] = tempans;
      update_prob_data(d);
  }
  void four::update_prob_data(int d){
      // q is where x and y are currently in the arrays
      // d is the index position we want them to be in
      int q = 0;
    while(prob_row[i][j][q] != issue_x && prob_col[i][j][q] != issue_y){
        q++;
    }
    if(q == d){
        return;
    }
    else{
        while(q < d){
            prob_row[i][j][q] = prob_row[i][j][q+1];
            prob_col[i][j][q] = prob_col[i][j][q+1];
            q++;
        }
        while(q > d){
            prob_row[i][j][q] = prob_row[i][j][q-1];
            prob_col[i][j][q] = prob_col[i][j][q-1];
            q--;
        }
        prob_row[i][j][d] = issue_x;
        prob_col[i][j][d] = issue_y;
    }
  }
  void four::find_poss_entries(sudoku_one::board &lev){
      int c = 0;
      for (int a = 0; a < 9; a++) {
          for (int b = 0; b < 9; b++) {
                  for (int d = 1; d < 9; d++) {
                      if(poss_entry_checker(a,b, d, lev)){
                          answers[a][b][last_ans[a][b]] = d;
                          last_ans[a][b]++;
                        }
                    }
                    c = last_ans[a][b];
                    while(c < 9){
                        answers[a][b][c] = 99;
                        c++;
                    }
            }
        }
        make_prob(lev);
    }
  bool four::poss_entry_checker(int a, int b, int d, sudoku_one::board &lev){
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
  void four::make_prob(sudoku_one::board &lev){
      for (int a = 0; a < 9; a++) {
          for (int b = 0; b < 9; b++) {
              for (int k = 0; k < 9; k++) {
                  if(lev.read_ini(a, k) == 0){
                        compare_ans(a,b,a,k,lev);
                        k = 0;
                    }
                   if( lev.read_ini(k, b) == 0)){
                       compare_ans(a,b,a,k,lev);
                       k = 0;
                      }
                  //SECTION CHECKER
                  if (k < 3) {
                      if (a< 3) { //Section 1
                          if (b < 3) {// section 1,1
                              for (int z = 0; z < 3; z++) {
                                  if (lev.read_ini(k, z) == 0) {
                                      compare_ans(a,b,k,z,lev);
                                      k = 0;
                                      a = -1;
                                    }
                                }
                            }
                          if (b > 2 && b < 6) {//section 1,2
                              for (int z = 3; z < 6; z++) {
                                  if (lev.read_ini(k, z) == 0) {
                                      compare_ans(a,b,k,z,lev);
                                      k = 0;
                                      a = 2;
                                  }
                              }
                          }
                          if (b > 5 && b < 9) {//section 1,3
                              for (int z = 6; z < 9; z++) {
                                  if (lev.read_ini(k, z) == 0) {
                                      compare_ans(a,b,k,z,lev);
                                      k = 0;
                                      a= 5;
                                  }
                              }
                          }
                      }//end section 1,k
                      if (a> 2 && a< 6) {//section 2, k
                          if (b < 3) {// section 2,1
                              for (int z = 0; z < 3; z++) {
                                  if (lev.read_ini(k + 3, z) == 0) {
                                      compare_ans(a,b,k+3,z,lev);
                                      k = 0;
                                      a = -1;
                                  }
                              }
                          }
                          if (b > 2 && b < 6) {//section 2,2
                              for (int z = 3; z < 6; z++) {
                                  if (lev.read_ini(k + 3, z) == 0) {
                                      compare_ans(a,b,k+3,z,lev);
                                      k = 0;
                                      a = 2;
                                  }
                              }
                          }
                          if (b > 5 && b < 9) {//section 2,3
                              for (int z = 6; z < 9; z++) {
                                  if (lev.read_ini(k + 3, z) == 0) {
                                      compare_ans(a,b,k+3,z,lev);
                                      k = 0;
                                      a = 5;
                                  }
                              }
                          }
                      }//end section 2,k
                      if (a> 5 && a< 9) {//section 3,k
                          if (b < 3) {// section 3,1
                              for (int z = 0; z < 3; z++) {
                                  if (lev.read_ini(k + 6, z) == 0) {
                                      compare_ans(a,b,k+6,z,lev);
                                      k = 0;
                                      a = -1;
                                  }
                              }
                          }
                          if (b > 2 && b < 6) {//section 3,2
                              for (int z = 3; z < 6; z++) {
                                  if (lev.read_ini(k + 6, z) == 0) {
                                      compare_ans(a,b,k+6,z,lev);
                                      k = 0;
                                      a = 2;
                                    }
                                }
                            }
                          if (b > 5 && b < 9) {//section 3,3
                              for (int z = 6; z < 9; z++) {
                                  if (lev.read_ini(k + 6, z) == 0) {
                                      compare_ans(a,b,k+6,z,lev);
                                      k = 0;
                                      a = 5;
                                    }
                                }
                            }
                        }//end section 3,k
                    }// end section checker
                }//end k
            }
        }
        for (int c = 0; c < 9; c++) {
            for (int d = 0; d < 9; d++) {
                last_prob[c][d] = current_prob[c][d];
                current_prob[c][d] = 0;
            }
        }
        return true;
  }
  bool four::compare_ans(int a,int b,int x,int y,sudoku_one::board &lev){
      for(int y = 0; y < 9; y++){
          for(int z = 0; z < 9; z++){
              if(answers[a][b][y] == answers[x][y][z] && answers[a][b][y] != 99){
                  prob_row[a][b][current_prob[a][b]] = x;
                  prob_col[a][b][current_prob[a][b]] = y;
                  current_prob[a][b]++;
                  return true;
              }
          }
      }
      return false;
  }
  int four::free_entry(sudoku_one::board &lev){
      int temp = 99;
      temp = check_for_free(lev);
      if(temp != 99){
          return temp;
      }
      else{
          entry = bad_ans[i][j][current_prob[i][j]];
          if(entry == 99){ //if there is no current entry
              current_prob[i][j] = 0;
              entry = bad_ans[i][j][current_prob[i][j]];
              if(entry == 99){
                  //if there are no entries to free_entry
                  //then there is a real issue
                  std::cout << "no entries to free" << std::endl;
                  return 99;
              }
          }
          set_issue(lev);
          mark_good(lev);
          free_entry_helper(lev);
      }
      return entry;
  }
  int four::check_for_free(sudoku_one::board &lev){
      int c = 0;
      while(answers[i][j][c] != 99){
          entry = answers[i][j][c];
          if(finder_checker(lev)){
              return answers[i][j][c];
          }
      }
      return 99;
  }
  bool four::free_entry_helper(int a, int b, sudoku_one::board &lev){
      int tempx, tempy;
      tempx = i;
      tempy  = j;
      i = issue_x;
      j = issue_y;
      issue_x = tempx;
      issue_y = tempy;
      mark_bad(lev);
      solve(lev);
  }
  void four::set_issue(sudoku_one::board &lev){
      issue_x = prob_row[i][j][current_prob[i][j]];
      issue_y = prob_col[i][j][current_prob[i][j]];
      if(freed[i][j][issue_x][issue_y] == 0){
          freed[i][j][issue_x][issue_y] = 1;//update matrix
          //now go back to free_entry
      }else{
          //go to the next problem
          next_problem();
          free_entry(lev);
          //this may cause a loop. in order to fix this we need to say this is
          //all done. you cannot change the entry for this x,y anymore. We need
          //to move to the next x,y or maybe the next x,y of the next x,y
      }
  }
  void four::next_problem(sudoku_one::board &lev){
    if(current_prob[i][j]+1 != last_prob[i][j])
    {
        current_prob[i][j]++;
        if(bad_ans[i][j][current_prob[i][j]] == 99){
            issue_x = prob_row[i][j][current_prob];
            issue_y = prob_col[i][j][current_prob];
            entry = lev.read(issue_x, issue_y);
        }
    }
    else{
        current_prob[i][j] = 0;
        std::cout << "this wont cut it for next next_problem <3"<< std::endl;
        //this may cause a loop. in order to fix this we need to say this is
        //all done. you cannot change the entry for this x,y anymore. We need
        //to move to the next x,y or maybe the next x,y of the next x,y
    }
}
  void four::mark_good(sudoku_one::board &lev){
      int c = current_prob[i][j] + 1;
      int endans = bad_ans[i][j][current_prob[i][j]];
      int endx = prob_row[i][j][current_prob[i][j]];
      int endy = prob_col[i][j][current_prob[i][j]];
      while(bad_ans[i][j][c] != 99){
          bad_ans[i][j][c - 1] = bad_ans[i][j][c];
          prob_row[i][j][c-1] = prob_row[i][j][c];
          prob_col[i][j][c-1] = prob_col[i][j][c];
          c++;
      }
      if(prob_row[i][j][c] == 99 && prob_col[i][j][c] == 99){
          std::cout <<c < "==" << last_prob << std::endl;
          prob_row[i][j][c] = endx;
          prob_col[i][j][c] = endy;
      }
      answers[i][j][last_ans+1] = end_ans;
      last_ans[i][j]++;
      current_prob[i][j] = 0;
      else{
          std::cout << "mark_good needs help when thing hasnt been marked back but has been added to lev" << std::endl;
      }
  }
