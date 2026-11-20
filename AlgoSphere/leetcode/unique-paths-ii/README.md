# Unique Paths II

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/unique-paths-ii/) · Pattern: **2D grid DP (counting paths)**

> Count the right/down routes from the top-left to the bottom-right cell of `obstacleGrid` that never step on a cell containing `1`.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The testcases are generated so that the answer will be less than or equal to 2 * 10^9.

Example 1:

Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:

Input: obstacleGrid = [[0,1],[0,0]]
Output: 1

Constraints:

- m == obstacleGrid.length

- n == obstacleGrid[i].length

- 1 <= m, n <= 100

- obstacleGrid[i][j] is 0 or 1.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Count how many different routes lead from the top-left cell of `obstacleGrid` to the bottom-right cell when every step moves one cell right or one cell down and no route may step on a cell marked `1`.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Any route into cell `(i, j)` arrives either from the cell directly above or from the cell directly to the left, and no route does both. In Example 1 the target is entered from `(1, 2)` or `(2, 1)`, and the centre `1` leaves each of those with exactly one route.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

`m` and `n` are at most 100, so a route has up to 198 moves and listing routes one by one is exponential. There are only `10^4` cells, so doing constant work per cell is instant: aim for `O(m·n)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is 2D grid dynamic programming (counting paths): the answer for a cell is built from the answers for the cell above and the cell to the left, and those smaller answers are shared by many cells.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

The number of routes to `(i, j)` is the routes to `(i - 1, j)` plus the routes to `(i, j - 1)`, and an obstacle cell has 0 routes. Filling cells top to bottom and left to right guarantees both inputs are ready.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep one array `dp` of length `n`: `dp[j]` is the number of routes from the start to column `j` of the row being processed. Just before you update it, `dp[j]` still holds the count of the cell above, and `dp[j - 1]` already holds the count of the cell on the left.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Create `dp` of length `n` filled with 0 and set `dp[0]` to 1.
Go through rows `i` from top to bottom.
Inside a row, go through columns `j` from left to right.
If `obstacleGrid[i][j]` is 1, set `dp[j]` to 0.
Otherwise, if `j > 0`, add `dp[j - 1]` to `dp[j]`.
After the last row, `dp[n - 1]` is the answer.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is the first row and column: once an obstacle appears there, every cell after it along that edge must get 0, which the same update does automatically. Return 0 when the start or the target is blocked, handle a single row or column, and note that cells that cannot reach the target may hold counts far above `2·10^9`, so pick an overflow-safe type in C++. Time `O(m·n)`, extra space `O(n)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "The robot can only move either down or right" | every cell is entered from at most two neighbours (above or left), which gives the recurrence `paths(i, j) = paths(i - 1, j) + paths(i, j - 1)`. |
| "Return the number of possible unique paths" | only a count is needed, so overlapping sub-answers can be added instead of listing routes. |
| "A path ... cannot include any square that is an obstacle" | an obstacle cell contributes 0 routes, which automatically cuts off every cell that can only be reached through it. |
| "1 <= m, n <= 100" | at most `10^4` cells, so constant work per cell is trivial while enumerating routes is exponential. |

### What the constraints tell you

With `m, n <= 100` there are at most `10^4` cells, so an `O(m·n)` fill is about `10^4` additions and runs instantly. Exploring routes one by one is exponential: a grid whose start is walled off by obstacles at `(0, 1)` and `(1, 0)` has answer 0 yet makes plain recursion explore about `9·10^58` dead-end routes. The target is `O(m·n)` time.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most direct way to count the routes?**

<details>
<summary>Answer</summary>

Walk every route: from the target, repeatedly ask where the previous step came from (above or left) until you reach `(0, 0)`, the edge of the grid or a `1`. It is correct, but the number of routes explored grows exponentially with `m + n`.

</details>

**Q2. How can a route arrive at cell `(i, j)`?**

<details>
<summary>Answer</summary>

Only from `(i - 1, j)` with a Down move or from `(i, j - 1)` with a Right move, and the last move of a route is unique. So `paths(i, j) = paths(i - 1, j) + paths(i, j - 1)` with `paths(0, 0) = 1`, and nothing is double-counted.

</details>

**Q3. What does an obstacle change in that formula?**

<details>
<summary>Answer</summary>

A cell with `obstacleGrid[i][j] = 1` simply has 0 routes, whatever its neighbours hold. In Example 2 the `1` at `(0, 1)` makes `paths(0, 1) = 0`, so the target only inherits the route Down, Right through `(1, 0)`.

