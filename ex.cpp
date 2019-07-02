


#include <iostream>


int main(){
  // int data[81][9];
  // int num[81];
  // for(int a = 0; a <81; a++){
  //   for(int b = 0; b <9; b++){
  //     data[a][b] = a;
  //   }
  // }
  // for(int a = 0; a < 81; a++){
  //   num[a] = a / 9;
  // }
  // for(int a = 0; a <81; a++){
  //   std::cout << "num: " << num[a] << "   ";
  //     std::cout << "data: " << data[a][num[a]] << std::endl;
  // }
  int k = 0;
  while(k < 4){
    for(int a = 0; a <3; a++){
      if(a > 1){
        k = 0;
      }
      std::cout << a << k<< std::endl;
        k++;

      }
    }
}
