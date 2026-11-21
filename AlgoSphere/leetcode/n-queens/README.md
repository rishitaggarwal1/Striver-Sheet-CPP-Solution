# N-Queens

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/n-queens/) · Pattern: **Backtracking with constant-time conflict sets**

> List every way to put `n` queens on an `n x n` board so that no two share a row, a column or a diagonal, with each board written as strings of 'Q' and '.'.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

Example 1:

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:

Input: n = 1
Output: [["Q"]]

Constraints:

- 1 <= n <= 9
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to list every way to put n queens on an n by n grid so that no two share a row, a column, or a diagonal, and return each arrangement drawn as rows of 'Q' and '.' characters.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Since no two queens can share a row and there are exactly n queens and n rows, every valid board has exactly one queen per row. So a solution is just a choice of one column for each row, and those columns must all be different.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n <= 9`, trying every way to place n queens on n*n cells is astronomically large, and even trying all `n!` column orderings blindly is wasteful. You can afford exponential search, but you must cut off bad partial placements early instead of checking only finished boards.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking: build the board one row at a time, and the moment a placement conflicts with an earlier queen, abandon that branch. Undo the placement and try the next column.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

A cell is attacked if its column is taken, or its `row - col` value is taken (one diagonal direction), or its `row + col` value is taken (the other direction). Recording these three facts for each placed queen lets you test any cell in constant time.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep three sets or boolean arrays: used columns, used `row - col` diagonals (offset by `n - 1` if you use an array), and used `row + col` anti-diagonals (size `2n - 1`). Also keep the current partial board, or the column chosen for each row, so you can turn it into strings when a solution is complete.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Start a recursive search at row 0 with all markers empty.
If the current row equals n, convert the board to a list of strings and add a copy to the results.
Otherwise, try each column in the current row.
Skip the column if its column, diagonal, or anti-diagonal is already marked.
Otherwise, place the queen, mark all three, and recurse to the next row.
After returning, remove the queen and clear all three marks.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is undoing state exactly: every mark set before recursing must be cleared afterward, and you must store a copy of the board, not a reference that later changes. For edge cases, `n = 1` gives one solution, while `n = 2` and `n = 3` give an empty list. Time is roughly `O(n!)` in the worst case plus `O(n^2)` to build each solution, and space is `O(n)` for recursion and markers, excluding the output.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "return all distinct solutions" | we must enumerate every configuration rather than count or optimise one, so exhaustive search with pruning (backtracking) is the natural tool. |
| no two queens attack each other, and there are exactly `n` queens on `n` rows | every row holds exactly one queen, so we can decide the board one row at a time by choosing a column. |
| diagonal attacks | every cell on the same '\' diagonal has the same `r - c`, and every cell on the same '/' diagonal has the same `r + c`, so a diagonal can be identified by a single integer. |
| 1 <= n <= 9 | the limit is tiny, which signals exponential search is expected and the goal is pruning, not a polynomial algorithm. |

### What the constraints tell you

Choosing any 9 of the 81 cells gives C(81,9) ≈ 2.6·10^11 boards, which is hopeless. Fixing one queen per row and using distinct columns leaves 9! = 362,880 permutations, and checking each in O(n^2) costs about 3·10^7 operations, which already fits. Backtracking that prunes as soon as a conflict appears visits only tens of thousands of partial boards for n = 9. The target is an exponential search with heavy pruning, roughly O(n!), plus the cost of writing out the 352 solutions.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most naive search space?**

<details>
<summary>Answer</summary>

Pick any `n` cells out of `n^2` and test whether the queens attack each other. For n = 9 that is about 2.6·10^11 subsets, so the structure of the problem has to shrink the space.

</details>

**Q2. Which constraint removes the most choices for free?**

<details>
<summary>Answer</summary>

Rows: `n` queens on `n` rows with at most one per row forces exactly one queen per row. A board is then just an array `cols[r]` giving the column of the queen in row `r`.

</details>

**Q3. Can columns be handled the same way?**

<details>
<summary>Answer</summary>

Yes. Each column also holds exactly one queen, so `cols` must be a permutation of 0..n-1. That leaves only n! candidates, and only diagonals still need checking.

</details>

**Q4. Why generate a full permutation before checking it?**

<details>
<summary>Answer</summary>

If the queens in rows 0 and 1 already share a diagonal, every completion of that prefix fails. So place queens row by row and backtrack the moment a placement conflicts. This cuts off whole subtrees early.

</details>

**Q5. How do we check "is (r, c) attacked?" without rescanning earlier rows?**

<details>
<summary>Answer</summary>

A queen at (r, c) occupies column `c`, anti-diagonal `r + c` and main diagonal `r - c`. Keep three sets (or boolean arrays, offsetting `r - c` by `n - 1`). A cell is safe exactly when none of its three keys is marked, which takes O(1). Mark the keys on placement and unmark them when backtracking.

</details>

**Q6. When do we record a solution?**

<details>
<summary>Answer</summary>

When row index `r` reaches `n`, every row has a safe queen. Convert `cols` into `n` strings, with 'Q' at column `cols[r]` and '.' elsewhere, and append a copy to the answer.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Enumerate column permutations](#1-brute-force-enumerate-column-permutations) | `O(n! · n^2)` | `O(n) besides output` |
| 2 | [Better: Row-by-row backtracking with scan check](#2-better-row-by-row-backtracking-with-scan-check) | `O(n! · n) roughly` | `O(n) besides output` |
| 3 | [Optimal: Backtracking with column/diagonal sets](#3-optimal-backtracking-with-columndiagonal-sets) | `O(n!) roughly` | `O(n) besides output` |

### 1. Brute force: Enumerate column permutations

> **Where you start:** Once you see that each row and each column gets exactly one queen, listing every permutation of columns and testing it is the most direct correct method.

**Idea.** Represent a board by `cols[r]`, the column of the queen in row `r`. Rows and columns are automatically distinct when `cols` is a permutation, so generate all n! permutations. For each one, check every pair of rows i < j for a diagonal clash: `|cols[i] - cols[j]| == j - i`. Permutations with no clash are exactly the valid boards, so collecting them gives every distinct solution.

**Steps**

1. Generate every permutation of the columns 0..n-1.
2. For each permutation, loop over all row pairs i < j.
3. If `|cols[i] - cols[j]| == j - i` for any pair, reject the permutation.
4. Otherwise build the board strings from `cols` and add them to the result.
5. Return the result after all permutations are tested.

**Complexity:** time `O(n! · n^2)`, space `O(n) besides output`. There are n! permutations and each pairwise diagonal check costs O(n^2), so for n = 9 this is about 3·10^7 operations. The extra memory is the permutation array and the recursion that generates it.

**Why move on:** Every permutation is built in full even when its first two queens already clash, so most of the work is spent completing boards that were dead after two or three rows. It passes for n = 9 but grows badly and wastes effort.

### 2. Better: Row-by-row backtracking with scan check

> **How you get here:** The brute force finishes all n! permutations even when a prefix like `cols = [0, 1, ...]` is already invalid. Checking each queen as it is placed lets us abandon such prefixes at once.

**Idea.** Recursively fill row `r` by trying each column `c`. Before placing a queen, scan the rows 0..r-1 and reject `c` if some earlier row has the same column or `|cols[i] - c| == r - i`. Recurse only when the placement is safe. Every prefix that survives is conflict-free, so reaching `r == n` means a full valid board, and because all safe columns are tried in every row, no solution is missed.

**Steps**

1. Start the recursion at row 0 with an empty `cols` array.
2. In row `r`, try each column `c` from 0 to n-1.
3. Scan the earlier rows i < r and skip `c` if it shares a column or diagonal with `cols[i]`.
4. If `c` is safe, set `cols[r] = c` and recurse on row r+1.
5. When `r == n`, convert `cols` into strings and save the board.
6. Return to try the next column (backtrack).

**Complexity:** time `O(n! · n) roughly`, space `O(n) besides output`. Pruning keeps the number of explored nodes far below n!, but each candidate column costs an O(n) scan of earlier rows. The extra memory is the `cols` array and the recursion stack of depth `n`.

**Why move on:** The repeated O(n) safety scan is wasted work: the same diagonal facts are recomputed at every node. It is easily fast enough for n <= 9, but the check can be made O(1).

### 3. Optimal: Backtracking with column/diagonal sets

> **How you get here:** The scan in the previous approach only answers three questions: is column `c` taken, is diagonal `r - c` taken, is anti-diagonal `r + c` taken. Storing those three facts directly turns the scan into an O(1) lookup.

**Idea.** Keep three boolean arrays: `colUsed[c]`, `diag[r - c + n - 1]` and `anti[r + c]`. All cells on one diagonal share the same `r - c` and all cells on one anti-diagonal share the same `r + c`, so a cell is attacked exactly when one of its three entries is true. Place a queen by setting the three entries, recurse, then clear them on return so the state again describes only rows 0..r-1. This invariant keeps every check O(1), and the search tree is the same as before, so correctness carries over. Bitmasks can replace the arrays for even tighter constant factors.

**Steps**

1. Create `colUsed` of size n, and `diag` and `anti` of size 2n-1, plus a board initialised to all '.'.
2. Recurse on row `r`, and if `r == n`, copy the board into the result.
3. For each column `c`, skip it if `colUsed[c]`, `diag[r - c + n - 1]` or `anti[r + c]` is set.
4. Otherwise set those three flags and put 'Q' at (r, c).
5. Recurse on row r+1.
6. Clear the three flags and reset (r, c) to '.' before trying the next column.

**Complexity:** time `O(n!) roughly`, space `O(n) besides output`. Running time is dominated by the number of nodes in the pruned search tree, which is bounded by n!, with O(1) work per candidate column plus O(n^2) to copy each found board. The extra memory is the three flag arrays of size O(n), the board, and the recursion depth `n`.

**Why this is the best:** No polynomial algorithm is known for listing all solutions, and the output itself can be large, so exponential search is unavoidable. This approach removes all redundant checking. The cost is careful bookkeeping: every flag set on the way down must be undone on the way back.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| n = 4 | [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]] | Smallest board with solutions; it has 2 mirror-image placements. |
| n = 5 | [["Q....","..Q..","....Q",".Q...","...Q."],["Q....","...Q.",".Q...","....Q","..Q.."],[".Q...","...Q.","Q....","..Q..","....Q"],[".Q...","....Q","..Q..","Q....","...Q."],["..Q..","Q....","...Q.",".Q...","....Q"],["..Q..","....Q",".Q...","...Q.","Q...."],["...Q.","Q....","..Q..","....Q",".Q..."],["...Q.",".Q...","....Q","..Q..","Q...."],["....Q",".Q...","...Q.","Q....","..Q.."],["....Q","..Q..","Q....","...Q.",".Q..."]] | Odd board size with 10 solutions. |
| n = 6 | [[".Q....","...Q..",".....Q","Q.....","..Q...","....Q."],["..Q...",".....Q",".Q....","....Q.","Q.....","...Q.."],["...Q..","Q.....","....Q.",".Q....",".....Q","..Q..."],["....Q.","..Q...","Q.....",".....Q","...Q..",".Q...."]] | Has only 4 solutions, fewer than n=5, so the count does not grow steadily. |
| n = 7 | 40 distinct boards of 7 strings each (list too long to write out) | Moderate search with 40 solutions. |
| n = 8 | 92 distinct boards of 8 strings each (list too long to write out) | Classic 8-queens puzzle with 92 solutions. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum n | n = 1 | [["Q"]] | A single queen on a 1x1 board. |
| No solution | n = 2 | [] | Two queens always attack each other on a 2x2 board. |
| No solution | n = 3 | [] | Largest n with no valid placement. |
| Maximum n | n = 9 | 352 distinct boards of 9 strings each (list too long to write out) | Checks performance with 352 solutions. |
| Smallest odd solvable board | n = 5 | 10 distinct boards (same list as the n=5 normal case) | Checks that diagonal handling works when the board has a centre square. |

## Mistakes and edge cases

**Common mistakes**

- Indexing the main diagonal by `r - c` directly. It ranges from -(n-1) to n-1, so the array index goes negative unless you offset it by `n - 1`.
- Forgetting to clear `colUsed`, `diag` and `anti` (or to reset the cell to '.') after the recursive call. Leftover flags block valid placements in later branches and solutions go missing.
- Appending the mutable board itself instead of a copy of its strings. Later backtracking then changes the stored solutions.
- Checking only columns and forgetting one of the two diagonal directions. For n = 4 this produces boards with diagonal attacks in the output.

**Edge cases to check**

- n = 1: the only answer is [["Q"]]. The recursion must record a solution after placing a single queen.
- n = 2 and n = 3: no solution exists, so the function must return an empty list rather than fail or return partial boards.
- n = 4: exactly the 2 boards in Example 1. This is a good small check for mirrored solutions and diagonal logic.
- n = 9: the maximum, with 352 solutions. It confirms performance and that output building is not accidentally O(n^3) per node.

## Practice next

- [N-Queens II](https://leetcode.com/problems/n-queens-ii/) · It is the same search with the same column and diagonal sets, but you count solutions instead of building boards.
- [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) · It is also backtracking over cells with O(1) constraint sets, here for rows, columns and boxes.
- [Permutations](https://leetcode.com/problems/permutations/) · It uses the choose, recurse, unchoose structure with a `used` array, which is exactly the column constraint of N-Queens.
- [Word Search](https://leetcode.com/problems/word-search/) · It is grid backtracking where state is marked before recursing and restored afterwards.

## Takeaways

- Use a forced structure to shrink the search: one queen per row turns subsets of cells into a single column choice per row.
- Diagonals on a grid are identified by `r - c` and `r + c`. This trick turns geometric attack checks into O(1) set lookups.
- Prune as early as possible: check each partial assignment as you build it, instead of validating complete candidates.
- In backtracking, every state change made before recursing must be undone after it, so the shared state always describes only the current prefix.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
