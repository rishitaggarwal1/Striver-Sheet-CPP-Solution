/*
 * Problem   : N-Queens (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/n-queens/
 * Pattern   : Backtracking with constant-time conflict sets
 * Approach  : Brute force: Enumerate column permutations
 * Complexity: Time O(n! · n^2), Space O(n)
 *
 * Represent a board by cols[r], the column of the queen in row r. Rows and
 * columns are automatically distinct when cols is a permutation, so generate
 * all n! permutations. For each one, check every pair of rows i < j for a
 * diagonal clash: |cols[i] - cols[j]| == j - i. Permutations with no clash
 * are exactly the valid boards, so collecting them gives every distinct
 * solution.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

string boardsToString(const vector<vector<string>>& b) {
    string out = "[";
    for (size_t k = 0; k < b.size(); k++) {
        if (k) out += ",";
        out += "[";
        for (size_t r = 0; r < b[k].size(); r++) {
            if (r) out += ",";
            out += "\"" + b[k][r] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> ans;
    // Returns true if no two queens on this board share a diagonal.
    // Rows and columns are already distinct because the board comes from a permutation.
    bool check(vector<string> board, int n)
    {
        vector<int> cols(n);
        for (int r = 0; r < n; r++)
            cols[r] = (int)board[r].find('Q');          // recover the queen's column in row r
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)               // every pair of rows i < j
                if (abs(cols[i] - cols[j]) == j - i)      // equal row and column gaps mean same diagonal
                    return false;
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        string st(n,'.');
        vector<string> s(n,st);
        vector<int> cols(n);
        iota(cols.begin(), cols.end(), 0);                // smallest permutation 0,1,...,n-1
        do {
            for (int r = 0; r < n; r++) {
                s[r] = st;                                // clear row r
                s[r][cols[r]] = 'Q';                      // place row r's queen at cols[r]
            }
            if (check(s, n))                              // keep only boards with no diagonal clash
                ans.push_back(s);
        } while (next_permutation(cols.begin(), cols.end())); // visit all n! permutations
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
