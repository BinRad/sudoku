// four(sudoku_one::board &lev, sudoku_one::rank &sim);
        //constructor will handle calling the find_poss & solve function
        //and setting up the vars
// void solve(sudoku_one::board &lev);
        //this function will use finder to continuously place the entrys
        //into the board until there is an error. Once there is an error it will
        //call next entry to get a different entry
// int finder(sudoku_one::board &lev);
        //this will update current_ans
        //based off of what has already been filled within the board.
        //if there is no available answer then call free entry
//bool finder_checker(sudoku_one::board &lev)
        //works like finder from 1, 2 ,3 attempts. except now it will
        // just say whether or not it is a valid answer for that spot
        //it also calls marks_bad on any entryt hat causes it to be false
        //this also store which x,y caused that soif it needs to free()
        //it can also change the x,y
//int mark_bad(sudoku_one::board &lev);
        //will put the current answer marked as bad and update BAD_ENTRY
        // it will also return the correct entry
        //in bad_entry_row&col stores the i,j value
// void find_poss_entries(sudoku_one::board &lev);
        //will be called by the constructor. It will be liek finder but
        //for the init board. It will populate the ANSWERS matrix
        //all non answers in answer matrix will be set to 99
//bool poss_entry_checker(int a, int b, int d, sudoku_one::board &lev);
        //goes through and sees if that is a valid possile entry. if it is
        //it will return true. Otherwise, it will return false.
//void make_prob(sudoku_one::board &lev);
        //this will generate possible problem matrices
        //prob_row
        //prob_col
// void free_entry(sudoku_one::board &lev);
        //when there are no more possible entries for a given ij, then
        // this will free one entry and then correc the mistakes caused by
        //freeing that entry recursively using HELPER functions
        //also checks and updates BAD_ENTRY, FREED, ANSWERS, CURRENT_ans
        // returns freed entry
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
    bool finder_checker(sudoku_one::board &lev);
    int mark_bad(sudoku_one::board &lev);
    void find_poss_entries(sudoku_one::board &lev);
    bool poss_entry_checker(int a, int b, int d, sudoku_one::board &lev);
    void make_prob(sudoku_one::board &lev);
    int free_entry(sudoku_one::board &lev);
    bool free_entry_helper(int a, int b, sudoku_one::board &lev);

  private:
    int i; //current row
    int j; //current column
    int issue_x; //row value of issue
    int issue y; //col value of issue
    int prob_row[9][9][9]; //contains x for any possible confliciting entry of ij
    int prob_col[9][9][9]; //contains y for any possible confliciting entry of ij
    int answers[9][9][9]; //possible answers for each i,j
    int current_prob[9][9]; //index of problem to investigate currently for ij
    int last_prob[9][9][9]; //index of last problem for each i,j
    int current_ans[9][9]; //index value of current ans for i,j
    int last_ans[9][9][9]; //index of last ans in ans matrix for i,j
    int bad_entry_row[9][9][9]; // stores i value which forced xy to update given index [x][y][index]
    int bad_entry_col[9][9][9]; // stores j value which forced xy to update given index [x][y][index]
    //index being taken from prob_row and prob_col
    int freed[9][9][9][9]; //is marked 1 if [i][j][x][y] was changed
  };
}
#endif
