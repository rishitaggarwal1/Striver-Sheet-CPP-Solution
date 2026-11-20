# Unique Paths

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/unique-paths/) · Pattern: **Grid DP for counting paths, which collapses to a binomial coefficient**

> Count the distinct sequences of Down and Right moves that take the robot from cell `(0, 0)` to cell `(m - 1, n - 1)` of an `m × n` grid.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to 2 * 10^9.

Example 1:

Input: m = 3, n = 7
Output: 28

Example 2:

Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Constraints:

- 1 <= m, n <= 100
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

A robot starts in the top-left cell of an `m × n` grid and may only step right or down. Count how many different routes lead it to the bottom-right cell.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Every cell in the top row, and every cell in the left column, can be reached in exactly one way: a straight line. In Example 2 (`m = 3`, `n = 2`) all three routes contain exactly two Downs and one Right; they differ only in the order of those moves.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `m, n <= 100` there are at most `10^4` cells, so work proportional to the size of the grid is instant. Following routes one at a time is not: answers go up to `2·10^9`, so enumerating them means billions of steps.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is grid dynamic programming for counting: the number of ways to reach a cell is the sum of the ways to reach the cells you can enter it from. Because every route is a fixed mix of two kinds of moves, it is also a combinatorics (binomial coefficient) problem.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Every route uses exactly `m - 1` Downs and `n - 1` Rights, so a route is decided by choosing which of its `m + n - 2` moves are Downs. The answer is therefore the binomial coefficient `C(m + n - 2, m - 1)`.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Build `C(N, k)` with `N = m + n - 2` and `k = min(m, n) - 1` as a running value `res` that starts at `1`: at step `i` it is multiplied by `N - k + i` and then divided by `i`, after which it equals `C(N - k + i, i)`. Keep `res` in a 64-bit integer because the product before the division can exceed `2^31`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `N = m + n - 2` and `k = min(m, n) - 1`.
Set a 64-bit `res = 1`.
For `i` from `1` to `k`:
multiply `res` by `N - k + i`,
then divide `res` by `i` (always exact).
Return `res`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is keeping every intermediate exact and in range: multiply before dividing (each partial result is a whole binomial coefficient), use 64-bit because a product can reach about `2.8·10^10`, and never compute full factorials like `198!`. When `m = 1` or `n = 1`, `k = 0`, the loop does nothing, and the answer is `1`. Time is `O(min(m, n))` and extra space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "The robot can only move either down or right" | a cell can be entered only from the cell above or the cell on its left, so `ways(i, j) = ways(i - 1, j) + ways(i, j - 1)`: grid DP. |
| "return the number of possible unique paths" | a counting question (add the counts of the choices), not a max/min optimisation. |
| "the answer will be less than or equal to 2 * 10^9" | the result fits in a 32-bit `int`, but a formula's intermediate products may not, and visiting paths one by one would take billions of steps. |
| "1 <= m, n <= 100" | at most `10^4` cells, so an `O(m·n)` table is tiny and even simpler closed forms are worth looking for. |

### What the constraints tell you

`m, n <= 100` means at most `10^4` cells, so an `O(m·n)` DP is about `10^4` additions and a closed formula needs at most `99` multiply/divide steps. Plain recursion makes `2 × answer - 1` calls, about `2.3·10^9` for `m = 17, n = 18`, far too slow. So any polynomial method is fine; the target is `O(m·n)` or better.

### Think it through

Answer each question yourself before opening it.

**Q1. How can I count paths without listing them?**

<details>
<summary>Answer</summary>

Look at the last move into the target `(m - 1, n - 1)`: it came either from the cell above or from the cell on the left, and those two groups never overlap. So `paths(i, j) = paths(i - 1, j) + paths(i, j - 1)`, with every top-row and left-column cell reachable in exactly one way.

</details>

**Q2. Why is recursing on that formula slow even for small grids?**

<details>
<summary>Answer</summary>

