#ifndef SUDOKU_ONE_BOARD_H
#define SUDOKU_ONE_BOARD_H



namespace sudoku_one {


    template<class Item>
    class board {

    public:
        // typedefs
        typedef Item value;

        // constructor
        board();

        ~board() {
            delete[] init;
            delete[] matrix;
        }

        // Modification functions
        void mod_ini(int x, int y, Item &entry);

        void mod_perm(int x, int y, Item &entry);

        void mod_temp(int x, int y, Item &entry, bool green);

        void printout();

    private:
        // matrix that holds restricted data
        int init[9][9];
        //matrix that holds general data
        int matrix[9][9];

    };

}
#include "board.cpp"
#endif