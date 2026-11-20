# Minimum Falling Path Sum

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/minimum-falling-path-sum/) · Pattern: **Grid DP, row by row (free start and end)**

> Choose one cell per row of the `n × n` `matrix`, starting anywhere in row 0, where each next cell is directly below or diagonally below-left or below-right of the previous one, and return the smallest possible sum.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

Example 1:

Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.

Example 2:

Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.

Constraints:

- n == matrix.length == matrix[i].length

- 1 <= n <= 100

- -100 <= matrix[i][j] <= 100
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Pick one cell from every row, starting anywhere in the top row, so that each chosen cell is in the same column as the one above it or one column to its left or right, and make the total of the chosen values as small as possible.

</details>

<details>
<summary>Hint 2 · Observation</summary>

A cell `(row, col)` can only be entered from at most three cells of the row above: `(row - 1, col - 1)`, `(row - 1, col)` and `(row - 1, col + 1)`; cells in the first and last columns have only two. In Example 1 the two best paths `1 → 5 → 7` and `1 → 4 → 8` both cost 13 but pass through different middle cells.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n <= 100`, a falling path makes up to 3 choices per row, so trying every path costs around `n · 3^(n-1)`, astronomical for `n = 100`. There are only `10^4` cells, so constant work per cell is enough: aim for `O(n^2)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is grid dynamic programming filled row by row: the best path ending at a cell is built from the best paths ending at its parents in the previous row, and neighbouring cells share those parents.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

