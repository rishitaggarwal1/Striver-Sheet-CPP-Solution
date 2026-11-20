/*
 * Problem   : Minimum Falling Path Sum (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/minimum-falling-path-sum/
 * Pattern   : Grid DP, row by row (free start and end)
 * Approach  : Optimal: Two rolling rows
 * Complexity: Time O(n^2), Space O(n)
 *
 * Start with prev equal to matrix[0]. For each later row build a new array
 * cur where cur[col] = matrix[row][col] + min(prev[col - 1], prev[col],
 * prev[col + 1]) over the in-range neighbours, then set prev = cur. A
 * separate cur is needed because cur[col + 1] still needs the old prev[col],
 * so overwriting prev in place would mix two rows. After the last row, prev
 * holds the best sum ending at every bottom cell, and its minimum is the
 * answer.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();                          // matrix is n x n
        vector<int> prev(matrix[0]);                    // row 0: a path ending there is just that cell
        for (int row = 1; row < n; ++row) {
            vector<int> cur(n, 0);                      // separate array: prev must stay intact while this row is built
            for (int col = 0; col < n; ++col) {
                int best = prev[col];                   // straight down from (row - 1, col)
                if (col > 0)
                    best = min(best, prev[col - 1]);    // diagonal from the up-left cell
                if (col < n - 1)
                    best = min(best, prev[col + 1]);    // diagonal from the up-right cell
                cur[col] = matrix[row][col] + best;     // extend the cheapest reachable path
            }
            prev = cur;                                 // only the latest row is needed for the next one
        }
        int ans = prev[0];
        for (int col = 1; col < n; ++col)
            ans = min(ans, prev[col]);                  // the path may end at any column of the last row
        return ans;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << "Example 1: output = " << sol.minFallingPathSum(matrix1) << " (expected: 13)\n";

    vector<vector<int>> matrix2 = {{-19, 57}, {-40, -5}};
    cout << "Example 2: output = " << sol.minFallingPathSum(matrix2) << " (expected: -59)\n";

    return 0;
}
