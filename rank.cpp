





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
