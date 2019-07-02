#ifndef SUDOKU_ONE_POSS_H
#define SUDOKU_ONE_POSS_H

namespace sudoku_one {
  class poss {
  public:
    poss(sudoku_one::board &lev, sudoku_one::rank &sim);
    ~poss();
    int finder(int i, int j, sudoku_one::board &lev, int entry = 1);
    void next(sudoku_one::board& lev, sudoku_one::rank &sim);
    int next_prob(int i, int j,sudoku_one::board &lev, sudoku_one::rank &sim);
    void prob_helper(int i, int j,sudoku_one::board &lev,sudoku_one::rank &sim);
    void set_old(int i, int j){
      old_i =i;
      old_j = j;
    }
    bool anti_loop(int i, int j,sudoku_one::board &lev);
  private:
    int data[81][9];
    int num[81];
    int ans;
    int matrics[9][9];
    int count;
    int children[81];
    int old_i;
    int old_j;
    int loop[9][9];
    int super_duper_looper[9][9];
    int looper_trooper[81];


  };
}
#endif
