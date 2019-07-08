#ifndef SUDOKU_ONE_POSS_H
#define SUDOKU_ONE_POSS_H

namespace sudoku_one {
  class poss {
  public:
    poss(sudoku_one::board &lev, sudoku_one::rank &sim);
    ~poss();
    int finder(int i, int j, sudoku_one::board &lev, int entry = 1);
    bool anti_loop(int i, int j,sudoku_one::board &lev);
    void violation(int i, int j, sudoku_one::board &lev);
    bool fix(int i, int j, int a, int b, sudoku_one::board &lev, int count);
    int next(int a, int b, sudoku_one::board &lev, int count);
  private:
    int matrics[9][9][9][9];
    int loop[9][9];
    int violator[9][9];
  };
}
#endif