The cheapest falling path that ends at `(row, col)` is `matrix[row][col]` plus the cheapest falling path ending at one of its in-range parents, so each row can be computed from the previous row alone, and the answer is the minimum over the last row.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep one number per column for the previous row: `prev[col]` is the minimum sum of a falling path ending at `(row - 1, col)`. Build a separate array `cur` for the current row from `prev`, then let `cur` become `prev`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Copy the first row of `matrix` into `prev`.
For each `row` from 1 to `n - 1`, create a new array `cur`.
For each `col`, start `best` at `prev[col]`.
If `col > 0` compare with `prev[col - 1]`; if `col < n - 1` compare with `prev[col + 1]`.
Set `cur[col]` to `matrix[row][col] + best`, and after the row replace `prev` with `cur`.
Return the smallest value in `prev`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is the border: column 0 has no up-left parent and column `n - 1` has no up-right parent, so skip them (or treat them as `+∞`) instead of reading outside the row. Also handle `n = 1` (the answer is the single value), values as low as -100 (never use 0 or -1 as an 'unset' marker), and write into `cur`, not into `prev`, while `prev` is still needed. Time `O(n^2)`, extra space `O(n)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1)" | each cell depends only on at most three cells in the row above, a row-by-row DP recurrence. |
| "starts at any element in the first row" | every cell of row 0 is a base case, and since the path can also end anywhere, the answer is a minimum over the whole last row. |
| "-100 <= matrix[i][j] <= 100" | values can be negative, so greedy choices and 'unset' markers like 0 or -1 are unsafe; the DP must compare real sums. |
| "1 <= n <= 100" | only `10^4` cells, so `O(n^2)` is trivial while exploring all `≈ n · 3^(n-1)` paths is impossible. |

### What the constraints tell you

With `n <= 100` the matrix has `10^4` cells, so an `O(n^2)` DP does about `3·10^4` comparisons and runs instantly. Enumerating every falling path costs roughly `n · 3^(n-1)`, about `1.7·10^49` at `n = 100` (even `n = 20` gives about `2·10^10`), so the target is `O(n^2)`.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most direct way to solve it?**

<details>
<summary>Answer</summary>

Try every falling path: for each end cell in the last row, look back at the up to three allowed cells in the row above, recursively, and keep the smallest total. It is correct, but each row multiplies the number of paths by up to 3.

</details>

**Q2. Can I just step greedily to the smallest of the cells below?**

<details>
<summary>Answer</summary>

No. In `[[1,2,3],[50,50,1],[50,50,1]]` greedy starts at `1` and must then step onto a `50`, while starting at `2` and going `2 → 1 → 1` costs only 4. A cheap cell now can lead into expensive cells later.

</details>

**Q3. If I knew the best path ending at every cell of row `row - 1`, what is the best path ending at `(row, col)`?**

<details>
<summary>Answer</summary>

Its previous cell is `(row - 1, col - 1)`, `(row - 1, col)` or `(row - 1, col + 1)`, and the part before the last step must itself be the cheapest path to that parent. So `best(row, col) = matrix[row][col] + min` of the in-range parents' best values.

</details>

**Q4. Why is recursion on that formula slow, and how is it fixed?**

<details>
<summary>Answer</summary>

Neighbouring cells share parents, so `best(row - 1, col)` is requested by up to three cells below it and the repetition compounds over the rows. There are only `n^2` distinct `(row, col)` states, so compute each once, row by row from the top.

</details>

**Q5. Where do paths start and end in the DP?**

<details>
<summary>Answer</summary>

Anywhere: the row 0 values are the base cases, `best(0, col) = matrix[0][col]`, and the answer is the minimum of `best(n - 1, col)` over all columns. In Example 1 the last row ends up as `[13, 13, 14]`, so the answer is 13.

</details>

**Q6. How much of the table do I actually need?**

<details>
<summary>Answer</summary>

Row `row` only reads row `row - 1`, so keep one array `prev` for the previous row and build `cur` for the current one; memory drops from `n^2` to `n`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Recursion from every bottom cell](#1-brute-force-recursion-from-every-bottom-cell) | `O(n·3^n)` | `O(n)` |
| 2 | [Better: Bottom-up DP table](#2-better-bottom-up-dp-table) | `O(n^2)` | `O(n^2)` |
| 3 | [Optimal: Two rolling rows](#3-optimal-two-rolling-rows) | `O(n^2)` | `O(n)` |

### 1. Brute force: Recursion from every bottom cell

> **Where you start:** A falling path is just a sequence of choices (down-left, down, down-right), so the first instinct is to try them all; working backwards from the last row turns that into a short recursive formula.

**Idea.** Define `best(row, col)` as the minimum sum of a falling path that starts anywhere in row 0 and ends at `(row, col)`. If `col` is outside `0..n-1` the move is illegal and the value is `+∞`; if `row` is 0 the value is `matrix[0][col]`; otherwise it is `matrix[row][col]` plus the minimum of `best` at `(row - 1, col - 1)`, `(row - 1, col)` and `(row - 1, col + 1)`. This is correct because the last step into `(row, col)` comes from exactly one of those parents and the prefix before it must be optimal for that parent. The answer is the minimum of `best(n - 1, endCol)` over every column `endCol`.

**Steps**

1. Set `ans = +∞`.
2. For each column `endCol` of the last row, compute `best(n - 1, endCol)` and keep the minimum in `ans`.
3. In `best(row, col)`, return `+∞` if `col < 0` or `col >= n`.
4. Return `matrix[0][col]` if `row` is 0.
5. Otherwise recurse on the three parents in row `row - 1` and return `matrix[row][col]` plus their minimum.
6. Return `ans`.

**Pseudocode**

```text
 1 │ function minFallingPathSum(matrix)
 2 │   n ← number of rows in matrix
 3 │   ans ← +∞
 4 │   for endCol ← 0 to n - 1
 5 │     ans ← min(ans, best(n - 1, endCol))  // the path may end at any cell of the last row
 6 │   return ans
 7 │ function best(row, col)  // min sum of a falling path that starts in row 0 and ends at (row, col)
 8 │   if col < 0 or col ≥ n
 9 │     return +∞  // fell off the side: this move is not allowed
10 │   if row = 0
11 │     return matrix[0][col]  // a path may start at any cell of the first row
12 │   upLeft ← best(row - 1, col - 1)
13 │   up ← best(row - 1, col)
14 │   upRight ← best(row - 1, col + 1)
15 │   return matrix[row][col] + min(upLeft, up, upRight)  // up is always in range, so the min is a real sum
```

**Time complexity: `O(n·3^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Outer loop over end columns (lines 4-5) | n iterations × one recursion tree | Every cell of the last row is tried as the end of the path. |
| Recursive calls (lines 7-15) | up to (3^n - 1)/2 calls per tree × O(1) | Each call with row > 0 makes three calls one row higher, so a tree of depth n - 1 has at most 1 + 3 + … + 3^(n-1) nodes. |
| Border and base checks (lines 8-11) | O(1) per call | Off-matrix columns and row 0 stop immediately, which only trims the tree near the edges. |

- **Adding it up:** n × (3^n - 1)/2 × O(1) = O(n·3^n); the recursion trees dominate the O(n) outer loop.
- **At the maximum input:** n = 100 → up to about 2.6·10^49 calls, hopeless; n = 12 is about 3·10^6 calls and n = 15 already about 10^8.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 7-15) | at most n frames × O(1) | Each nested call moves one row up, from row n - 1 to row 0. |

