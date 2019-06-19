//printout 0 = all
//         1 = initial board
//         2 = current board
//         3 = rank board


#ifndef SUDOKU_ONE_BOARD_H
#define SUDOKU_ONE_BOARD_H

namespace sudoku_one {
    class board {
    public:
        // typedefs
        typedef int value;
        // constructor & destructor
        board();
        ~board();
        // Modification functions
        void mod_ini(int x, int y, int entry); 	//setting permanent positions in the board originally
        void mod(int x, int y, int entry);	//a set of values that are definitely correct in their position
        void modrank(int x, int y, int entry);
        void const printout(int m = 0);
        void clearrank();			          // prints whatvever is in the board
        int read(int x, int y);
        int readrank(int x, int y);
    private:
        // matrix that holds restricted data
        int init[9][9];
        // matrix that holds general data
        int matrix[9][9];

    };

}
//#include "board.cpp"
#endif
