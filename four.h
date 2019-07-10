// four(sudoku_one::board &lev, sudoku_one::rank &sim);
        //constructor will handle calling the find_poss & solve function
        //and setting up the vars
// void solve(sudoku_one::board &lev, sudoku_one::rank &sim);
        //this function will use finder to continuously place the entrys
        //into the board until there is an error. Once there is an error it will
        //call next entry to get a different entry
// int finder(sudoku_one::board &lev, sudoku_one::rank &sim);
        //this will update current_ans
        //based off of what has already been filled within the board.
        //if there is no available answer then call free entry
//bool finder_checker(sudoku_one::board &lev, sudoku_one::rank &sim)
        //works like finder from 1, 2 ,3 attempts. except now it will
        // just say whether or not it is a valid answer for that spot
        //it also calls marks_bad on any entryt hat causes it to be false
        //this also store which x,y caused that soif it needs to free()
        //it can also change the x,y
//void mark_bad(sudoku_one::board &lev, sudoku_one::rank &sim);
        //takes entry out of answers and shifts them
        //also update last_ans
        //puts entry into bad_ans
        //updtaes prob_row and prob_col using function update_prob_data
//void update_prob_data(int d);
        //finds where x,y is in prob row and col
        //either shifts everything u or everything down depending on where
        //d is
        //then places x,y in d index
        //d index is where bad_ans is stored
// void find_poss_entries(sudoku_one::board &lev, sudoku_one::rank &sim);
        //will be called by the constructor. It will be liek finder but
        //for the init board. It will populate the ANSWERS matrix
        //all non answers in answer matrix will be set to 99
//bool poss_entry_checker(int a, int b, int d, sudoku_one::board &lev, sudoku_one::rank &sim);
        //goes through and sees if that is a valid possile entry. if it is
        //it will return true. Otherwise, it will return false.
//void make_prob(sudoku_one::board &lev, sudoku_one::rank &sim);
        //this will generate possible problem matrices
        //prob_row
        //prob_col
        //lastly this will mark last prob after gettng to the
        //last prob by inserting all of the ones before it
//bool compare_ans(int a,int b,int x,int y,sudoku_one::board &lev, sudoku_one::rank &sim);
        //takes row col and compares it to the toher row cols
        // passed in. If they ever have any fo the same possible answers
        //then they are stored in prob_row and prob_col
// void free_entry(sudoku_one::board &lev, sudoku_one::rank &sim);
        //when there are no more possible entries for a given ij, then
        // this will free one entry and then correct the mistakes caused by
        //freeing that entry recursively using HELPER functions
        //also checks and updates BAD_ENTRY, FREED, ANSWERS, CURRENT_ans
        // returns freed entry
        //step 1: call check_for_free.
        //step 2: call helper: using bad entry row and col, find which i,j
            //caused entry at INDEX to be marked bad.
        //step 3: return entry
//int check_for_free(sudoku_one::board &lev, sudoku_one::rank &sim);
        //use finder checker to check any avaialble values in the
        //answers matrix that haven't been marked as bad
        //if all are bad return 99.
//void free_entry_helper(sudoku_one::board &lev, sudoku_one::rank &sim);
        //sets xy as ij and vice versa. then calls marks_bad
        // then calls solve
//void set_issue(sudoku_one::board &lev, sudoku_one::rank &sim);
        //takes issue_x&y and sets them using prob_row[i][j][current_prob]
        //importantly, it also keeps track of whether or not this speciifc issue
        //for this particular i,j x,y was ever done before.
        //if it was then it moves on the to the next problem
//void next_problem(sudoku_one::board &lev, sudoku_one::rank &sim);
        //this safely updates current_prob and if there is no bad ans it will
        //still update using whatever is in prob_row and prob_col
//void mark_good(sudoku_one::board &lev, sudoku_one::rank &sim);
        //takes out current prob from bad_ans, bad_entry_col, bad_entry_row
        // and puts them in the back. It then pushes everything forward.

#ifndef SUDOKU_ONE_FOUR_H
#define SUDOKU_ONE_FOUR_H

namespace sudoku_one {
  class four {
  public:
    //constructor and destructor
    four(sudoku_one::board &lev, sudoku_one::rank &sim);
    ~four(){}
    //functions
    void solve(sudoku_one::board &lev, sudoku_one::rank &sim);
    int finder(sudoku_one::board &lev, sudoku_one::rank &sim);
    bool finder_checker(sudoku_one::board &lev, sudoku_one::rank &sim);
    void mark_bad(sudoku_one::board &lev, sudoku_one::rank &sim);
    void update_prob_data(int d);
    void find_poss_entries(sudoku_one::board &lev, sudoku_one::rank &sim);
    bool poss_entry_checker(int a, int b, int d, sudoku_one::board &lev, sudoku_one::rank &sim);
    void make_prob(sudoku_one::board &lev, sudoku_one::rank &sim);
    bool compare_ans(int a,int b,int x,int y,sudoku_one::board &lev, sudoku_one::rank &sim);
    int free_entry(sudoku_one::board &lev, sudoku_one::rank &sim);
    int check_for_free(sudoku_one::board &lev, sudoku_one::rank &sim);
    void free_entry_helper(sudoku_one::board &lev, sudoku_one::rank &sim);
    void set_issue(sudoku_one::board &lev, sudoku_one::rank &sim);
    void next_problem(sudoku_one::board &lev, sudoku_one::rank &sim);
    void mark_good(sudoku_one::board &lev, sudoku_one::rank &sim);
  private:
    int i; //current row
    int j; //current column
    int entry;
    int issue_x; //row value of issue
    int issue_y; //col value of issue
    int prob_row[9][9][9]; //contains x for any possible confliciting entry of ij
    int prob_col[9][9][9]; //contains y for any possible confliciting entry of ij
    int answers[9][9][9]; //possible answers for each i,j
    int current_prob[9][9]; //index of problem to investigate currently for ij
    int last_prob[9][9]; //index of last problem for each i,j
    int current_ans[9][9]; //index value of current ans for i,j
    int last_ans[9][9]; //index of last ans in ans matrix for i,j
    int bad_ans[9][9][9]; // stores bad answers
    //index being taken from prob_row and prob_col
    int freed[9][9][9][9]; //is marked 1 if [i][j][x][y] was changed
    int current_free[9][9]; //stores index
  };
}
#endif
