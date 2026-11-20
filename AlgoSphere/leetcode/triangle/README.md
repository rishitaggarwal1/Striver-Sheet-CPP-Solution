# Triangle

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/triangle/) · Pattern: **2D grid DP on a triangle, filled bottom-up**

> Find the smallest sum of a top-to-bottom path through `triangle`, where from index `j` in one row you may step to index `j` or `j + 1` in the next row.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:

Input: triangle = [[-10]]
Output: -10

Constraints:

- 1 <= triangle.length <= 200

- triangle[0].length == 1

- triangle[i].length == triangle[i - 1].length + 1

- -10^4 <= triangle[i][j] <= 10^4

Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You start on the single number at the top and walk down one row at a time until you reach the bottom row; from position `i` in a row you may step only to position `i` or `i + 1` in the next row. Add up every number you stand on and return the smallest total any such walk can reach.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Taking the smaller neighbour each time happens to work on Example 1 (2 → 3 → 5 → 1), but on `[[1],[2,3],[9,8,1]]` it goes 1 → 2 → 8 = 11 while 1 → 3 → 1 = 5. Also notice that the 5 at row 2, index 1 can be reached from both the 3 and the 4 above it: different paths share the same lower part.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `triangle.length` up to 200 there are 2^199 top-to-bottom paths, so trying them all is hopeless. But the triangle has only 200 · 201 / 2 = 20,100 cells, so any method that does constant work per cell, `O(n^2)`, is instant.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is dynamic programming on a grid (a triangle-shaped one): the best answer for a cell is built from the best answers of the two cells it can step to, so solve cells in an order where those two are already known.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

The cheapest path from cell `(i, j)` down to the bottom does not depend on how you reached `(i, j)`: it is `triangle[i][j] + min(best(i + 1, j), best(i + 1, j + 1))`. Solving from the bottom row upward makes everything funnel into the single apex, so the answer is one cell instead of a minimum over the whole last row.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep one array `dp` of length `n` (the number of rows). It starts as a copy of the last row; after you finish row `i`, `dp[j]` is the minimum path sum from `(i, j)` to the bottom for every `j <= i`, and at the end `dp[0]` is the answer.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Copy the last row of `triangle` into `dp`.
For each row `i` from `n - 2` up to `0`:
For each column `j` from `0` to `i`:
Set `dp[j]` to `triangle[i][j] + min(dp[j], dp[j + 1])`.
Going left to right is safe because `dp[j + 1]` still holds the row-below value.
Return `dp[0]`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is overwriting `dp[j]` in place: it works only because cell `(i, j)` reads `dp[j]` and `dp[j + 1]`, and `dp[j + 1]` is overwritten later in the same pass; going right to left would break it. Check a single-row triangle (the loop never runs, the answer is `triangle[0][0]`) and negative values (you can never stop early or prune by the running sum). Time is `O(n^2)` for the `n(n + 1)/2` cells and extra space is `O(n)` for `dp`, which meets the follow-up.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "you may move to either index i or index i + 1 on the next row" | every cell has exactly two successors, so a cell's best answer is built from two smaller subproblems: grid DP. |
| The 5 at `(2, 1)` in Example 1 is reachable from both `(1, 0)` and `(1, 1)` | paths overlap, so plain recursion solves the same cells repeatedly: memoise or tabulate. |
| "1 <= triangle.length <= 200" | only about 20,100 cells but 2^199 paths: per-cell work is fine, per-path work is not. |
| "Follow up: ... only O(n) extra space" | each row depends only on the row below, so a single 1D array of length n is enough. |

### What the constraints tell you

With n = 200 rows there are 2^199 ≈ 8·10^59 distinct paths, so enumerating them is impossible. The triangle has only n(n + 1)/2 = 20,100 cells, so an `O(n^2)` DP with constant work per cell is about 2·10^4 operations, effectively instant; the follow-up additionally asks to keep extra memory to `O(n)` = 200 integers.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most direct way to get the minimum?**

<details>
<summary>Answer</summary>

Try every path: from the apex, branch into index `j` and `j + 1` on every row and keep the smallest total. With n rows that is 2^(n - 1) paths, only 8 for Example 1 but 2^199 at the limit.

</details>

**Q2. Does stepping to the smaller neighbour each time work?**

<details>
<summary>Answer</summary>

No. On `[[1],[2,3],[9,8,1]]` greedy picks 2 and then 8 for 11, but 1 → 3 → 1 costs 5. A cheap cell now can lead into an expensive region, so each choice must know the best cost of everything below it.

</details>

