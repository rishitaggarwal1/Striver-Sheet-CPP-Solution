/*
 * Problem   : Zigzag Conversion (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/zigzag-conversion/
 * Pattern   : Simulation, then periodic index arithmetic
 * Approach  : Brute force: 2D grid simulation
 * Complexity: Time O(numRows · n), Space O(numRows · n)
 *
 * Allocate a grid with numRows rows and enough columns: each cycle of
 * 2*numRows-2 characters uses numRows-1 columns. Place characters going
 * straight down a column, then diagonally up-right one cell per character
 * until row 0, and repeat. Reading the grid row by row, skipping empty
 * cells, gives exactly the line-by-line order. This is correct because the
 * grid is a faithful copy of the drawn zigzag.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows == 1) return s;                 // no zigzag; also avoids cycle == 0
        int cycle = 2 * numRows - 2;                // chars in one down + diagonal pass
        int cols = ((n + cycle - 1) / cycle) * (numRows - 1); // ceil(n/cycle) cycles, numRows-1 columns each
        vector<string> grid(numRows, string(cols, '\0')); // '\0' is BLANK; '.' can't be used since s may contain it
        int row = 0, col = 0;                       // current cell of the cursor
        for (int i = 0; i < n; ++i) {
            grid[row][col] = s[i];                  // place the character
            if (i % cycle < numRows - 1) {
                ++row;                              // still on the vertical stroke: go down
            } else {
                --row;                              // on the diagonal: go up ...
                ++col;                              // ... and one column right
            }
        }
        string result;
        result.reserve(n);                          // the output has exactly n characters
        for (int r = 0; r < numRows; ++r)           // read line by line
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] != '\0')             // skip the empty cells
                    result += grid[r][c];
        return result;
    }
};

int main() {
    Solution sol;
    vector<tuple<string, int, string>> tests = {
        {"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
        {"PAYPALISHIRING", 4, "PINALSIGYAHRPI"},
        {"A", 1, "A"}
    };
    for (auto& [s, rows, expected] : tests) {
        string got = sol.convert(s, rows);
        cout << "convert(\"" << s << "\", " << rows << ") = \"" << got
             << "\"  expected \"" << expected << "\""
             << (got == expected ? "  [OK]" : "  [FAIL]") << "\n";
    }
    return 0;
}
