# Count Square Submatrices with All Ones

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/count-square-submatrices-with-all-ones/) · Pattern: **2D DP: largest square ending at each cell**

> Count how many `k × k` blocks of the 0/1 grid `matrix`, over every side length `k` and every position, contain only 1s.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation:
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:

Input: matrix =
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation:
There are 6 squares of side 1.
There is 1 square of side 2.
Total number of squares = 6 + 1 = 7.

Constraints:

- 1 <= arr.length <= 300

- 1 <= arr[0].length <= 300

- 0 <= arr[i][j] <= 1
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You are given a grid of 0s and 1s and must count every square block (any side length, any position) whose cells are all 1. A big block also contains smaller blocks, and each of those is counted separately: Example 1 counts 10 squares of side 1, 4 of side 2 and 1 of side 3 for a total of 15.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Look at where a square ends rather than where it starts. In Example 1 the bottom-right cell `(2,3)` is the corner of a 3 × 3, a 2 × 2 and a 1 × 1 square, so a cell that can end a square of side `s` automatically ends exactly `s` squares (sides `1..s`).

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `m, n <= 300` there are only `9·10^4` cells, but trying every top-left corner with every side and checking cells grows like `m·n·min(m,n)^2`, which is about `7·10^8` border checks on a 300 × 300 all-ones grid. Aim for a constant amount of work per cell, `O(m·n)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a 2D grid DP ("largest square ending at this cell"): the answer for a cell can be built from the answers of cells above and to the left, which are already known if you sweep the grid row by row, left to right.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

A `k × k` all-ones square with bottom-right corner `(i, j)` exists exactly when `matrix[i][j] = 1` and the cells above, to the left and diagonally up-left each end a square of side at least `k - 1`. So the largest side at `(i, j)` is `1 + min(up, left, diagonal)`, and the final answer is the sum of these sides over all cells.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Store `dp[i][j]` = the side of the largest all-ones square whose bottom-right corner is `(i, j)` (0 on a 0 cell, 1 on a 1 cell in the top row or left column), plus a running `total`. Since row `i` only reads row `i - 1` and the cell to its left, two arrays of length `n` (`prev` for the row above, `cur` for the current row) are enough.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `prev` to n zeros and `total` to 0.
For each row `i`, start `cur` as n zeros.
For each column `j` with `matrix[i][j] = 1`: if `i = 0` or `j = 0` set `cur[j]` to 1, otherwise set it to 1 plus the minimum of `prev[j]`, `cur[j - 1]` and `prev[j - 1]`.
Add `cur[j]` to `total`.
After the row, copy `cur` into `prev`.
Return `total`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is using `min` (not `max`) of all three neighbours, including the diagonal, and summing every `dp` value instead of taking the largest one. Check a single cell `[[0]]` (answer 0), a single row or column (answer = number of 1s), a checkerboard (no 2 × 2 squares) and a 300 × 300 all-ones grid (answer 9,045,050, still fits in `int`). Time is `O(m·n)`, extra space `O(n)` (or `O(1)` if you overwrite `matrix`).

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "return how many square submatrices have all ones" with Example 1 adding 10 + 4 + 1 | squares of every size count separately, so look for a per-cell number that counts several nested squares at once. |
| "square" rather than rectangle | a square is fixed by its bottom-right corner and side, and a `k × k` square contains three overlapping `(k - 1) × (k - 1)` squares ending at the top, left and diagonal neighbours: overlapping subproblems on a grid. |
| "0 <= arr[i][j] <= 1" | a single 0 destroys every square that contains it, so a cell holding 0 ends no square at all. |
| "1 <= arr.length, arr[0].length <= 300" | at most `9·10^4` cells, so one constant-time update per cell is trivial, while enumerating corners and sides is not. |

### What the constraints tell you

With `m, n <= 300` there are at most `9·10^4` cells. Growing a square from every top-left corner and checking only each new border costs `684,037,550` border iterations (about `1.4·10^9` cell reads) on a 300 × 300 all-ones grid, around a second or more in C++, while one `O(1)` update per cell is just `9·10^4` steps. So the target is `O(m·n)`.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most direct way to count the squares?**

<details>
<summary>Answer</summary>

Stand on each cell `(i, j)` as a top-left corner and try sides `k = 1, 2, 3, …` while the square fits, counting every side whose cells are all 1. In Example 2 the corner `(1,0)` gives the 1 × 1 and the 2 × 2 square made of rows 1-2, columns 0-1.

</details>

**Q2. Once a side `k` fails from some corner, do I need to try `k + 1`?**

<details>
<summary>Answer</summary>

No. The `(k + 1) × (k + 1)` square from the same corner contains the `k × k` one, so it contains the same 0. Each corner therefore contributes a run of sides `1..s` and then stops, but different corners still re-read the same cells over and over.

</details>

**Q3. What if I anchor each square at its bottom-right corner instead?**

<details>
<summary>Answer</summary>

Then a cell that ends a square of side `s` also ends squares of sides `1..s`, so it contributes exactly `s` to the answer. In Example 1 the cell `(2,3)` ends the 3 × 3 square, so it contributes 3 (sides 1, 2 and 3); the answer is the sum of these largest sides over all cells.

</details>

**Q4. How can the largest side at `(i, j)` be computed from cells already processed?**

<details>
<summary>Answer</summary>

A `k × k` square ending at `(i, j)` is the cell itself plus three overlapping `(k - 1) × (k - 1)` squares ending at `(i - 1, j)`, `(i, j - 1)` and `(i - 1, j - 1)`. So if `matrix[i][j] = 1`, the largest side is `1 + min(up, left, diagonal)`: the weakest neighbour limits how far the square can grow.

</details>

**Q5. Do I need the whole `m × n` table of sides?**

<details>
<summary>Answer</summary>

No. Row `i` only reads row `i - 1` (`up` and `diagonal`) and its own cell to the left, so keeping `prev` (the row above) and `cur` (the row being filled) is enough, cutting extra memory to `O(n)`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Grow a square from every top-left corner](#1-brute-force-grow-a-square-from-every-top-left-corner) | `O(m·n·min(m,n)^2)` | `O(1)` |
| 2 | [Better: 2D DP: largest square ending at each cell](#2-better-2d-dp-largest-square-ending-at-each-cell) | `O(m·n)` | `O(m·n)` |
| 3 | [Optimal: Space-optimised DP with two rows](#3-optimal-space-optimised-dp-with-two-rows) | `O(m·n)` | `O(n)` |

### 1. Brute force: Grow a square from every top-left corner

> **Where you start:** The problem literally asks to count squares, so the first idea is to stand on each cell as a top-left corner and try sides 1, 2, 3, … until the square stops being all ones.

**Idea.** For each top-left corner `(i, j)`, grow the side `k` while the `k × k` square fits inside the `m × n` grid. Because the `(k - 1) × (k - 1)` part was verified in the previous round, only the new bottom row and right column need to be checked. As soon as a 0 appears we stop, since every larger square from the same corner contains that 0. Each successful `k` is a distinct square, and every square has exactly one top-left corner, so nothing is counted twice or missed.

**Steps**

1. Set `count` to 0.
2. For every cell `(i, j)`, treat it as the top-left corner and start with side `k = 1`.
3. While the `k × k` square fits (`i + k - 1 < m` and `j + k - 1 < n`), check the `k` cells of its new bottom row and the `k` cells of its new right column.
4. If any of them is 0, stop growing from this corner.
5. Otherwise add 1 to `count` and try `k + 1`.
6. After all corners, return `count`.

**Pseudocode**

```text
 1 │ function countSquares(matrix)
 2 │   m ← number of rows in matrix
 3 │   n ← number of columns in matrix
 4 │   count ← 0
 5 │   for i ← 0 to m - 1  // top row of the square
 6 │     for j ← 0 to n - 1  // left column of the square
 7 │       k ← 1  // side length being tested
 8 │       while i + k - 1 < m and j + k - 1 < n  // the k × k square must fit in the grid
 9 │         ok ← true