**Q3. What do I really need to know about the part of the path below cell `(i, j)`?**

<details>
<summary>Answer</summary>

Only its minimum cost. If `best(i, j)` is the cheapest path from `(i, j)` to the bottom, then `best(i, j) = triangle[i][j] + min(best(i + 1, j), best(i + 1, j + 1))`, with `best(n - 1, j) = triangle[n - 1][j]`, and the answer is `best(0, 0)`.

</details>

**Q4. Why is that recursion slow, and how many different subproblems are there?**

<details>
<summary>Answer</summary>

In Example 1, `best(2, 1)` is needed by both `(1, 0)` and `(1, 1)`, and the sharing compounds row after row, so recursion makes about 2^n calls. Yet there are only n(n + 1)/2 = 10 distinct cells in Example 1, so remembering each answer once gives `O(n^2)`.

</details>

**Q5. Should the table be filled top-down or bottom-up?**

<details>
<summary>Answer</summary>

Bottom-up: row `n - 1` is already solved (each cell is its own answer) and everything funnels into the single apex, so the answer is just `dp[0]`. Filling from the top would need boundary checks at `j = 0` and `j = i` and a final minimum over the whole bottom row.

</details>

**Q6. Do I need the whole table?**

<details>
<summary>Answer</summary>

No. Row `i` only reads row `i + 1`, so one array `dp` of length n works. Updating `dp[j]` left to right is safe because cell `(i, j)` reads `dp[j]` and `dp[j + 1]`, and `dp[j + 1]` has not been overwritten yet in this pass.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Plain recursion over both moves](#1-brute-force-plain-recursion-over-both-moves) | `O(2^n)` | `O(n)` |
| 2 | [Better: Top-down recursion with a memo table](#2-better-top-down-recursion-with-a-memo-table) | `O(n^2)` | `O(n^2)` |
| 3 | [Optimal: Bottom-up DP with one row array](#3-optimal-bottom-up-dp-with-one-row-array) | `O(n^2)` | `O(n)` |

### 1. Brute force: Plain recursion over both moves

> **Where you start:** Every cell offers exactly two moves, so the first idea is to try both from every cell and keep the cheaper total; it is a direct translation of the movement rule.

**Idea.** Define `f(i, j)` as the minimum path sum from cell `(i, j)` to the bottom row. On the bottom row (`i = n - 1`) the path is just the cell, so `f(n - 1, j) = triangle[n - 1][j]`. Above it, a path from `(i, j)` must continue through `(i + 1, j)` or `(i + 1, j + 1)`, so `f(i, j) = triangle[i][j] + min(f(i + 1, j), f(i + 1, j + 1))`. This is correct because any path from `(i, j)` is the cell itself followed by a path from one of those two cells, and the best total uses the best continuation. The answer is `f(0, 0)`.

**Steps**

1. Let `n` be the number of rows and call `f(0, 0)` at the apex.
2. In `f(i, j)`, if `i = n - 1`, return `triangle[i][j]`.
3. Otherwise compute `down = f(i + 1, j)` and `diag = f(i + 1, j + 1)`.
4. Return `triangle[i][j] + min(down, diag)`.
5. The value returned by `f(0, 0)` is the answer.

**Pseudocode**

```text
 1 │ function minimumTotal(triangle)
 2 │   n ← number of rows in triangle  // f reads n to detect the bottom row
 3 │   return f(0, 0)  // every path starts at the apex
 4 │ function f(i, j)  // cheapest path sum from cell (i, j) down to the bottom row
 5 │   if i = n - 1  // bottom row: the path is just this cell
 6 │     return triangle[i][j]
 7 │   down ← f(i + 1, j)  // step to index j on the next row
 8 │   diag ← f(i + 1, j + 1)  // step to index j + 1 on the next row
 9 │   best ← min(down, diag)
10 │   return triangle[i][j] + best
```

**Time complexity: `O(2^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup and first call (lines 2-3) | 1 × O(1) | Reads the row count once and starts the recursion at the apex. |
| Recursive calls (lines 7-8) | 2^n - 1 calls in total | Each call above the bottom row spawns two calls, so depth i of the call tree holds 2^i calls: 1 + 2 + 4 + … + 2^(n-1). |
| Work inside one call (lines 5-6, 9-10) | O(1) per call | One comparison, one min and one addition. |

- **Adding it up:** 1 + 2 + 4 + … + 2^(n-1) = 2^n - 1 calls × O(1) = O(2^n); the call tree dominates the O(1) setup.
- **At the maximum input:** n = 200 → about 1.6·10^60 calls, which never finishes; even n = 30 already needs about 10^9 calls, roughly a second.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 7-8) | n frames × O(1) | Each nested call moves one row down, so at most n calls are active at once, each holding i, j, down, diag and best. |

- **Adding it up:** n frames × O(1) = O(n).
- **Not counted:** The input triangle is not counted. Nothing is cached, and a stack depth of at most 200 is safe.

**Dry run** on `triangle = [[2],[3,4],[6,5,7]] (the first three rows of Example 1, to keep the call tree small)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 3 rows, so the bottom row is i = 2. Line 3 is about to call f(0, 0) at the apex. | `n = 3`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]`<br>`call stack = []` |
| 2 | 5 | f(0, 0) starts. i = 0 is not the bottom row (n - 1 = 2), so it must explore both moves. | `i = 0`<br>`j = 0`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[0,0])<br>`call stack = [f(0,0)] ← top` |
| 3 | 6 | Line 7 of f(0, 0) calls f(1, 0), whose line 7 calls f(2, 0). Row 2 is the bottom, so f(2, 0) returns triangle[2][0] = 6. | `i = 2`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[2,0])<br>`call stack = [f(0,0), f(1,0), f(2,0)] ← top` |
| 4 | 7 | Back in f(1, 0): down = 6, the cheapest path below if we step straight down to index 0. | `i = 1`<br>`down = 6`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[1,0])<br>`call stack = [f(0,0), f(1,0)] ← top` |
| 5 | 8 | f(1, 0) calls f(2, 1), another bottom cell, which returns 5, so diag = 5. | `diag = 5` |
| 6 | 10 | Line 9 sets best = min(6, 5) = 5, and f(1, 0) returns 3 + 5 = 8 to f(0, 0). | `best = 5` |
| 7 | 7 | Back in f(0, 0): down = 8, the best total below the apex when going to index 0. | `i = 0`<br>`down = 8`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[0,0])<br>`call stack = [f(0,0)] ← top` |
| 8 | 6 | Line 8 of f(0, 0) calls f(1, 1), whose line 7 calls f(2, 1) again: the same cell f(1, 0) already evaluated. It returns 5 a second time; this repeated work is what memoisation removes. | `i = 2`<br>`j = 1`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[2,1])<br>`call stack = [f(0,0), f(1,1), f(2,1)] ← top` |
| 9 | 7 | Back in f(1, 1): down = 5. | `i = 1`<br>`down = 5`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[1,1])<br>`call stack = [f(0,0), f(1,1)] ← top` |
| 10 | 8 | f(1, 1) calls f(2, 2), a bottom cell that returns 7, so diag = 7. | `diag = 7` |
| 11 | 10 | best = min(5, 7) = 5, so f(1, 1) returns 4 + 5 = 9 to f(0, 0). | `best = 5` |
| 12 | 8 | Back in f(0, 0): diag = 9, the best total below the apex when going to index 1. | `i = 0`<br>`j = 0`<br>`down = 8`<br>`diag = 9`<br>`triangle = 3×1 table: [2] [3, 4] [6, 5, 7]` (f→[0,0])<br>`call stack = [f(0,0)] ← top` |
| 13 | 9 | best = min(8, 9) = 8: going left through the 3 is cheaper. | `best = 8` |
| 14 | 10 | f(0, 0) returns 2 + 8 = 10. | (no change) |
| 15 | 3 | minimumTotal returns 10. In total 7 calls were made for 6 cells, and f(2, 1) ran twice. | `triangle = 3×1 table: [2] [3, 4] [6, 5, 7]`<br>`call stack = []` |

**Result:** 10: the cheapest path is 2 → 3 → 5 (indices 0, 0, 1); every path was tried, so nothing cheaper exists, but f(2, 1) was evaluated twice.

**C++ solution**

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();                 // number of rows; row n - 1 is the bottom
        return solve(0, 0, n, triangle);         // every path starts at the apex (0, 0)
    }

private:
    // Cheapest path sum from cell (i, j) down to the bottom row
    int solve(int i, int j, int n, vector<vector<int>>& triangle) {
        if (i == n - 1) return triangle[i][j];        // bottom row: the path is just this cell
        int down = solve(i + 1, j, n, triangle);      // move to index j on the next row
        int diag = solve(i + 1, j + 1, n, triangle);  // move to index j + 1 on the next row
        int best = min(down, diag);                   // cheaper of the two continuations
        return triangle[i][j] + best;                 // pay for this cell plus the best continuation
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
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();                 // number of rows; row n - 1 is the bottom
        return solve(0, 0, n, triangle);         // every path starts at the apex (0, 0)
    }

private:
    // Cheapest path sum from cell (i, j) down to the bottom row
    int solve(int i, int j, int n, vector<vector<int>>& triangle) {
        if (i == n - 1) return triangle[i][j];        // bottom row: the path is just this cell
        int down = solve(i + 1, j, n, triangle);      // move to index j on the next row
        int diag = solve(i + 1, j + 1, n, triangle);  // move to index j + 1 on the next row
        int best = min(down, diag);                   // cheaper of the two continuations
        return triangle[i][j] + best;                 // pay for this cell plus the best continuation
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
```

</details>

**Why move on:** The same cells are solved again and again: in Example 1, `f(2, 1)` is computed twice and the bottom cells `f(3, 1)` and `f(3, 2)` three times each. At n = 200 that is about 2^200 calls, hopeless against the limit.

### 2. Better: Top-down recursion with a memo table

> **How you get here:** The recursion only ever asks about n(n + 1)/2 distinct cells, yet in Example 1 it computes `f(2, 1)` twice and `f(3, 1)` three times; storing each cell's answer the first time removes all of that repeated work.

**Idea.** Keep a triangle-shaped table `memo` where `memo[i][j]` stores `f(i, j)` once it is known, and ∞ means not computed yet (-1 cannot be the marker because path sums can be negative). Before expanding a cell above the bottom row, check `memo[i][j]`; if it is set, return it immediately. The recurrence is unchanged, so every value equals the brute-force one, but each of the n(n - 1)/2 non-bottom cells is expanded at most once and every later request for it is an O(1) lookup.

**Steps**

1. Create `memo` with row `i` holding `i + 1` slots, all set to ∞.
2. Call `f(0, 0)`.
3. In `f(i, j)`, return `triangle[i][j]` on the bottom row.
4. If `memo[i][j]` is not ∞, return it.
5. Otherwise compute `down = f(i + 1, j)` and `diag = f(i + 1, j + 1)`.
6. Store `memo[i][j] = triangle[i][j] + min(down, diag)` and return it.

**Pseudocode**

```text
 1 │ function minimumTotal(triangle)
 2 │   n ← number of rows in triangle
 3 │   memo ← triangle-shaped table, row i has i + 1 slots, all ∞  // ∞ = not computed; real sums stay within ±2·10^6
 4 │   return f(0, 0)
 5 │ function f(i, j)  // cheapest path sum from (i, j) to the bottom row
 6 │   if i = n - 1  // bottom row: the path is just this cell
 7 │     return triangle[i][j]
 8 │   if memo[i][j] ≠ ∞  // solved before: reuse it
 9 │     return memo[i][j]
10 │   down ← f(i + 1, j)
11 │   diag ← f(i + 1, j + 1)
12 │   memo[i][j] ← triangle[i][j] + min(down, diag)  // store before returning so later callers reuse it
13 │   return memo[i][j]
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table setup (lines 2-3) | n(n + 1)/2 slots × O(1) | Every slot of the triangle-shaped memo is set to ∞ once. |
| First expansion of each non-bottom cell (lines 10-12) | n(n - 1)/2 cells × O(1) plus 2 calls each | A cell above the bottom row is expanded only the first time it is requested; afterwards its memo slot is set. |
| Calls that end immediately (lines 6-9) | at most n(n - 1) calls × O(1) | Every call is made by some expansion and each expansion makes exactly two, so bottom-row returns and memo hits together number at most n(n - 1). |

- **Adding it up:** n(n + 1)/2 + n(n - 1)/2 + n(n - 1) = O(n^2); for n = 200 that is 20,100 + 19,900 + 39,800 ≈ 8·10^4 simple steps.
- **At the maximum input:** n = 200 → under 10^5 simple steps, well under a millisecond.

**Space complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| memo table (line 3) | n(n + 1)/2 integers | One slot per triangle cell, 20,100 slots for n = 200. |
| Recursion stack (lines 10-11) | n frames × O(1) | Each nested call goes one row lower, so at most n frames are active. |

- **Adding it up:** O(n^2) + O(n) = O(n^2); the table dominates.
- **Not counted:** The input triangle is not counted. A recursion depth of 200 is safe.

**Dry run** on `triangle = [[2],[3,4],[6,5,7],[4,1,8,3]] (Example 1)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 4. memo gets one slot per cell, all ∞ (not computed). ∞ is used instead of -1 because a path sum could legitimately be -1. | `n = 4`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]`<br>`memo = 4×1 table: [∞] [∞, ∞] [∞, ∞, ∞] [∞, ∞, ∞, ∞]`<br>`call stack = []` |
| 2 | 8 | f(0, 0) calls f(1, 0) on line 10, which calls f(2, 0). Row 2 is not the bottom and memo[2][0] = ∞, so f(2, 0) must be computed. | `i = 2`<br>`j = 0`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[2,0])<br>`call stack = [f(0,0), f(1,0), f(2,0)] ← top` |
| 3 | 11 | In f(2, 0), line 10 gets down = f(3, 0) = 4 and line 11 gets diag = f(3, 1) = 1; both are bottom cells returned straight from line 7. | `down = 4`<br>`diag = 1` |
| 4 | 12 | memo[2][0] = 6 + min(4, 1) = 7 is stored, then returned to f(1, 0). | `memo = 4×1 table: [∞] [∞, ∞] [7, ∞, ∞] [∞, ∞, ∞, ∞]` |
| 5 | 10 | Back in f(1, 0): down = 7. | `i = 1`<br>`down = 7`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[1,0])<br>`call stack = [f(0,0), f(1,0)] ← top` |
| 6 | 12 | Line 11 of f(1, 0) calls f(2, 1): memo[2][1] is ∞, so it gets down = f(3, 1) = 1 and diag = f(3, 2) = 8, and stores memo[2][1] = 5 + 1 = 6. | `i = 2`<br>`j = 1`<br>`down = 1`<br>`diag = 8`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[2,1])<br>`memo = 4×1 table: [∞] [∞, ∞] [7, 6, ∞] [∞, ∞, ∞, ∞]`<br>`call stack = [f(0,0), f(1,0), f(2,1)] ← top` |
| 7 | 12 | Back in f(1, 0): diag = 6, so memo[1][0] = 3 + min(7, 6) = 9. | `i = 1`<br>`j = 0`<br>`down = 7`<br>`diag = 6`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[1,0])<br>`memo = 4×1 table: [∞] [9, ∞] [7, 6, ∞] [∞, ∞, ∞, ∞]`<br>`call stack = [f(0,0), f(1,0)] ← top` |
| 8 | 10 | Back in f(0, 0): down = 9. | `i = 0`<br>`down = 9`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[0,0])<br>`call stack = [f(0,0)] ← top` |
| 9 | 9 | f(0, 0) calls f(1, 1) (memo ∞, so it expands), and f(1, 1) calls f(2, 1). memo[2][1] = 6 is set, so it returns 6 at once: a memo hit where brute force would have recomputed the whole subtree. | `i = 2`<br>`j = 1`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[2,1])<br>`call stack = [f(0,0), f(1,1), f(2,1)] ← top` |
| 10 | 10 | Back in f(1, 1): down = 6. | `i = 1`<br>`down = 6`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[1,1])<br>`call stack = [f(0,0), f(1,1)] ← top` |
| 11 | 12 | f(1, 1) calls f(2, 2): it gets down = f(3, 2) = 8 and diag = f(3, 3) = 3, and stores memo[2][2] = 7 + 3 = 10. | `i = 2`<br>`j = 2`<br>`down = 8`<br>`diag = 3`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[2,2])<br>`memo = 4×1 table: [∞] [9, ∞] [7, 6, 10] [∞, ∞, ∞, ∞]`<br>`call stack = [f(0,0), f(1,1), f(2,2)] ← top` |
| 12 | 12 | Back in f(1, 1): diag = 10, so memo[1][1] = 4 + min(6, 10) = 10. | `i = 1`<br>`j = 1`<br>`down = 6`<br>`diag = 10`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[1,1])<br>`memo = 4×1 table: [∞] [9, 10] [7, 6, 10] [∞, ∞, ∞, ∞]`<br>`call stack = [f(0,0), f(1,1)] ← top` |
| 13 | 12 | Back in f(0, 0): diag = 10, so memo[0][0] = 2 + min(9, 10) = 11. | `i = 0`<br>`j = 0`<br>`down = 9`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (f→[0,0])<br>`memo = 4×1 table: [11] [9, 10] [7, 6, 10] [∞, ∞, ∞, ∞]`<br>`call stack = [f(0,0)] ← top` |
| 14 | 4 | minimumTotal returns 11. Each of the 6 non-bottom cells was expanded exactly once; the bottom row is never stored because line 7 answers it directly. | `triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]`<br>`call stack = []` |

**Result:** 11: memo[0][0] = 2 + min(9, 10) along 2 → 3 → 5 → 1, matching the expected output, and the second request for f(2, 1) was answered from memo.

**C++ solution**

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();                          // number of rows
        // memo[i] has i + 1 slots, one per cell of row i; INT_MAX means "not computed yet".
        // -1 cannot be the marker because path sums can be negative (they stay within +/-2e6).
        vector<vector<int>> memo(n);
        for (int i = 0; i < n; i++) memo[i].assign(i + 1, INT_MAX);
        return solve(0, 0, n, triangle, memo);            // start at the apex
    }

private:
    // Cheapest path sum from (i, j) to the bottom row, cached in memo
    int solve(int i, int j, int n, vector<vector<int>>& triangle, vector<vector<int>>& memo) {
        if (i == n - 1) return triangle[i][j];            // bottom row: the path is just this cell
        if (memo[i][j] != INT_MAX) return memo[i][j];     // solved before: reuse the stored answer
        int down = solve(i + 1, j, n, triangle, memo);    // best path through (i + 1, j)
        int diag = solve(i + 1, j + 1, n, triangle, memo);// best path through (i + 1, j + 1)
        memo[i][j] = triangle[i][j] + min(down, diag);    // store before returning so later callers reuse it
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
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();                          // number of rows
        // memo[i] has i + 1 slots, one per cell of row i; INT_MAX means "not computed yet".
        // -1 cannot be the marker because path sums can be negative (they stay within +/-2e6).
        vector<vector<int>> memo(n);
        for (int i = 0; i < n; i++) memo[i].assign(i + 1, INT_MAX);
        return solve(0, 0, n, triangle, memo);            // start at the apex
    }

private:
    // Cheapest path sum from (i, j) to the bottom row, cached in memo
    int solve(int i, int j, int n, vector<vector<int>>& triangle, vector<vector<int>>& memo) {
        if (i == n - 1) return triangle[i][j];            // bottom row: the path is just this cell
        if (memo[i][j] != INT_MAX) return memo[i][j];     // solved before: reuse the stored answer
        int down = solve(i + 1, j, n, triangle, memo);    // best path through (i + 1, j)
        int diag = solve(i + 1, j + 1, n, triangle, memo);// best path through (i + 1, j + 1)
        memo[i][j] = triangle[i][j] + min(down, diag);    // store before returning so later callers reuse it
        return memo[i][j];
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
```