The same cell is counted from many parents: in a `3 × 3` grid `paths(1,1)` is solved once for `paths(1,2)` and again for `paths(2,1)`. Each leaf adds just `1`, so the recursion makes about `2 × answer` calls, billions when the answer is near `2·10^9`.

</details>

**Q3. In what order can I compute each cell exactly once?**

<details>
<summary>Answer</summary>

A cell needs only the cell above and the cell to its left, so filling the grid row by row, left to right, always has both ready. That is `m·n <= 10^4` additions, and `dp[m - 1][n - 1]` is the answer (for Example 1, `28`).

</details>

**Q4. What do all the paths in Example 2 (`m = 3`, `n = 2`) have in common?**

<details>
<summary>Answer</summary>

Each has exactly two Downs and one Right: `Right→Down→Down`, `Down→Down→Right` and `Down→Right→Down` differ only in where the single Right sits. In general every path has `m - 1` Downs and `n - 1` Rights.

</details>

**Q5. So is there a closed form?**

<details>
<summary>Answer</summary>

A path is fixed once you choose which of its `m + n - 2` moves are Downs, so the count is `C(m + n - 2, m - 1)`. For Example 1 that is `C(8, 2) = 28`, matching the table.

</details>

**Q6. How do I evaluate `C(N, k)` without overflow or fractions?**

<details>
<summary>Answer</summary>

