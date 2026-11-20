/*
 * Problem   : Triangle (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/triangle/
 * Pattern   : 2D grid DP on a triangle, filled bottom-up
 * Approach  : Optimal: Bottom-up DP with one row array
 * Complexity: Time O(n^2), Space O(n)
 *
 * Let dp[j] hold the minimum path sum from column j of the row below to the
 * bottom; initially that row is the last row itself, so dp is a copy of it.
 * To lift dp to row i, set dp[j] = triangle[i][j] + min(dp[j], dp[j + 1])
 * for j = 0..i. Going left to right is safe: when dp[j] is overwritten, the
 * values it needs, old dp[j] and dp[j + 1], are still the row-below values,
 * and old dp[j] is never needed again because column j - 1 is already done.
 * After row 0, dp[0] is the answer; the higher entries are leftovers from
 * lower rows and are ignored.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();                     // number of rows
        vector<int> dp(n, 0);                        // dp[j] = cheapest sum from column j of the last finished row to the bottom
        for (int j = 0; j < n; j++)
            dp[j] = triangle[n - 1][j];              // bottom row: each cell is its own path
        for (int i = n - 2; i >= 0; i--) {           // lift dp one row at a time, bottom to top
            for (int j = 0; j <= i; j++) {           // row i has i + 1 cells
                int down = dp[j];                    // best from (i + 1, j)
                int diag = dp[j + 1];                // best from (i + 1, j + 1); still row i + 1 because we go left to right
                dp[j] = triangle[i][j] + min(down, diag);  // overwrite with the answer for (i, j)
            }
        }
        return dp[0];                                // the apex holds the minimum total
    }
};

int main() {
    Solution sol;

    vector<vector<int>> triangle1 = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << "Example 1: " << sol.minimumTotal(triangle1) << " (expected 11)\n";

    vector<vector<int>> triangle2 = {{-10}};
    cout << "Example 2: " << sol.minimumTotal(triangle2) << " (expected -10)\n";

    return 0;
}