</details>

**Why move on:** Time is already optimal, but it stores all 20,100 slots for n = 200 and uses an n-deep recursion stack; the follow-up asks for `O(n)` extra space, which needs an iterative fill that keeps only one row.

### 3. Optimal: Bottom-up DP with one row array

> **How you get here:** In the memo version, row `i` only ever reads row `i + 1`, and once row `i` is finished row `i + 1` is never needed again. So fill rows from the bottom up and keep just the row below in a 1D array, overwriting it in place.

**Idea.** Let `dp[j]` hold the minimum path sum from column `j` of the row below to the bottom; initially that row is the last row itself, so `dp` is a copy of it. To lift `dp` to row `i`, set `dp[j] = triangle[i][j] + min(dp[j], dp[j + 1])` for `j = 0..i`. Going left to right is safe: when `dp[j]` is overwritten, the values it needs, old `dp[j]` and `dp[j + 1]`, are still the row-below values, and old `dp[j]` is never needed again because column `j - 1` is already done. After row 0, `dp[0]` is the answer; the higher entries are leftovers from lower rows and are ignored.

**Steps**

1. Let `n` be the number of rows and copy the bottom row `triangle[n - 1]` into an array `dp` of length `n`.
2. Process rows `i = n - 2, n - 3, ..., 0`, one at a time.
3. Within row `i`, go through `j = 0..i` and read `down = dp[j]` and `diag = dp[j + 1]`, both still the values for row `i + 1`.
4. Overwrite `dp[j]` with `triangle[i][j] + min(down, diag)`.
5. After row 0, return `dp[0]`.

