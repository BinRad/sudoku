//Program: context_check
// this program will use the context given by the contents of the surrounding sections
// and rows and columns to figure out the different possibilities of each spot

//this function will iterate through the possibilities of each entry
//and it will delete any answer that is not possible based off of this
//checking system

// 1: check 2 rows within subsection if we are in row 1, col 1.
//check row 2  and row 3 seion 2 & 3 and see if there are any numbers which
//appear both in section 2 and 3 on row 2 and 3 then it must be a possible answ
//for row 1 secton 1. if on the INIT board there is only one empty space for any
// row in any given section then we can use this to find the answer and lock it.
//we can also do this with columns

//in order to do this sytematically we will call this fuction passing in the entry
//it will check and see if the entry is in the other rows or columns in the other
//sections. if it in both rows or both columns then check and see if the rest of
//that row or col in the subsection that we are trying to fill is full in INIT
//if it is we can lock it in

void context_check(sudoku_one::board &lev, sudoku_one::rank &sim){
    if (i < 3) { //Section 1
        if (j < 3) {// section 1,1

        }
        if (j > 2 && j < 6) {//section 1,2

        }
        if (j > 5 && j < 9) {//section 1,3

        }
    }
    if (i > 2 && i < 6) {//section 2, k
        if (j < 3) {// section 2,1

        }
        if (j > 2 && j < 6) {//section 2,2

        }
        if (j > 5 && j < 9) {//section 2,3

        }
    }
    if (i > 5 && i < 9) {//section 3,k
        if (j < 3) {// section 3,1

        }
        if (j > 2 && j < 6) {//section 3,2

        }
        if (j > 5 && j < 9) {//section 3,3

        }
    }

}
