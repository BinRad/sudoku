// TODO: SOLVER THREE
// use recursion to make backtracking easy

#include <iostream>
#include "board.h"
#include "rank.h"

//prototyping
bool solve(sudoku_one::board &lev, sudoku_one::rank &sim, int count = 0);
int finder(int i, int j, sudoku_one::board &lev, int entry = 1);
sudoku_one::board correct(sudoku_one::board &lev, sudoku_one::rank &sim,  int csoln,  int cposs);
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
    solve(lev, sim);
    lev.printout();
    lev.printout(4);
    return 0;
}

//SOLVE function
bool solve(sudoku_one::board &lev, sudoku_one::rank &sim, int count) {
    int i, j;
    int entry = 0;
    i = sim.getrow();
    j = sim.getcol();
        sim.advance();
    entry = finder(i, j, lev);
    if(entry == 0){ //try a different possibility
        next_board(lev, sim, current);
        return false;
    }
    lev.mod(i, j, entry);
    count++;
    if (count > 81) {
        return;
    }
    //std::cout << "count: " << count << std::endl;
    solve(lev, sim, count);
    //lev.printout(4);
}

//FINDER function
int finder(int i, int j, sudoku_one::board &lev, int entry) {
    for (int k = 0; k < 9; k++) {
        //std::cout <<entry<< "      ";
        if (lev.read(i, k) == entry) {
            //std::cout << lev.read(i, k) << "==" << entry << std::endl;
            entry++;
            k = 0;
        }
        if (lev.read(k, j) == entry) {
            //std::cout << lev.read(k, j) << "==" << entry << std::endl;
            entry++;
            k = 0;
        }
        //SECTION CHECKER
        //std::cout << "point: " << i << "," << j << "    entry: " << entry << std::endl;
        if (k < 3) {
            if (i < 3) { //Section 1
                if (j < 3) {// section 1,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 1,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 1,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k, a) == entry) {
                            //std::cout << lev.read(k, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 1,k
            if (i > 2 && i < 6) {//section 2, k
                if (j < 3) {// section 2,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 2,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 2,3
                    for (int a = 6; a < 9; a++){
                        if (lev.read(k + 3, a) == entry) {
                            //std::cout << lev.read(k+3, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 2,k
            if (i > 5 && i < 9) {//section 3,k
                if (j < 3) {// section 3,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 0;
                        }
                    }
                }
                if (j > 2 && j < 6) {//section 3,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 3;
                        }
                    }
                }
                if (j > 5 && j < 9) {//section 3,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            //std::cout << lev.read(k+6, a) << "===" << entry << std::endl;
                            entry++;
                            k = 0;
                            a = 6;
                        }
                    }
                }
            }//end section 3,k
        }// end section checker
    }//end k
    if (entry > 9) {
        return 0;
    } else {
        return entry;
    }
}

sudoku_one::board correct(sudoku_one::board& lev, sudoku_one::rank &sim, int num,  int ans){
  lev.reset();
  int poss[81][9];
  for(int a = 0; a <81; a++){
    for(int b = 0; b <9; b++){
      i = sim.getrow(a);
      j = sim.getcol(a);
      poss[b] = finder(i,j, lev, finder(i,j,lev)+b);
    }
  }
    int soln[81];
    for(int c = 0; c < 81; c++){
      soln[c] = 0;
    }

    if(solve(lev, sim)){//if the board worked then return the board
      return lev;
    }
      else{//if ti didnt work
        if(poss[num][ans] != 0 ){//try the next possibility for the current
            correct(lev, sim, num ,ans++);
        }
          else{
              correct(lev, sim, csoln++,0);
              std::assert(poss[soln[cposs]] == 0);
          }
      }
    }














      // lev.reset();
      // count = 0;
      // if (finder(sim.getrow(count), sim.getcol(count), lev, finder(sim.getrow(count), sim.getcol(count), lev) + 1) !=
      //     0) {
      //     entry = finder(sim.getrow(count), sim.getcol(count), lev,
      //                    finder(sim.getrow(count), sim.getcol(count), lev) + 1);
      //     //std::cout << "entry from finder after reset: " << entry << std::endl;
      //     lev.mod(i, j, entry);
      // }
      // else {
      //     count++;
      //     solve(lev, sim, count);
      // }
}

