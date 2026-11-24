/*
 * Problem   : Sudoku Solver (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/sudoku-solver/
 * Pattern   : Backtracking with constraint bitmasks
 * Approach  : Brute force: Backtracking with full rescans
 * Complexity: Time O(9^m · 27), Space O(m)
 *
 * Walk the cells in row-major order. At an empty cell, try each digit 1-9
 * and check its row, column and box by scanning board. If the digit is
 * legal, write it and recurse; if the recursion fails, reset the cell to '.'
 * and try the next digit. Every complete filling reached this way is valid
 * by construction, and the search tries every consistent partial assignment,
 * so it must find the unique solution.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Check by rescanning the board whether digit d can go at (r, c)
    bool isValid(vector<vector<char>>& board, int r, int c, char d) {
        int br = 3 * (r / 3);              // top row of the 3x3 box
        int bc = 3 * (c / 3);              // left column of the 3x3 box
        for (int k = 0; k < 9; k++) {
            if (board[r][k] == d) return false;                       // same row
            if (board[k][c] == d) return false;                       // same column
            if (board[br + k / 3][bc + k % 3] == d) return false;     // same box
        }
        return true;
    }

    // Fill the first empty cell, recurse, and backtrack on failure
    bool solve(vector<vector<char>>& board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') continue;      // only empty cells need a choice
                for (char d = '1'; d <= '9'; d++) {
                    if (!isValid(board, r, c, d)) continue;  // skip digits that clash
                    board[r][c] = d;                   // tentatively place d
                    if (solve(board)) return true;     // rest solved: keep it
                    board[r][c] = '.';                 // undo and try the next digit
                }
                return false;                          // no digit fits: backtrack
            }
        }
        return true;                                   // no empty cell left: solved
    }

    void solveSudoku(vector<vector<char>>& board) {
        solve(board);                                  // board is filled in place
    }
};

int main() {
    vector<vector<char>> board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}};
    vector<vector<char>> expected = {
        {'5','3','4','6','7','8','9','1','2'},
        {'6','7','2','1','9','5','3','4','8'},
        {'1','9','8','3','4','2','5','6','7'},
        {'8','5','9','7','6','1','4','2','3'},
        {'4','2','6','8','5','3','7','9','1'},
        {'7','1','3','9','2','4','8','5','6'},
        {'9','6','1','5','3','7','2','8','4'},
        {'2','8','7','4','1','9','6','3','5'},
        {'3','4','5','2','8','6','1','7','9'}};
    Solution sol;
    sol.solveSudoku(board);
    cout << "Output            | Expected" << endl;
    for (int i = 0; i < 9; i++) {
        for (char ch : board[i]) cout << ch << ' ';
        cout << "| ";
        for (char ch : expected[i]) cout << ch << ' ';
        cout << endl;
    }
    cout << (board == expected ? "MATCH" : "MISMATCH") << endl;
    return 0;
}
