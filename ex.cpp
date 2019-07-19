(m,bool get_bad_ans_checker(int m, int n, sudoku_one::board &lev, sudoku_one::rank &sim) {
    //possible issue that entry is being checked against
    //itself since k does not skip over the value that it is supposed to be
    //iterating through
    //may cause it to passover a valid answer. easy fix if necessary
    //just if statement when k == n when applicable etc...
    for (int k = 0; k < 9; k++) {
        if (lev.read(m, k) == entry) {
            issue_x = m
            issue_y = k;
            return false;
        }
        if (lev.read(k, n) == entry) {
            issue_x = k;
            issue_y = n;
            return false;
        }
        //SECTION CHECKER
        //std::cout << "point: " <<m<< "," << n << "    entry: " << entry << std::endl;
        if (k < 3) {
            if (m < 3) { //Section 1
                if (n < 3) {// section 1,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k, a) == entry) {
                            issue_x = k;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 2 && n < 6) {//section 1,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k, a) == entry) {
                            issue_x = k;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 5 && n < 9) {//section 1,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k, a) == entry) {
                            issue_x = k;
                            issue_y = a;
                            return false;
                        }
                    }
                }
            }//end section 1,k
            if (m > 2 && m < 6) {//section 2, k
                if (n < 3) {// section 2,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            issue_x = k + 3;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 2 && n < 6) {//section 2,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            issue_x = k + 3;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 5 && n < 9) {//section 2,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k + 3, a) == entry) {
                            issue_x = k + 3;
                            issue_y = a;
                            return false;
                        }
                    }
                }
            }//end section 2,k
            if (m > 5 && m < 9) {//section 3,k
                if (n < 3) {// section 3,1
                    for (int a = 0; a < 3; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            issue_x = k + 6;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 2 && n < 6) {//section 3,2
                    for (int a = 3; a < 6; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            issue_x = k + 6;
                            issue_y = a;
                            return false;
                        }
                    }
                }
                if (n > 5 && n < 9) {//section 3,3
                    for (int a = 6; a < 9; a++) {
                        if (lev.read(k + 6, a) == entry) {
                            issue_x = k + 6;
                            issue_y = a;
                            return false;
                        }
                    }
                }
            }//end section 3,k
        }// end section checker
    }//end k
    return true;
}