10 │         for t ← 0 to k - 1  // the (k-1) × (k-1) part was already verified
11 │           if matrix[i + k - 1][j + t] = 0 or matrix[i + t][j + k - 1] = 0  // new bottom row / right column
12 │             ok ← false
13 │         if not ok
14 │           break  // every bigger square from (i, j) contains this 0 too
15 │         count ← count + 1  // the k × k square at (i, j) is all ones
16 │         k ← k + 1
17 │   return count
```

**Time complexity: `O(m·n·min(m,n)^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Corner loops (lines 5-6) | m·n corners | Every cell is tried once as the top-left corner of a square. |
| Side growth loop (lines 8-16) | up to min(m − i, n − j) sides per corner | The side grows until the square leaves the grid or a 0 appears; on an all-ones grid it reaches the grid edge. |
| Border check (lines 10-12) | k iterations × 2 cell reads for side k | Only the new bottom row and right column are read, because the smaller square was already verified. |

- **Adding it up:** A corner whose largest side is s costs 1 + 2 + … + s = s(s+1)/2 border iterations; with s ≤ min(m,n) for each of the m·n corners the total is at most m·n·min(m,n)^2 / 2 = O(m·n·min(m,n)^2).
- **Best vs worst case:** Best case: an all-zeros grid, where every corner fails at k = 1, so only O(m·n) work. Worst case: an all-ones grid, where every corner grows until it hits the grid edge.
- **At the maximum input:** 300 × 300 all ones → 684,037,550 border iterations (about 1.4·10^9 cell reads), roughly a second or more in C++, which is at the edge of the time limit.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| Scalars m, n, count, i, j, k, ok, t (lines 2-12) | O(1) | Only a fixed number of counters is kept; no table is built. |

- **Adding it up:** O(1); nothing grows with the input size.
- **Not counted:** The input matrix is only read, never copied, and the output is a single integer.

**Dry run** on `matrix = [[1,1,0],[1,1,1]]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | The grid has m = 2 rows and n = 3 columns; no square has been counted yet, so count = 0. | `m = 2`<br>`n = 3`<br>`count = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` |
| 2 | 15 | Corner (0,0), k = 1: the single cell matrix[0][0] is 1, so the 1 × 1 square is all ones and count becomes 1. | `count = 1`<br>`i = 0`<br>`j = 0`<br>`k = 1`<br>`ok = true`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,0]) |
| 3 | 15 | Still corner (0,0), now k = 2: the new bottom row (1,0),(1,1) and right column (0,1),(1,1) are all 1, so the 2 × 2 square counts; count = 2. | `count = 2`<br>`k = 2` |
| 4 | 8 | k = 3: i + k - 1 = 2 is not < m = 2, so a 3 × 3 square does not fit and the while loop ends for corner (0,0). | `k = 3` |
| 5 | 15 | Corner (0,1), k = 1: matrix[0][1] = 1, so count = 3. | `count = 3`<br>`j = 1`<br>`k = 1`<br>`ok = true`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,1]) |
| 6 | 12 | Corner (0,1), side k = 2, t = 0: the right-column cell matrix[0][2] is 0, so ok becomes false. (matrix[1][1] = 1 on the bottom row is fine.) | `k = 2`<br>`ok = false`<br>`t = 0` |
| 7 | 14 | t = 1 also ran (matrix[1][2] = 1), but ok is already false, so we break: any 3 × 3 square from (0,1) would also contain the 0 at (0,2). | (no change) |
| 8 | 14 | Corner (0,2), k = 1: the cell itself, matrix[0][2], is 0, so ok is false and we break immediately; no square of any size starts here. | `j = 2`<br>`k = 1`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,2]) |
| 9 | 15 | Row 1 now. Corner (1,0), k = 1: matrix[1][0] = 1, so count = 4. | `count = 4`<br>`i = 1`<br>`j = 0`<br>`ok = true`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,0]) |
| 10 | 8 | k = 2: i + k - 1 = 2 is not < m = 2, so no 2 × 2 square can start on the last row; move to the next corner. | `k = 2` |
| 11 | 15 | Corner (1,1), k = 1: matrix[1][1] = 1, so count = 5. Side 2 will not fit below row 1 (same exit as before, skipped here). | `count = 5`<br>`j = 1`<br>`k = 1`<br>`ok = true`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,1]) |
| 12 | 15 | Corner (1,2), k = 1: matrix[1][2] = 1, so count = 6. This was the last corner. | `count = 6`<br>`j = 2`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,2]) |
| 13 | 17 | All 6 corners are done. count = 6: five 1 × 1 squares and one 2 × 2 square. | `matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` |

**Result:** 6 — five cells hold a 1 (five 1 × 1 squares) and the block in rows 0-1, columns 0-1 is the only all-ones 2 × 2 square; every square is counted once from its top-left corner.

**C++ solution**

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();         // number of rows
        int n = matrix[0].size();      // number of columns (at least 1 by the constraints)
        int count = 0;                 // all-ones squares found so far
        for (int i = 0; i < m; i++) {          // top row of the square
            for (int j = 0; j < n; j++) {      // left column of the square
                // grow the side k while the k x k square still fits inside the grid
                for (int k = 1; i + k - 1 < m && j + k - 1 < n; k++) {
                    bool ok = true;
                    // the (k-1) x (k-1) part was verified in the previous round,
                    // so only the new bottom row and right column need checking
                    for (int t = 0; t < k; t++) {
                        if (matrix[i + k - 1][j + t] == 0 || matrix[i + t][j + k - 1] == 0) {
                            ok = false;
                        }
                    }
                    if (!ok) break;    // every larger square from (i, j) contains this 0 too
                    count++;           // the k x k square with top-left (i, j) is all ones
                }
            }
        }
        return count;
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
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();         // number of rows
        int n = matrix[0].size();      // number of columns (at least 1 by the constraints)
        int count = 0;                 // all-ones squares found so far
        for (int i = 0; i < m; i++) {          // top row of the square
            for (int j = 0; j < n; j++) {      // left column of the square
                // grow the side k while the k x k square still fits inside the grid
                for (int k = 1; i + k - 1 < m && j + k - 1 < n; k++) {
                    bool ok = true;
                    // the (k-1) x (k-1) part was verified in the previous round,
                    // so only the new bottom row and right column need checking
                    for (int t = 0; t < k; t++) {
                        if (matrix[i + k - 1][j + t] == 0 || matrix[i + t][j + k - 1] == 0) {
                            ok = false;
                        }
                    }
                    if (!ok) break;    // every larger square from (i, j) contains this 0 too
                    count++;           // the k x k square with top-left (i, j) is all ones
                }
            }
        }
        return count;
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
```

</details>

**Why move on:** On a 300 × 300 all-ones grid it performs `684,037,550` border iterations because overlapping squares from different corners re-read the same cells again and again. That is borderline-to-too-slow, and none of the work done for one corner is reused by its neighbours.

### 2. Better: 2D DP: largest square ending at each cell

> **How you get here:** The brute force re-checks the same cells for every corner. But a `k × k` all-ones square whose bottom-right corner is `(i, j)` is exactly the cell plus three overlapping `(k - 1) × (k - 1)` squares ending at `(i - 1, j)`, `(i, j - 1)` and `(i - 1, j - 1)`, so each cell's answer can be built from its neighbours' answers.

**Idea.** Let `dp[i][j]` be the side of the largest all-ones square whose bottom-right corner is `(i, j)`. It is 0 when `matrix[i][j] = 0`, 1 on the top row or left column, and otherwise `1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])`, because the smallest of the three neighbouring squares is what limits how far the new square can extend. A cell with `dp[i][j] = s` is the bottom-right corner of exactly `s` squares (sides `1..s`), and every square has exactly one bottom-right corner, so the answer is the sum of all `dp` values. Filling rows top to bottom and columns left to right guarantees the three neighbours are ready when needed.

**Steps**

1. Create an `m × n` table `dp` of zeros and set `total` to 0.
2. Visit cells row by row, left to right.
3. If `matrix[i][j]` is 0, `dp[i][j]` stays 0.
4. Else if `i = 0` or `j = 0`, set `dp[i][j]` to 1.
5. Otherwise set `dp[i][j]` to 1 plus the minimum of the cell above, the cell to the left and the cell diagonally up-left.
6. Add `dp[i][j]` to `total`, and return `total` at the end.

**Pseudocode**

```text
 1 │ function countSquares(matrix)
 2 │   m ← number of rows in matrix
 3 │   n ← number of columns in matrix
 4 │   dp ← m × n table filled with 0  // dp[i][j] = side of the largest all-ones square with bottom-right corner (i, j)
 5 │   total ← 0
 6 │   for i ← 0 to m - 1
 7 │     for j ← 0 to n - 1
 8 │       if matrix[i][j] = 0
 9 │         dp[i][j] ← 0  // no square can end on a 0
10 │       else if i = 0 or j = 0
11 │         dp[i][j] ← 1  // on the top row or left column only a 1 × 1 square fits
12 │       else
13 │         dp[i][j] ← 1 + min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1])  // the weakest neighbour limits the side
14 │       total ← total + dp[i][j]  // side s means squares of sides 1..s end here
15 │   return total
```

**Time complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table creation (line 4) | m·n writes | Every entry of dp is initialised to 0 once. |
| Cell loops (lines 6-7) | m·n iterations | Each cell is visited exactly once in row-major order. |
| Per-cell update (lines 8-14) | O(1) per cell | At most one comparison, a minimum of three already-computed values and one addition. |

- **Adding it up:** m·n (setup) + m·n × O(1) (updates) = O(m·n); both pieces are linear in the number of cells.
- **At the maximum input:** 300 × 300 → 9·10^4 cells with a handful of operations each, well under a millisecond.

**Space complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table dp (line 4) | m·n integers | One largest-side value is stored for every cell. |
| Scalars m, n, total, i, j (lines 2-7) | O(1) | A fixed number of counters. |

- **Adding it up:** O(m·n) + O(1) = O(m·n); the table dominates.
- **Not counted:** The input matrix is not counted. At the 300 × 300 limit the table is 9·10^4 ints, about 360 KB.

**Dry run** on `matrix = [[1,1,0],[1,1,1]]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 5 | Create a 2 × 3 table dp of zeros and set total = 0. dp[i][j] will hold the side of the biggest all-ones square whose bottom-right corner is (i, j). | `m = 2`<br>`n = 3`<br>`total = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]`<br>`dp = 2×3 table: [0, 0, 0] [0, 0, 0]` |
| 2 | 11 | matrix[0][0] = 1 on the top row, so only a 1 × 1 square can end here: dp[0][0] = 1. | `i = 0`<br>`j = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,0])<br>`dp = 2×3 table: [1, 0, 0] [0, 0, 0]` (i,j→[0,0]) |
| 3 | 14 | Add dp[0][0] = 1 (one 1 × 1 square ends here): total = 1. | `total = 1` |
| 4 | 11 | matrix[0][1] = 1 on the top row, so only a 1 × 1 square can end here: dp[0][1] = 1. | `j = 1`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,1])<br>`dp = 2×3 table: [1, 1, 0] [0, 0, 0]` (i,j→[0,1]) |
| 5 | 14 | Add dp[0][1] = 1 (one 1 × 1 square ends here): total = 2. | `total = 2` |
| 6 | 9 | matrix[0][2] = 0, so no square can have its bottom-right corner here: dp[0][2] = 0. | `j = 2`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,2])<br>`dp = 2×3 table: [1, 1, 0] [0, 0, 0]` (i,j→[0,2]) |
| 7 | 14 | dp[0][2] = 0 adds nothing; total stays 2. | (no change) |
| 8 | 11 | matrix[1][0] = 1 on the left column, so only a 1 × 1 square can end here: dp[1][0] = 1. | `i = 1`<br>`j = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,0])<br>`dp = 2×3 table: [1, 1, 0] [1, 0, 0]` (i,j→[1,0]) |
| 9 | 14 | Add dp[1][0] = 1 (one 1 × 1 square ends here): total = 3. | `total = 3` |
| 10 | 13 | matrix[1][1] = 1 and it is an inner cell: dp[1][1] = 1 + min(up 1, left 1, diagonal 1) = 2; all three neighbours support a 1 × 1 square, so a 2 × 2 square ends here. | `j = 1`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,1])<br>`dp = 2×3 table: [1, 1, 0] [1, 2, 0]` (i,j→[1,1]) |
| 11 | 14 | Add dp[1][1] = 2: both the 1 × 1 and the 2 × 2 square end at (1,1), so total = 5. | `total = 5` |
| 12 | 13 | matrix[1][2] = 1 and it is an inner cell: dp[1][2] = 1 + min(up 0, left 2, diagonal 1) = 1; the 0 directly above caps the square at 1 × 1 even though the left neighbour supports side 2. | `j = 2`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,2])<br>`dp = 2×3 table: [1, 1, 0] [1, 2, 1]` (i,j→[1,2]) |
| 13 | 14 | Add dp[1][2] = 1 (one 1 × 1 square ends here): total = 6. | `total = 6` |
| 14 | 15 | Every cell is processed; total = sum of dp = 6. | `matrix = 2×3 table: [1, 1, 0] [1, 1, 1]`<br>`dp = 2×3 table: [1, 1, 0] [1, 2, 1]` |

**Result:** 6 — the dp table ends as [[1,1,0],[1,2,1]], and its sum counts each square exactly once at its bottom-right corner (the 2 at (1,1) covers both the 1 × 1 and the 2 × 2 square there).

**C++ solution**

```cpp
class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();         // number of rows
        int n = matrix[0].size();      // number of columns
        // dp[i][j] = side of the largest all-ones square whose bottom-right corner is (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int total = 0;                 // sum of all dp values = number of squares
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;              // no square can end on a 0
                } else if (i == 0 || j == 0) {
                    dp[i][j] = 1;              // top row / left column: only a 1x1 square fits
                } else {
                    // a k x k square here needs (k-1) x (k-1) squares ending above,
                    // to the left and diagonally up-left; the smallest one limits k
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
                total += dp[i][j];             // side s means squares of sides 1..s end here
            }
        }
        return total;
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
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();         // number of rows
        int n = matrix[0].size();      // number of columns
        // dp[i][j] = side of the largest all-ones square whose bottom-right corner is (i, j)
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int total = 0;                 // sum of all dp values = number of squares
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 0) {
                    dp[i][j] = 0;              // no square can end on a 0
                } else if (i == 0 || j == 0) {
                    dp[i][j] = 1;              // top row / left column: only a 1x1 square fits
                } else {
                    // a k x k square here needs (k-1) x (k-1) squares ending above,
                    // to the left and diagonally up-left; the smallest one limits k
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
                total += dp[i][j];             // side s means squares of sides 1..s end here
            }
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
```

</details>

**Why move on:** It is fast (`9·10^4` cells), but it keeps the whole `m × n` table even though row `i` only ever reads row `i - 1` and the cells to its left in row `i`.

### 3. Optimal: Space-optimised DP with two rows

> **How you get here:** In the table version `dp[i][j]` only reads `dp[i - 1][j]` and `dp[i - 1][j - 1]` from the previous row and `dp[i][j - 1]` from the current row, so every row older than `i - 1` is dead weight.

**Idea.** Keep `prev`, the dp values of the row above, and `cur`, the row being filled. For each `matrix[i][j] = 1`, `cur[j]` is 1 on the top row or left column and `1 + min(prev[j], cur[j - 1], prev[j - 1])` otherwise, while a 0 cell keeps `cur[j] = 0`. Each `cur[j]` is added to `total`, and after the row `prev ← cur`. The recurrence and the evaluation order are exactly those of the 2D table, so the result is identical, but only two rows are alive at any time.

**Steps**

1. Set `prev` to `n` zeros and `total` to 0.
2. For each row `i`, start `cur` as `n` zeros.
3. For each column `j` with `matrix[i][j] = 1`, set `cur[j]` to 1 if `i = 0` or `j = 0`, else to 1 plus the minimum of `prev[j]`, `cur[j - 1]` and `prev[j - 1]`.
4. Add `cur[j]` to `total`.
5. When the row is finished, set `prev` to `cur`.
6. Return `total`.

**Pseudocode**

```text
 1 │ function countSquares(matrix)
 2 │   m ← number of rows in matrix
 3 │   n ← number of columns in matrix
 4 │   prev ← array of n zeros  // dp values of the row above (nothing is above row 0)
 5 │   total ← 0
 6 │   for i ← 0 to m - 1
 7 │     cur ← array of n zeros  // dp values of row i; a 0 cell simply keeps 0
 8 │     for j ← 0 to n - 1
 9 │       if matrix[i][j] = 1