Take `k = min(m, n) - 1` and build `res = res × (N - k + i) / i` for `i = 1..k` in 64-bit. After each step `res` equals `C(N - k + i, i)`, a whole number, so the division is exact, and no product exceeds about `2.8·10^10`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Recursion on the last move](#1-brute-force-recursion-on-the-last-move) | `O(2^(m+n))` | `O(m + n)` |
| 2 | [Better: 2D DP table filled row by row](#2-better-2d-dp-table-filled-row-by-row) | `O(m·n)` | `O(m·n)` |
| 3 | [Optimal: Binomial coefficient C(m + n − 2, m − 1)](#3-optimal-binomial-coefficient-cm--n--2-m--1) | `O(min(m, n))` | `O(1)` |

### 1. Brute force: Recursion on the last move

> **Where you start:** Asking 'where did the robot come from just before this cell?' gives the recurrence immediately, and recursing on it is the first thing anyone writes.

**Idea.** Let `paths(i, j)` be the number of Down/Right paths from `(0,0)` to `(i, j)`. If `i = 0` or `j = 0` the cell is on the top row or left column and only one straight path reaches it. Otherwise the last move was a Down from `(i - 1, j)` or a Right from `(i, j - 1)`; those groups are disjoint and together contain every path, so `paths(i, j) = paths(i - 1, j) + paths(i, j - 1)`. The answer is `paths(m - 1, n - 1)`, but since every leaf contributes only `1`, the work grows with the answer itself.

**Steps**

1. Call `paths(m - 1, n - 1)`.
2. In `paths(i, j)`, return `1` if `i == 0` or `j == 0`.
3. Otherwise compute `up = paths(i - 1, j)` and `left = paths(i, j - 1)`.
4. Return `up + left`.

**Pseudocode**

```text
 1 │ function uniquePaths(m, n)
 2 │   ans ← paths(m - 1, n - 1)  // count the paths that end in the bottom-right cell
 3 │   return ans
 4 │ function paths(i, j)  // number of Down/Right paths from (0,0) to cell (i, j)
 5 │   if i = 0 or j = 0
 6 │     return 1  // top row or left column: only a straight line reaches it
 7 │   up ← paths(i - 1, j)  // paths whose last move is Down, from (i-1, j)
 8 │   left ← paths(i, j - 1)  // paths whose last move is Right, from (i, j-1)
 9 │   total ← up + left  // the two groups share no path, so add them
10 │   return total
```

**Time complexity: `O(2^(m+n))`**

| Part | Cost | Why |
| --- | --- | --- |
| Base cases (lines 5-6) | answer leaves × O(1) | Every leaf returns 1 and the root adds them all up, so there are exactly `answer` leaves. |
| Recursive calls (lines 7-10) | (answer − 1) inner calls × O(1) | Each inner call makes exactly two calls, and a full binary tree with `answer` leaves has `answer − 1` inner nodes. |

- **Adding it up:** answer + (answer − 1) = 2·C(m + n − 2, m − 1) − 1 calls of O(1) work; since C(N, k) ≤ 2^N, this is O(2^(m + n)).
- **Best vs worst case:** A single row or column (`m = 1` or `n = 1`) makes just one call; for a fixed `m + n`, square grids are the worst because the middle binomial coefficient is the largest.
- **At the maximum input:** m = 3, n = 7 → 55 calls; m = 17, n = 18 → about 2.3·10^9 calls, several seconds in C++, so it times out.

**Space complexity: `O(m + n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 7-8) | at most m + n − 2 frames × O(1) | Each call lowers i + j by one, and the recursion stops as soon as i or j reaches 0. |

- **Adding it up:** Only one chain of calls is alive at a time, so the peak is O(m + n) frames of O(1) each.
- **Not counted:** No table is stored; the grid itself is never built.

**Dry run** on `m = 3, n = 3`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 5 | uniquePaths(3, 3) calls paths(2,2) for the target cell; i = 2 and j = 2 are both non-zero, so it must recurse. | `m = 3`<br>`n = 3`<br>`i = 2`<br>`j = 2`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2)] ← top` |
| 2 | 6 | paths(2,2) asks paths(1,2) for its up value, which in turn asks paths(0,2); (0,2) is on the top row, so it returns 1. | `i = 0`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[0,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2), paths(1,2), paths(0,2)] ← top` |
| 3 | 7 | Back in paths(1,2): up = paths(0,2) = 1. | `i = 1`<br>`up = 1`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[1,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2), paths(1,2): up=1] ← top` |
| 4 | 10 | paths(1,2) now asks paths(1,1), which gets up = paths(0,1) = 1 and left = paths(1,0) = 1 and returns total = 2. | `j = 1`<br>`left = 1`<br>`total = 2`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[1,1])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2), paths(1,2): up=1, paths(1,1): up=1, left=1, total=2] ← top` |
| 5 | 8 | paths(1,2): left = paths(1,1) = 2. | `j = 2`<br>`left = 2`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[1,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2), paths(1,2): up=1, left=2] ← top` |
| 6 | 10 | paths(1,2): total = up + left = 1 + 2 = 3, which it returns as the up value of paths(2,2). | `total = 3`<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2), paths(1,2): up=1, left=2, total=3] ← top` |
| 7 | 7 | Back in paths(2,2): up = paths(1,2) = 3. | `i = 2`<br>`up = 3`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3] ← top` |
| 8 | 5 | paths(2,2) now asks paths(2,1) for its left value; i = 2 and j = 1 are both non-zero, so it recurses. | `j = 1`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,1])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, paths(2,1)] ← top` |
| 9 | 10 | paths(2,1) asks paths(1,1) — the same cell already solved two steps earlier — and it redoes paths(0,1) and paths(1,0) to return 2 again. This repeated work is what makes the recursion exponential. | `i = 1`<br>`up = 1`<br>`left = 1`<br>`total = 2`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[1,1])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, paths(2,1), paths(1,1): up=1, left=1, total=2] ← top` |
| 10 | 7 | Back in paths(2,1): up = paths(1,1) = 2. | `i = 2`<br>`up = 2`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,1])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, paths(2,1): up=2] ← top` |
| 11 | 6 | paths(2,0) is in the left column, so it returns 1. | `j = 0`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,0])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, paths(2,1): up=2, paths(2,0)] ← top` |
| 12 | 10 | paths(2,1): left = paths(2,0) = 1, so total = 2 + 1 = 3, which it returns. | `j = 1`<br>`up = 2`<br>`left = 1`<br>`total = 3`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,1])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, paths(2,1): up=2, left=1, total=3] ← top` |
| 13 | 8 | Back in paths(2,2): left = paths(2,1) = 3. | `j = 2`<br>`up = 3`<br>`left = 3`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]` ((i,j)→[2,2])<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, left=3] ← top` |
| 14 | 9 | paths(2,2): total = up + left = 3 + 3 = 6, and it returns 6. | `total = 6`<br>`call stack = [uniquePaths(m=3, n=3), paths(2,2): up=3, left=3, total=6] ← top` |
| 15 | 2 | The outer call paths(2,2) has returned, so ans = 6. | `ans = 6`<br>`grid = 3×3 table: [S, ·, ·] [·, ·, ·] [·, ·, T]`<br>`call stack = [uniquePaths(m=3, n=3): ans=6] ← top` |
| 16 | 3 | Return ans = 6. | (no change) |

**Result:** 6 — the target (2,2) is reached by 3 paths through (1,2) plus 3 paths through (2,1); C(4, 2) = 6 confirms it.

**C++ solution**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        // Count the paths that end in the bottom-right cell (m-1, n-1)
        return paths(m - 1, n - 1);
    }

private:
    // Number of Down/Right paths from (0,0) to (i,j), by plain recursion (no caching)
    int paths(int i, int j) {
        if (i == 0 || j == 0) return 1;   // top row or left column: one straight path
        int up = paths(i - 1, j);         // last move was Down, from the cell above
        int left = paths(i, j - 1);       // last move was Right, from the cell on the left
        return up + left;                 // the two groups never share a path
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
    int uniquePaths(int m, int n) {
        // Count the paths that end in the bottom-right cell (m-1, n-1)
        return paths(m - 1, n - 1);
    }

private:
    // Number of Down/Right paths from (0,0) to (i,j), by plain recursion (no caching)
    int paths(int i, int j) {
        if (i == 0 || j == 0) return 1;   // top row or left column: one straight path
        int up = paths(i - 1, j);         // last move was Down, from the cell above
        int left = paths(i, j - 1);       // last move was Right, from the cell on the left
        return up + left;                 // the two groups never share a path
    }
};

int main() {
    Solution sol;

    cout << "Example 1: " << sol.uniquePaths(3, 7) << " (expected 28)\n";
    cout << "Example 2: " << sol.uniquePaths(3, 2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why move on:** The same cell is recomputed from many parents (`paths(1,1)` twice even in `3 × 3`), so a grid like `17 × 18` needs about `2.3·10^9` calls and times out.

### 2. Better: 2D DP table filled row by row

> **How you get here:** The recursion solves the same cell again and again (`paths(1,1)` twice even in `3 × 3`), yet there are only `m·n` distinct cells; storing each count once, in an order where the cell above and the cell on the left are already known, removes all the repetition.

**Idea.** Let `dp[i][j]` be the number of paths from `(0,0)` to `(i, j)`. Every cell in row `0` or column `0` gets `1`, because only a straight line reaches it. Any other cell is entered by a Down from `(i - 1, j)` or a Right from `(i, j - 1)`, and those two groups never overlap, so `dp[i][j] = dp[i - 1][j] + dp[i][j - 1]`. Filling rows top to bottom and each row left to right guarantees both neighbours are final when they are read, so `dp[m - 1][n - 1]` is the answer.

**Steps**

1. Create an `m × n` table `dp`.
2. Set every cell in row `0` and column `0` to `1`.
3. For `i` from `1` to `m - 1` and `j` from `1` to `n - 1`, set `dp[i][j] = dp[i - 1][j] + dp[i][j - 1]`.
4. Return `dp[m - 1][n - 1]`.

**Pseudocode**

```text
 1 │ function uniquePaths(m, n)
 2 │   dp ← m × n table of 0  // dp[i][j] = number of paths from (0,0) to (i, j)
 3 │   for i ← 0 to m - 1
 4 │     for j ← 0 to n - 1
 5 │       if i = 0 or j = 0
 6 │         dp[i][j] ← 1  // first row or first column: one straight path
 7 │       else
 8 │         up ← dp[i - 1][j]  // paths arriving by a Down move
 9 │         left ← dp[i][j - 1]  // paths arriving by a Right move
