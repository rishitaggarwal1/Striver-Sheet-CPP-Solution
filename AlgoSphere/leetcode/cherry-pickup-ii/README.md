# Cherry Pickup II

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/cherry-pickup-ii/) · Pattern: **3D DP on (row, j1, j2): two walkers moving in lockstep**

> Two robots start at `(0, 0)` and `(0, cols - 1)` and each moves down one row per step, shifting at most one column; maximise the cherries collected when a cell visited by both on the same row counts once.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.

You have two robots that can collect cherries for you:

- Robot #1 is located at the top-left corner (0, 0), and

- Robot #2 is located at the top-right corner (0, cols - 1).

Return the maximum number of cherries collection using both robots by following the rules below:

- From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).

- When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.

- When both robots stay in the same cell, only one takes the cherries.

- Both robots cannot move outside of the grid at any moment.

- Both robots should reach the bottom row in grid.

Example 1:

Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.

Example 2:

Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.

Constraints:

- rows == grid.length

- cols == grid[i].length

- 2 <= rows, cols <= 70

- 0 <= grid[i][j] <= 100
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Two walkers start on the top row, one in the leftmost column and one in the rightmost. At every step both move down exactly one row, each shifting at most one column left or right, until both stand on the bottom row. Maximise the total of the cells they stand on, where a cell both stand on in the same row is counted only once.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Because every move goes from row `i` to row `i + 1`, the two robots are always on the same row. So the whole situation at any moment is just the row plus the two columns. In Example 1 the robots never share a cell, but if both stood on the 5 at `(1, 1)` only 5 would be added, not 10.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

Each robot has up to 3 moves per row, so together there are 9 joint moves per row and up to 9^69 move sequences for 70 rows, which rules out trying them all. But there are only rows × cols × cols = 70 × 70 × 70 = 343,000 possible (row, column 1, column 2) situations, and 9 transitions each is about 3·10^6 operations, easily fast.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is 3D dynamic programming on (row, column of robot 1, column of robot 2), filled row by row like a falling-path problem. It fits because the best future total from a situation depends only on that situation, not on how the robots got there.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Move the two robots together, one row at a time, instead of planning their paths separately. Then 'a shared cell counts once' becomes a local check on the current row (`j1 == j2`), and the state stays small.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Let `dp[i][j1][j2]` be the most cherries both robots can still collect from row `i` to the bottom when robot 1 is in column `j1` and robot 2 in column `j2` of row `i`. Each row is a `cols × cols` layer, and a layer only depends on the layer below, so two layers at a time are enough.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Fill the bottom layer: `grid[rows-1][j1] + grid[rows-1][j2]`, or just `grid[rows-1][j1]` when `j1 == j2`.
For each row `i` from `rows - 2` up to `0`, build a new `cols × cols` layer.
For every pair `(j1, j2)`, look at the 9 moves `(j1 + d1, j2 + d2)` where each of `d1` and `d2` is -1, 0 or 1, skipping moves off the grid.
Take the largest lower-layer value among them.
Add this row's cherries, counting a shared cell once.
After row 0, return the entry for `(0, cols - 1)`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest parts are counting a shared cell once and never reading a column outside `0..cols-1` (skip such moves or score them as minus infinity). Check the smallest `2 × 2` grid, an all-zero grid, and wide grids where some cells are unreachable in time. Time is `O(rows · cols^2 · 9)`, about 3·10^6 steps at the limits, with `O(cols^2)` extra space using two layers.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1)" | both robots are always on the same row, so one row index plus two columns describes the whole state. |
| "When both robots stay in the same cell, only one takes the cherries" | the robots interact, so they must be planned together; the overlap is just the check `j1 == j2` on the current row. |
| "2 <= rows, cols <= 70" | 70 × 70 × 70 = 343,000 states × 9 moves ≈ 3·10^6 operations is fine, while 9^69 move sequences is not. |
| "Both robots should reach the bottom row in grid" | the bottom row is a natural base case, so fill layers bottom-up and read the answer at `(0, 0, cols - 1)`. |

### What the constraints tell you

With rows = cols = 70, enumerating joint move sequences costs up to 9^69 ≈ 7·10^65 paths, impossible. The DP has rows · cols^2 = 343,000 states with 9 transitions each, about 3·10^6 operations, which runs in milliseconds; a full 3D table of 343,000 ints is about 1.4 MB, and keeping only two layers cuts it to 2 · 4,900 ints.

### Think it through

Answer each question yourself before opening it.

**Q1. Can I find the best path for robot 1 alone, then the best path for robot 2 on what is left?**

<details>
<summary>Answer</summary>

No. In `[[1,0,0],[2,9,1]]`, robot 1's best solo path grabs the 9 (1 + 9 = 10) and leaves robot 2 only 1, for a total of 11; letting robot 1 take the 2 and robot 2 take the 9 gives 12. The two paths have to be decided together.

</details>

**Q2. What do I need to know to describe the situation at any moment?**

<details>
<summary>Answer</summary>

Both robots move down exactly one row per step, so they are always on the same row `i`. The triple `(i, j1, j2)` is all that matters for the future: the cherries already taken above row `i` cannot affect what is collectable below it.

</details>

**Q3. What would plain recursion look like?**

<details>
<summary>Answer</summary>

`f(i, j1, j2)` = this row's cherries (`grid[i][j1]`, plus `grid[i][j2]` only if `j1 ≠ j2`) plus the best of the 9 calls `f(i + 1, j1 + d1, j2 + d2)` where each of `d1` and `d2` is -1, 0 or 1, returning minus infinity when a robot leaves the grid. On the bottom row it is just this row's cherries. That makes up to 9^(rows - 1) calls.

</details>

**Q4. Is there repeated work?**

<details>
<summary>Answer</summary>

Yes. In Example 1 the state `(2, 1, 1)` is requested by all four reachable row-1 states `(1, 0, 1)`, `(1, 0, 2)`, `(1, 1, 1)` and `(1, 1, 2)`, yet there are only rows · cols^2 = 4 · 3 · 3 = 36 distinct states. Caching `f(i, j1, j2)` in a 3D table makes each state cost 9 lookups once.

