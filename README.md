# sudoku
Each file (one.cpp two.cpp and so on) acts as the main function for the program.
Each of these files is a different implementation of the a sudoku solver created by me.
Each of these iterations will use the board class to manipulate and store the values.

one.cpp will check the row column and sub square (3x3) and will place the next available entry in. If that entry already appears in one of the 3 areas checked then it will put in the next number that hasn't been taken.

two.cpp uses the ranking system to choose which number to find the answer to first that is most likely to be the most accurate using the what numbers are in the rows and columns and subsquare with it.

three.cpp uses the poss, rank, and board data structures to try and find the answer. First it uses rankers
