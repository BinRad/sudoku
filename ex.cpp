//if current prob has same answers as last prob, then record that

void make_prob(sudoku_one::board &lev){
    for (int k = 0; k < 9; k++) {
        if(lev.read_ini(a, k) != 0){
          for(int c = 0; c<9; c++){
              if()
          }
            return false;
         }
         if( lev.read_ini(k, b) != 0)){
             return false;
         }
        //SECTION CHECKER
        if (k < 3) {
            if (a< 3) { //Section 1
                if (b < 3) {// section 1,1
                    for (int z = 0; z < 3; z++) {
                        if (lev.read_ini(k, z) != 0) {
                            return false;
                          }
                      }
                  }
                if (b > 2 && b < 6) {//section 1,2
                    for (int z = 3; z < 6; z++) {
                        if (lev.read_ini(k, z) != 0) {
                            return false;
                        }
                    }
                }
                if (b > 5 && b < 9) {//section 1,3
                    for (int z = 6; z < 9; z++) {
                        if (lev.read_ini(k, z) != 0) {
                            return false;
                        }
                    }
                }
            }//end section 1,k
            if (a> 2 && a< 6) {//section 2, k
                if (b < 3) {// section 2,1
                    for (int z = 0; z < 3; z++) {
                        if (lev.read_ini(k + 3, z) != 0) {
                           return false;
                        }
                    }
                }
                if (b > 2 && b < 6) {//section 2,2
                    for (int z = 3; z < 6; z++) {
                        if (lev.read_ini(k + 3, z) != 0) {
                           return false;
                        }
                    }
                }
                if (b > 5 && b < 9) {//section 2,3
                    for (int z = 6; z < 9; z++) {
                        if (lev.read_ini(k + 3, z) != 0) {
                            return false;
                        }
                    }
                }
            }//end section 2,k
            if (a> 5 && a< 9) {//section 3,k
                if (b < 3) {// section 3,1
                    for (int z = 0; z < 3; z++) {
                        if (lev.read_ini(k + 6, z) != 0) {
                          return false;
                        }
                    }
                }
                if (b > 2 && b < 6) {//section 3,2
                    for (int z = 3; z < 6; z++) {
                        if (lev.read_ini(k + 6, z) != 0) {
                            return false;
                          }
                      }
                  }
                if (b > 5 && b < 9) {//section 3,3
                    for (int z = 6; z < 9; z++) {
                        if (lev.read_ini(k + 6, z) != 0) {
                           return false;
                          }
                      }
                  }
              }//end section 3,k
          }// end section checker
      }//end k
      return true;
}
