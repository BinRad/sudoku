#include <iostream>
#include "board.h"
#include "rank.h"
#include "four.h"

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
    sudoku_one::four solver(lev, sim);
    lev.printout();
    lev.printout(4);
    return 0;
}
#include "board.cpp"
#include "rank.cpp"
#include "four.cpp"