</details>

**Q4. Why is plain recursion on that formula still slow?**

<details>
<summary>Answer</summary>

The same cell is requested again and again: in a free 2 × 3 grid, `paths(0, 1)` is needed by both `paths(0, 2)` and `paths(1, 1)`, and the repetition compounds over larger grids. There are only `m·n` distinct cells, so each count should be computed once and stored.

</details>

**Q5. In which order can the cells be filled without recursion?**

<details>
<summary>Answer</summary>

Row by row from the top, left to right inside each row. Then the cell above and the cell to the left of `(i, j)` are always finished before `(i, j)` is computed.

</details>

**Q6. Do we need the whole `m × n` table?**

<details>
<summary>Answer</summary>

No. Cell `(i, j)` only reads the row above and the current row, so one array `dp` of length `n` is enough: before the update `dp[j]` is the value from above and `dp[j - 1]` is the value from the left, giving `dp[j] ← dp[j] + dp[j - 1]`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Plain recursion on the last move](#1-brute-force-plain-recursion-on-the-last-move) | `O(2^(m+n))` | `O(m+n)` |
| 2 | [Better: Memoized recursion (top-down DP)](#2-better-memoized-recursion-top-down-dp) | `O(m·n)` | `O(m·n)` |
| 3 | [Optimal: Bottom-up DP with a single row](#3-optimal-bottom-up-dp-with-a-single-row) | `O(m·n)` | `O(n)` |

### 1. Brute force: Plain recursion on the last move

> **Where you start:** Every route into a cell ends with either a Down or a Right move, so the first idea is to write the count for a cell as the sum of the two smaller questions and let recursion answer them.

**Idea.** Define `countPaths(i, j)` as the number of obstacle-free routes from `(0, 0)` to `(i, j)`. If `(i, j)` is outside the grid or is an obstacle the answer is 0; if it is the start the answer is 1; otherwise it is `countPaths(i - 1, j) + countPaths(i, j - 1)`. This is correct because the last move of every route into `(i, j)` is unique, so the two groups split all routes without overlap. The answer is `countPaths(m - 1, n - 1)`.

**Steps**

1. Call `countPaths(m - 1, n - 1)` for the target cell.
2. If `i < 0` or `j < 0`, return 0 because the route left the grid.
3. If `obstacleGrid[i][j]` is 1, return 0 because no route may use this cell.
4. If `(i, j)` is `(0, 0)`, return 1: the route has reached the start.
5. Otherwise return `countPaths(i - 1, j) + countPaths(i, j - 1)`.

**Pseudocode**

```text
 1 │ function uniquePathsWithObstacles(obstacleGrid)
 2 │   m ← number of rows in obstacleGrid
 3 │   n ← number of columns in obstacleGrid
 4 │   return countPaths(m - 1, n - 1)  // count the routes that end at the target cell
 5 │ function countPaths(i, j)  // routes from (0, 0) to (i, j) using only Down and Right moves
 6 │   if i < 0 or j < 0
 7 │     return 0  // stepped outside the grid
 8 │   if obstacleGrid[i][j] = 1
 9 │     return 0  // tested before the start check, so a blocked start gives 0
10 │   if i = 0 and j = 0
11 │     return 1  // reached the start: exactly one route
12 │   up ← countPaths(i - 1, j)  // routes whose last move was Down from (i - 1, j)
13 │   left ← countPaths(i, j - 1)  // routes whose last move was Right from (i, j - 1)
14 │   return up + left  // the two groups never share a route
```

**Time complexity: `O(2^(m+n))`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup and first call (lines 2-4) | 1 × O(1) | Reads the grid size once and starts the recursion at the target. |
| Base-case checks (lines 6-11) | one per call × O(1) | Every call first tests the bounds, the obstacle and the start before doing anything else. |
| Recursive expansion (lines 12-14) | up to 2^(m+n) calls × O(1) | Each free, non-start cell makes two calls, and each call lowers i + j by one, so chains are at most m + n - 1 deep. |

- **Adding it up:** O(1) + (number of calls) × O(1). The call tree is binary with depth at most m + n - 1, so it has fewer than 2^(m+n) nodes: O(2^(m+n)).
- **Best vs worst case:** Best case: the target is an obstacle, so the first call returns 0 immediately. Worst case: a large free region whose routes cannot reach the start, e.g. obstacles at (0, 1) and (1, 0) in a 100 × 100 grid, where the answer is 0 but about 9·10^58 calls are made.
- **At the maximum input:** A free 14 × 14 grid (answer 10,400,600) already takes about 6·10^7 calls, a fraction of a second; at m = n = 100 the worst case is about 9·10^58 calls, far beyond any time limit.

**Space complexity: `O(m+n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 5-14) | at most m + n frames × O(1) | Each nested call lowers i + j by one, from m + n - 2 at the target down to -1 off the grid. |

- **Adding it up:** O(m + n) for the stack; nothing else is allocated.
- **Not counted:** obstacleGrid is the input and is not counted; at m = n = 100 the stack is at most 200 frames deep.

**Dry run** on `obstacleGrid = [[0,0,0],[1,0,0]] (a 2 × 3 grid with an obstacle at (1, 0); Example 1 has 9 cells, so a smaller grid keeps the trace short)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | The grid has m = 2 rows and n = 3 columns with an obstacle at (1, 0). We count the routes into the target (1, 2) by calling countPaths(1, 2). | `m = 2`<br>`n = 3`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`call stack = [uniquePathsWithObstacles] ← top` |
| 2 | 7 | countPaths(1, 2) first asks for up = countPaths(0, 2), which in turn asks for countPaths(-1, 2). Row -1 is outside the grid, so that call returns 0. | `i = -1`<br>`j = 2`<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2), countPaths(-1,2)] ← top` |
| 3 | 11 | Back in countPaths(0, 2), up = 0. Its left call countPaths(0, 1) gets 0 from the off-grid countPaths(-1, 1) and then calls countPaths(0, 0), which is the start and returns 1. | `i = 0`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,0])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0, countPaths(0,1) up=0, countPaths(0,0)] ← top` |
| 4 | 14 | countPaths(0, 1) has up = 0 and left = 1, so it returns 0 + 1 = 1: the only route to (0, 1) is a single Right move. | `j = 1`<br>`up = 0`<br>`left = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0, countPaths(0,1) up=0 left=1] ← top` |
| 5 | 14 | countPaths(0, 2) now has up = 0 and left = 1 and returns 1 (the route Right, Right). | `j = 2`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0 left=1] ← top` |
| 6 | 12 | Control is back in countPaths(1, 2), which stores up = 1: one route reaches the target with a final Down move from (0, 2). | `i = 1`<br>`up = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1] ← top` |
| 7 | 11 | countPaths(1, 2) now asks for left = countPaths(1, 1), whose up call is countPaths(0, 1) again. Plain recursion has no memory, so (0, 1) is explored from scratch and the start is reached a second time. | `i = 0`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,0])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1), countPaths(0,1) up=0, countPaths(0,0)] ← top` |
| 8 | 14 | The repeated countPaths(0, 1) returns 1, exactly the value computed earlier. This duplicated work is what memoisation removes. | `j = 1`<br>`up = 0`<br>`left = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1), countPaths(0,1) up=0 left=1] ← top` |
| 9 | 12 | countPaths(1, 1) stores up = 1 (the route Right, Down). | `i = 1`<br>`up = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1) up=1] ← top` |
| 10 | 9 | Its left call countPaths(1, 0) lands on obstacleGrid[1][0] = 1, so it returns 0: no route may pass through (1, 0). | `j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,0])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1) up=1, countPaths(1,0)] ← top` |
| 11 | 14 | countPaths(1, 1) returns up + left = 1 + 0 = 1. | `j = 1`<br>`up = 1`<br>`left = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1) up=1 left=0] ← top` |
| 12 | 14 | countPaths(1, 2) has up = 1 and left = 1 and returns 1 + 1 = 2. | `j = 2`<br>`left = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1 left=1] ← top` |
| 13 | 4 | uniquePathsWithObstacles returns countPaths(1, 2) = 2. | `obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`call stack = [uniquePathsWithObstacles] ← top` |

**Result:** 2 — the routes Right, Right, Down and Right, Down, Right; the third route Down, Right, Right is blocked by the obstacle at (1, 0).

**C++ solution**

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();     // number of rows
        int n = obstacleGrid[0].size();  // number of columns
        return countPaths(obstacleGrid, m - 1, n - 1); // count the routes that end at the target cell
    }

private:
    // Routes from (0, 0) to (i, j) using only Down and Right moves.
    // int is enough: every cell we expand can still reach the target, so its count is <= the answer <= 2 * 10^9.
    int countPaths(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || j < 0) return 0;          // stepped outside the grid
        if (grid[i][j] == 1) return 0;         // obstacle; tested before the start so a blocked start gives 0
        if (i == 0 && j == 0) return 1;        // reached the start: exactly one route
        int up = countPaths(grid, i - 1, j);   // routes whose last move was Down from (i - 1, j)
        int left = countPaths(grid, i, j - 1); // routes whose last move was Right from (i, j - 1)
        return up + left;                      // the two groups never share a route
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
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();     // number of rows
        int n = obstacleGrid[0].size();  // number of columns
        return countPaths(obstacleGrid, m - 1, n - 1); // count the routes that end at the target cell
    }

private:
    // Routes from (0, 0) to (i, j) using only Down and Right moves.
    // int is enough: every cell we expand can still reach the target, so its count is <= the answer <= 2 * 10^9.
    int countPaths(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || j < 0) return 0;          // stepped outside the grid
        if (grid[i][j] == 1) return 0;         // obstacle; tested before the start so a blocked start gives 0
        if (i == 0 && j == 0) return 1;        // reached the start: exactly one route
        int up = countPaths(grid, i - 1, j);   // routes whose last move was Down from (i - 1, j)
        int left = countPaths(grid, i, j - 1); // routes whose last move was Right from (i, j - 1)
        return up + left;                      // the two groups never share a route
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
```