**Pseudocode**

```text
 1 │ function minimumTotal(triangle)
 2 │   n ← number of rows in triangle
 3 │   dp ← array of n zeros  // dp[j] = cheapest sum from column j of the last finished row to the bottom
 4 │   for j ← 0 to n - 1
 5 │     dp[j] ← triangle[n - 1][j]  // bottom row: each cell is its own path
 6 │   for i ← n - 2 down to 0  // lift dp one row at a time
 7 │     for j ← 0 to i  // row i has i + 1 cells
 8 │       down ← dp[j]  // best from (i + 1, j)
 9 │       diag ← dp[j + 1]  // best from (i + 1, j + 1): not overwritten yet because we go left to right
10 │       dp[j] ← triangle[i][j] + min(down, diag)
11 │   return dp[0]  // the apex (0, 0)
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Copy the bottom row (lines 3-5) | n iterations × O(1) | Each of the n bottom cells is its own best path. |
| Row loop with inner column loop (lines 6-10) | (n - 1) + (n - 2) + … + 1 = n(n - 1)/2 iterations × O(1) | Row i has i + 1 cells and each needs two reads, one min and one addition. |
| Return (line 11) | O(1) | Reads a single entry. |

- **Adding it up:** n + n(n - 1)/2 + 1 = O(n^2); the nested loops dominate. For n = 200: 200 + 19,900 + 1 ≈ 2·10^4 steps.
- **At the maximum input:** n = 200 → about 2·10^4 additions, a few microseconds.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp array (line 3) | n integers | Holds one row of best sums and is overwritten in place as we move up. |
| Loop variables (lines 6-9) | O(1) | Just i, j, down and diag. |

- **Adding it up:** n + O(1) = O(n), which meets the follow-up.
- **Not counted:** The input triangle is read but not modified, and it is not counted.

**Dry run** on `triangle = [[2],[3,4],[6,5,7],[4,1,8,3]] (Example 1)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 4, and dp starts as 4 zeros. | `n = 4`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]`<br>`dp = [0, 0, 0, 0]` |
| 2 | 5 | The loop on lines 4-5 copies the bottom row (shown at its last iteration, j = 3): dp = [4, 1, 8, 3]. Each bottom cell is its own cheapest path. | `j = 3`<br>`dp = [4, 1, 8, 3]` (j→3) |
| 3 | 9 | Row i = 2, j = 0: down = dp[0] = 4 and diag = dp[1] = 1 are the best sums from the two cells below the 6. | `i = 2`<br>`j = 0`<br>`down = 4`<br>`diag = 1`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[2,0])<br>`dp = [4, 1, 8, 3]` (j→0) |
| 4 | 10 | dp[0] = 6 + min(4, 1) = 7. dp[1] = 1 still belongs to row 3, which column 1 needs next. | `dp = [7, 1, 8, 3]` (j→0) |
| 5 | 10 | j = 1: down = dp[1] = 1, diag = dp[2] = 8, so dp[1] = 5 + 1 = 6. | `j = 1`<br>`down = 1`<br>`diag = 8`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[2,1])<br>`dp = [7, 6, 8, 3]` (j→1) |
| 6 | 10 | j = 2: down = dp[2] = 8, diag = dp[3] = 3, so dp[2] = 7 + 3 = 10. Row 2 is done: dp[0..2] = [7, 6, 10]. | `j = 2`<br>`down = 8`<br>`diag = 3`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[2,2])<br>`dp = [7, 6, 10, 3]` (j→2) |
| 7 | 10 | Row i = 1, j = 0: down = 7, diag = 6, so dp[0] = 3 + 6 = 9. | `i = 1`<br>`j = 0`<br>`down = 7`<br>`diag = 6`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[1,0])<br>`dp = [9, 6, 10, 3]` (j→0) |
| 8 | 10 | j = 1: down = 6, diag = 10, so dp[1] = 4 + 6 = 10. dp[3] = 3 is a leftover from row 3 that is never read again. | `j = 1`<br>`down = 6`<br>`diag = 10`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[1,1])<br>`dp = [9, 10, 10, 3]` (j→1) |
| 9 | 9 | Row i = 0, j = 0: down = dp[0] = 9 (path via the 3) and diag = dp[1] = 10 (path via the 4). | `i = 0`<br>`j = 0`<br>`down = 9`<br>`triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]` (i,j→[0,0])<br>`dp = [9, 10, 10, 3]` (j→0) |
| 10 | 10 | dp[0] = 2 + min(9, 10) = 11. | `dp = [11, 10, 10, 3]` (j→0) |
| 11 | 11 | Both loops are done; return dp[0] = 11. | `triangle = 4×1 table: [2] [3, 4] [6, 5, 7] [4, 1, 8, 3]`<br>`dp = [11, 10, 10, 3]` |

**Result:** 11: dp[0] is the cheapest path from the apex, 2 + 3 + 5 + 1, because each dp[j] always held the best sum from its cell to the bottom.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Every cell must be read at least once because any single value can change the answer, so `O(n^2)` time (linear in the input size) cannot be beaten, and `O(n)` space meets the follow-up. You could reach `O(1)` extra space by writing the sums into `triangle` itself, but that destroys the input.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| triangle = [[1],[2,3],[4,5,6]] | 7 | The optimal path runs straight down the left edge: 1 + 2 + 4. |
| triangle = [[1],[2,3],[9,8,1]] | 5 | Greedy trap: taking the smaller neighbour 2 leads to 11, but going through 3 to the 1 gives 5. |
| triangle = [[-1],[2,3],[1,-1,-3]] | -1 | Negative values: the best path -1 + 3 + (-3) ends at the bottom-right cell. |
| triangle = [[7],[3,8],[8,1,0],[2,7,4,4],[4,5,2,6,5]] | 17 | Five rows with a zig-zag optimum 7 + 3 + 1 + 4 + 2 (indices 0, 0, 1, 2, 2). |
| triangle = [[5],[-2,4],[3,-6,1],[2,2,-8,0]] | -11 | Mixed signs: the path collects every negative, 5 - 2 - 6 - 8. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single row | triangle = [[10000]] | 10000 | The answer is the only element, here the maximum value 10^4. |
| Two rows | triangle = [[1],[5,2]] | 3 | Only two paths exist, so pick the cheaper bottom cell 2. |
| All equal | triangle = [[1],[1,1],[1,1,1],[1,1,1,1]] | 4 | Every path ties, so the answer is the number of rows. |
| All minimum values | triangle = [[-10000],[-10000,-10000],[-10000,-10000,-10000]] | -30000 | Sums go far below zero; at 200 rows the extreme is -2·10^6, still inside int. |
| Right edge | triangle = [[1],[9,2],[9,9,3],[9,9,9,4]] | 10 | The optimal path always moves to index i + 1 and ends at the last cell of the last row. |
| Hidden negative | triangle = [[1],[100,100],[100,-10000,100]] | -9899 | The path looks expensive until the -10^4 at the bottom, so pruning by partial sums is wrong. |

## Mistakes and edge cases

**Common mistakes**

- Going greedy from the top: choosing the smaller of the two neighbours at each step fails on `[[1],[2,3],[9,8,1]]` (greedy gives 11, the true answer is 5).
- Updating the 1D `dp` right to left (`j` from `i` down to `0`): `dp[j + 1]` has then already been overwritten with a row-`i` value, so cell `(i, j)` combines two cells of the same row and the answer is wrong.
- Filling top-down and returning a single corner such as `dp[n - 1][0]`: when sums flow from the apex downward, the answer is the minimum over the whole last row; bottom-up avoids this because everything funnels into `dp[0]`.
- Using -1 as the 'not computed' marker in the memo: any cell whose true answer is -1 looks unsolved, so it is recomputed on every request and, when many cells share that value, the exponential running time quietly comes back; use a value outside ±2·10^6 such as INT_MAX.

**Edge cases to check**

- Single row (`[[-10]]`): the row loop starts at `i = n - 2 = -1` and never runs, so the answer must be `triangle[0][0]` straight from the copied bottom row.
- All negative values such as `[[-10000],[-10000,-10000],[-10000,-10000,-10000]]` (answer -30000): checks that no code assumes sums are non-negative, for example a 0 or -1 sentinel.
- A large negative hidden at the bottom, like `[[1],[100,100],[100,-10000,100]]` (answer -9899): any pruning by the partial sum so far would discard the optimal path.
- Optimal path along an edge (`j` always 0, or always equal to `i`): checks that the first and last cells of each row use the right neighbours; `[[1],[9,2],[9,9,3],[9,9,9,4]]` must give 10.

## Practice next

- [Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/) · Same row-by-row minimum DP, but on a square matrix with three moves (down-left, down, down-right) and boundary checks.
- [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) · Grid DP where each cell's best cost comes from two neighbours, also solvable with a single 1D row array.
- [Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) · The same two-move grid recurrence, counting paths instead of minimising, with the same 1D space optimisation.
- [Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/) · Extends row-by-row DP to two walkers moving together, with a 2D layer per row instead of a 1D row.

## Takeaways

- When the answer at a cell depends only on cells in the next row, define `best(cell)` as the optimal cost from that cell onward and the recurrence writes itself.
- Choose the fill direction so the boundary is trivial and the answer lands in one cell: bottom-up turns a minimum over the last row into just `dp[0]`.
- If row `i` reads only row `i + 1`, one 1D array is enough; pick the update order (here left to right) so you never read a value already overwritten in the current pass.
- Greedy local choices fail when a cheap step can lead into an expensive region; overlapping two-way choices are a strong DP signal.
