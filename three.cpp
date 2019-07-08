// TODO: SOLVER THREE
// use recursion to make backtracking easy

#include <iostream>
#include "board.h"
#include "rank.h"
#include "poss.h"

//prototyping
bool solve(sudoku_one::board &lev, sudoku_one::rank &sim, sudoku_one::poss &tahor, int index = 0, int entry = 1);

int finder(int i, int j, sudoku_one::board &lev, int entry = 1);
//int *ranker(sudoku_one::board &lev);

//MAIN function
int main() {
    sudoku_one::board lev;
    for (int i = 0; i < 9; i++) {
        std::cout << "start line: " << i + 1 << "\n";
        for (int j = 0; j < 9; j++) {
            int q = 0;
            std::cin >> q;
            lev.mod_ini(i, j, q);
        }
        std::cout << "end line: " << i + 1 << "\n";
        if (i > 8) {
            std::cout << "all done here, good luck \n";
        }
    }
    std::cout << "Finished the for loop \n";
    sudoku_one::rank sim(lev);
    sudoku_one::poss tahor(lev, sim);
    solve(lev, sim, tahor);
    lev.printout();
    lev.printout(4);
    return 0;
}

//SOLVE function
bool solve(sudoku_one::board &lev, sudoku_one::rank &sim, sudoku_one::poss &tahor, int index, int entry) {
    int i, j;
    i = sim.getrow(index);
    j = sim.getcol(index);
    if(lev.read_ini(i,j)!= 0){
      solve(lev,sim,tahor,index+1);
      return true;
    }
    entry = tahor.finder(i,j,lev);
    //lev.printout(4);
    if (tahor.anti_loop(i, j,lev) == true) {
        if (sim.advance()) {
            index++;
            return solve(lev, sim, tahor, index);
        } else {
            return solve(lev, sim, tahor, 0, 1);
        }
      }
    if (lev.read(i, j) != 0) {
            if (sim.rerank(lev)) {
                solve(lev, sim, tahor, 0);
            } else {return true;}
      }
    if(entry == 0){
      tahor.violation(i,j,lev);
      index = 0;
    } else { index++;}
    lev.mod(i,j,entry);
    solve(lev,sim,tahor,index);
  }


#include "board.cpp"
#include "rank.cpp"
#include "poss.cpp"