//RANKER function
//int *p;
// p = ranker(lev);
// if (*p == 99) {
//     return;
// } else {
//     i = *p;//x coordiante of entry
//     j = *(p + 1); //  y coordinate of entry
//
// int *ranker(sudoku_one::board &lev) {
//     lev.clearrank();
//     //RANK
//     int x = 0;
//     int y = 0;
//     for (int i = 0; i < 9; i++) {
//         for (int j = 0; j < 9; j++) {
//             if (lev.read(i, j) != 0) {
//                 lev.modrank(i, j, lev.readrank(i, j) + 1);
//             }
//         }
//     }
//     // SUM SECTION
//     int section[9];
//     for (int i = 0; i < 9; i++) {
//         section[i] = 0;
//     }
//     for (int k = 0; k < 3; k++) { // goes through each section
//         for (int i = 0; i < 3; i++) { //rows
//             for (int j = 0; j < 3; j++) { //columns
//                 section[k] += lev.readrank(i, j + (k * 3));
//                 section[k + 3] += lev.readrank(i + 3, j + (k * 3));
//                 section[k + 6] += lev.readrank(i + 6, j + (k * 3));
//             }
//         }
//     }
//     // add sum section value to eahc entry in that SECTION
//     // if there is an entry there alredy then we rank it 0 which is what
//     // the if and else statements do
//     for (int k = 0; k < 3; k++) { // goes through each section
//         for (int i = 0; i < 3; i++) { //rows
//             for (int j = 0; j < 3; j++) { //columns
//                 if (lev.readrank(i, j + (k * 3)) == 0) {
//                     lev.modrank(i, j + (k * 3), lev.readrank(i, j + (k * 3)) + section[k]);
//                 } else { lev.modrank(i, j + (k * 3), 0); }
//                 if (lev.readrank(i + 3, j + (k * 3)) == 0) {
//                     lev.modrank(i + 3, j + (k * 3), lev.readrank(i + 3, j + (k * 3)) + section[k + 3]);
//                 } else { lev.modrank(3 + i, j + (k * 3), 0); }
//                 if (lev.readrank(i + 6, j + (k * 3)) == 0) {
//                     lev.modrank(i + 6, j + (k * 3), lev.readrank(i + 6, j + (k * 3)) + section[k + 6]);
//                 } else { lev.modrank(i + 6, j + (k * 3), 0); }
//             }
//         }
//     }
//     //rows
//     int row = 0;
//     for (int i = 0; i < 9; i++) { //rows
//         row = 0;
//         for (int j = 0; j < 9; j++) { //column
//             if (lev.read(i, j) != 0) {
//                 row++; // store how many values are in the row
//             }
//         }
//         for (int q = 0; q < 9; q++) {
//             if (lev.readrank(i, q) != 0) {
//                 lev.modrank(i, q, lev.readrank(i, q) + row);
//             }
//         }
//     }
//     //columns
//     int col = 0;
//     for (int j = 0; j < 9; j++) { //columna
//         col = 0;
//         for (int i = 0; i < 9; i++) { //rows
//             if (lev.read(i, j) != 0) {
//                 col++; // store how many values are in the row
//             }
//         }
//         for (int q = 0; q < 9; q++) {
//             if (lev.readrank(q, j) != 0) {
//                 lev.modrank(q, j, lev.readrank(q, j) + col);
//             }
//         }
//     }
//     int *soln = new int[2];
//     soln[0] = 99;
//     soln[1] = 0;
//     int temp = 0;
//     for (int i = 0; i < 9; i++) { //rows
//         for (int j = 0; j < 9; j++) { //columns
//             if (lev.readrank(i, j) > temp) {
//                 soln[0] = i;
//                 soln[1] = j;
//                 temp = lev.readrank(i, j);
//             }
//         }
//     }
//     if (temp == 0) {
//         soln[0] = 99;
//     }
//     int *p = soln;
//     return p;
// }


// cout tool list
    //std::cout << "count: " << count << std::endl;
    //std::cout << lev.read(i, k) << "==" << entry << std::endl;
    //std::cout << "i,j: " << i << "," << j << std::endl;
    //std::cout << "entry: " << entry << std::endl;
    //lev.printout(4);
    //lev.printout();

#include "board.cpp"
#include "rank.cpp"
