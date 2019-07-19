// TODO: create a data structure that can store
//all of the values necessary to rank every spot on the board and check them
//off one at a time
// In order to create an accurate list we wil fill the
// board with a place holder in the previous spots and then use that
//to calculate where the next entry should be.
#ifndef SUDOKU_ONE_RANK_H
#define SUDOKU_ONE_RANK_H

namespace sudoku_one {
    class rank {
    public:
      rank(sudoku_one::board lev);
      ~rank(){}
      bool advance(int i = 99, int j = 99);
      bool rerank(sudoku_one::board lev);
      void beginning();
      int const getindex(int x, int y);
      int const getrow(int index = 99);//give index get i value
      int const getcol(int index = 99);//gve index get j value
      int const getcurrent();
      void add_to_queue(int i, int j);
    private:
      int rows[81];
      int cols[81];
      int current;
      int tail;
    };
  }
#endif