- **Adding it up:** O(n) for the stack; no arrays are allocated.
- **Not counted:** matrix is the input and is not counted; with n <= 100 the stack is at most 100 frames deep.

**Dry run** on `matrix = [[-19,57],[-40,-5]] (Example 2; Example 1 has 9 cells, more than a short trace allows)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 2 and ans = +∞. Every cell of the last row will be tried as the end of the path. | `n = 2`<br>`ans = +∞`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`call stack = [minFallingPathSum] ← top` |
| 2 | 9 | endCol = 0 calls best(1, 0), whose first request is the up-left parent best(0, -1). Column -1 is off the matrix, so it returns +∞: that move is not allowed. | `endCol = 0`<br>`row = 0`<br>`col = -1`<br>`call stack = [minFallingPathSum endCol=0, best(1,0), best(0,-1)] ← top` |
| 3 | 13 | best(1, 0) stored upLeft = +∞; then best(0, 0) returned matrix[0][0] = -19 because row 0 is where paths start, so up = -19. | `row = 1`<br>`col = 0`<br>`upLeft = +∞`<br>`up = -19`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,0])<br>`call stack = [minFallingPathSum endCol=0, best(1,0) upLeft=+∞ up=-19] ← top` |
| 4 | 14 | best(0, 1) returns matrix[0][1] = 57, so upRight = 57. | `upRight = 57`<br>`call stack = [minFallingPathSum endCol=0, best(1,0) upLeft=+∞ up=-19 upRight=57] ← top` |
| 5 | 15 | best(1, 0) returns matrix[1][0] + min(+∞, -19, 57) = -40 + (-19) = -59. | (no change) |
| 6 | 5 | ans = min(+∞, -59) = -59 for paths that end at column 0. | `ans = -59`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`call stack = [minFallingPathSum endCol=0] ← top` |
| 7 | 12 | endCol = 1 calls best(1, 1). Its up-left parent best(0, 0) is computed again from scratch and returns -19, so upLeft = -19. | `endCol = 1`<br>`row = 1`<br>`col = 1`<br>`upLeft = -19`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,1])<br>`call stack = [minFallingPathSum endCol=1, best(1,1) upLeft=-19] ← top` |
| 8 | 13 | best(0, 1) is also recomputed and returns 57, so up = 57. | `up = 57`<br>`call stack = [minFallingPathSum endCol=1, best(1,1) upLeft=-19 up=57] ← top` |
| 9 | 9 | The up-right parent would be column 2, outside 0..1, so best(0, 2) returns +∞. | `row = 0`<br>`col = 2`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`call stack = [minFallingPathSum endCol=1, best(1,1) upLeft=-19 up=57, best(0,2)] ← top` |
| 10 | 15 | best(1, 1) returns matrix[1][1] + min(-19, 57, +∞) = -5 + (-19) = -24. | `row = 1`<br>`col = 1`<br>`upLeft = -19`<br>`up = 57`<br>`upRight = +∞`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,1])<br>`call stack = [minFallingPathSum endCol=1, best(1,1) upLeft=-19 up=57 upRight=+∞] ← top` |
| 11 | 5 | ans = min(-59, -24) = -59; the path ending at column 0 is still the cheapest. | `matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`call stack = [minFallingPathSum endCol=1] ← top` |
| 12 | 6 | Every end column has been tried, so the function returns ans = -59. | `call stack = [minFallingPathSum] ← top` |

**Result:** -59 — the path -19 → -40 (straight down from (0, 0) to (1, 0)) has sum -59, smaller than the best path ending at column 1 (-19 → -5 = -24).