10 │         if i = 0 or j = 0
11 │           cur[j] ← 1  // border cell: only a 1 × 1 square fits
12 │         else
13 │           cur[j] ← 1 + min(prev[j], cur[j - 1], prev[j - 1])  // up, left, diagonal
14 │         total ← total + cur[j]  // side s means s squares end here
15 │     prev ← cur  // row i becomes the row above for row i + 1
16 │   return total
```

**Time complexity: `O(m·n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Row loop with fresh cur (lines 6-7) | m rows × O(n) | Each row allocates and zeroes an array of length n. |
| Cell loop and update (lines 8-14) | m·n iterations × O(1) | Each cell does at most one comparison, a minimum of three values and one addition. |
| Row hand-over prev ← cur (line 15) | m rows × O(n) | Copying n values once per row. |

- **Adding it up:** m·n (allocation) + m·n·O(1) (updates) + m·n (copies) = O(m·n).
- **At the maximum input:** 300 × 300 → about 9·10^4 cell updates plus 600 row copies of 300 ints, well under a millisecond.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Arrays prev and cur (lines 4, 7) | 2·n integers | Only the previous and current rows of dp are kept. |
| Scalars m, n, total, i, j | O(1) | A fixed number of counters. |

- **Adding it up:** 2·n + O(1) = O(n).
- **Not counted:** The input matrix is only read, not counted. Storing dp in matrix itself would make the extra space O(1) but would modify the input.

**Dry run** on `matrix = [[1,1,0],[1,1,1]]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 5 | prev starts as 3 zeros because there is no row above row 0, and total = 0. | `m = 2`<br>`n = 3`<br>`total = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]`<br>`prev = [0, 0, 0]` |
| 2 | 7 | Start row 0 with a fresh cur = [0, 0, 0]; cells that are 0 will simply keep cur[j] = 0. | `i = 0`<br>`cur = [0, 0, 0]` |
| 3 | 14 | matrix[0][0] = 1 on the top row, so cur[0] = 1 (line 11) and total becomes 1. | `total = 1`<br>`j = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,0])<br>`prev = [0, 0, 0]` (j→0)<br>`cur = [1, 0, 0]` (j→0) |
| 4 | 14 | matrix[0][1] = 1 on the top row, so cur[1] = 1 (line 11) and total becomes 2. | `total = 2`<br>`j = 1`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,1])<br>`prev = [0, 0, 0]` (j→1)<br>`cur = [1, 1, 0]` (j→1) |
| 5 | 9 | matrix[0][2] = 0, so the if fails and cur[2] stays 0; total stays 2. | `j = 2`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[0,2])<br>`prev = [0, 0, 0]` (j→2)<br>`cur = [1, 1, 0]` (j→2) |
| 6 | 15 | Row 0 finished: prev ← cur, so prev = [1, 1, 0] is now the row above. | `matrix = 2×3 table: [1, 1, 0] [1, 1, 1]`<br>`prev = [1, 1, 0]`<br>`cur = [1, 1, 0]` |
| 7 | 7 | Start row 1 with a fresh cur = [0, 0, 0]; cells that are 0 will simply keep cur[j] = 0. | `i = 1`<br>`cur = [0, 0, 0]` |
| 8 | 14 | matrix[1][0] = 1 on the left column, so cur[0] = 1 (line 11) and total becomes 3. | `total = 3`<br>`j = 0`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,0])<br>`prev = [1, 1, 0]` (j→0)<br>`cur = [1, 0, 0]` (j→0) |
| 9 | 13 | matrix[1][1] = 1: cur[1] = 1 + min(prev[1] 1, cur[0] 1, prev[0] 1) = 2; a 2 × 2 square ends at (1,1). | `j = 1`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,1])<br>`prev = [1, 1, 0]` (j→1)<br>`cur = [1, 2, 0]` (j→1) |
| 10 | 14 | Add cur[1] = 2 to total, which becomes 5. | `total = 5` |
| 11 | 13 | matrix[1][2] = 1: cur[2] = 1 + min(prev[2] 0, cur[1] 2, prev[1] 1) = 1; prev[2] = 0 (the 0 above) caps it at 1 even though cur[1] = 2. | `j = 2`<br>`matrix = 2×3 table: [1, 1, 0] [1, 1, 1]` (i,j→[1,2])<br>`prev = [1, 1, 0]` (j→2)<br>`cur = [1, 2, 1]` (j→2) |
| 12 | 14 | Add cur[2] = 1 to total, which becomes 6. | `total = 6` |
| 13 | 15 | Row 1 finished: prev = [1, 2, 1]. | `matrix = 2×3 table: [1, 1, 0] [1, 1, 1]`<br>`prev = [1, 2, 1]`<br>`cur = [1, 2, 1]` |
| 14 | 16 | All rows are done; total = 6. | (no change) |