</details>

**Q5. How do I turn it into a loop, and how much memory is really needed?**

<details>
<summary>Answer</summary>

Fill layers from the bottom row up: layer `i` (a `cols × cols` table over `(j1, j2)`) only reads layer `i + 1`. So keep two tables, `front` for row `i + 1` and `cur` for row `i`, and after row 0 the answer is `front[0][cols - 1]`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Recursion over all 9 joint moves](#1-brute-force-recursion-over-all-9-joint-moves) | `O(9^rows)` | `O(rows)` |
| 2 | [Better: Memoised recursion on (i, j1, j2)](#2-better-memoised-recursion-on-i-j1-j2) | `O(rows · cols^2 · 9)` | `O(rows · cols^2)` |
| 3 | [Optimal: Bottom-up DP with two cols × cols layers](#3-optimal-bottom-up-dp-with-two-cols--cols-layers) | `O(rows · cols^2 · 9)` | `O(cols^2)` |

### 1. Brute force: Recursion over all 9 joint moves

> **Where you start:** Each row the two robots each pick one of three moves, so the first idea is to try every combination of moves for both robots together and keep the best total.

**Idea.** Define `f(i, j1, j2)` as the most cherries both robots can collect from row `i` to the bottom when they stand in columns `j1` and `j2` of row `i`. If either column is outside `0..cols-1` the state is illegal and returns minus infinity, so it never wins a max. Otherwise collect `grid[i][j1]`, plus `grid[i][j2]` only when `j1 ≠ j2`; on the bottom row that is the answer, and above it add the best of the 9 calls `f(i + 1, j1 + d1, j2 + d2)`. This is correct because what can be collected below row `i` depends only on where the robots are now, and since both robots are on row `i`, the shared-cell rule is applied exactly once per row.

**Steps**

1. Call `f(0, 0, cols - 1)`.
2. In `f(i, j1, j2)`, return minus infinity if `j1` or `j2` is outside the grid.
3. Set `here = grid[i][j1]`, and add `grid[i][j2]` if `j1 ≠ j2`.
4. If `i = rows - 1`, return `here`.
5. Otherwise try all 9 pairs `(d1, d2)` with each shift -1, 0 or 1, and keep the largest `f(i + 1, j1 + d1, j2 + d2)`.
6. Return `here` plus that maximum.

**Pseudocode**

```text
 1 │ function cherryPickup(grid)
 2 │   rows ← number of rows in grid
 3 │   cols ← number of columns in grid
 4 │   return f(0, 0, cols - 1)  // robot 1 starts at (0, 0), robot 2 at (0, cols - 1)
 5 │ function f(i, j1, j2)  // most cherries collectable from row i to the bottom, robots in columns j1 and j2
 6 │   if j1 < 0 or j1 ≥ cols or j2 < 0 or j2 ≥ cols
 7 │     return -∞  // a robot left the grid: this move sequence is illegal
 8 │   here ← grid[i][j1]
 9 │   if j1 ≠ j2
10 │     here ← here + grid[i][j2]  // a shared cell is counted once
11 │   if i = rows - 1
12 │     return here  // both robots are on the bottom row
13 │   best ← -∞
14 │   for d1 ← -1 to 1  // robot 1: down-left, down, down-right
15 │     for d2 ← -1 to 1  // robot 2 moves independently: 9 joint moves
16 │       best ← max(best, f(i + 1, j1 + d1, j2 + d2))
17 │   return here + best
```

**Time complexity: `O(9^rows)`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup and first call (lines 2-4) | 1 × O(1) | Reads the grid size and starts the recursion at the two corners. |
| Recursive calls (lines 14-16) | up to 9^0 + 9^1 + … + 9^(rows-1) calls | Each in-grid call above the bottom row makes 9 calls, so depth d of the call tree holds up to 9^d calls; off-grid calls stop at once. |
| Work inside one call (lines 6-13, 17) | O(1) per call | A bounds check, at most two additions and one comparison with the bottom row. |

- **Adding it up:** (9^rows - 1)/8 calls × O(1) = O(9^rows); the call tree dominates the O(1) setup.
- **Best vs worst case:** Narrow grids prune more: with cols = 2 only 4 of the 9 joint moves stay on the grid, so the tree grows like 4^rows; wide grids approach the full 9^rows.
- **At the maximum input:** rows = 70 → up to about 7·10^65 calls, which never finishes; already at rows = 10 a wide grid needs up to about 4·10^8 calls.

**Space complexity: `O(rows)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (line 16) | rows frames × O(1) | Each nested call goes one row down, so at most rows (70) frames are active, each holding i, j1, j2, here, best, d1 and d2. |

- **Adding it up:** rows × O(1) = O(rows).
- **Not counted:** The grid is not counted and nothing is cached.

**Dry run** on `grid = [[3,1,1],[2,5,1]] (the first two rows of Example 1, so the root's 9 calls are all base cases)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | rows = 2 and cols = 3. Line 4 will call f(0, 0, 2): robot 1 in column 0, robot 2 in column 2. | `rows = 2`<br>`cols = 3`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]`<br>`call stack = []` |
| 2 | 10 | f(0, 0, 2): both columns are on the grid, here = grid[0][0] = 3, and since 0 ≠ 2 line 10 adds grid[0][2] = 1, so here = 4. | `i = 0`<br>`j1 = 0`<br>`j2 = 2`<br>`here = 4`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 3 | 13 | Row 0 is not the bottom (rows - 1 = 1), so best starts at -∞ before trying the 9 joint moves. | `best = -∞` |
| 4 | 7 | d1 = -1, d2 = -1 calls f(1, -1, 1). Robot 1 would be in column -1, off the grid, so it returns -∞ immediately. | `i = 1`<br>`j1 = -1`<br>`j2 = 1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r2→[1,1])<br>`call stack = [f(0,0,2), f(1,-1,1)] ← top` |
| 5 | 16 | Back in f(0, 0, 2): f(1, -1, 2) and f(1, -1, 3) are off the grid too, so after all three d1 = -1 moves best is still -∞. | `i = 0`<br>`j1 = 0`<br>`j2 = 2`<br>`here = 4`<br>`best = -∞`<br>`d1 = -1`<br>`d2 = 1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 6 | 12 | d1 = 0, d2 = -1 calls f(1, 0, 1): here = 2 + 5 = 7, and row 1 is the bottom, so it returns 7. | `i = 1`<br>`j2 = 1`<br>`here = 7`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[1,0], r2→[1,1])<br>`call stack = [f(0,0,2), f(1,0,1)] ← top` |
| 7 | 16 | best = max(-∞, 7) = 7. | `i = 0`<br>`j2 = 2`<br>`here = 4`<br>`best = 7`<br>`d1 = 0`<br>`d2 = -1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 8 | 12 | d1 = 0, d2 = 0 calls f(1, 0, 2): here = 2 + 1 = 3 on the bottom row, so it returns 3. | `i = 1`<br>`here = 3`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[1,0], r2→[1,2])<br>`call stack = [f(0,0,2), f(1,0,2)] ← top` |
| 9 | 16 | best = max(7, 3) = 7; then d2 = 1 calls f(1, 0, 3), where robot 2 is off the right edge (3 ≥ cols), so best stays 7. | `i = 0`<br>`here = 4`<br>`best = 7`<br>`d1 = 0`<br>`d2 = 1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 10 | 12 | d1 = 1, d2 = -1 calls f(1, 1, 1): both robots are on the 5. Line 9 is false (j1 = j2), so here = 5, counted once, and it returns 5. | `i = 1`<br>`j1 = 1`<br>`j2 = 1`<br>`here = 5`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[1,1], r2→[1,1])<br>`call stack = [f(0,0,2), f(1,1,1)] ← top` |
| 11 | 16 | best = max(7, 5) = 7. | `i = 0`<br>`j1 = 0`<br>`j2 = 2`<br>`here = 4`<br>`best = 7`<br>`d1 = 1`<br>`d2 = -1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 12 | 12 | d1 = 1, d2 = 0 calls f(1, 1, 2): here = 5 + 1 = 6, returned from the bottom row. | `i = 1`<br>`j1 = 1`<br>`here = 6`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[1,1], r2→[1,2])<br>`call stack = [f(0,0,2), f(1,1,2)] ← top` |
| 13 | 16 | best = max(7, 6) = 7; the last move f(1, 1, 3) is off the grid, so best stays 7 after all 9 joint moves. | `i = 0`<br>`j1 = 0`<br>`here = 4`<br>`best = 7`<br>`d1 = 1`<br>`d2 = 1`<br>`grid = 2×3 table: [3, 1, 1] [2, 5, 1]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 14 | 17 | f(0, 0, 2) returns here + best = 4 + 7 = 11. | (no change) |
| 15 | 4 | cherryPickup returns 11. The root made 9 calls: 5 left the grid and 4 were scored on the bottom row. | `grid = 2×3 table: [3, 1, 1] [2, 5, 1]`<br>`call stack = []` |

**Result:** 11: robot 1 goes 3 → 2 and robot 2 goes 1 → 5; every one of the 9 joint moves was tried, and the best one, (1, 0, 1), gives 7 on top of the 4 from row 0.

**C++ solution**

```cpp
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();                          // number of rows
        int cols = grid[0].size();                       // number of columns
        return solve(0, 0, cols - 1, rows, cols, grid);  // robot 1 at (0, 0), robot 2 at (0, cols - 1)
    }

private:
    static constexpr int NEG = -100000000;               // stands in for -infinity; far below any real total (at most 14000)

    // Most cherries collectable from row i to the bottom with the robots in columns j1 and j2
    int solve(int i, int j1, int j2, int rows, int cols, vector<vector<int>>& grid) {
        if (j1 < 0 || j1 >= cols || j2 < 0 || j2 >= cols) return NEG;  // a robot left the grid: illegal
        int here = grid[i][j1];                          // robot 1's cell
        if (j1 != j2) here += grid[i][j2];               // robot 2's cell, unless they share it
        if (i == rows - 1) return here;                  // both robots are on the bottom row
        int best = NEG;
        for (int d1 = -1; d1 <= 1; d1++)                 // robot 1: down-left, down, down-right
            for (int d2 = -1; d2 <= 1; d2++)             // robot 2 independently: 9 joint moves
                best = max(best, solve(i + 1, j1 + d1, j2 + d2, rows, cols, grid));
        return here + best;                              // this row plus the best continuation
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
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();                          // number of rows
        int cols = grid[0].size();                       // number of columns
        return solve(0, 0, cols - 1, rows, cols, grid);  // robot 1 at (0, 0), robot 2 at (0, cols - 1)
    }

private:
    static constexpr int NEG = -100000000;               // stands in for -infinity; far below any real total (at most 14000)

    // Most cherries collectable from row i to the bottom with the robots in columns j1 and j2
    int solve(int i, int j1, int j2, int rows, int cols, vector<vector<int>>& grid) {
        if (j1 < 0 || j1 >= cols || j2 < 0 || j2 >= cols) return NEG;  // a robot left the grid: illegal
        int here = grid[i][j1];                          // robot 1's cell
        if (j1 != j2) here += grid[i][j2];               // robot 2's cell, unless they share it
        if (i == rows - 1) return here;                  // both robots are on the bottom row
        int best = NEG;
        for (int d1 = -1; d1 <= 1; d1++)                 // robot 1: down-left, down, down-right
            for (int d2 = -1; d2 <= 1; d2++)             // robot 2 independently: 9 joint moves
                best = max(best, solve(i + 1, j1 + d1, j2 + d2, rows, cols, grid));
        return here + best;                              // this row plus the best continuation
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
```

</details>

**Why move on:** The same `(i, j1, j2)` states are recomputed along many move sequences; with rows = 70 that is up to 9^69 calls, so it only works for a handful of rows.

### 2. Better: Memoised recursion on (i, j1, j2)

> **How you get here:** The brute force only ever asks about rows · cols^2 distinct `(i, j1, j2)` states (36 in Example 1) but asks for many of them again and again; caching each answer the first time removes every repeated subtree.

**Idea.** Keep a 3D table `memo[i][j1][j2]` initialised to -1, which is a safe 'not solved' marker because every real answer is at least 0. `f` first rejects off-grid columns, then returns `memo[i][j1][j2]` if it is already set. Otherwise it computes the same recurrence as the brute force (this row's cherries, plus the best of the 9 moves unless `i` is the bottom row) and stores it before returning. Each state is computed once, and every later request for it is an O(1) lookup.

**Steps**

1. Create `memo` of size `rows × cols × cols` filled with -1.
2. Call `f(0, 0, cols - 1)`.
3. In `f`, return minus infinity for off-grid columns, and the stored value if `memo[i][j1][j2] ≠ -1`.
4. Compute this row's cherries, counting a shared cell once.
5. If `i` is not the bottom row, add the best of the 9 moves `f(i + 1, j1 + d1, j2 + d2)`.
6. Store the total in `memo[i][j1][j2]` and return it.

**Pseudocode**

```text
 1 │ function cherryPickup(grid)
 2 │   rows ← number of rows in grid
 3 │   cols ← number of columns in grid
 4 │   memo ← rows × cols × cols table filled with -1  // -1 = not solved yet; real answers are ≥ 0
 5 │   return f(0, 0, cols - 1)
 6 │ function f(i, j1, j2)  // most cherries from row i down, robots in columns j1 and j2
 7 │   if j1 < 0 or j1 ≥ cols or j2 < 0 or j2 ≥ cols
 8 │     return -∞  // off the grid: illegal
 9 │   if memo[i][j1][j2] ≠ -1
10 │     return memo[i][j1][j2]  // this (row, j1, j2) state is already solved
11 │   here ← grid[i][j1]
12 │   if j1 ≠ j2
13 │     here ← here + grid[i][j2]  // a shared cell counts once
14 │   best ← 0  // bottom row: nothing below to add
15 │   if i < rows - 1
16 │     best ← -∞
17 │     for d1 ← -1 to 1
18 │       for d2 ← -1 to 1
19 │         best ← max(best, f(i + 1, j1 + d1, j2 + d2))
20 │   memo[i][j1][j2] ← here + best
21 │   return memo[i][j1][j2]
```

**Time complexity: `O(rows · cols^2 · 9)`**

| Part | Cost | Why |
| --- | --- | --- |
| Allocate memo (line 4) | rows · cols^2 slots × O(1) | Every (i, j1, j2) slot starts at -1. |
| First evaluation of each state (lines 11-20) | rows · cols^2 states × up to 9 calls | A state is expanded only the first time it is requested; above the bottom row it makes 9 calls. |
| Calls that end immediately (lines 7-10) | at most 9 · rows · cols^2 calls × O(1) | Off-grid calls and memo hits are each made by some expansion, and an expansion makes at most 9 calls. |

- **Adding it up:** rows·cols^2 + 9·rows·cols^2 + 9·rows·cols^2 = O(rows · cols^2 · 9); for 70 × 70 that is 343,000 + 2 · 3,087,000 ≈ 6.5·10^6 simple steps.
- **Best vs worst case:** Only states reachable from (0, 0, cols - 1) are expanded: on row i robot 1 is in a column ≤ i and robot 2 in a column ≥ cols - 1 - i, so the first rows touch far fewer than cols^2 states.
- **At the maximum input:** rows = cols = 70 → a few million steps, around 10 ms in C++.

**Space complexity: `O(rows · cols^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| memo table (line 4) | rows · cols^2 integers | 343,000 ints, about 1.4 MB, for a 70 × 70 grid. |
| Recursion stack (line 19) | rows frames × O(1) | Each nested call goes one row lower, so at most 70 frames are active. |

- **Adding it up:** O(rows · cols^2) + O(rows) = O(rows · cols^2); the table dominates.
- **Not counted:** The grid is not counted. A recursion depth of 70 is safe.

**Dry run** on `` grid = [[3,1,1],[2,5,1],[1,5,5]] (the first three rows of Example 1). The memo is 3D, so each step shows one j1 × j2 layer; the var `layer` says which row it is. ``

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | rows = 3, cols = 3, and every memo slot is -1 (not solved). Shown: the row-0 layer. | `rows = 3`<br>`cols = 3`<br>`layer = row 0`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]`<br>`memo layer (j1 × j2) = 3×3 table: [-1, -1, -1] [-1, -1, -1] [-1, -1, -1]`<br>`call stack = []` |
| 2 | 13 | f(0, 0, 2): on the grid and memo[0][0][2] = -1, so compute it; here = 3 + 1 = 4. | `i = 0`<br>`j1 = 0`<br>`j2 = 2`<br>`here = 4`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 3 | 19 | Row 0 is not the bottom, so best = -∞; the three d1 = -1 calls f(1, -1, ·) leave the grid and return -∞, so best is still -∞. | `best = -∞`<br>`d1 = -1`<br>`d2 = 1` |
| 4 | 13 | d1 = 0, d2 = -1 calls f(1, 0, 1): memo[1][0][1] = -1, so compute; here = 2 + 5 = 7. Shown: the row-1 layer. | `layer = row 1`<br>`i = 1`<br>`j2 = 1`<br>`here = 7`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,1])<br>`call stack = [f(0,0,2), f(1,0,1)] ← top` |
| 5 | 20 | f(1, 0, 1)'s d1 = -1 calls leave the grid; its d1 = 0, d2 = -1 call is f(2, 0, 0). Both robots share the 1, so here = 1, best stays 0 on the bottom row, and memo[2][0][0] = 1. Shown: the row-2 layer. | `layer = row 2`<br>`i = 2`<br>`j2 = 0`<br>`here = 1`<br>`best = 0`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[2,0], r2→[2,0])<br>`memo layer (j1 × j2) = 3×3 table: [1, -1, -1] [-1, -1, -1] [-1, -1, -1]`<br>`call stack = [f(0,0,2), f(1,0,1), f(2,0,0)] ← top` |
| 6 | 19 | f(1, 0, 1)'s remaining legal calls fill memo[2][0][1] = 6, memo[2][0][2] = 6, memo[2][1][0] = 6, memo[2][1][1] = 5 and memo[2][1][2] = 10 (robot 2 in column 1 can reach columns 0-2; only robot 1's column -1 is off the grid). The largest is 10, so best = 10. | `i = 1`<br>`j2 = 1`<br>`here = 7`<br>`best = 10`<br>`d1 = 1`<br>`d2 = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,1])<br>`memo layer (j1 × j2) = 3×3 table: [1, 6, 6] [6, 5, 10] [-1, -1, -1]`<br>`call stack = [f(0,0,2), f(1,0,1)] ← top` |
| 7 | 20 | memo[1][0][1] = 7 + 10 = 17. Shown: the row-1 layer. | `layer = row 1`<br>`memo layer (j1 × j2) = 3×3 table: [-1, 17, -1] [-1, -1, -1] [-1, -1, -1]` |
| 8 | 19 | Back in f(0, 0, 2): best = max(-∞, 17) = 17. | `i = 0`<br>`j2 = 2`<br>`here = 4`<br>`best = 17`<br>`d1 = 0`<br>`d2 = -1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 9 | 10 | d1 = 0, d2 = 0 calls f(1, 0, 2) (here = 2 + 1 = 3). After its off-grid d1 = -1 calls, it calls f(2, 0, 1): memo[2][0][1] = 6 is set, so it returns 6 at once. Memo hit: brute force would have recomputed it. | `layer = row 2`<br>`i = 2`<br>`j2 = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[2,0], r2→[2,1])<br>`memo layer (j1 × j2) = 3×3 table: [1, 6, 6] [6, 5, 10] [-1, -1, -1]`<br>`call stack = [f(0,0,2), f(1,0,2), f(2,0,1)] ← top` |
| 10 | 20 | f(1, 0, 2)'s other legal calls f(2, 0, 2) = 6, f(2, 1, 1) = 5 and f(2, 1, 2) = 10 are memo hits too, so best = 10 and memo[1][0][2] = 3 + 10 = 13. | `layer = row 1`<br>`i = 1`<br>`j2 = 2`<br>`here = 3`<br>`best = 10`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,2])<br>`memo layer (j1 × j2) = 3×3 table: [-1, 17, 13] [-1, -1, -1] [-1, -1, -1]`<br>`call stack = [f(0,0,2), f(1,0,2)] ← top` |
| 11 | 19 | Back in f(0, 0, 2): best = max(17, 13) = 17; then d2 = 1 calls f(1, 0, 3), off the grid, so best stays 17. | `i = 0`<br>`here = 4`<br>`best = 17`<br>`d1 = 0`<br>`d2 = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`call stack = [f(0,0,2)] ← top` |
| 12 | 19 | d1 = 1, d2 = -1 calls f(1, 1, 1): both robots on the 5, so here = 5. Of its 9 calls, six are memo hits and three are new: memo[2][2][0] = 6, memo[2][2][1] = 10, memo[2][2][2] = 5. best = 10. Shown: the now complete row-2 layer. | `layer = row 2`<br>`i = 1`<br>`j1 = 1`<br>`j2 = 1`<br>`here = 5`<br>`best = 10`<br>`d1 = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,1], r2→[1,1])<br>`memo layer (j1 × j2) = 3×3 table: [1, 6, 6] [6, 5, 10] [6, 10, 5]`<br>`call stack = [f(0,0,2), f(1,1,1)] ← top` |
| 13 | 20 | memo[1][1][1] = 5 + 10 = 15. | `layer = row 1`<br>`memo layer (j1 × j2) = 3×3 table: [-1, 17, 13] [-1, 15, -1] [-1, -1, -1]` |
| 14 | 20 | d1 = 1, d2 = 0 calls f(1, 1, 2): here = 5 + 1 = 6, all six legal calls are memo hits, best = 10, so memo[1][1][2] = 16. | `j2 = 2`<br>`here = 6`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,1], r2→[1,2])<br>`memo layer (j1 × j2) = 3×3 table: [-1, 17, 13] [-1, 15, 16] [-1, -1, -1]`<br>`call stack = [f(0,0,2), f(1,1,2)] ← top` |
| 15 | 20 | Back in f(0, 0, 2): the last call f(1, 1, 3) is off the grid, so best = max(17, 13, 15, 16) = 17 and memo[0][0][2] = 4 + 17 = 21. Shown: the row-0 layer. | `layer = row 0`<br>`i = 0`<br>`j1 = 0`<br>`here = 4`<br>`best = 17`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`memo layer (j1 × j2) = 3×3 table: [-1, -1, 21] [-1, -1, -1] [-1, -1, -1]`<br>`call stack = [f(0,0,2)] ← top` |
| 16 | 5 | cherryPickup returns 21. Only 14 states were ever computed (1 on row 0, 4 on row 1, 9 on row 2); every repeat was a memo hit. | `grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]`<br>`call stack = []` |

**Result:** 21: robot 1 takes 3 → 2 → 5 (columns 0, 0, 1) and robot 2 takes 1 → 5 → 5 (columns 2, 1, 2), the best of the 4 legal row-1 states, f(1, 0, 1) = 17, plus 4 from row 0.

**C++ solution**

```cpp
class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();                          // number of rows
        int cols = grid[0].size();                       // number of columns
        // memo[i][j1][j2] = -1 means "not solved yet"; every real answer is >= 0
        vector<vector<vector<int>>> memo(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return solve(0, 0, cols - 1, grid, memo);        // robots start at (0, 0) and (0, cols - 1)
    }

