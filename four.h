// four(sudoku_one::board &lev, sudoku_one::rank &sim);
        //constructor will handle calling the solve function and setting up the vars
// void solve(sudoku_one::board &lev);
        //this function will use finder to continuously place the entrys
        //into the board until there is an error. Once there is an error it will
        //call next entry to get a different entry
// int finder(sudoku_one::board &lev);
        //this will update current_ans
        //based off of what has already been filled within the board.
        //if there is no available answer then call free entry
//int mark_bad(sudoku_one::board &lev);
        //will put the current answer marked as bad and update BAD_ENTRY
// void find_poss_entries(sudoku_one::board &lev);
        //will be called by the constructor. It will be liek finder but when
        //for the init board. It will populate the ANSWERS matrix
// int get_prob(sudoku_one::board &lev);
        //this will return the current problem for that i,j and then current++
// void free_entry(sudoku_one::board &lev);
        //when there are no more possible entries for a given ij, then
        // this will free one entry and then correc the mistakes caused by
        //freeing that entry recursively using HELPER functions
        //also checks and updates BAD_ENTRY, FREED, ANSWERS, CURRENT_ans
// bool free_entry_helper(int a, int b, sudoku_one::board &lev);
        //runs recursively stoing i,j in it's recurive calls and then changing
        //the variables. It sets i,j to the orignal i,j that caused the need
        //for a free entry. It then calls solve on that entry. When solve returns
        //then this will put back i,j to what it was. 


#ifndef SUDOKU_ONE_FOUR_H
#define SUDOKU_ONE_FOUR_H

namespace sudoku_one {
  class four {
  public:
    //constructor and destructor
    four(sudoku_one::board &lev, sudoku_one::rank &sim);
    ~four();
    //modification functions
    void solve(sudoku_one::board &lev);
    int finder(sudoku_one::board &lev);
    int mark_bad(sudoku_one::board &lev);
    void find_poss_entries(sudoku_one::board &lev);
    int get_prob(sudoku_one::board &lev);
    void free_entry(sudoku_one::board &lev);
    bool free_entry_helper(int a, int b, sudoku_one::board &lev);

  private:
    int i; //current row
    int j; //current column
    int issue_x; //row value of issue
    int issue y; //col value of issue
    int prob_row[9][9][9]; //contains i for any possible confliciting entry of ij
    int prob_col[9][9][9]; //contains j for any possible confliciting entry of ij
    int answers[9][9][9]; //possible answers for each i,j
    int current_prob[9][9][9]; //index of problem to investigate currently for ij
    int last_prob[9][9][9]; //index of last problem for each i,j
    int current_ans[9][9][9]; //index value of current ans for i,j
    int last_ans[9][9][9]; //index of last ans in ans matrix for i,j
    int bad_entry_row[9][9][9]; // stores i value which forced xy to update given index [x][y][index]
    int bad_entry_col[9][9][9]; // stores j value which forced xy to update given index [x][y][index]
    int freed[9][9][9][9]; //is marked 1 if [i][j][x][y] was changed
  };
}
#endif