**Result:** 6 — the two rows of dp were [1,1,0] and [1,2,1], the same values as the full table, and their sum counts each all-ones square once at its bottom-right corner.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Time cannot beat `O(m·n)` because every cell must be read at least once: flipping any single cell can change the answer. Space can drop to `O(1)` by writing the dp values into `matrix` itself, but that destroys the caller's input.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| matrix = [[1,1,0,0],[1,1,1,1],[0,1,1,1],[0,1,1,1]] | 18 | A 3 × 3 block of ones in the bottom-right overlaps a separate 2 × 2 block in the top-left. |
| matrix = [[1,0,1,1],[1,1,1,1],[1,1,1,0]] | 13 | Zeros in opposite corners cap the squares at side 2 while several 2 × 2 squares overlap. |
| matrix = [[1,1,1,1,1],[1,1,0,1,1],[1,1,1,1,1]] | 18 | A single 0 in the middle kills every 3 × 3 square and the 2 × 2 squares that would contain it. |
| matrix = [[0,1,1,1],[1,1,1,1],[1,1,1,1],[1,1,1,0]] | 23 | A 4 × 4 grid whose two corner zeros stop the full 4 × 4 square but still allow two 3 × 3 squares. |
| matrix = [[1,1],[1,1],[0,1],[1,1],[1,1]] | 11 | Tall 5 × 2 grid where a 0 in the middle row splits the 2 × 2 squares into a top and a bottom group. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single cell one | matrix = [[1]] | 1 | The minimum grid size with exactly one 1 × 1 square. |
| Single cell zero | matrix = [[0]] | 0 | No squares at all, so the answer is 0. |
| All zeros | matrix = [[0,0,0],[0,0,0]] | 0 | Every dp value is 0 and the answer is 0. |
| Single row | matrix = [[1,1,0,1,1,1]] | 5 | Only 1 × 1 squares are possible, so the answer is the number of 1s. |
| Single column | matrix = [[1],[1],[1],[0],[1]] | 4 | Again only 1 × 1 squares, so the answer is the number of 1s. |
| All ones | matrix = [[1,1,1,1],[1,1,1,1],[1,1,1,1],[1,1,1,1]] | 30 | 16 + 9 + 4 + 1 = 30; at the 300 × 300 maximum the answer is 9,045,050, which still fits in an int. |
| Checkerboard | matrix = [[1,0,1],[0,1,0],[1,0,1]] | 5 | No two 1s form a 2 × 2 block, so only the five 1 × 1 squares count. |

