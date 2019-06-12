#ifndef SUDOKU_ONE_BOARD_H
#define SUDOKU_ONE_BOARD_H



namespace sudoku_one {


    class board {

    public:
        // typedefs
        typedef int value;

        // constructor & destructor
        board(){}
        ~board() {//inline function
            delete[] init;
            delete[] matrix;
        }

        // Modification functions
        void mod_ini(int x, int y, int &entry); 	//setting permanent positions in the board originally
        void mod_perm(int x, int y, int &entry);	//a set of values that are definitely correct in their position
        void mod_temp(int x, int y, int &entry, bool green);//set of values that may be the solution to the board
        void printout();				// prints whatvever is in the board

    private:
        // matrix that holds restricted data
        int init[9][9];
        //matrix that holds general data
        int matrix[9][9];

    };

}
#include "board.cpp"
#endif
