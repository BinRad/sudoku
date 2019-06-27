#include "rank.h"
#include "board.h"
#include <iostream>

namespace sudoku_one {
    rank::rank(sudoku_one::board lev) {
        current = 0;
        correct = 0;
        int counter = 0;
        while (counter < 81) {
            lev.clearrank();
            //RANK
            int x = 0;
            int y = 0;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (lev.read(i, j) != 0) {
                        lev.modrank(i, j, lev.readrank(i, j) + 1);
                    }
                }
            }
            // SUM SECTION
            int section[9];
            for (int i = 0; i < 9; i++) {
                section[i] = 0;
            }
            for (int k = 0; k < 3; k++) { // goes through each section
                for (int i = 0; i < 3; i++) { //rows
                    for (int j = 0; j < 3; j++) { //columns
                        section[k] += lev.readrank(i, j + (k * 3));
                        section[k + 3] += lev.readrank(i + 3, j + (k * 3));
                        section[k + 6] += lev.readrank(i + 6, j + (k * 3));
                    }
                }
            }
            // add sum section value to eahc entry in that SECTION
            // if there is an entry there alredy then we rank it 0 which is what
            // the if and else statements do
            for (int k = 0; k < 3; k++) { // goes through each section
                for (int i = 0; i < 3; i++) { //rows
                    for (int j = 0; j < 3; j++) { //columns
                        if (lev.readrank(i, j + (k * 3)) == 0) {
                            lev.modrank(i, j + (k * 3), lev.readrank(i, j + (k * 3)) + section[k]);
                        } else { lev.modrank(i, j + (k * 3), 0); }
                        if (lev.readrank(i + 3, j + (k * 3)) == 0) {
                            lev.modrank(i + 3, j + (k * 3), lev.readrank(i + 3, j + (k * 3)) + section[k + 3]);
                        } else { lev.modrank(3 + i, j + (k * 3), 0); }
                        if (lev.readrank(i + 6, j + (k * 3)) == 0) {
                            lev.modrank(i + 6, j + (k * 3), lev.readrank(i + 6, j + (k * 3)) + section[k + 6]);
                        } else { lev.modrank(i + 6, j + (k * 3), 0); }
                    }
                }
            }
            //rows
            int row = 0;
            for (int i = 0; i < 9; i++) { //rows
                row = 0;
                for (int j = 0; j < 9; j++) { //column
                    if (lev.read(i, j) != 0) {
                        row++; // store how many values are in the row
                    }
                }
                for (int q = 0; q < 9; q++) {
                    if (lev.readrank(i, q) != 0) {
                        lev.modrank(i, q, lev.readrank(i, q) + row);
                    }
                }
            }
            //columns
            int col = 0;
            for (int j = 0; j < 9; j++) { //columns
                col = 0;
                for (int i = 0; i < 9; i++) { //rows
                    if (lev.read(i, j) != 0) {
                        col++; // store how many values are in the row
                    }
                }
                for (int q = 0; q < 9; q++) {
                    if (lev.readrank(q, j) != 0) {
                        lev.modrank(q, j, lev.readrank(q, j) + col);
                    }
                }
            }
            int i = 0;
            int j = 0;
            int temp = 0;
            for (int a = 0; a < 9; a++) { //rows
                for (int b = 0; b < 9; b++) { //columns
                    if (lev.readrank(a, b) > temp) {
                        i = a;
                        j = b;
                        temp = lev.readrank(i, j);
                    }
                }
            }
            std::cout << "i,j: " << i<< ","<< j << std::endl;
            rows[counter] = i;
            cols[counter] = j;
            lev.mod_ini(i, j, 5);
            counter++;
            //end while
        }
        //end constructor
    }
    void rank::advance() {
        current++;
    }
    int const rank::getrow() {
        return rows[current];
    }
    int const rank::getcol() {
        return cols[current];
    }
    int const rank::getindex(int x, int y) {
        for (int w = 0; w > 81; w++) {
            if (x == rows[w] && y == cols[w]) {
                return w;
            }
        }
    }
    int const rank::getrow(int index) {
        return rows[index];
    }
    int const rank::getcol(int index) {
        return cols[index];
    }
    int const rank::getcurrent(){
        return current;
    }
}