## Mistakes and edge cases

**Common mistakes**

- Taking `max` instead of `min` of the three neighbours: in `[[1,0],[1,1]]` the cell `(1,1)` would get `1 + max(0,1,1) = 2` and count a 2 × 2 square that contains the 0.
- Forgetting the diagonal neighbour: in `[[0,1],[1,1]]` both `up` and `left` of `(1,1)` are 1, so `1 + min(up, left) = 2` would count a 2 × 2 square even though `(0,0)` is 0.
- Returning the largest `dp` value (or its square, as in Maximal Square) instead of the sum of all `dp` values: Example 1 would give 3 instead of 15.
- Reading `dp[i - 1][...]` or `dp[...][j - 1]` on the top row or left column without a border check, which goes out of bounds; in a single-array version, overwriting `dp[j - 1]` before saving the old value loses the diagonal.

**Edge cases to check**

- `matrix = [[0]]`: the only cell is 0, so the answer must be 0, not 1.
- A single row such as `[[1,1,0,1,1,1]]` or a single column: no square bigger than 1 × 1 fits, so the answer is the count of 1s (5 here); this checks the border case `i = 0` or `j = 0`.
- A checkerboard like `[[1,0,1],[0,1,0],[1,0,1]]`: every inner 1 has a 0 neighbour, so all dp values stay at most 1 and the answer is 5.
- A 300 × 300 all-ones grid: the answer is 1^2 + 2^2 + … + 300^2 = 9,045,050, which confirms an `int` total is safe and that the solution must be `O(m·n)` rather than enumerating squares.

## Practice next

- [Maximal Square](https://leetcode.com/problems/maximal-square/) · Uses the identical `1 + min(up, left, diagonal)` recurrence, but returns the area of the largest square instead of summing all sides.
- [Count Submatrices With All Ones](https://leetcode.com/problems/count-submatrices-with-all-ones/) · The rectangle version of this problem: count all-ones submatrices by anchoring each one at its bottom-right corner, using row heights instead of a min of three neighbours.
- [Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/) · Finds the largest all-ones rectangle by building per-row heights from the row above, the same row-by-row grid sweep with only the previous row kept.

## Takeaways

- To count shapes in a grid without double counting, anchor every shape at one canonical cell (here the bottom-right corner) and count per cell.
- A "largest structure ending here" DP often turns counting into a sum: if size `s` ending at a cell implies `s` nested structures, add up the dp values.
- When a structure needs all of its overlapping sub-structures to be valid, combine the neighbours with `min`, not `max`.
- A grid DP that only reads the previous row and the current row can be rolled into two arrays of length `n`.
