#include "rank.h"
#include "board.h"
#include <iostream>

namespace sudoku_one {
    rank::rank(sudoku_one::board lev) {
        current = 0;
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
            //find the most likely one
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
            //std::cout << "i,j: " << i<< ","<< j << std::endl;
            rows[counter] = i;
            cols[counter] = j;
            lev.mod_ini(i, j, 5);
            counter++;
            //end while
        }
        bool temp = false;
        for(int a = 0; a < 81; a++){
          if(rows[a] == 0 && cols[a] == 0){
            if(temp ==true){
              tail = a;
              //std::cout<< rows[a]<< " here it is " <<cols[a]<<a  <<std::endl;
              a = 150;
            }
            temp = true;
          }
        }
        //end constructor
    }
    bool rank::advance(int i, int j) {
        if(i != 99 && j != 99){
            current = getindex(i,j);
        }
      if(current >= tail){
        current = 80;
        rows[80] = 99;
        cols[80] = 99;
        return false;
      }
      else{
        current++;
        return true;
      }
    }
    bool rank::rerank(sudoku_one::board lev) {
          current = 0;
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
              //find the most likely one
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
              //std::cout << "i,j: " << i<< ","<< j << std::endl;
              rows[counter] = i;
              cols[counter] = j;
              lev.mod_ini(i, j, 5);
              counter++;
              //end while
          }
          bool temp = false;
          for(int a = 0; a < 81; a++){
            if(rows[a] == 0 && cols[a] == 0){
              if(temp ==true){
                tail = a;
                //std::cout<< rows[a]<< " here it is " <<cols[a]<<a  <<std::endl;
                a = 150;
              }
              temp = true;
            }
          }
          if(tail == 0){
            return false;
          }
          else{
            return true;
          }
        }
    void rank::beginning(){
      current == 0;}
    int const rank::getindex(int x, int y) {
        int a =0;
        for(a = 0; a < 81; a++) {
            if (rows[a] == x && cols[a] == y) {
              if(a > tail){
                return 0;
              }
                return a;
            }
        }
        return 0;

    }
    int const rank::getrow(int index) {
      if(index = 99){
          return rows[current];
      }else{
        return rows[index];
      }
    }
    int const rank::getcol(int index) {
      if(index = 99){
          return cols[current];
      }else{
        return cols[index];
      }
    }
    int const rank::getcurrent(){
        return current;
    }
}
