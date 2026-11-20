/*
 * Problem   : Count Square Submatrices with All Ones (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/count-square-submatrices-with-all-ones/
 * Pattern   : 2D DP: largest square ending at each cell
 * Approach  : Optimal: Space-optimised DP with two rows
 * Complexity: Time O(m·n), Space O(n)
 *
 * Keep prev, the dp values of the row above, and cur, the row being filled.
 * For each matrix[i][j] = 1, cur[j] is 1 on the top row or left column and 1
 * + min(prev[j], cur[j - 1], prev[j - 1]) otherwise, while a 0 cell keeps
 * cur[j] = 0. Each cur[j] is added to total, and after the row prev ← cur.
 * The recurrence and the evaluation order are exactly those of the 2D table,
 * so the result is identical, but only two rows are alive at any time.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();         // number of rows
        int n = matrix[0].size();      // number of columns
        vector<int> prev(n, 0);        // dp values of the row above (all 0 above row 0)
        int total = 0;                 // running count of all-ones squares
        for (int i = 0; i < m; i++) {
            vector<int> cur(n, 0);     // dp values of row i; a 0 cell keeps 0
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    if (i == 0 || j == 0) {
                        cur[j] = 1;    // border cell: only a 1x1 square can end here
                    } else {
                        // limited by the smallest square ending directly above (prev[j]),
                        // directly left (cur[j - 1]) and diagonally up-left (prev[j - 1])
                        cur[j] = 1 + min({prev[j], cur[j - 1], prev[j - 1]});
                    }
                    total += cur[j];   // side s means s squares (sides 1..s) end here
                }
            }
            prev = cur;                // row i becomes the row above for row i + 1
        }
        return total;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}};
    cout << "Example 1: " << sol.countSquares(matrix1) << " (expected 15)\n";

    vector<vector<int>> matrix2 = {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}};
    cout << "Example 2: " << sol.countSquares(matrix2) << " (expected 7)\n";

    return 0;
}