</details>

**Why move on:** The same cell is recomputed once for every route that leads from it back to the target, so the work explodes: a free 14 × 14 grid already needs about `6·10^7` calls, and a 100 × 100 grid with the start walled off needs about `9·10^58` even though the answer is 0.

### 2. Better: Memoized recursion (top-down DP)

> **How you get here:** Plain recursion asks for the same cell over and over (in a free 2 × 3 grid `countPaths(0, 1)` is computed once for `(0, 2)` and again for `(1, 1)`), yet a cell's count never changes, so it can be stored the first time.

**Idea.** Keep the same recurrence but add an `m × n` table `memo` filled with -1. Before expanding `(i, j)`, return `memo[i][j]` if it has been filled; otherwise compute `countPaths(i - 1, j) + countPaths(i, j - 1)`, store it in `memo[i][j]` and return it. Correctness is unchanged because a cell's count depends only on its position, not on which caller asked. Each cell now expands at most once, so the work drops from exponential to proportional to the number of cells.

**Steps**

1. Create `memo` of size `m × n` filled with -1 (not computed).
2. Call `countPaths(m - 1, n - 1)`.
3. Return 0 for cells outside the grid or on an obstacle, and 1 for `(0, 0)`.
4. If `memo[i][j]` is not -1, return it immediately.
5. Otherwise compute `up = countPaths(i - 1, j)` and `left = countPaths(i, j - 1)`.
6. Store `up + left` in `memo[i][j]` and return it.