**C++ solution**

```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();                 // matrix is n x n
        int ans = INT_MAX;                     // no path seen yet
        for (int endCol = 0; endCol < n; ++endCol)
            ans = min(ans, best(matrix, n - 1, endCol)); // the path may end at any cell of the last row
        return ans;
    }

private:
    const int INF = 1000000000;                // larger than any real sum (|sum| <= 100 * 100 = 10^4)

    // Minimum sum of a falling path that starts anywhere in row 0 and ends at (row, col).
    int best(vector<vector<int>>& matrix, int row, int col) {
        int n = matrix.size();
        if (col < 0 || col >= n) return INF;   // fell off the side: this move is not allowed
        if (row == 0) return matrix[0][col];   // a path may start at any cell of the first row
        int upLeft = best(matrix, row - 1, col - 1);  // came diagonally from the up-left cell
        int up = best(matrix, row - 1, col);          // came straight down
        int upRight = best(matrix, row - 1, col + 1); // came diagonally from the up-right cell
        return matrix[row][col] + min({upLeft, up, upRight}); // up is always in range, so the min is a real sum
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();                 // matrix is n x n
        int ans = INT_MAX;                     // no path seen yet
        for (int endCol = 0; endCol < n; ++endCol)
            ans = min(ans, best(matrix, n - 1, endCol)); // the path may end at any cell of the last row
        return ans;
    }

private:
    const int INF = 1000000000;                // larger than any real sum (|sum| <= 100 * 100 = 10^4)

    // Minimum sum of a falling path that starts anywhere in row 0 and ends at (row, col).
    int best(vector<vector<int>>& matrix, int row, int col) {
        int n = matrix.size();
        if (col < 0 || col >= n) return INF;   // fell off the side: this move is not allowed
        if (row == 0) return matrix[0][col];   // a path may start at any cell of the first row
        int upLeft = best(matrix, row - 1, col - 1);  // came diagonally from the up-left cell
        int up = best(matrix, row - 1, col);          // came straight down
        int upRight = best(matrix, row - 1, col + 1); // came diagonally from the up-right cell
        return matrix[row][col] + min({upLeft, up, upRight}); // up is always in range, so the min is a real sum
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
```

</details>

**Why move on:** The same `best(row, col)` is recomputed for every path that passes through it, so the work grows like `3^n`: `n = 15` already needs about `10^8` calls, while `n` can be 100.

### 2. Better: Bottom-up DP table

> **How you get here:** The recursion asks for `best(row - 1, col)` from up to three different cells below it, and that repetition multiplies with every row; there are only `n^2` different `(row, col)` states, so each can be computed once and stored.

**Idea.** Create an `n × n` table `dp` where `dp[row][col]` is the minimum sum of a falling path ending at `(row, col)`. Copy row 0 of `matrix` into `dp[0]`, then fill rows top to bottom with `dp[row][col] = matrix[row][col] + min` of `dp[row - 1][col]` and whichever of `dp[row - 1][col - 1]` and `dp[row - 1][col + 1]` exist. Because every parent lives in the previous row, it is always finished before it is needed. The answer is the minimum of the last row `dp[n - 1]`.

**Steps**

1. Create `dp` of size `n × n`.
2. Copy `matrix[0]` into `dp[0]`: a path may start at any top cell.
3. For each `row` from 1 to `n - 1` and each `col`, set `best = dp[row - 1][col]`.
4. If `col > 0`, set `best = min(best, dp[row - 1][col - 1])`; if `col < n - 1`, set `best = min(best, dp[row - 1][col + 1])`.
5. Store `dp[row][col] = matrix[row][col] + best`.
6. Return the minimum value in `dp[n - 1]`.

**Pseudocode**

