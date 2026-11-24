/*
 * Problem   : N-Queens (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/n-queens/
 * Pattern   : Backtracking with constant-time conflict sets
 * Approach  : Optimal: Backtracking with column/diagonal sets
 * Complexity: Time O(n!), Space O(n)
 *
 * Keep three boolean arrays: colUsed[c], diag[r - c + n - 1] and anti[r +
 * c]. All cells on one diagonal share the same r - c and all cells on one
 * anti-diagonal share the same r + c, so a cell is attacked exactly when one
 * of its three entries is true. Place a queen by setting the three entries,
 * recurse, then clear them on return so the state again describes only rows
 * 0..r-1. This invariant keeps every check O(1), and the search tree is the
 * same as before, so correctness carries over. Bitmasks can replace the
 * arrays for even tighter constant factors.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

string boardsToString(const vector<vector<string>>& b) {
    string out = "[";
    for (size_t i = 0; i < b.size(); i++) {
        if (i) out += ",";
        out += "[";
        for (size_t j = 0; j < b[i].size(); j++) {
            if (j) out += ",";
            out += "\"" + b[i][j] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> ans;          // collected solutions
    vector<bool> colUsed, diag, anti;    // attack flags for columns, diagonals, anti-diagonals

    // O(1) check: is cell (r, c) attacked by a queen in rows 0..r-1?
    bool valid(vector<string>& s, int r, int c)
    {
        int n = s.size();
        return !colUsed[c] && !diag[r - c + n - 1] && !anti[r + c]; // r-c+n-1 shifts the diagonal id into [0, 2n-2]
    }

    // place a queen in row r, given that rows 0..r-1 are already filled safely
    void nqueen(vector<string>& s, int r, int n)
    {
        if (r == n)                      // all rows filled: s is a full solution
        {
            ans.push_back(s);            // store a copy of the board
            return;
        }
        for (int c = 0; c < n; c++)
        {
            if (!valid(s, r, c)) continue;          // attacked: skip this column
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = true; // claim column and both diagonals
            s[r][c] = 'Q';
            nqueen(s, r + 1, n);                    // fill the remaining rows
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = false; // undo so state covers rows 0..r-1 only
            s[r][c] = '.';
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        ans.clear();                                 // allow reuse of the same object
        colUsed.assign(n, false);                    // one flag per column
        diag.assign(2 * n - 1, false);               // 2n-1 diagonals (r-c constant)
        anti.assign(2 * n - 1, false);               // 2n-1 anti-diagonals (r+c constant)
        string s(n, '.');
        vector<string> v(n, s);                      // empty n x n board
        nqueen(v, 0, n);                             // start from row 0
        return ans;
    }
};

int main() {
    {
        Solution sol;
        auto res = sol.solveNQueens(4);
        cout << "n = 4\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\".Q..\",\"...Q\",\"Q...\",\"..Q.\"],[\"..Q.\",\"Q...\",\"...Q\",\".Q..\"]]\n\n";
    }
    {
        Solution sol;
        auto res = sol.solveNQueens(1);
        cout << "n = 1\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\"Q\"]]\n";
    }
    return 0;
}
