#ifndef SUDOKU_ONE_POSS_H
#define SUDOKU_ONE_POSS_H

namespace sudoku_one {
  class poss{
  public:
    poss(sudoku_one::board &lev, sudoku_one::rank &sim);
    ~poss();
    int finder(int i, int j, sudoku_one::board &lev, int entry = 1);
    sudoku_one::board next(sudoku_one::board& lev, sudoku_one::rank &sim);
  private:
    int data[81][9];
    int num[81];
    int ans;


  };








#endif