```text
 1 │ function minFallingPathSum(matrix)
 2 │   n ← number of rows in matrix
 3 │   dp ← n × n table of zeros  // dp[row][col] = min sum of a falling path ending at (row, col)
 4 │   for col ← 0 to n - 1
 5 │     dp[0][col] ← matrix[0][col]  // a path may start at any cell of row 0
 6 │   for row ← 1 to n - 1
 7 │     for col ← 0 to n - 1
 8 │       best ← dp[row - 1][col]  // straight down from (row - 1, col)
 9 │       if col > 0
10 │         best ← min(best, dp[row - 1][col - 1])  // diagonal from the up-left cell
11 │       if col < n - 1
12 │         best ← min(best, dp[row - 1][col + 1])  // diagonal from the up-right cell
13 │       dp[row][col] ← matrix[row][col] + best
14 │   ans ← dp[n - 1][0]
15 │   for col ← 1 to n - 1
16 │     ans ← min(ans, dp[n - 1][col])  // the path may end at any column of the last row
17 │   return ans
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table allocation and row 0 copy (lines 3-5) | n^2 + n steps | The table is zero-filled once and row 0 is copied from matrix. |
| Filling rows 1 to n - 1 (lines 6-13) | (n - 1)·n cells × at most 3 comparisons | Each cell reads at most three parents from the previous row and writes one value. |
| Scanning the last row (lines 14-16) | n steps | The path may end at any column, so all of dp[n - 1] is compared. |

- **Adding it up:** n^2 + n + 3n(n - 1) + n ≈ 4n^2 = O(n^2); the double loop dominates.
- **At the maximum input:** n = 100 → about 4·10^4 basic steps, well under a millisecond.

**Space complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp table (line 3) | n × n integers | One best sum per cell, with every row kept. |

- **Adding it up:** n^2 = O(n^2).
- **Not counted:** matrix is the input and is not counted; best, ans, row and col are O(1).

**Dry run** on `matrix = [[-19,57],[-40,-5]] (Example 2; Example 1 has 9 cells, more than a short trace allows)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 2; dp is a 2 × 2 table of zeros, where dp[row][col] will hold the cheapest falling path ending at (row, col). | `n = 2`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`dp = 2×2 table: [0, 0] [0, 0]` |
| 2 | 5 | col = 0: a path may start here, so dp[0][0] = matrix[0][0] = -19. | `col = 0`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[0,0])<br>`dp = 2×2 table: [-19, 0] [0, 0]` ((row,col)→[0,0]) |
| 3 | 5 | col = 1: dp[0][1] = matrix[0][1] = 57. Row 0 is complete. | `col = 1`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[0,1])<br>`dp = 2×2 table: [-19, 57] [0, 0]` ((row,col)→[0,1]) |
| 4 | 8 | row = 1, col = 0: start with the straight-down parent, best = dp[0][0] = -19. | `row = 1`<br>`col = 0`<br>`best = -19`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,0])<br>`dp = 2×2 table: [-19, 57] [0, 0]` ((row,col)→[1,0]) |
| 5 | 12 | col = 0 has no up-left parent, so lines 9-10 are skipped; the up-right parent dp[0][1] = 57 leaves best = min(-19, 57) = -19. | (no change) |
| 6 | 13 | dp[1][0] = matrix[1][0] + best = -40 + (-19) = -59. | `dp = 2×2 table: [-19, 57] [-59, 0]` ((row,col)→[1,0]) |
| 7 | 8 | row = 1, col = 1: best starts at the straight-down parent dp[0][1] = 57. | `col = 1`<br>`best = 57`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,1])<br>`dp = 2×2 table: [-19, 57] [-59, 0]` ((row,col)→[1,1]) |
| 8 | 10 | The up-left parent dp[0][0] = -19 is smaller, so best = min(57, -19) = -19. The last column has no up-right parent, so lines 11-12 are skipped. | `best = -19` |
| 9 | 13 | dp[1][1] = matrix[1][1] + best = -5 + (-19) = -24. The table is full. | `dp = 2×2 table: [-19, 57] [-59, -24]` ((row,col)→[1,1]) |
| 10 | 14 | ans starts at the first cell of the last row, dp[1][0] = -59. | `ans = -59`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,0])<br>`dp = 2×2 table: [-19, 57] [-59, -24]` ((row,col)→[1,0]) |
| 11 | 16 | col = 1: ans = min(-59, dp[1][1]) = min(-59, -24) = -59. | `col = 1`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,1])<br>`dp = 2×2 table: [-19, 57] [-59, -24]` ((row,col)→[1,1]) |
| 12 | 17 | Return ans = -59. | `matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`dp = 2×2 table: [-19, 57] [-59, -24]` |

**Result:** -59 — dp[1][0] = -59 is the smallest value in the last row, from the path -19 → -40.

**C++ solution**

```cpp
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();                                   // matrix is n x n
        vector<vector<int>> dp(n, vector<int>(n, 0));            // dp[row][col] = min sum of a falling path ending at (row, col)
        for (int col = 0; col < n; ++col)
            dp[0][col] = matrix[0][col];                         // a path may start at any cell of row 0
        for (int row = 1; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                int best = dp[row - 1][col];                     // straight down from (row - 1, col)
                if (col > 0)
                    best = min(best, dp[row - 1][col - 1]);      // diagonal from the up-left cell
                if (col < n - 1)
                    best = min(best, dp[row - 1][col + 1]);      // diagonal from the up-right cell
                dp[row][col] = matrix[row][col] + best;          // extend the cheapest reachable path
            }
        }
        int ans = dp[n - 1][0];
        for (int col = 1; col < n; ++col)
            ans = min(ans, dp[n - 1][col]);                      // the path may end at any column of the last row
        return ans;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();                                   // matrix is n x n
        vector<vector<int>> dp(n, vector<int>(n, 0));            // dp[row][col] = min sum of a falling path ending at (row, col)
        for (int col = 0; col < n; ++col)
            dp[0][col] = matrix[0][col];                         // a path may start at any cell of row 0
        for (int row = 1; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                int best = dp[row - 1][col];                     // straight down from (row - 1, col)
                if (col > 0)
                    best = min(best, dp[row - 1][col - 1]);      // diagonal from the up-left cell
                if (col < n - 1)
                    best = min(best, dp[row - 1][col + 1]);      // diagonal from the up-right cell
                dp[row][col] = matrix[row][col] + best;          // extend the cheapest reachable path
            }
        }
        int ans = dp[n - 1][0];
        for (int col = 1; col < n; ++col)
            ans = min(ans, dp[n - 1][col]);                      // the path may end at any column of the last row
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
```

</details>

**Why move on:** Time is optimal, but the table keeps all `n` rows (`10^4` integers) although row `row` only ever reads row `row - 1`; everything above that is dead weight.

### 3. Optimal: Two rolling rows

> **How you get here:** In the table, `dp[row]` is read only while filling `dp[row + 1]`, so keeping just the previous row `prev` and the row being built `cur` loses nothing.

**Idea.** Start with `prev` equal to `matrix[0]`. For each later row build a new array `cur` where `cur[col] = matrix[row][col] + min(prev[col - 1], prev[col], prev[col + 1])` over the in-range neighbours, then set `prev = cur`. A separate `cur` is needed because `cur[col + 1]` still needs the old `prev[col]`, so overwriting `prev` in place would mix two rows. After the last row, `prev` holds the best sum ending at every bottom cell, and its minimum is the answer.

**Steps**

1. Copy `matrix[0]` into `prev`.
2. For each `row` from 1 to `n - 1`, create a new array `cur` of length `n`.
3. For each `col`, start `best` at `prev[col]`, then take the minimum with `prev[col - 1]` if `col > 0` and with `prev[col + 1]` if `col < n - 1`.
4. Set `cur[col] = matrix[row][col] + best`.
5. After the row is finished, set `prev = cur`.
6. Return the minimum value in `prev`.

**Pseudocode**

```text
 1 │ function minFallingPathSum(matrix)
 2 │   n ← number of rows in matrix
 3 │   prev ← copy of matrix[0]  // prev[c] = min sum of a falling path ending at (row - 1, c)
 4 │   for row ← 1 to n - 1
 5 │     cur ← array of n zeros  // separate array: prev must stay intact while this row is built
 6 │     for col ← 0 to n - 1
 7 │       best ← prev[col]  // straight down from (row - 1, col)
 8 │       if col > 0
 9 │         best ← min(best, prev[col - 1])  // diagonal from the up-left cell
