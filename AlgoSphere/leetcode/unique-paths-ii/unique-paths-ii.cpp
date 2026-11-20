/*
 * Problem   : Unique Paths II (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/unique-paths-ii/
 * Pattern   : 2D grid DP (counting paths)
 * Approach  : Optimal: Bottom-up DP with a single row
 * Complexity: Time O(m·n), Space O(n)
 *
 * Let dp[j] be the number of routes from (0, 0) to (i, j) for the row i
 * being processed. Scanning a row left to right, the old dp[j] is the count
 * of the cell above and dp[j - 1] was just updated to the count of the cell
 * on the left, so dp[j] ← dp[j] + dp[j - 1] is exactly the recurrence. An
 * obstacle sets dp[j] ← 0, which also stops its count from flowing right or
 * down. After the last row, dp[n - 1] is the count for the target.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();     // number of rows
        int n = obstacleGrid[0].size();  // number of columns
        // dp[j] = routes from (0, 0) to (i, j) for the row i being processed.
        // unsigned: cells that can never reach the target may hold counts far above 2 * 10^9; unsigned
        // overflow wraps (well defined) and the target's true count (<= 2 * 10^9 < 2^32) still comes out exact.
        vector<unsigned int> dp(n, 0);
        dp[0] = 1;                                // seed for the start; reset below if (0, 0) is an obstacle
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;                    // no route may pass through an obstacle
                } else if (j > 0) {
                    dp[j] += dp[j - 1];           // old dp[j] = routes from above, dp[j - 1] = routes from the left
                }
                // j == 0 and free: dp[0] keeps the count of the cell above (its only source)
            }
        }
        return (int)dp[n - 1];                    // count for the bottom-right cell
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << "Example 1: output = " << sol.uniquePathsWithObstacles(grid1) << " (expected: 2)\n";

    vector<vector<int>> grid2 = {{0, 1}, {0, 0}};
    cout << "Example 2: output = " << sol.uniquePathsWithObstacles(grid2) << " (expected: 1)\n";

    return 0;
}