10 │         dp[i][j] ← up + left  // the two groups are disjoint, so add
11 │   return dp[m - 1][n - 1]
```

**Time complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table allocation (line 2) | m·n cells × O(1) | Zero-filling the table touches every cell once. |
| Double loop (lines 3-10) | m·n iterations × O(1) | Each cell is set to 1 or to one addition of two already-known cells. |
| Return (line 11) | O(1) | A single table lookup. |

- **Adding it up:** m·n + m·n + 1 = 2·m·n + 1 = O(m·n).
- **At the maximum input:** m = n = 100 → 10^4 cells and about 2·10^4 simple operations, a few microseconds.

**Space complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp table (line 2) | m × n integers | One path count per cell of the grid. |

- **Adding it up:** m·n integers = O(m·n); at most 10^4 ints, about 40 KB.
- **Not counted:** Keeping only the previous row would cut this to O(n) with the same recurrence; the inputs and the returned int are not counted.

**Dry run** on `m = 3, n = 3`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | Create a 3 × 3 table of zeros; dp[i][j] will hold the number of paths into cell (i, j). | `m = 3`<br>`n = 3`<br>`dp = 3×3 table: [0, 0, 0] [0, 0, 0] [0, 0, 0]` |
| 2 | 6 | Cell (0,0) is the start cell, reachable by a single straight path, so dp[0][0] = 1. | `i = 0`<br>`j = 0`<br>`dp = 3×3 table: [1, 0, 0] [0, 0, 0] [0, 0, 0]` ((i,j)→[0,0]) |
| 3 | 6 | Cell (0,1) is in the first row, reachable by a single straight path, so dp[0][1] = 1. | `j = 1`<br>`dp = 3×3 table: [1, 1, 0] [0, 0, 0] [0, 0, 0]` ((i,j)→[0,1]) |
| 4 | 6 | Cell (0,2) is in the first row, reachable by a single straight path, so dp[0][2] = 1. | `j = 2`<br>`dp = 3×3 table: [1, 1, 1] [0, 0, 0] [0, 0, 0]` ((i,j)→[0,2]) |
| 5 | 6 | Cell (1,0) is in the first column, reachable by a single straight path, so dp[1][0] = 1. | `i = 1`<br>`j = 0`<br>`dp = 3×3 table: [1, 1, 1] [1, 0, 0] [0, 0, 0]` ((i,j)→[1,0]) |
| 6 | 10 | Cell (1,1): up = dp[0][1] = 1, left = dp[1][0] = 1, so dp[1][1] = 1 + 1 = 2. | `j = 1`<br>`up = 1`<br>`left = 1`<br>`dp = 3×3 table: [1, 1, 1] [1, 2, 0] [0, 0, 0]` ((i,j)→[1,1]) |
| 7 | 10 | Cell (1,2): up = dp[0][2] = 1, left = dp[1][1] = 2, so dp[1][2] = 1 + 2 = 3. | `j = 2`<br>`left = 2`<br>`dp = 3×3 table: [1, 1, 1] [1, 2, 3] [0, 0, 0]` ((i,j)→[1,2]) |
| 8 | 6 | Cell (2,0) is in the first column, reachable by a single straight path, so dp[2][0] = 1. | `i = 2`<br>`j = 0`<br>`dp = 3×3 table: [1, 1, 1] [1, 2, 3] [1, 0, 0]` ((i,j)→[2,0]) |
| 9 | 10 | Cell (2,1): up = dp[1][1] = 2, left = dp[2][0] = 1, so dp[2][1] = 2 + 1 = 3. | `j = 1`<br>`up = 2`<br>`left = 1`<br>`dp = 3×3 table: [1, 1, 1] [1, 2, 3] [1, 3, 0]` ((i,j)→[2,1]) |
| 10 | 10 | Cell (2,2): up = dp[1][2] = 3, left = dp[2][1] = 3, so dp[2][2] = 3 + 3 = 6. | `j = 2`<br>`up = 3`<br>`left = 3`<br>`dp = 3×3 table: [1, 1, 1] [1, 2, 3] [1, 3, 6]` ((i,j)→[2,2]) |
| 11 | 11 | Return dp[2][2] = 6. | (no change) |

**Result:** 6 — dp[2][2] = dp[1][2] + dp[2][1] = 3 + 3, and the table is Pascal's triangle, so the corner equals C(4, 2) = 6.

**C++ solution**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[i][j] = number of paths from (0,0) to (i,j); every value is <= the answer, so int is enough
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;                          // first row/column: one straight path
                } else {
                    // Arrive by a Down move from above or a Right move from the left
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];                           // paths into the bottom-right cell
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
    int uniquePaths(int m, int n) {
        // dp[i][j] = number of paths from (0,0) to (i,j); every value is <= the answer, so int is enough
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;                          // first row/column: one straight path
                } else {
                    // Arrive by a Down move from above or a Right move from the left
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }
        return dp[m - 1][n - 1];                           // paths into the bottom-right cell
    }
};

int main() {
    Solution sol;

    cout << "Example 1: " << sol.uniquePaths(3, 7) << " (expected 28)\n";
    cout << "Example 2: " << sol.uniquePaths(3, 2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why move on:** It passes the limits easily, but it keeps all `m·n` counts although each row only reads the row above (one rolling row of `n` cells would give `O(n)` space), and it still does `m·n` additions where a closed formula needs only `min(m, n) - 1` steps.

### 3. Optimal: Binomial coefficient C(m + n − 2, m − 1)

> **How you get here:** Every entry of the `dp` table counts arrangements of Downs and Rights — `dp[i][j] = C(i + j, i)`, Pascal's triangle — so the bottom-right entry is one binomial coefficient and the table is not needed at all.

**Idea.** A path is fully described by which of its `N = m + n - 2` moves are Downs, and any choice of `m - 1` positions gives a valid path, so the count is `C(N, m - 1) = C(N, n - 1)`. Using `k = min(m, n) - 1` keeps the loop as short as possible. Building it as `res = res × (N - k + i) / i` for `i = 1..k` keeps every intermediate equal to the whole number `C(N - k + i, i)`, so integer division never loses anything, and a 64-bit `res` absorbs the temporary product before each division.

**Steps**

1. Set `N = m + n - 2` and `k = min(m, n) - 1`.
2. Start with a 64-bit `res = 1`.
3. For `i` from `1` to `k`, multiply `res` by `N - k + i`.
4. Then divide `res` by `i`; the result is exactly `C(N - k + i, i)`.
5. Return `res` as an `int`.

**Pseudocode**

```text
 1 │ function uniquePaths(m, n)
 2 │   N ← m + n - 2  // total moves on every path
 3 │   downs ← m - 1  // every path has exactly m-1 Down moves ...
 4 │   rights ← n - 1  // ... and exactly n-1 Right moves
 5 │   k ← min(downs, rights)  // C(N, downs) = C(N, rights); the smaller k means fewer steps
 6 │   res ← 1  // 64-bit; after step i it holds C(N - k + i, i)
 7 │   for i ← 1 to k
 8 │     res ← res × (N - k + i)  // multiply first ...
 9 │     res ← res / i  // ... then divide: the result is a whole binomial, so this is exact
