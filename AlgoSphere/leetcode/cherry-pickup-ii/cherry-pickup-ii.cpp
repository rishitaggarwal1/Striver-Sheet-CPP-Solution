/*
 * Problem   : Cherry Pickup II (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/cherry-pickup-ii/
 * Pattern   : 3D DP on (row, j1, j2): two walkers moving in lockstep
 * Approach  : Optimal: Bottom-up DP with two cols × cols layers
 * Complexity: Time O(rows · cols^2 · 9), Space O(cols^2)
 *
 * Let front[j1][j2] hold the best total from row i + 1 to the bottom with
 * the robots at j1 and j2. Start with the bottom row, where front[j1][j2] is
 * just that row's cherries. For each row i going up, compute every
 * cur[j1][j2] as row i's cherries plus the largest front[n1][n2] over the 9
 * moves that stay on the grid, then make cur the new front. Some pairs (for
 * example both robots in column 0 on row 0) can never actually occur, but
 * computing them is harmless: the answer reads only front[0][cols - 1], and
 * its chain of best moves passes only through states reachable from the
 * start.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();                          // number of rows
        int cols = grid[0].size();                       // number of columns
        // Cherries picked on row i when the robots stand in columns j1 and j2 (a shared cell counts once)
        auto cherries = [&](int i, int j1, int j2) {
            return j1 == j2 ? grid[i][j1] : grid[i][j1] + grid[i][j2];
        };
        // front[j1][j2] = best total from the row below down to the bottom with the robots at j1, j2
        vector<vector<int>> front(cols, vector<int>(cols, 0));
        for (int j1 = 0; j1 < cols; j1++)                // base layer: the bottom row
            for (int j2 = 0; j2 < cols; j2++)
                front[j1][j2] = cherries(rows - 1, j1, j2);
        for (int i = rows - 2; i >= 0; i--) {            // build each layer from the one below it
            vector<vector<int>> cur(cols, vector<int>(cols, 0));
            for (int j1 = 0; j1 < cols; j1++) {
                for (int j2 = 0; j2 < cols; j2++) {
                    int best = INT_MIN;                  // -infinity; the move (0, 0) is always legal, so it gets replaced
                    for (int d1 = -1; d1 <= 1; d1++) {
                        for (int d2 = -1; d2 <= 1; d2++) {
                            int n1 = j1 + d1, n2 = j2 + d2;                       // robots' columns on row i + 1
                            if (n1 >= 0 && n1 < cols && n2 >= 0 && n2 < cols)    // skip moves that leave the grid
                                best = max(best, front[n1][n2]);
                        }
                    }
                    cur[j1][j2] = cherries(i, j1, j2) + best;  // this row plus the best continuation
                }
            }
            front = move(cur);                           // row i becomes the layer below for row i - 1
        }
        return front[0][cols - 1];                       // robots start at (0, 0) and (0, cols - 1)
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid1 = {{3, 1, 1}, {2, 5, 1}, {1, 5, 5}, {2, 1, 1}};
    cout << "Example 1: " << sol.cherryPickup(grid1) << " (expected 24)\n";

    vector<vector<int>> grid2 = {{1, 0, 0, 0, 0, 0, 1}, {2, 0, 0, 0, 0, 3, 0}, {2, 0, 9, 0, 0, 0, 0}, {0, 3, 0, 5, 4, 0, 0}, {1, 0, 2, 3, 0, 0, 6}};
    cout << "Example 2: " << sol.cherryPickup(grid2) << " (expected 28)\n";

    return 0;
}