**Pseudocode**

```text
 1 │ function uniquePathsWithObstacles(obstacleGrid)
 2 │   m ← number of rows in obstacleGrid
 3 │   n ← number of columns in obstacleGrid
 4 │   memo ← m × n table filled with -1  // -1 means not computed yet; real counts are ≥ 0
 5 │   return countPaths(m - 1, n - 1)
 6 │ function countPaths(i, j)  // routes from (0, 0) to (i, j)
 7 │   if i < 0 or j < 0
 8 │     return 0  // stepped outside the grid
 9 │   if obstacleGrid[i][j] = 1
10 │     return 0  // a route cannot pass through an obstacle
11 │   if i = 0 and j = 0
12 │     return 1  // reached the start: exactly one route
13 │   if memo[i][j] ≠ -1
14 │     return memo[i][j]  // solved before: reuse instead of re-exploring
15 │   up ← countPaths(i - 1, j)  // routes whose last move was Down
16 │   left ← countPaths(i, j - 1)  // routes whose last move was Right
17 │   memo[i][j] ← up + left  // store before returning so later callers reuse it
18 │   return memo[i][j]
```

**Time complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Memo setup (line 4) | m·n cells × O(1) | Every memo cell is filled with -1 once. |
| Expanding a cell (lines 15-18) | at most m·n expansions × O(1) | A cell is expanded only while memo[i][j] = -1, and the expansion fills it immediately. |
| All calls, including base cases and memo hits (lines 6-14) | at most 2·m·n + 1 calls × O(1) | Each expansion makes exactly two calls, plus the first call from line 5. |