10 │   return res  // C(N, k): ways to place the k rarer moves among N slots
```

**Time complexity: `O(min(m, n))`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup (lines 2-6) | O(1) | A few additions, one min and one assignment. |
| Product loop (lines 7-9) | k = min(m, n) − 1 iterations × O(1) | One multiplication and one exact division per iteration. |

- **Adding it up:** O(1) + (min(m, n) − 1)·O(1) = O(min(m, n)).
- **Best vs worst case:** `m = 1` or `n = 1` gives k = 0, so the loop never runs and the answer is 1; otherwise the length depends only on the smaller side.
- **At the maximum input:** At most 99 iterations for any allowed input; Example 1 (m = 3, n = 7) needs just 2.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| Scalars N, downs, rights, k, res, i (lines 2-7) | 6 numbers | No table and no recursion are used. |

- **Adding it up:** 6 scalars regardless of m and n = O(1).
- **Not counted:** `res` must be 64-bit: the product before a division can exceed 2^31 − 1 (up to about 2.8·10^10) even though the final answer fits in an int.

**Dry run** on `m = 3, n = 7`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | N = m + n - 2 = 3 + 7 - 2 = 8: every path makes exactly 8 moves. | `m = 3`<br>`n = 7`<br>`N = 8` |
| 2 | 3 | downs = m - 1 = 2: every path goes down exactly 2 times. | `downs = 2` |
| 3 | 4 | rights = n - 1 = 6: every path goes right exactly 6 times. | `rights = 6` |
| 4 | 5 | k = min(2, 6) = 2: choosing where the 2 Down moves go among 8 slots fixes the path, and the smaller k means only 2 loop steps. | `k = 2` |
| 5 | 6 | res = 1, the empty product (C(anything, 0) = 1). | `res = 1` |
| 6 | 8 | i = 1: res = 1 × (N - k + i) = 1 × 7 = 7. | `res = 7`<br>`i = 1` |
| 7 | 9 | res = 7 / 1 = 7, which is exactly C(7, 1). | (no change) |
| 8 | 8 | i = 2: res = 7 × (N - k + i) = 7 × 8 = 56. | `res = 56`<br>`i = 2` |
| 9 | 9 | res = 56 / 2 = 28, which is exactly C(8, 2). | `res = 28` |
| 10 | 10 | The loop is done; return res = 28 = C(8, 2). | (no change) |

**Result:** 28 — choosing which 2 of the 8 moves are Downs gives C(8, 2) = 28, the same as filling the 3 × 7 table.

**C++ solution**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        // Every path has exactly m-1 Downs and n-1 Rights, so it is fixed by choosing
        // which of the N = m+n-2 moves are Downs: answer = C(N, m-1) = C(N, n-1)
        int N = m + n - 2;
        int k = min(m - 1, n - 1);      // use the smaller side so the loop is shortest
        long long res = 1;              // 64-bit: res * (N-k+i) can exceed 2^31 - 1
        for (int i = 1; i <= k; ++i) {
            res = res * (N - k + i);    // multiply first ...
            res /= i;                   // ... then divide: res is now C(N-k+i, i), exact
        }
        return (int)res;                // the problem guarantees the answer <= 2 * 10^9
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
    int uniquePaths(int m, int n) {
        // Every path has exactly m-1 Downs and n-1 Rights, so it is fixed by choosing
        // which of the N = m+n-2 moves are Downs: answer = C(N, m-1) = C(N, n-1)
        int N = m + n - 2;
        int k = min(m - 1, n - 1);      // use the smaller side so the loop is shortest
        long long res = 1;              // 64-bit: res * (N-k+i) can exceed 2^31 - 1
        for (int i = 1; i <= k; ++i) {
            res = res * (N - k + i);    // multiply first ...
            res /= i;                   // ... then divide: res is now C(N-k+i, i), exact
        }
        return (int)res;                // the problem guarantees the answer <= 2 * 10^9
    }
};

int main() {
    Solution sol;

    cout << "Example 1: " << sol.uniquePaths(3, 7) << " (expected 28)\n";
    cout << "Example 2: " << sol.uniquePaths(3, 2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why this is the best:** With at most `99` arithmetic steps and constant memory there is nothing meaningful left to save. The trade-off is generality: the formula works only because every cell is open, so blocked cells (Unique Paths II) or weighted cells send you back to the DP.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| m = 3<br>n = 3 | 6 | Small square grid: 2 Downs and 2 Rights in any order, `C(4, 2) = 6`. |
| m = 4<br>n = 5 | 35 | Rectangular grid: 3 Downs among 7 moves, `C(7, 3) = 35`. |
| m = 7<br>n = 3 | 28 | Example 1 transposed: swapping `m` and `n` must not change the count. |
| m = 10<br>n = 10 | 48620 | Medium square grid where plain recursion already repeats a lot of work: `C(18, 9) = 48620`. |
| m = 23<br>n = 12 | 193536720 | Larger rectangle with a nine-digit answer, `C(33, 11)`. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single cell | m = 1<br>n = 1 | 1 | The start is the target, and the empty route counts as one path. |
| Single row at maximum width | m = 1<br>n = 100 | 1 | Only Right moves, so exactly one path. |
| Single column at maximum height | m = 100<br>n = 1 | 1 | Only Down moves, so exactly one path. |
| Two rows | m = 2<br>n = 100 | 100 | The single Down can happen in any of the 100 columns. |
| Tall narrow grid at maximum height | m = 100<br>n = 3 | 5050 | `C(101, 2) = 5050`. |
| Near the `2·10^9` cap | m = 17<br>n = 18 | 1166803110 | `C(33, 16)`; the last product before dividing overflows a 32-bit `int`. |
|   | m = 100<br>n = 7 | 1609344100 | Maximum height with the widest grid that stays under the cap: `C(105, 6)`. |

## Mistakes and edge cases

**Common mistakes**

- Computing `C(m + n - 2, m - 1)` from full factorials: `198!` overflows every integer type long before the division; build the value incrementally instead.
- Dividing before multiplying, or keeping `res` in a 32-bit `int`: `res / i` on its own is not always a whole number, and `res × (N - k + i)` can reach about `2.8·10^10`, overflowing `int`.
- Off-by-one moves: a path has `m - 1` Downs and `n - 1` Rights, not `m` and `n`; using `C(m + n, m)` gives `C(10, 3) = 120` instead of `28` for Example 1.
- Starting the DP with only `dp[0][0] = 1` and then reading `dp[i - 1][j]` and `dp[i][j - 1]` for every cell without handling row `0` and column `0`, which reads outside the table.

**Edge cases to check**

- `m = 1, n = 1`: the start is the target, so the answer is `1` (the empty path); `k = 0` and the loop never runs.
- `m = 1` or `n = 1` (for example `1 × 100`): only one straight path exists, so the answer is `1`, not `0` or `100`.
- `m = 2, n = 100`: the answer is `100`, one path for each column where the single Down can happen; it checks that `k = min(m, n) - 1 = 1` is used.
- `m = 17, n = 18`: the answer `1166803110` is close to the `2·10^9` cap and the last product `565722720 × 33` exceeds `2^31`, catching a 32-bit `res`.

## Practice next

- [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) · The same grid DP with blocked cells; the closed formula no longer works, so the table (or one rolling row) is required.
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) · The same right/down grid recurrence, but taking the minimum of the two neighbours plus the cell cost instead of adding counts.
- [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) · The 1D version of counting ways: `ways(i) = ways(i - 1) + ways(i - 2)`, summing over the possible last moves.
- [Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/) · Each entry is the sum of the two above it, which is this problem's table rotated 45 degrees; its entries are the binomial coefficients used in the formula.

## Takeaways

- To count paths in a grid where moves only go forward, `ways(cell)` is the sum of `ways` over the cells that can step into it; fill the table in an order where those cells come first.
- When every valid object is an arrangement of a fixed multiset of moves, the count is a binomial coefficient, so check for a formula before building a table.
- Compute `C(N, k)` incrementally with `res = res × (N - k + i) / i` in 64-bit, using the smaller of `k` and `N - k`; every intermediate is a whole number, so the division is exact.
