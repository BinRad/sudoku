#include "rank.h"
#include "board.h"
#include "four.h"
#include <iostream>
#include "assert.h"

namespace sudoku_one {
    four::four(sudoku_one::board &lev, sudoku_one::rank &sim) {
        i = sim.getrow();
        j = sim.getcol();
        issue_x = 99;
        issue_y = 99;
        entry = 0;
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                for (int c = 0; c < 9; c++) {
                    for (int d = 0; d < 9; d++) {
                        freed[a][b][c][d] = 0;
                    }
                    answers[a][b][c] = 99;
                    bad_ans[a][b][c] = 99;
                }
                for (int w = 0; w < 81; w++) {
                    prob_row[a][b][w] = 99;
                    prob_col[a][b][w] = 99;
                }
                current_prob[a][b] = 0;
                last_prob[a][b] = 0;
                current_ans[a][b] = 0;
                last_ans[a][b] = 0;
                current_free[a][b] = 0;
            }
        }
        find_poss_entries(lev, sim);
        make_prob(lev, sim);
        solve(lev, sim);
    }

    //modification functions
    void four::solve(sudoku_one::board &lev, sudoku_one::rank &sim) {
        std::cout << std::endl;
        entry = finder(lev, sim);
        std::cout << i << j << entry << std::endl;
        lev.mod(i, j, entry);
        //  lev.printout();
        //    lev.printout(4);
        sim.advance(i, j);
        i = sim.getrow();
        j = sim.getcol();
        if (i > 8 || j > 8) {
            if (is_done(lev, sim)) {
                return;
            } else {
                sim.beginning();
                i = sim.getrow();
                j = sim.getcol();
            }
        }
        entry = 0;
        lev.printout();
        lev.printout(4);
        solve(lev, sim);
    }

    int four::finder(sudoku_one::board &lev, sudoku_one::rank &sim) {
        entry = answers[i][j][current_ans[i][j]];
        //while loop can be skipped if current ans is correct
        while (finder_checker(lev, sim) == false || entry == 99) {
            entry = answers[i][j][current_ans[i][j]];
            if (entry == 99) {
                std::cout << i << j << "99 to free entry awayyyyy" << std::endl;
                entry = free_entry(lev, sim);
                // free_entry will update current_ans
                if (entry == 99) {
                    sim.add_to_queue(i, j);
                    sim.advance();
                    solve(lev, sim);
                }
                return entry;
            }
        }
        return entry;
    }

    bool four::finder_checker(sudoku_one::board &lev, sudoku_one::rank &sim) {
        //possible issue that entry is being checked against
        //itself since k does not skip over the value that it is supposed to be
        //iterating through
        //may cause it to passover a valid answer. easy fix if necessary
        //just if statement when k == j when applicable etc...
        for (int k = 0; k < 9; k++) {
            if (lev.read(i, k) == entry) {
                if (j != k) {
                    issue_x = i;
                    issue_y = k;
                    mark_bad(lev, sim);
                    return false;
                }
            }
            if (lev.read(k, j) == entry) {
                if (i != k) {
                    issue_x = k;
                    issue_y = j;
                    mark_bad(lev, sim);
                    return false;
                }
            }
            //SECTION CHECKER
            //std::cout << "point: " << i << "," << j << "    entry: " << entry << std::endl;
            if (k < 3) {
                if (i < 3) { //Section 1
                    if (j < 3) {// section 1,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 1,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 1,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                }//end section 1,k
                if (i > 2 && i < 6) {//section 2, k
                    if (j < 3) {// section 2,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 2,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 2,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                }//end section 2,k
                if (i > 5 && i < 9) {//section 3,k
                    if (j < 3) {// section 3,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 3,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 3,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    mark_bad(lev, sim);
                                    return false;
                                }
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
        return true;
    }

    void four::mark_bad(sudoku_one::board &lev, sudoku_one::rank &sim) {
        //take entry out of answers array

        int tempans = answers[i][j][current_ans[i][j]];
        for (int c = current_ans[i][j]; c <= last_ans[i][j]; c++) {
            if (c + 1 < 9) {
                answers[i][j][c] = answers[i][j][c + 1];
            }
        }
        last_ans[i][j]--;
        for (int d = last_ans[i][j]; d < 9; d++) {
            answers[i][j][d] = 99;
        }
        int d = 0;
        while (bad_ans[i][j][d] != 99 && d < 9 && bad_ans[i][j][d] != tempans) {
            d++;
        }
        bad_ans[i][j][d] = tempans;
        update_prob_data(d);
    }

    void four::update_prob_data(int d) {
        // q is where x and y are currently in the arrays
        // d is the index position we want them to be in
        int q = 1;
        while (prob_row[i][j][q] != issue_x && prob_col[i][j][q] != issue_y) {
            q++;
        }
        if (q == d) {
            return;
        } else {
            while (q < d) {
                prob_row[i][j][q - 1] = prob_row[i][j][q];
                prob_col[i][j][q - 1] = prob_col[i][j][q];
                q++;
            }
            while (q > d) {
                prob_row[i][j][q] = prob_row[i][j][q - 1];
                prob_col[i][j][q] = prob_col[i][j][q - 1];
                q--;
            }
            prob_row[i][j][d] = issue_x;
            prob_col[i][j][d] = issue_y;
        }
    }

    void four::find_poss_entries(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int c = 0;
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                for (int d = 1; d < 10; d++) {
                    if (poss_entry_checker(a, b, d, lev, sim)) {
                        answers[a][b][last_ans[a][b]] = d;
                        last_ans[a][b]++;
                    }
                }
                c = last_ans[a][b];
                while (c < 9) {
                    answers[a][b][c] = 99;
                    c++;
                }
            }
        }
    }

    bool four::poss_entry_checker(int a, int b, int d, sudoku_one::board &lev, sudoku_one::rank &sim) {
        for (int k = 0; k < 9; k++) {
            if (lev.read_ini(a, k) == d) {

                return false;
            }
            if (lev.read_ini(k, b) == d) {
                return false;
            }
            //SECTION CHECKER
            if (k < 3) {
                if (a < 3) { //Section 1
                    if (b < 3) {// section 1,1
                        for (int z = 0; z < 3; z++) {
                            if (lev.read_ini(k, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 2 && b < 6) {//section 1,2
                        for (int z = 3; z < 6; z++) {
                            if (lev.read_ini(k, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 5 && b < 9) {//section 1,3
                        for (int z = 6; z < 9; z++) {
                            if (lev.read_ini(k, z) == d) {
                                return false;
                            }
                        }
                    }
                }//end section 1,k
                if (a > 2 && a < 6) {//section 2, k
                    if (b < 3) {// section 2,1
                        for (int z = 0; z < 3; z++) {
                            if (lev.read_ini(k + 3, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 2 && b < 6) {//section 2,2
                        for (int z = 3; z < 6; z++) {
                            if (lev.read_ini(k + 3, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 5 && b < 9) {//section 2,3
                        for (int z = 6; z < 9; z++) {
                            if (lev.read_ini(k + 3, z) == d) {
                                return false;
                            }
                        }
                    }
                }//end section 2,k
                if (a > 5 && a < 9) {//section 3,k
                    if (b < 3) {// section 3,1
                        for (int z = 0; z < 3; z++) {
                            if (lev.read_ini(k + 6, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 2 && b < 6) {//section 3,2
                        for (int z = 3; z < 6; z++) {
                            if (lev.read_ini(k + 6, z) == d) {
                                return false;
                            }
                        }
                    }
                    if (b > 5 && b < 9) {//section 3,3
                        for (int z = 6; z < 9; z++) {
                            if (lev.read_ini(k + 6, z) == d) {
                                return false;
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
        return true;
    }

    void four::make_prob(sudoku_one::board &lev, sudoku_one::rank &sim) {
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                for (int k = 0; k < 9; k++) {
                    if (lev.read_ini(a, k) == 0) {
                        if (b != k) {
                            compare_ans(a, b, a, k);
                            //k = 0;
                        }
                        if (lev.read_ini(k, b) == 0) {
                            if (a != k) {
                                compare_ans(a, b, k, b);
                            }
                            //k = 0;
                        }
                        //SECTION CHECKER
                        if (k < 3) {
                            if (a < 3) { //Section 1
                                if (b < 3) {// section 1,1
                                    for (int z = 0; z < 3; z++) {
                                        if (lev.read_ini(k, z) == 0) {
                                            if (a != k || b != z) {
                                                compare_ans(a, b, k, z);
                                            }
                                            //k = 0;
                                            //a = -1;
                                        }
                                    }
                                }
                                if (b > 2 && b < 6) {//section 1,2
                                    for (int z = 3; z < 6; z++) {
                                        if (lev.read_ini(k, z) == 0) {
                                            if (a != k || b != z) {
                                                compare_ans(a, b, k, z);
                                            }
//                                      k = 0;
//                                      a = 2;
                                        }
                                    }
                                }
                                if (b > 5 && b < 9) {//section 1,3
                                    for (int z = 6; z < 9; z++) {
                                        if (lev.read_ini(k, z) == 0) {
                                            if (a != k || b != z) {
                                                compare_ans(a, b, k, z);
                                            }
//                                      k = 0;
//                                      a= 5;
                                        }
                                    }
                                }
                            }//end section 1,k
                            if (a > 2 && a < 6) {//section 2, k
                                if (b < 3) {// section 2,1
                                    for (int z = 0; z < 3; z++) {
                                        if (lev.read_ini(k + 3, z) == 0) {
                                            if (a != k + 3 || b != z) {
                                                compare_ans(a, b, k + 3, z);
                                            }
//                                      k = 0;
//                                      a = -1;
                                        }
                                    }
                                }
                                if (b > 2 && b < 6) {//section 2,2
                                    for (int z = 3; z < 6; z++) {
                                        if (lev.read_ini(k + 3, z) == 0) {
                                            if (a != k + 3 || b != z) {
                                                compare_ans(a, b, k + 3, z);
                                            }
//                                      k = 0;
//                                      a = 2;
                                        }
                                    }
                                }
                                if (b > 5 && b < 9) {//section 2,3
                                    for (int z = 6; z < 9; z++) {
                                        if (lev.read_ini(k + 3, z) == 0) {
                                            if (a != k + 3 || b != z) {
                                                compare_ans(a, b, k + 3, z);
                                            }
//                                      k = 0;
//                                      a = 5;
                                        }
                                    }
                                }
                            }//end section 2,k
                            if (a > 5 && a < 9) {//section 3,k
                                if (b < 3) {// section 3,1
                                    for (int z = 0; z < 3; z++) {
                                        if (lev.read_ini(k + 6, z) == 0) {
                                            compare_ans(a, b, k + 6, z);
//                                      k = 0;
//                                      a = -1;
                                        }
                                    }
                                }
                                if (b > 2 && b < 6) {//section 3,2
                                    for (int z = 3; z < 6; z++) {
                                        if (lev.read_ini(k + 6, z) == 0) {
                                            if (a != k + 6 || b != z) {
                                                compare_ans(a, b, k + 6, z);
                                            }
//                                      k = 0;
//                                      a = 2;
                                        }
                                    }
                                }
                                if (b > 5 && b < 9) {//section 3,3
                                    for (int z = 6; z < 9; z++) {
                                        if (lev.read_ini(k + 6, z) == 0) {
                                            if (a != k + 6 || b != z) {
                                                compare_ans(a, b, k + 6, z);
                                            }
//                                      k = 0;
//                                      a = 5;
                                        }
                                    }
                                }
                            }//end section 3,k
                        }// end section checker
                    }//end k
                }
            }
        }
    }

    void four::compare_ans(int a, int b, int m, int n) {
        for (int q = 0; q < 9; q++) {
            if (prob_row[a][b][q] == m && prob_col[a][b][q] == n) {
                return;
            }
            for (int z = 0; z < 9; z++) {
                if (answers[a][b][q] == answers[m][n][z] && answers[a][b][q] != 99) {
                    //make sure its not the actual ij
                    if (a == m && b == n) {
                        return;
                    }
                    //make sure there are nor repetitions
                    for (int x = 0; x < 81; x++) {
                        if (prob_row[a][b][x] == m && prob_col[a][b][x] == n) {
                            return;
                        }
                    }
                    prob_row[a][b][last_prob[a][b]] = m;
                    prob_col[a][b][last_prob[a][b]] = n;
                    last_prob[a][b]++;
                    //return;
                }
            }
        }
//        return false;
    }

    int four::free_entry(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int temp = 99;
        temp = check_for_free(lev, sim);
        if (temp != 99) {
            std::cout << " found free: " << entry << std::endl;
            return temp;
        } else {
            //calls function which finds
            entry = bad_ans[i][j][0];
            if (entry == 99) { //if there is no current entry
                sim.add_to_queue(i,j);
                sim.advance();
                solve(lev,sim);
            }
            get_bad_ans(lev, sim);
            set_issue(lev, sim);
            mark_good(lev, sim); // puts entry in answers[0] and put probrow in back
            free_entry_helper(lev, sim);
        }
        return entry;
    }

    int four::get_bad_ans(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int g = 0;
        while (g <= last_prob[i][j]) {
            entry = bad_ans[i][j][g];
            if (get_bad_ans_checker(lev, sim, 0)) {
                return entry;
            }
            g++;
        }
        entry = bad_ans[i][j][current_prob[i][j]];
        get_bad_ans_checker(lev, sim, 1);
        return entry;
    }

    bool four::get_bad_ans_checker(sudoku_one::board &lev, sudoku_one::rank &sim, int setting) {
        //possible issue that entry is being checked against
        //itself since k does not skip over the value that it is supposed to be
        //iterating through
        //may cause it to passover a valid answer. easy fix if necessary
        //just if statement when k == j when applicable etc...
        for (int k = 0; k < 9; k++) {
            if (lev.read(i, k) == entry) {
                if (j != k) {
                    issue_x = i;
                    issue_y = k;
                    if (setting == 1) {
                        lev.mod(issue_x, issue_y, 0);
                        sim.add_to_queue(issue_x, issue_y);
                    } else {
                        return false;
                    }
                }
            }
            if (lev.read(k, j) == entry) {
                if (i != k) {
                    issue_x = k;
                    issue_y = j;
                    if (setting == 1) {
                        lev.mod(issue_x, issue_y, 0);
                        sim.add_to_queue(issue_x, issue_y);
                    } else {
                        return false;
                    }
                }
            }
            //SECTION CHECKER
            //std::cout << "point: " << i << "," << j << "    entry: " << entry << std::endl;
            if (k < 3) {
                if (i < 3) { //Section 1
                    if (j < 3) {// section 1,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 1,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 1,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k, a) == entry) {
                                if (i != k || j != a) {
                                    issue_x = k;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }//end section 1,k
                if (i > 2 && i < 6) {//section 2, k
                    if (j < 3) {// section 2,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 2,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 2,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 3, a) == entry) {
                                if (i != k + 3 || j != a) {
                                    issue_x = k + 3;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }//end section 2,k
                if (i > 5 && i < 9) {//section 3,k
                    if (j < 3) {// section 3,1
                        for (int a = 0; a < 3; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 2 && j < 6) {//section 3,2
                        for (int a = 3; a < 6; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                    if (j > 5 && j < 9) {//section 3,3
                        for (int a = 6; a < 9; a++) {
                            if (lev.read(k + 6, a) == entry) {
                                if (i != k + 6 || j != a) {
                                    issue_x = k + 6;
                                    issue_y = a;
                                    if (setting == 1) {
                                        lev.mod(issue_x, issue_y, 0);
                                        sim.add_to_queue(issue_x, issue_y);
                                    } else {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }//end section 3,k
            }// end section checker
        }//end k
        return true;
    }

    int four::check_for_free(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int c = 0;
        while (answers[i][j][c] != 99) {
            entry = answers[i][j][c];
            if (finder_checker(lev, sim)) {
                return answers[i][j][c];
            }
            c++;
        }
        return 99;
    }

    void four::free_entry_helper(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int tempx, tempy;
        tempx = i;
        tempy = j;
        i = issue_x;
        j = issue_y;
        issue_x = tempx;
        issue_y = tempy;
        lev.mod(i, j, 0);
        mark_bad(lev, sim);
        issue_x = i;
        issue_y = j;
        i = tempx;
        j = tempy;
        //solve(lev, sim);
    }

    void four::set_issue(sudoku_one::board &lev, sudoku_one::rank &sim) {
        issue_x = prob_row[i][j][current_prob[i][j]];
        issue_y = prob_col[i][j][current_prob[i][j]];
        if (freed[i][j][issue_x][issue_y] == 0) {
            freed[i][j][issue_x][issue_y] = 1;//update matrix
            //now go back to free_entry
        } else {
            //go to the next problem
            next_problem(lev, sim);
            free_entry(lev, sim);
            //this may cause a loop. in order to fix this we need to say this is
            //all done. you cannot change the entry for this x,y anymore. We need
            //to move to the next x,y or maybe the next x,y of the next x,y
        }
    }

    void four::next_problem(sudoku_one::board &lev, sudoku_one::rank &sim) {
        if (current_prob[i][j] + 1 != last_prob[i][j]) {
            current_prob[i][j]++;
            if (bad_ans[i][j][current_prob[i][j]] == 99) {
                issue_x = prob_row[i][j][current_prob[i][j]];
                issue_y = prob_col[i][j][current_prob[i][j]];
                entry = lev.read(issue_x, issue_y);
            }
        } else {
            current_prob[i][j] = 0;
            std::cout << "this wont cut it for next next_problem <3" << std::endl;
            //this may cause a loop. in order to fix this we need to say this is
            //all done. you cannot change the entry for this x,y anymore. We need
            //to move to the next x,y or maybe the next x,y of the next x,y
        }
    }

    void four::mark_good(sudoku_one::board &lev, sudoku_one::rank &sim) {
        int c = current_prob[i][j];
        int freeans = bad_ans[i][j][current_prob[i][j]];
        int endx = prob_row[i][j][current_prob[i][j]];
        int endy = prob_col[i][j][current_prob[i][j]];
        while (prob_row[i][j][c] != 99 && prob_col[i][j][c] != 99) {
            if (c + 1 < 9) {
                bad_ans[i][j][c] = bad_ans[i][j][c + 1];
            }
            prob_row[i][j][c] = prob_row[i][j][c + 1];
            prob_col[i][j][c] = prob_col[i][j][c + 1];
            c++;
        }
        prob_row[i][j][c] = endx;
        prob_col[i][j][c] = endy;
        for (int q = last_ans[i][j]; q > 0; q--) {
            answers[i][j][q] = answers[i][j][q - 1];
        }
        answers[i][j][0] = freeans;
        last_ans[i][j]++;
        current_prob[i][j] = 0;
    }

    bool four::is_done(sudoku_one::board &lev, sudoku_one::rank &sim) {
        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 9; b++) {
                if (lev.read(a, b) == 0) {
                    return false;
                }
            }
        }
        return true;
    }
}