- **Adding it up:** m·n + m·n + (2·m·n + 1) ≈ 4·m·n = O(m·n).
- **At the maximum input:** m = n = 100 → about 4·10^4 basic steps, well under a millisecond.

**Space complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| memo table (line 4) | m × n integers | One stored count per cell. |
| Recursion stack (lines 6-18) | at most m + n frames | Each nested call lowers i + j by one. |

- **Adding it up:** m·n + (m + n) = O(m·n); the table dominates.
- **Not counted:** obstacleGrid is the input and is not counted.

**Dry run** on `obstacleGrid = [[0,0,0],[1,0,0]] (a 2 × 3 grid with an obstacle at (1, 0); Example 1 has 9 cells, so a smaller grid keeps the trace short)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | m = 2 and n = 3; every memo cell starts at -1, meaning not computed yet. | `m = 2`<br>`n = 3`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`memo = 2×3 table: [-1, -1, -1] [-1, -1, -1]`<br>`call stack = [uniquePathsWithObstacles] ← top` |
| 2 | 8 | countPaths(1, 2) asks for up = countPaths(0, 2), which asks for countPaths(-1, 2). Row -1 is off the grid, so it returns 0. | `i = -1`<br>`j = 2`<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2), countPaths(-1,2)] ← top` |
| 3 | 12 | countPaths(0, 2) has up = 0 and calls countPaths(0, 1). After its off-grid up call returns 0, countPaths(0, 1) calls countPaths(0, 0), the start, which returns 1. | `i = 0`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,0])<br>`memo = 2×3 table: [-1, -1, -1] [-1, -1, -1]` ((i,j)→[0,0])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0, countPaths(0,1) up=0, countPaths(0,0)] ← top` |
| 4 | 17 | countPaths(0, 1) has up = 0 and left = 1, so it stores memo[0][1] = 1 before returning it. | `j = 1`<br>`up = 0`<br>`left = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,1])<br>`memo = 2×3 table: [-1, 1, -1] [-1, -1, -1]` ((i,j)→[0,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0, countPaths(0,1) up=0 left=1] ← top` |
| 5 | 17 | countPaths(0, 2) receives left = 1 from (0, 1) and stores memo[0][2] = 0 + 1 = 1. | `j = 2`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,2])<br>`memo = 2×3 table: [-1, 1, 1] [-1, -1, -1]` ((i,j)→[0,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2), countPaths(0,2) up=0 left=1] ← top` |
| 6 | 15 | Back in countPaths(1, 2): up = 1, the single route that ends with a Down move from (0, 2). | `i = 1`<br>`up = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,2])<br>`memo = 2×3 table: [-1, 1, 1] [-1, -1, -1]` ((i,j)→[1,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1] ← top` |
| 7 | 14 | countPaths(1, 2) calls left = countPaths(1, 1), which asks for countPaths(0, 1). This time memo[0][1] = 1 is already filled, so the call returns 1 at once instead of re-exploring (0, 1). | `i = 0`<br>`j = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,1])<br>`memo = 2×3 table: [-1, 1, 1] [-1, -1, -1]` ((i,j)→[0,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1), countPaths(0,1)] ← top` |
| 8 | 10 | countPaths(1, 1) has stored up = 1 and now calls countPaths(1, 0); obstacleGrid[1][0] = 1, so it returns 0. | `i = 1`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,0])<br>`memo = 2×3 table: [-1, 1, 1] [-1, -1, -1]` ((i,j)→[1,0])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1) up=1, countPaths(1,0)] ← top` |
| 9 | 17 | countPaths(1, 1) stores memo[1][1] = 1 + 0 = 1. | `j = 1`<br>`up = 1`<br>`left = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,1])<br>`memo = 2×3 table: [-1, 1, 1] [-1, 1, -1]` ((i,j)→[1,1])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1, countPaths(1,1) up=1 left=0] ← top` |
| 10 | 17 | countPaths(1, 2) has up = 1 and left = 1 and stores memo[1][2] = 2. | `j = 2`<br>`left = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,2])<br>`memo = 2×3 table: [-1, 1, 1] [-1, 1, 2]` ((i,j)→[1,2])<br>`call stack = [uniquePathsWithObstacles, countPaths(1,2) up=1 left=1] ← top` |
| 11 | 5 | The top call returns 2. memo[0][0] and memo[1][0] stay -1 because the start and the obstacle are answered by base cases and never stored. | `obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`memo = 2×3 table: [-1, 1, 1] [-1, 1, 2]`<br>`call stack = [uniquePathsWithObstacles] ← top` |

**Result:** 2 — memo[1][2] = memo[0][2] + memo[1][1] = 1 + 1, the routes Right, Right, Down and Right, Down, Right; (0, 1) was expanded only once.

**C++ solution**

```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();     // number of rows
        int n = obstacleGrid[0].size();  // number of columns
        vector<vector<int>> memo(m, vector<int>(n, -1)); // -1 = not computed yet (real counts are >= 0)
        return countPaths(obstacleGrid, m - 1, n - 1, memo); // count the routes that end at the target cell
    }

