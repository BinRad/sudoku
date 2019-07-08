# sudoku
Each file (one.cpp two.cpp and so on) acts as the main function for the program.
Each of these files is a different implementation of the a sudoku solver created by me.
Each of these iterations will use the board class to manipulate and store the values.

one.cpp will check the row column and sub square (3x3) and will place the next available entry in. If that entry already appears in one of the 3 areas checked then it will put in the next number that hasn't been taken.

two.cpp uses the ranking system to choose which number to find the answer to first that is most likely to be the most accurate using the what numbers are in the rows and columns and subsquare with it.

three.cpp uses the poss, rank, and board data structures to try and find the answer. First it uses ranker to get the entries into a queue, that way it can go back if needs be, or jump forward. Then it uses board to add values and save them. If finder, the function used to find the proper number to put into each entry, returns zero then we will use the poss data structure to try to find the correct answer. The attempt was to continuously look for which entry may have caused the issue. Then call that one with a different value. If that one came up with an issue then poss would look for what caused it's issue until it gets down to the root of the issue. The problem with this is that there is no way of keeping track of anything properly. In addition, the code needs to be compartmentalized so that when there is an issue I can fix that one function and not have to change the entire code. It is hard to keep track of in the sense that without having a very clear system that remembers each attempt to fix the issue and what was done, and if that fix isn't the real fix and causes another issue then how to undo that and find something else to fix it. 
