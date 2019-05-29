#include "board.h"
#include <iostream>

    template<class Item>
    sudoku_one::board<Item>::board() {
        // matrix that holds restricted data
        int init[9][9];
        //matrix that holds general data
        int matrix[9][9];
        for(int i = 0; i<=8; i++){
            for (int j = 0; j <= 8; j++) {
                 init[i][j] = 0;
                 matrix[i][j] = 0;
            }
        }
    }
    // Modification functions
    template<class Item>
    void sudoku_one::board<Item>::mod_ini(int x, int y, Item &entry) {
                matrix[x][y] = entry;
    }
    template<class Item>
    void sudoku_one::board<Item>::mod_perm(int x, int y, Item &entry) {
        matrix[x][y] = entry;
    }

    template<class Item>
    void sudoku_one::board<Item>::mod_temp(int x, int y, Item &entry, bool green) {
        int tempx = x;
        int tempy = y;
        if (green) {
            matrix[x][y] = entry;
        }
    }
    template<class Item>
    void sudoku_one::board<Item>::printout() {
        for(int i = 0; i<=8; i++){
            std::cout << "/n";
            for(int j = 0; j <= 8; j++){
                std::cout << matrix[i][j];
            }

    }
}