private:
    // Routes from (0, 0) to (i, j); memo makes every cell expand at most once.
    // int is enough: every memoised cell can still reach the target, so its count is <= the answer <= 2 * 10^9.
    int countPaths(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
        if (i < 0 || j < 0) return 0;                // stepped outside the grid
        if (grid[i][j] == 1) return 0;               // obstacle; tested before the start so a blocked start gives 0
        if (i == 0 && j == 0) return 1;              // reached the start: exactly one route
        if (memo[i][j] != -1) return memo[i][j];     // solved before: reuse instead of re-exploring
        int up = countPaths(grid, i - 1, j, memo);   // routes whose last move was Down from (i - 1, j)
        int left = countPaths(grid, i, j - 1, memo); // routes whose last move was Right from (i, j - 1)
        memo[i][j] = up + left;                      // store before returning so later callers reuse it
        return memo[i][j];
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
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();     // number of rows
        int n = obstacleGrid[0].size();  // number of columns
        vector<vector<int>> memo(m, vector<int>(n, -1)); // -1 = not computed yet (real counts are >= 0)
        return countPaths(obstacleGrid, m - 1, n - 1, memo); // count the routes that end at the target cell
    }

private:
    // Routes from (0, 0) to (i, j); memo makes every cell expand at most once.
    // int is enough: every memoised cell can still reach the target, so its count is <= the answer <= 2 * 10^9.
    int countPaths(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& memo) {
        if (i < 0 || j < 0) return 0;                // stepped outside the grid
        if (grid[i][j] == 1) return 0;               // obstacle; tested before the start so a blocked start gives 0
        if (i == 0 && j == 0) return 1;              // reached the start: exactly one route
        if (memo[i][j] != -1) return memo[i][j];     // solved before: reuse instead of re-exploring
        int up = countPaths(grid, i - 1, j, memo);   // routes whose last move was Down from (i - 1, j)
        int left = countPaths(grid, i, j - 1, memo); // routes whose last move was Right from (i, j - 1)
        memo[i][j] = up + left;                      // store before returning so later callers reuse it
        return memo[i][j];
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
```

</details>

**Why move on:** Time is already optimal, but the `10^4`-entry table and up to 200 stack frames are more than needed, and recursion adds call overhead. Each cell only needs the row above it, which a bottom-up fill can exploit to keep a single row.

### 3. Optimal: Bottom-up DP with a single row

> **How you get here:** In the memo table, row `i` is only ever read while filling row `i + 1`, so filling the grid row by row from the top lets one array of length `n` replace both the table and the recursion.

**Idea.** Let `dp[j]` be the number of routes from `(0, 0)` to `(i, j)` for the row `i` being processed. Scanning a row left to right, the old `dp[j]` is the count of the cell above and `dp[j - 1]` was just updated to the count of the cell on the left, so `dp[j] ← dp[j] + dp[j - 1]` is exactly the recurrence. An obstacle sets `dp[j] ← 0`, which also stops its count from flowing right or down. After the last row, `dp[n - 1]` is the count for the target.

**Steps**

1. Create `dp` of length `n` filled with 0 and set `dp[0] = 1` for the start.
2. For each row `i` from 0 to `m - 1`, scan `j` from 0 to `n - 1`.
3. If `obstacleGrid[i][j]` is 1, set `dp[j] = 0` (this also handles a blocked start).
4. Else if `j > 0`, set `dp[j] = dp[j] + dp[j - 1]` (above + left).
5. Else (`j = 0` and free) leave `dp[0]` as is: its only source is the cell above, which `dp[0]` already holds.
6. Return `dp[n - 1]`.

**Pseudocode**

```text
 1 │ function uniquePathsWithObstacles(obstacleGrid)
 2 │   m ← number of rows in obstacleGrid
 3 │   n ← number of columns in obstacleGrid
 4 │   dp ← array of n zeros  // dp[j] = routes from (0, 0) to (i, j) for the row i being processed
 5 │   dp[0] ← 1  // seed for the start; the loop resets it to 0 if (0, 0) is an obstacle
 6 │   for i ← 0 to m - 1
 7 │     for j ← 0 to n - 1
 8 │       if obstacleGrid[i][j] = 1
 9 │         dp[j] ← 0  // no route may pass through an obstacle
10 │       else if j > 0
11 │         dp[j] ← dp[j] + dp[j - 1]  // old dp[j] = from above, dp[j - 1] = from the left
12 │   return dp[n - 1]
```

**Time complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup (lines 2-5) | n steps | dp is filled with n zeros and seeded once. |
| Nested loops (lines 6-11) | m·n iterations × O(1) | Each cell is visited once and does one obstacle test and at most one addition. |

- **Adding it up:** n + m·n = O(m·n); the double loop dominates.
- **At the maximum input:** m = n = 100 → 10^4 iterations, a few microseconds.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp array (line 4) | n counters | One running count per column; earlier rows are overwritten in place. |

- **Adding it up:** O(n).
- **Not counted:** obstacleGrid is the input and is not counted; i and j are O(1).

**Dry run** on `obstacleGrid = [[0,0,0],[1,0,0]] (a 2 × 3 grid with an obstacle at (1, 0); Example 1 has 9 cells, so a smaller grid keeps the trace short)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | m = 2 and n = 3; dp holds one counter per column, all 0. | `m = 2`<br>`n = 3`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`dp = [0, 0, 0]` |
| 2 | 5 | Seed dp[0] = 1 for the start cell (0, 0). If the start were an obstacle, the loop would reset it to 0. | `dp = [1, 0, 0]` |
| 3 | 10 | i = 0, j = 0: the cell is free and j = 0, so nothing is added and dp[0] keeps the single route to the start. | `i = 0`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,0])<br>`dp = [1, 0, 0]` (j→0) |
| 4 | 11 | i = 0, j = 1: dp[1] = dp[1] + dp[0] = 0 + 1 = 1. Nothing comes from above on row 0; one route comes from the left. | `j = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,1])<br>`dp = [1, 1, 0]` (j→1) |
| 5 | 11 | i = 0, j = 2: dp[2] = 0 + 1 = 1, so every cell of row 0 has exactly one route (Right moves only). | `j = 2`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[0,2])<br>`dp = [1, 1, 1]` (j→2) |
| 6 | 9 | i = 1, j = 0: obstacleGrid[1][0] = 1, so dp[0] = 0; the route that starts with Down dies here. | `i = 1`<br>`j = 0`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,0])<br>`dp = [0, 1, 1]` (j→0) |
| 7 | 11 | i = 1, j = 1: dp[1] = dp[1] + dp[0] = 1 + 0 = 1: one route from above (0, 1), none from the blocked cell on the left. | `j = 1`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,1])<br>`dp = [0, 1, 1]` (j→1) |
| 8 | 11 | i = 1, j = 2: dp[2] = dp[2] + dp[1] = 1 + 1 = 2: one route from above (0, 2) and one from the left (1, 1). | `j = 2`<br>`obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]` ((i,j)→[1,2])<br>`dp = [0, 1, 2]` (j→2) |
| 9 | 12 | Both rows are done, so dp[n - 1] = dp[2] = 2 is the number of routes to the target (1, 2). | `obstacleGrid = 2×3 table: [0, 0, 0] [1, 0, 0]`<br>`dp = [0, 1, 2]` |

**Result:** 2 — the routes Right, Right, Down and Right, Down, Right; the third route Down, Right, Right is blocked by the obstacle at (1, 0).

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Every cell must be read at least once because any single obstacle can change the answer, so `O(m·n)` time cannot be beaten. Space could drop to `O(min(m, n))` by scanning along the shorter side, or to `O(1)` by writing counts into `obstacleGrid`, at the cost of destroying the input.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| obstacleGrid = [[0,0,0,0],[0,1,0,0],[0,0,0,0]] | 4 | A 3 × 4 grid with one interior obstacle that removes the routes through (1, 1). |
| obstacleGrid = [[0,0,0],[0,0,0],[0,0,0]] | 6 | No obstacles: the count equals plain Unique Paths, C(4, 2) = 6. |
| obstacleGrid = [[0,0,1],[0,0,0],[1,0,0]] | 4 | Obstacles in two corners away from start and target cut off the routes along the outer edges. |
| obstacleGrid = [[0,0,0,0,0],[0,0,1,0,0],[1,0,0,0,1],[0,0,0,0,0]] | 7 | A 4 × 5 grid with three scattered obstacles, so counts merge from several directions. |
| obstacleGrid = [[0,0,0],[1,1,0],[0,0,0]] | 1 | A wall of obstacles leaves a single corridor along the top row and right column. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single free cell | obstacleGrid = [[0]] | 1 | Start equals target, so there is exactly one (empty) route. |
| Single blocked cell | obstacleGrid = [[1]] | 0 | The start itself is an obstacle, so no route exists. |
| Blocked start | obstacleGrid = [[1,0],[0,0]] | 0 | Every other cell is free but the robot cannot begin. |
| Blocked target | obstacleGrid = [[0,0],[0,1]] | 0 | Routes exist to every neighbour of the target but not into it. |
| Single row | obstacleGrid = [[0,0,0,0,0]] | 1 | Only Right moves are possible, so there is one route (a 1 × 100 row behaves the same). |
| Single column with an obstacle | obstacleGrid = [[0],[0],[1],[0]] | 0 | There is no way around it, so the answer drops to 0. |
| Start walled off | obstacleGrid = [[0,1],[1,0]] | 0 | Both neighbours of the start are obstacles, so the target is unreachable. |

## Mistakes and edge cases

**Common mistakes**

- Initialising the whole first row and first column to 1 as in Unique Paths: an obstacle at `(0, k)` must make every cell `(0, k')` with `k' > k` equal 0, because those cells can only be reached through it.
- Ignoring that the start or the target can be an obstacle: `[[1,0],[0,0]]` and `[[0,0],[0,1]]` must both return 0. A recursion that tests `i == 0 && j == 0` before the obstacle check, or a table that hard-codes `dp[0][0] = 1`, returns 2 for the first.
- Scanning `j` from right to left in the one-row version: `dp[j - 1]` would still hold the previous row's value, so the routes arriving from the left would be taken from the wrong row.
- Using plain `int` in a bottom-up fill: the answer is at most `2·10^9`, but cells that cannot reach the target may hold counts far larger and overflow (undefined behaviour in C++); use unsigned arithmetic, a wider type or a cap.

**Edge cases to check**

- `[[0]]`: start equals target, so the answer is 1 (the empty route), not 0.
- `[[1]]`, a blocked start such as `[[1,0],[0,0]]`, or a blocked target such as `[[0,0],[0,1]]`: the answer must be 0.
- A single row or column such as `[[0],[0],[1],[0]]`: one obstacle leaves no way around it, so the answer is 0.
- An obstacle on the first row such as `[[0,1,0],[0,0,0]]`: `(0, 2)` must get 0 routes, not inherit 1, and the answer is 1 (Down, Right, Right).
- A large grid where many cells cannot reach the target (for example, obstacles surrounding the target region): those cells can hold counts far above `2·10^9`, which tests overflow handling.

## Practice next

- [Unique Paths](https://leetcode.com/problems/unique-paths/) · The same right/down route counting without obstacles; the recurrence and the one-row DP are identical minus the 0 rule.
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) · Same grid and moves, but each cell takes the minimum of above and left plus its own cost instead of the sum.
- [Dungeon Game](https://leetcode.com/problems/dungeon-game/) · Right/down grid DP that must be filled from the target backwards, a good next step after this forward fill.
- [Unique Paths III](https://leetcode.com/problems/unique-paths-iii/) · Grid route counting with obstacles where moves go in four directions and every free cell must be visited, which needs backtracking instead of DP.

## Takeaways

- When moves are restricted to right and down, each cell depends only on the cell above and the cell to the left, so a row-major fill always has its inputs ready.
- Blocked states are handled by forcing their value to the neutral element of the combine step (0 for counting, +∞ for a minimum); the recurrence then propagates the block automatically.
- If a DP row reads only the previous row and the already-updated entry to its left, a single 1D array updated in place can replace the 2D table.
- A bound on the final answer does not bound intermediate DP values; check which states actually feed the answer before choosing an integer type.