private:
    static constexpr int NEG = -100000000;               // stands in for -infinity; far below any real total

    // Most cherries collectable from row i to the bottom with the robots in columns j1 and j2
    int solve(int i, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>& memo) {
        int rows = grid.size(), cols = grid[0].size();
        if (j1 < 0 || j1 >= cols || j2 < 0 || j2 >= cols) return NEG;  // off the grid: illegal
        if (memo[i][j1][j2] != -1) return memo[i][j1][j2];             // state already solved: reuse it
        int here = grid[i][j1];                          // robot 1's cell
        if (j1 != j2) here += grid[i][j2];               // robot 2's cell, unless they share it
        int best = 0;                                    // bottom row: nothing below to add
        if (i < rows - 1) {
            best = NEG;
            for (int d1 = -1; d1 <= 1; d1++)             // all 9 joint moves to row i + 1
                for (int d2 = -1; d2 <= 1; d2++)
                    best = max(best, solve(i + 1, j1 + d1, j2 + d2, grid, memo));
        }
        memo[i][j1][j2] = here + best;                   // store before returning so later callers reuse it
        return memo[i][j1][j2];
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
    int cherryPickup(vector<vector<int>>& grid) {
        int rows = grid.size();                          // number of rows
        int cols = grid[0].size();                       // number of columns
        // memo[i][j1][j2] = -1 means "not solved yet"; every real answer is >= 0
        vector<vector<vector<int>>> memo(rows, vector<vector<int>>(cols, vector<int>(cols, -1)));
        return solve(0, 0, cols - 1, grid, memo);        // robots start at (0, 0) and (0, cols - 1)
    }

private:
    static constexpr int NEG = -100000000;               // stands in for -infinity; far below any real total

    // Most cherries collectable from row i to the bottom with the robots in columns j1 and j2
    int solve(int i, int j1, int j2, vector<vector<int>>& grid, vector<vector<vector<int>>>& memo) {
        int rows = grid.size(), cols = grid[0].size();
        if (j1 < 0 || j1 >= cols || j2 < 0 || j2 >= cols) return NEG;  // off the grid: illegal
        if (memo[i][j1][j2] != -1) return memo[i][j1][j2];             // state already solved: reuse it
        int here = grid[i][j1];                          // robot 1's cell
        if (j1 != j2) here += grid[i][j2];               // robot 2's cell, unless they share it
        int best = 0;                                    // bottom row: nothing below to add
        if (i < rows - 1) {
            best = NEG;
            for (int d1 = -1; d1 <= 1; d1++)             // all 9 joint moves to row i + 1
                for (int d2 = -1; d2 <= 1; d2++)
                    best = max(best, solve(i + 1, j1 + d1, j2 + d2, grid, memo));
        }
        memo[i][j1][j2] = here + best;                   // store before returning so later callers reuse it
        return memo[i][j1][j2];
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
```

</details>

**Why move on:** Time already meets the target, but it keeps all 70 layers of the 3D table (about 1.4 MB) even though a layer is only ever read by the layer above it, and it pays for recursion overhead and a 70-deep call stack.

### 3. Optimal: Bottom-up DP with two cols × cols layers

> **How you get here:** In the memo version, row `i` only reads row `i + 1`. Filling rows from the bottom up finishes each layer before the layer above needs it, so only two `cols × cols` tables are ever needed instead of all `rows` layers.

**Idea.** Let `front[j1][j2]` hold the best total from row `i + 1` to the bottom with the robots at `j1` and `j2`. Start with the bottom row, where `front[j1][j2]` is just that row's cherries. For each row `i` going up, compute every `cur[j1][j2]` as row `i`'s cherries plus the largest `front[n1][n2]` over the 9 moves that stay on the grid, then make `cur` the new `front`. Some pairs (for example both robots in column 0 on row 0) can never actually occur, but computing them is harmless: the answer reads only `front[0][cols - 1]`, and its chain of best moves passes only through states reachable from the start.

**Steps**

1. Fill `front` for the bottom row: `grid[rows-1][j1] + grid[rows-1][j2]`, or just `grid[rows-1][j1]` when `j1 == j2`.
2. For each row `i` from `rows - 2` up to `0`, create a fresh `cur` table.
3. For every pair `(j1, j2)`, look at the 9 neighbours `(j1 + d1, j2 + d2)` in `front` that are inside the grid and take the largest.
4. Set `cur[j1][j2]` to that maximum plus row `i`'s cherries at `j1` and `j2`, counting a shared cell once.
5. Replace `front` with `cur`.
6. Return `front[0][cols - 1]`, the robots' starting columns.

**Pseudocode**

```text
 1 │ function cherryPickup(grid)
 2 │   rows ← number of rows in grid
 3 │   cols ← number of columns in grid
 4 │   front ← cols × cols table of 0  // front[j1][j2] = best total from row i + 1 to the bottom, robots at j1, j2
 5 │   for j1 ← 0 to cols - 1  // base layer: the bottom row
 6 │     for j2 ← 0 to cols - 1
 7 │       front[j1][j2] ← cherries(rows - 1, j1, j2)
 8 │   for i ← rows - 2 down to 0  // build each layer from the one below it
 9 │     cur ← cols × cols table of 0
10 │     for j1 ← 0 to cols - 1
11 │       for j2 ← 0 to cols - 1
12 │         best ← -∞
13 │         for d1 ← -1 to 1
14 │           for d2 ← -1 to 1
15 │             n1 ← j1 + d1
16 │             n2 ← j2 + d2
17 │             if 0 ≤ n1 < cols and 0 ≤ n2 < cols  // skip moves that leave the grid
18 │               best ← max(best, front[n1][n2])
19 │         cur[j1][j2] ← cherries(i, j1, j2) + best
20 │     front ← cur  // row i becomes the layer below for row i - 1
21 │   return front[0][cols - 1]  // robots start at (0, 0) and (0, cols - 1)
22 │ function cherries(i, j1, j2)  // cherries picked on row i
23 │   if j1 = j2
24 │     return grid[i][j1]  // shared cell counted once
25 │   return grid[i][j1] + grid[i][j2]
```

**Time complexity: `O(rows · cols^2 · 9)`**

| Part | Cost | Why |
| --- | --- | --- |
| Base layer (lines 4-7) | cols^2 × O(1) | One cherries() call per (j1, j2) pair on the bottom row. |
| Layer loops (lines 8-19) | (rows - 1) · cols^2 pairs × 9 moves | Every (j1, j2) of every non-bottom row checks its 9 neighbouring pairs in front. |
| New cur table and swap (lines 9, 20) | (rows - 1) × O(cols^2) | A fresh cols × cols table per row; the swap itself is O(1) or O(cols^2) depending on the language. |

- **Adding it up:** cols^2 + 9·(rows - 1)·cols^2 + (rows - 1)·cols^2 = O(rows · cols^2 · 9); for 70 × 70: 4,900 + 3,042,900 + 338,100 ≈ 3.4·10^6 steps.
- **At the maximum input:** rows = cols = 70 → about 3.4·10^6 simple steps, a few milliseconds.

**Space complexity: `O(cols^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| front layer (line 4) | cols^2 integers | The finished layer for the row below. |
| cur layer (line 9) | cols^2 integers | The layer being built for row i. |

- **Adding it up:** 2 · cols^2 = O(cols^2), 9,800 ints for cols = 70.
- **Not counted:** The grid is not counted. There is no recursion.

**Dry run** on `` grid = [[3,1,1],[2,5,1],[1,5,5]] (the first three rows of Example 1). Each layer is a j1 × j2 table; `front row` and `cur row` in vars say which grid row each layer belongs to. ``

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | rows = 3 and cols = 3. | `rows = 3`<br>`cols = 3`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` |
| 2 | 7 | Lines 5-7 fill the bottom layer from row 2 = [1, 5, 5] (shown at the last pair, j1 = 2, j2 = 2): off the diagonal front[j1][j2] = grid[2][j1] + grid[2][j2], e.g. front[1][2] = 5 + 5 = 10, and on it just one cell, e.g. front[1][1] = 5. | `j1 = 2`<br>`j2 = 2`<br>`front row = 2`<br>`front = 3×3 table: [1, 6, 6] [6, 5, 10] [6, 10, 5]` |
| 3 | 9 | i = 1: start an empty cur layer for row 1; front still holds row 2. | `i = 1`<br>`cur row = 1`<br>`cur = 3×3 table: [0, 0, 0] [0, 0, 0] [0, 0, 0]` |
| 4 | 19 | (j1, j2) = (0, 0): the legal moves reach front[0][0] = 1, front[0][1] = 6, front[1][0] = 6, front[1][1] = 5 (column -1 is skipped), so best = 6 and cur[0][0] = cherries(1, 0, 0) + 6 = 2 + 6 = 8. | `j1 = 0`<br>`j2 = 0`<br>`best = 6`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,0])<br>`cur = 3×3 table: [8, 0, 0] [0, 0, 0] [0, 0, 0]` (j1,j2→[0,0]) |
| 5 | 19 | (0, 1): moves reach front rows 0-1, columns 0-2, whose largest value is front[1][2] = 10, so cur[0][1] = (2 + 5) + 10 = 17. | `j2 = 1`<br>`best = 10`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,1])<br>`cur = 3×3 table: [8, 17, 0] [0, 0, 0] [0, 0, 0]` (j1,j2→[0,1]) |
| 6 | 19 | (0, 2): moves reach front[0][1] = 6, front[0][2] = 6, front[1][1] = 5, front[1][2] = 10, so cur[0][2] = (2 + 1) + 10 = 13. | `j2 = 2`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,0], r2→[1,2])<br>`cur = 3×3 table: [8, 17, 13] [0, 0, 0] [0, 0, 0]` (j1,j2→[0,2]) |
| 7 | 19 | j1 = 1 (shown after j2 = 2): each pair can reach a 10 in front, so cur[1][0] = 7 + 10 = 17, cur[1][1] = 5 + 10 = 15 (shared cell counted once) and cur[1][2] = 6 + 10 = 16. | `j1 = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,1], r2→[1,2])<br>`cur = 3×3 table: [8, 17, 13] [17, 15, 16] [0, 0, 0]` (j1,j2→[1,2]) |
| 8 | 19 | j1 = 2 (shown after j2 = 2): cur[2][0] = 3 + 10 = 13, cur[2][1] = 6 + 10 = 16 and cur[2][2] = 1 + 10 = 11. Row 1's layer is complete. | `j1 = 2`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[1,2], r2→[1,2])<br>`cur = 3×3 table: [8, 17, 13] [17, 15, 16] [13, 16, 11]` (j1,j2→[2,2]) |
| 9 | 20 | front ← cur: front now holds row 1, the layer below for row 0. | `front row = 1`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]`<br>`front = 3×3 table: [8, 17, 13] [17, 15, 16] [13, 16, 11]`<br>`cur = 3×3 table: [8, 17, 13] [17, 15, 16] [13, 16, 11]` |
| 10 | 9 | i = 0: start an empty cur layer for row 0. | `i = 0`<br>`cur row = 0`<br>`cur = 3×3 table: [0, 0, 0] [0, 0, 0] [0, 0, 0]` |
| 11 | 19 | (0, 0): best of front[0][0] = 8, front[0][1] = 17, front[1][0] = 17, front[1][1] = 15 is 17, so cur[0][0] = 3 + 17 = 20. Both robots in column 0 on row 0 can never happen, but computing it is harmless. | `j1 = 0`<br>`j2 = 0`<br>`best = 17`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,0])<br>`cur = 3×3 table: [20, 0, 0] [0, 0, 0] [0, 0, 0]` (j1,j2→[0,0]) |
| 12 | 19 | (0, 1) gave cur[0][1] = 4 + 17 = 21. Now the real start (0, 2): cherries = 3 + 1 = 4, and the moves reach front[0][1] = 17, front[0][2] = 13, front[1][1] = 15, front[1][2] = 16, so cur[0][2] = 4 + 17 = 21. | `j2 = 2`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`cur = 3×3 table: [20, 21, 21] [0, 0, 0] [0, 0, 0]` (j1,j2→[0,2]) |
| 13 | 19 | The rest of row 0 (j1 = 1 and 2, shown after the last pair (2, 2)) is filled the same way: [21, 18, 19] and [21, 19, 17]. For (2, 2) the moves reach 15, 16, 16, 11, so best = 16 and cur[2][2] = 1 + 16 = 17. | `j1 = 2`<br>`best = 16`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,2], r2→[0,2])<br>`cur = 3×3 table: [20, 21, 21] [21, 18, 19] [21, 19, 17]` (j1,j2→[2,2]) |
| 14 | 20 | front ← cur: front now holds row 0. | `front row = 0`<br>`grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]`<br>`front = 3×3 table: [20, 21, 21] [21, 18, 19] [21, 19, 17]`<br>`cur = 3×3 table: [20, 21, 21] [21, 18, 19] [21, 19, 17]` |
| 15 | 21 | Return front[0][2] = 21: robot 1 starts in column 0 and robot 2 in column 2. | `grid = 3×3 table: [3, 1, 1] [2, 5, 1] [1, 5, 5]` (r1→[0,0], r2→[0,2])<br>`front = 3×3 table: [20, 21, 21] [21, 18, 19] [21, 19, 17]` (start→[0,2]) |

**Result:** 21: front[0][2] is the best total for robots starting in columns 0 and 2, reached by 3 → 2 → 5 for robot 1 and 1 → 5 → 5 for robot 2, the same value the memoised version stored in memo[0][0][2].

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Each of the rows · cols^2 states can matter and has 9 possible successors, so constant work per state is as good as this DP gets. Using symmetry (`f(i, j1, j2) = f(i, j2, j1)`, so `j1 ≤ j2` is enough) roughly halves the work, but the complexity class stays the same.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| grid = [[5,0,0,5],[0,9,9,0],[0,1,1,0]] | 30 | Both robots step inward to the two 9s and then the two 1s without ever sharing a cell. |
| grid = [[1,2,1],[0,10,0],[0,0,0]] | 12 | Both robots can reach the single 10 in row 1, but it is counted once: 1 + 1 + 10. |
| grid = [[0,0,0,0,9],[0,0,0,9,0],[0,0,9,0,0]] | 27 | All cherries lie on robot 2's diagonal 4 → 3 → 2; robot 1 adds nothing. |
| grid = [[2,7,3,0,4],[1,3,8,2,6],[9,0,4,5,1],[3,6,1,7,2]] | 42 | Unique optimum: robot 1 zig-zags through columns 0, 1, 0, 1 (2 + 3 + 9 + 6) and robot 2 takes 4, 4, 3, 3 (4 + 6 + 5 + 7). |
| grid = [[4,0,4],[0,6,0],[3,0,3],[0,8,0],[5,5,5]] | 38 | The 6 and 8 in the middle column can be taken only once each; one robot dips into the middle while the other keeps its edge. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum size 2 x 2 | grid = [[3,4],[7,1]] | 15 | The robots can always cover both columns, so every cell is collected. |
| All zeros | grid = [[0,0,0],[0,0,0]] | 0 | The answer is 0, so the minus-infinity sentinel must never leak into the result. |
| Shared cell | grid = [[0,0],[0,100],[0,0]] | 100 | Both robots can stand on the 100, but it counts once, so 100 and not 200. |
| All maximum values | grid = [[100,100,100],[100,100,100],[100,100,100]] | 600 | The robots should never share a cell; a 70 x 70 grid of 100s gives the largest possible answer, 14,000. |
| Two columns | grid = [[1,2],[3,4],[5,6],[7,8]] | 36 | Each robot keeps its own column and every cell is collected. |
| Unreachable cell | grid = [[1,0,0,0,0,0,1],[0,0,0,50,0,0,0]] | 2 | With one move, neither robot can reach the 50 in the middle column. |

## Mistakes and edge cases

**Common mistakes**

- Adding `grid[i][j1] + grid[i][j2]` even when `j1 == j2`: on `[[0,0],[0,100],[0,0]]` that reports 200 instead of 100.
- Planning the robots one after the other (robot 1's best path, then robot 2 on the leftover grid): on `[[1,0,0],[2,9,1]]` this gives 11, while the true answer is 12.
- Reading `front[j1 + d1][j2 + d2]` without checking that both columns are in `0..cols-1`: column -1 or `cols` is out of range (undefined behaviour in C++) and is not a legal move.
- Returning the maximum over the whole top layer instead of `front[0][cols - 1]`: the robots must start at `(0, 0)` and `(0, cols - 1)`, so other top-row pairs are not allowed starting positions.

**Edge cases to check**

- Robots reaching the same cell, as in `[[0,0],[0,100],[0,0]]`: the 100 must be counted once, giving 100.
- Smallest grid `2 × 2` (`[[3,4],[7,1]]`): most of the 9 joint moves fall off the grid, so the bounds checks run on every state; the answer is 15.
- Wide grid with a middle target neither robot can reach in time, such as `[[1,0,0,0,0,0,1],[0,0,0,50,0,0,0]]`: the answer is 2, which catches code that lets a robot move more than one column.
- All-zero grid: the answer is 0, so the minus-infinity sentinel must never leak into the result.
- Largest input, `70 × 70` full of 100s: the answer is 70 · 200 = 14,000, which fits easily in `int`, and the DP does about 3·10^6 steps.

## Practice next

- [Cherry Pickup](https://leetcode.com/problems/cherry-pickup/) · The harder round-trip version with obstacles, solved with the same trick of moving two walkers in lockstep and keying the DP on both positions.
- [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/) · The single-walker version: the same three moves per row, with a 1D layer per row instead of a 2D one.
- [Triangle](https://leetcode.com/problems/triangle/) · Row-by-row bottom-up DP where each row depends only on the row below, using the same keep-one-layer space trick.
- [Minimum Falling Path Sum II](https://leetcode.com/problems/minimum-falling-path-sum-ii/) · Another row-layer DP whose transition scans many cells of the previous row, where the cost of the transition decides the complexity.

## Takeaways

- When two agents move one step at a time in sync, put both positions in the state (`(i, j1, j2)`) instead of solving them separately; interaction rules like 'a shared cell counts once' become local checks.
- In a max-DP, score illegal states as minus infinity so they never win, and use a separate marker (here -1) for 'not computed' when real answers are non-negative.
- If layer `i` only reads layer `i + 1`, keep two layers; for a 3D DP that drops memory from `rows · cols^2` to `cols^2`.
- Estimate the cost as states × transitions (here 343,000 × 9) to confirm the target complexity before coding.