10 │       if col < n - 1
11 │         best ← min(best, prev[col + 1])  // diagonal from the up-right cell
12 │       cur[col] ← matrix[row][col] + best
13 │     prev ← cur  // this row is done; only it is needed for the next row
14 │   ans ← prev[0]
15 │   for col ← 1 to n - 1
16 │     ans ← min(ans, prev[col])  // the path may end at any column of the last row
17 │   return ans
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Copying row 0 (line 3) | n steps | prev starts as the first row of matrix. |
| Building each row (lines 4-13) | (n - 1) rows × (n cells × at most 3 comparisons + O(n) to create cur and copy it into prev) | Each cell reads at most three values of prev and writes one value of cur. |
| Scanning the last row (lines 14-16) | n steps | The path may end at any column, so all of prev is compared. |

- **Adding it up:** n + (n - 1)(3n + 2n) + n ≈ 5n^2 = O(n^2); the nested loops dominate.
- **At the maximum input:** n = 100 → about 5·10^4 basic steps, effectively instant.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| prev (line 3) | n integers | Best sums for the previous row. |
| cur (line 5) | n integers | Best sums for the row being built, kept separate so prev is not corrupted. |

- **Adding it up:** n + n = 2n = O(n).
- **Not counted:** matrix is the input and is not counted. Writing results into matrix itself would make the extra space O(1) but destroys the input.

