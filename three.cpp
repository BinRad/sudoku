// TODO: SOLVER THREE
// use recursion to make backtracking easy

#include <iostream>
#include "board.h"
//prototyping
void solve(sudoku_one::board &lev, int count = 1);
int finder(int i, int j, sudoku_one::board &lev, int count = 1);
int* ranker(sudoku_one::board& lev);

//MAIN function
int main(){
    sudoku_one::board lev;
    for(int i = 0; i < 9; i++){
      std::cout << "start line: " << i + 1 << "\n";
        for(int j = 0; j < 9; j++){
            int q = 0;
            std::cin >> q;
            lev.mod_ini(i , j, q);
        }
      std::cout << "end line: " << i + 1 << "\n";
      if( i > 8){
        std::cout << "all done here, good luck \n";
      }
    }
    std::cout << "Finished the for loop \n";
    lev.printout();
      solve(lev);
      lev.printout();
return 0;
}

//SOLVE function
void solve(sudoku_one::board &lev, int count){
      // if valid answer then put it in and move to the nextif not valid
      //answer then undo all answers up until then and increment up
      int i, j;
      int *p;
      p = ranker(lev);
      if(*p == 99){
        lev.printout();
        return;
      }
      else{
            i = *p;//x coordiante of entry
            j = *(p+1); //  y coordinate of entry
            count = finder(i,j,lev, count);
            if(count == 0){
              std::cout << "i,j: " << i << "," << j  << std::endl;
              std::cout << " count: " << count << std::endl;
              lev.reset();
              p = ranker(lev);
              i = *p;//x coordiante of entry
              j = *(p+1); //  y coordinate of entry
              count = finder(i,j,lev, finder(i,j,lev) + 1);
              std::cout << "i,j: " << i << "," << j  << std::endl;
              std::cout << " count: " << count << std::endl;
              if(finder(i,j,lev, count + 1) == 0){
                lev.mod_ini(i,j, count);
                std::cout << "yoohoo" << std::endl;
              }
              std::cout << "after mod ini" << std::endl;
              if(count == 0){
                std::cout << "yooh123oo" << std::endl;
                lev.reset();
                p = ranker(lev);
                i = *p;//x coordiante of entry
                j = *(p+1); //  y coordinate of entry
                count = finder(i,j,lev, finder(i,j,lev) + 1);
                if(finder(i,j,lev, count + 1) == 0){
                  lev.mod_ini(i,j, count);
                }
                else{
                  if(count == 0){
                    lev.reset();
                    p = ranker(lev);
                    i = *p;//x coordiante of entry
                    j = *(p+1); //  y coordinate of entry
                    count = finder(i,j,lev, finder(i,j,lev) + 2);
                  }
                }
              }
              std::cout << "after if count ==0" << std::endl;
            }
            lev.mod(i, j, count);
            solve(lev);
          }
      std::cout << "i,j: " << i << "," << j  << std::endl;
      std::cout << " count: " << count << std::endl;
}

//FINDER function
int finder(int i, int j, sudoku_one::board &lev, int count){
  for(int k = 0; k < 9; k++){
      if(lev.read(i,k) == count){
          count++;
          k = 0;
      }
      if(lev.read(k,j) == count){
          count++;
          k = 0;
      }
      if(k < 3){
        for(int z = 0; z < 3; z++){
          if(lev.read(k, j) == count){
            count++;
              k = 0;
          }
        }
      }
  }
      if(count > 9){
        return 0;
      }
      else{
        return count;
      }
}

//RANKER function
int* ranker(sudoku_one::board& lev){
  lev.clearrank();
  //RANK
  int x = 0;
  int y = 0;
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(lev.read(i, j) != 0){
        lev.modrank(i, j, lev.readrank(i, j) + 1);
      }
    }
  }
  // SUM SECTION
  int section[9];
  for(int i = 0; i < 9; i++){
  section[i] = 0;
  }
  for(int k = 0; k < 3; k++){ // goes through each section
  for(int i = 0; i < 3; i++){ //rows
    for(int j = 0; j < 3; j++){ //columns
      section[k] += lev.readrank(i, j + (k*3));
      section[k + 3] += lev.readrank(i + 3, j + (k*3));
      section[k + 6] += lev.readrank(i + 6, j + (k*3));
    }
  }
  }
  // add sum section value to eahc entry in that SECTION
  // if there is an entry there alredy then we rank it 0 which is what
  // the if and else statements do
  for(int k = 0; k < 3; k++){ // goes through each section
    for(int i = 0; i < 3; i++){ //rows
      for(int j = 0; j < 3; j++){ //columns
          if(lev.readrank(i, j + (k*3)) == 0){
            lev.modrank(i, j + (k*3), lev.readrank(i, j + (k*3)) + section[k]);
          }
          else{lev.modrank(i, j + (k*3), 0);}
          if(lev.readrank(i + 3, j + (k*3)) == 0){
            lev.modrank(i + 3, j + (k*3), lev.readrank(i + 3, j + (k*3)) + section[k + 3]);
          }
          else{lev.modrank(3 + i, j + (k*3), 0);}
          if(lev.readrank(i + 6, j + (k*3)) == 0){
            lev.modrank(i + 6, j + (k*3), lev.readrank(i + 6, j + (k*3)) + section[k + 6]);
          }
          else{lev.modrank(i + 6, j + (k*3), 0);}
        }
      }
    }
    //rows
    int row = 0;
    for(int i = 0; i < 9; i++){ //rows
      row = 0;
      for(int j = 0; j < 9; j++){ //column
        if(lev.read(i,j) != 0){
          row++; // store how many values are in the row
        }
      }
      for(int q = 0; q < 9; q++){
        if(lev.readrank(i,q) != 0){
          lev.modrank(i, q, lev.readrank(i,q) + row);
        }
      }
    }
    //columns
    int col = 0;
    for(int j = 0; j < 9; j++){ //columna
      col = 0;
      for(int i = 0; i < 9; i++){ //rows
        if(lev.read(i,j) != 0){
          col++; // store how many values are in the row
        }
      }
      for(int q = 0; q < 9; q++){
        if(lev.readrank(q,j) != 0){
          lev.modrank(q, j, lev.readrank(q,j) + col);
        }
      }
    }
   int* soln = new int[2];
    soln[0] = 99;
    soln[1] = 0;
    int temp = 0;
      for(int i = 0; i < 9; i++){ //rows
        for(int j = 0; j < 9; j++){ //columns
          if(lev.readrank(i, j) > temp){
            soln[0] = i;
            soln[1] = j;
            temp = lev.readrank(i, j);
          }
        }
      }
      if(temp == 0){
        soln[0] = 99;
      }
    int *p = soln;
    return p;
}