**Dry run** on `matrix = [[-19,57],[-40,-5]] (Example 2; Example 1 has 9 cells, more than a short trace allows)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 2; prev starts as a copy of row 0, [-19, 57]: a path that ends in row 0 is just that cell. | `n = 2`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`prev = [-19, 57]` |
| 2 | 5 | row = 1: create a fresh cur = [0, 0] so prev stays intact while row 1 is built. | `row = 1`<br>`cur = [0, 0]` |
| 3 | 7 | col = 0: best = prev[0] = -19, the straight-down parent. | `col = 0`<br>`best = -19`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,0])<br>`prev = [-19, 57]` (col→0)<br>`cur = [0, 0]` (col→0) |
| 4 | 11 | col = 0 has no up-left parent (line 9 is skipped); the up-right parent prev[1] = 57 leaves best = min(-19, 57) = -19. | (no change) |
| 5 | 12 | cur[0] = matrix[1][0] + best = -40 + (-19) = -59. | `cur = [-59, 0]` (col→0) |
| 6 | 7 | col = 1: best = prev[1] = 57, the straight-down parent. | `col = 1`<br>`best = 57`<br>`matrix = 2×2 table: [-19, 57] [-40, -5]` ((row,col)→[1,1])<br>`prev = [-19, 57]` (col→1)<br>`cur = [-59, 0]` (col→1) |
| 7 | 9 | The up-left parent prev[0] = -19 is cheaper, so best = min(57, -19) = -19. col = 1 is the last column, so there is no up-right parent. | `best = -19` |
| 8 | 12 | cur[1] = matrix[1][1] + best = -5 + (-19) = -24. | `cur = [-59, -24]` (col→1) |
| 9 | 13 | Row 1 is finished, so prev = cur = [-59, -24]; row 0's values are no longer needed. | `matrix = 2×2 table: [-19, 57] [-40, -5]`<br>`prev = [-59, -24]`<br>`cur = [-59, -24]` |
| 10 | 14 | ans = prev[0] = -59. | `ans = -59` |
| 11 | 16 | col = 1: ans = min(-59, prev[1]) = min(-59, -24) = -59. | `col = 1`<br>`prev = [-59, -24]` (col→1) |
| 12 | 17 | Return ans = -59. | `prev = [-59, -24]` |

**Result:** -59 — prev[0] = -59 is the smallest falling-path sum ending in the last row, from the path -19 → -40.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Every cell can change the answer, so all `n^2` values must be read and `O(n^2)` time cannot be beaten. The `O(n)` arrays could be dropped to `O(1)` by adding the minimum directly into `matrix[row][col]`, at the cost of overwriting the caller's input.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| matrix = [[1,2,3],[4,5,6],[7,8,9]] | 12 | Sorted values: the best path goes straight down the first column, 1 + 4 + 7. |
| matrix = [[5,-3,2],[1,4,-6],[-2,7,3]] | -6 | Mixed signs: the path -3 → -6 → 3 is best because the two negative cells outweigh the forced last step onto 3. |
| matrix = [[1,2,3],[50,50,1],[50,50,1]] | 4 | Greedy trap: starting at the smallest top cell 1 forces a 50, while 2 → 1 → 1 costs only 4. |
| matrix = [[3,8,1,7],[9,2,7,4],[4,6,5,1],[2,9,3,8]] | 9 | A 4 × 4 matrix where the best path 1 → 2 → 4 → 2 drifts left using diagonal moves. |
| matrix = [[-1,4,-2,0,3],[2,-5,1,6,-3],[7,0,-4,2,1],[-6,3,5,-1,2],[1,-2,4,0,-7]] | -19 | A 5 × 5 matrix with scattered negatives: the best path -2 → -5 → -4 → -1 → -7 changes column at almost every row. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single cell | matrix = [[7]] | 7 | N = 1, no moves are made and the answer is the only value. |
| Minimum value with n = 1 | matrix = [[-100]] | -100 | Checks that an initial minimum such as 0 does not cap the answer. |
| All equal at the maximum value | matrix = [[100,100],[100,100]] | 200 | Every path costs the same (a 100 × 100 grid of 100s would give 10000). |
| All values at the minimum | matrix = [[-100,-100,-100],[-100,-100,-100],[-100,-100,-100]] | -300 | The answer is -100 · n, the most negative sum possible for n = 3. |
| All zeros | matrix = [[0,0],[0,0]] | 0 | Every path sums to 0, so a sentinel of 0 must not be confused with 'no path'. |
| Anti-diagonal path | matrix = [[100,100,1],[100,1,100],[1,100,100]] | 3 | The only cheap route moves down-left twice, from the top-right corner to the bottom-left corner. |

## Mistakes and edge cases

**Common mistakes**

- Reading `prev[col - 1]` at `col = 0` or `prev[col + 1]` at `col = n - 1`: that is out of bounds in C++; border cells have only two parents, so skip the missing one or treat it as `+∞`.
- Returning the value at one fixed column such as `dp[n - 1][0]`, or starting from only the smallest top cell: the path can start at any column of row 0 and end at any column of the last row.
- Updating `prev` in place while scanning a row: once `prev[col]` is overwritten, cell `col + 1` reads the new value as its up-left parent, mixing two rows.
- Using 0 or -1 as a memo 'unset' marker or as the initial minimum: sums range from -10^4 to 10^4, so pick a sentinel outside that range such as `INT_MAX`.

**Edge cases to check**

- `n = 1`, e.g. `[[-7]]`: no moves are made, so the answer is the single value.
- `n = 2`, e.g. Example 2: each bottom cell has a parent in only two columns, so both border rules (no up-left at column 0, no up-right at column 1) are exercised.
- All values at -100: the answer is `-100 · n`, which checks that no sentinel like 0 caps the minimum.
- A cheap top cell that leads into expensive cells, e.g. `[[1,2,3],[50,50,1],[50,50,1]]` → 4: checks that the solution is not greedy.
- An anti-diagonal optimum such as `[[100,100,1],[100,1,100],[1,100,100]]` → 3: needs diagonal moves in the down-left direction at every step.

## Practice next

- [Minimum Falling Path Sum II](https://leetcode.com/problems/minimum-falling-path-sum-ii/) · Same falling-path DP, but the next cell must be in a different column, which needs the smallest and second-smallest values of the previous row.
- [Triangle](https://leetcode.com/problems/triangle/) · Top-to-bottom path DP where each cell has two parents; the same rolling-row trick gives O(n) space.
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) · Grid min-cost DP with right/down moves; the same 'cell value plus best parent' recurrence.
- [Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/) · Row-by-row grid DP where each step moves to column col - 1, col or col + 1, extended to two walkers at once.

## Takeaways

- When a path may start and end anywhere in a row, make every first-row cell a base case and take a minimum (or maximum) over the last row.
- Out-of-range moves should contribute the neutral value of the combine step (`+∞` for a minimum) or be skipped; never read past the array border.
- If row `r` depends only on row `r - 1`, keep two arrays; use a separate `cur` whenever an update would overwrite a value a neighbour still needs.
- Negative values break greedy choices and magic 'unset' markers; prove the recurrence and choose sentinels outside the value range.
