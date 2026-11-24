# N-Queens

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/n-queens/) · Pattern: **Backtracking with constant-time conflict sets** · ✅ Solved in C++

> List every way to put `n` queens on an `n x n` board so that no two share a row, a column or a diagonal, with each board written as strings of 'Q' and '.'.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [My solution](#my-solution) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

**Pseudocode**

```text
 1 │ function solveNQueens(n)
 2 │   ans ← empty list of boards
 3 │   cols ← [0, 1, …, n−1]  // cols[r] = column of the queen in row r; start at the smallest permutation
 4 │   repeat
 5 │     valid ← true
 6 │     for i ← 0 to n−2
 7 │       for j ← i+1 to n−1  // every pair of rows i < j
 8 │         if |cols[i] − cols[j]| = j − i  // row gap equals column gap, so they share a diagonal
 9 │           valid ← false
10 │     if valid
11 │       board ← n strings, each n copies of '.'
12 │       for r ← 0 to n−1
13 │         board[r][cols[r]] ← 'Q'  // place row r's queen
14 │       append board to ans
15 │   until not nextPermutation(cols)  // stops once the last (descending) permutation has been tested
16 │   return ans
```

**Time complexity: `O(n! · n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Permutation loop (lines 4-15) | n! iterations × O(n) amortized for nextPermutation | Every arrangement of the n distinct columns is visited exactly once. |
| Diagonal pair check (lines 6-9) | n! permutations × n(n−1)/2 pairs × O(1) | Each permutation compares every pair of rows once. |
| Board building (lines 10-14) | S solutions × O(n^2) | Only valid permutations are turned into n strings of length n, and S ≤ n!. |

- **Adding it up:** n! · n(n−1)/2 + n! · O(n) + S · n^2 ≤ n! · O(n^2) = O(n! · n^2); the pair check dominates
- **Best vs worst case:** Every case costs the same, because all n! permutations are generated and fully checked no matter what the value of n is.
- **At the maximum input:** n = 9 → 362,880 permutations × 36 pairs ≈ 1.3·10^7 checks (a few times more in the C++ code, which rebuilds the board for every permutation), well under 0.1 s

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| cols array (line 3) | O(n) | It holds one column index per row. |
| Scalars valid, i, j, r (lines 5-13) | O(1) | These are a constant number of loop variables. |

- **Adding it up:** O(n) + O(1) = O(n)
- **Not counted:** The output ans (S boards × n^2 characters) is not counted. The board being built is one future output board, so it is not counted either. There is no recursion, because nextPermutation is iterative.

**Dry run** on `n = 4`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | Start with the identity permutation, which puts each row's queen in column r. The answer list is empty. | `n = 4`<br>`cols = [0, 1, 2, 3]`<br>`ans = []` |
| 2 | 5 | Assume permutation [0,1,2,3] is valid until a diagonal clash shows otherwise. | `valid = true` |
| 3 | 9 | Pair i=0, j=1 gives \|0−1\| = 1 = j−i, so both queens sit on one diagonal and valid becomes false. The remaining pairs are still scanned but cannot undo this. | `valid = false`<br>`i = 0`<br>`j = 1`<br>`cols = [0, 1, 2, 3]` (i→0, j→1) |
| 4 | 15 | Because valid is false, no board is built. Skipping ahead: 0132, 0213, 0231, 0312, 0321, 1023, 1032, 1203, 1230 and 1302 all hit a diagonal clash. nextPermutation then produces [1,3,0,2]. | `cols = [1, 3, 0, 2]` |
| 5 | 5 | Reset valid to true for permutation [1,3,0,2]. | `valid = true` |
| 6 | 8 | Pair i=0, j=1 gives \|1−3\| = 2 ≠ 1, so no clash. Pairs (0,2) and (0,3) give 1 ≠ 2 and 1 ≠ 3, also fine. | `i = 0`<br>`j = 1`<br>`cols = [1, 3, 0, 2]` (i→0, j→1) |
| 7 | 8 | Pair i=1, j=2 gives \|3−0\| = 3 ≠ 1, no clash. Pair (1,3) gives \|3−2\| = 1 ≠ 2, fine too. | `i = 1`<br>`j = 2`<br>`cols = [1, 3, 0, 2]` (i→1, j→2) |
| 8 | 8 | The last pair i=2, j=3 gives \|0−2\| = 2 ≠ 1. All 6 pairs pass, so valid stays true. | `i = 2`<br>`j = 3`<br>`cols = [1, 3, 0, 2]` (i→2, j→3) |
| 9 | 13 | Build the board by putting a 'Q' at column cols[r] in each row r. This shows the state after the loop finishes at r=3. | `r = 3`<br>`cols = [1, 3, 0, 2]` (r→3)<br>`board = [.Q.., ...Q, Q..., ..Q.]` (r→3) |
| 10 | 14 | Append the first solution to ans. | `cols = [1, 3, 0, 2]`<br>`board = [.Q.., ...Q, Q..., ..Q.]`<br>`ans = [[.Q.., ...Q, Q..., ..Q.]]` |
| 11 | 15 | Skipping ahead: 1320, 2013 and 2031 are rejected. nextPermutation then produces [2,0,3,1]. | `cols = [2, 0, 3, 1]` |
| 12 | 8 | All 6 pairs of [2,0,3,1] pass. The last pair i=2, j=3 gives \|3−1\| = 2 ≠ 1, so valid stays true. | `valid = true`<br>`i = 2`<br>`j = 3`<br>`cols = [2, 0, 3, 1]` (i→2, j→3) |
| 13 | 14 | Build board [..Q., Q..., ...Q, .Q..] and append it as the second solution. | `cols = [2, 0, 3, 1]`<br>`board = [..Q., Q..., ...Q, .Q..]`<br>`ans = [[.Q.., ...Q, Q..., ..Q.], [..Q., Q..., ...Q, .Q..]]` |
| 14 | 15 | The remaining permutations 2103 through 3210 all clash. After [3,2,1,0], nextPermutation returns false and the loop ends. | `cols = [3, 2, 1, 0]` |
| 15 | 16 | Return the 2 collected boards. | (no change) |

**Result:** [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]. A permutation already rules out shared rows and columns, so the only remaining attacks are diagonal ones. Exactly 2 of the 24 permutations have no diagonal clash.

**C++ solution**

```cpp
class Solution {
public:
    vector<vector<string>> ans;
    // Returns true if no two queens on this board share a diagonal.
    // Rows and columns are already distinct because the board comes from a permutation.
    bool check(vector<string> board, int n)
    {
        vector<int> cols(n);
        for (int r = 0; r < n; r++)
            cols[r] = (int)board[r].find('Q');          // recover the queen's column in row r
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)               // every pair of rows i < j
                if (abs(cols[i] - cols[j]) == j - i)      // equal row and column gaps mean same diagonal
                    return false;
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        string st(n,'.');
        vector<string> s(n,st);
        vector<int> cols(n);
        iota(cols.begin(), cols.end(), 0);                // smallest permutation 0,1,...,n-1
        do {
            for (int r = 0; r < n; r++) {
                s[r] = st;                                // clear row r
                s[r][cols[r]] = 'Q';                      // place row r's queen at cols[r]
            }
            if (check(s, n))                              // keep only boards with no diagonal clash
                ans.push_back(s);
        } while (next_permutation(cols.begin(), cols.end())); // visit all n! permutations
        return ans;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

string boardsToString(const vector<vector<string>>& b) {
    string out = "[";
    for (size_t k = 0; k < b.size(); k++) {
        if (k) out += ",";
        out += "[";
        for (size_t r = 0; r < b[k].size(); r++) {
            if (r) out += ",";
            out += "\"" + b[k][r] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> ans;
    // Returns true if no two queens on this board share a diagonal.
    // Rows and columns are already distinct because the board comes from a permutation.
    bool check(vector<string> board, int n)
    {
        vector<int> cols(n);
        for (int r = 0; r < n; r++)
            cols[r] = (int)board[r].find('Q');          // recover the queen's column in row r
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)               // every pair of rows i < j
                if (abs(cols[i] - cols[j]) == j - i)      // equal row and column gaps mean same diagonal
                    return false;
        return true;
    }
    vector<vector<string>> solveNQueens(int n) {
        string st(n,'.');
        vector<string> s(n,st);
        vector<int> cols(n);
        iota(cols.begin(), cols.end(), 0);                // smallest permutation 0,1,...,n-1
        do {
            for (int r = 0; r < n; r++) {
                s[r] = st;                                // clear row r
                s[r][cols[r]] = 'Q';                      // place row r's queen at cols[r]
            }
            if (check(s, n))                              // keep only boards with no diagonal clash
                ans.push_back(s);
        } while (next_permutation(cols.begin(), cols.end())); // visit all n! permutations
        return ans;
    }
};

int main() {
    {
        Solution sol;
        auto res = sol.solveNQueens(4);
        cout << "n = 4\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\".Q..\",\"...Q\",\"Q...\",\"..Q.\"],[\"..Q.\",\"Q...\",\"...Q\",\".Q..\"]]\n\n";
    }
    {
        Solution sol;
        auto res = sol.solveNQueens(1);
        cout << "n = 1\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\"Q\"]]\n";
    }
    return 0;
}
```

</details>

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

**Pseudocode**

```text
 1 │ function solveNQueens(n):
 2 │   colUsed ← array of n values, all false
 3 │   diag ← array of 2n−1 values, all false   // index r−c+n−1 names one diagonal
 4 │   anti ← array of 2n−1 values, all false   // index r+c names one anti-diagonal
 5 │   board ← n strings, each of n '.' characters
 6 │   result ← empty list
 7 │   place(0)   // fill rows starting from row 0
 8 │   return result
 9 │ function place(r):
10 │   if r = n:
11 │     append a copy of board to result   // every row holds a safe queen
12 │     return
13 │   for c ← 0 to n−1:
14 │     if colUsed[c] or diag[r−c+n−1] or anti[r+c]:   // O(1) attack test
15 │       continue   // a queen in an earlier row attacks (r, c)
16 │     colUsed[c] ← true; diag[r−c+n−1] ← true; anti[r+c] ← true
17 │     board[r][c] ← 'Q'
18 │     place(r+1)   // try to complete rows r+1..n−1
19 │     colUsed[c] ← false; diag[r−c+n−1] ← false; anti[r+c] ← false   // undo: state again covers rows 0..r−1 only
20 │     board[r][c] ← '.'
```

**Time complexity: `O(n!)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursive calls of place (lines 9-20) | at most about n·(n−1)·(n−2)·… ≈ n! partial placements | Row r can use at most n−r columns that no earlier queen occupies, and diagonal pruning cuts far more branches. |
| Column loop inside each call (lines 13-20) | n iterations × O(1) | Each candidate cell is tested with three array lookups instead of scanning the board. |
| Copying a solution (line 11) | S solutions × O(n^2) | Each finished board has n strings of length n to copy. |
| Setup (lines 2-6) | O(n^2) | Allocates the flag arrays and the n×n board once. |

- **Adding it up:** (number of calls ≈ n!) × n checks + S·n^2 copies + n^2 setup; the search term dominates, so it is roughly O(n!) (more precisely bounded by O(n·n!), and in practice much smaller because of diagonal pruning)
- **Best vs worst case:** Every input explores the full search tree since all solutions are required, so there is no separate best case; cost depends only on n.
- **At the maximum input:** n = 9 → about 350 solutions and only tens of thousands of explored partial boards, which finishes in well under a millisecond

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Flag arrays colUsed, diag, anti (lines 2-4) | n + (2n−1) + (2n−1) = 5n−2 booleans | One flag per column, per diagonal and per anti-diagonal. |
| Recursion stack (line 18) | depth n+1 × O(1) frame | One call per row being filled, plus the final r = n call. |

- **Adding it up:** O(n) flags + O(n) stack = O(n)
- **Not counted:** The result list (S boards of n^2 chars) is output and not counted. The single n×n scratch board has the same shape as one output entry and is counted with the output; if you count it as auxiliary, space is O(n^2).

**Dry run** on `n = 4`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 5 | All flags start false: colUsed has 4 entries, diag and anti have 2·4−1 = 7 entries each. The board is empty, and then place(0) is called. | `n = 4`<br>`colUsed = [F, F, F, F]`<br>`diag = [F, F, F, F, F, F, F]`<br>`anti = [F, F, F, F, F, F, F]`<br>`board = 4×4 table: [., ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]`<br>`result = []` |
| 2 | 17 | Row 0, column 0 is free, so we mark colUsed[0], diag[0−0+3]=diag[3] and anti[0+0]=anti[0], and put a queen at (0,0). | `r = 0`<br>`c = 0`<br>`colUsed = [T, F, F, F]` (c→0)<br>`diag = [F, F, F, T, F, F, F]`<br>`anti = [T, F, F, F, F, F, F]`<br>`board = 4×4 table: [Q, ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]` (q→[0,0]) |
| 3 | 14 | In row 1, c=0 is blocked by colUsed[0]. Now c=1 has diag[1−1+3]=diag[3] true, so (1,1) is on the queen's diagonal and is skipped. | `r = 1`<br>`c = 1`<br>`colUsed = [T, F, F, F]` (c→1)<br>`board = 4×4 table: [Q, ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]` |
| 4 | 17 | c=2 in row 1: colUsed[2], diag[2] and anti[3] are all false, so the cell is safe. We set them and place a queen at (1,2). | `c = 2`<br>`colUsed = [T, F, T, F]` (c→2)<br>`diag = [F, F, T, T, F, F, F]`<br>`anti = [T, F, F, T, F, F, F]`<br>`board = 4×4 table: [Q, ., ., .] [., ., Q, .] [., ., ., .] [., ., ., .]` (q→[1,2]) |
| 5 | 14 | In row 2, c=0 and c=2 hit used columns and c=1 hits anti[3]. The last option, c=3, hits diag[2−3+3]=diag[2], so row 2 has no safe cell and place(2) returns. | `r = 2`<br>`c = 3`<br>`colUsed = [T, F, T, F]` (c→3)<br>`board = 4×4 table: [Q, ., ., .] [., ., Q, .] [., ., ., .] [., ., ., .]` |
| 6 | 20 | Back in row 1, we undo the queen at (1,2) by clearing colUsed[2], diag[2] and anti[3]. The state again describes only row 0. | `r = 1`<br>`c = 2`<br>`colUsed = [T, F, F, F]` (c→2)<br>`diag = [F, F, F, T, F, F, F]`<br>`anti = [T, F, F, F, F, F, F]`<br>`board = 4×4 table: [Q, ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]` |
| 7 | 17 | Row 1, c=3 is safe because colUsed[3], diag[1] and anti[4] are false. A queen goes on (1,3). | `c = 3`<br>`colUsed = [T, F, F, T]` (c→3)<br>`diag = [F, T, F, T, F, F, F]`<br>`anti = [T, F, F, F, T, F, F]`<br>`board = 4×4 table: [Q, ., ., .] [., ., ., Q] [., ., ., .] [., ., ., .]` (q→[1,3]) |
| 8 | 17 | Row 2: c=0 is a used column, and c=1 is safe (colUsed[1], diag[4] and anti[3] are false). A queen goes on (2,1). | `r = 2`<br>`c = 1`<br>`colUsed = [T, T, F, T]` (c→1)<br>`diag = [F, T, F, T, T, F, F]`<br>`anti = [T, F, F, T, T, F, F]`<br>`board = 4×4 table: [Q, ., ., .] [., ., ., Q] [., Q, ., .] [., ., ., .]` (q→[2,1]) |
| 9 | 14 | In row 3, columns 0, 1 and 3 are used. c=2 hits diag[3−2+3]=diag[4], set by the queen at (2,1), so this branch is another dead end. | `r = 3`<br>`c = 2`<br>`colUsed = [T, T, F, T]` (c→2)<br>`board = 4×4 table: [Q, ., ., .] [., ., ., Q] [., Q, ., .] [., ., ., .]` |
| 10 | 20 | Several undos happen here (skipped): (2,1) is cleared, (2,2) and (2,3) fail, (1,3) is cleared and row 1 runs out of columns. Finally (0,0) is cleared, so a queen at (0,0) leads to no solution and every flag is false again. | `r = 0`<br>`c = 0`<br>`colUsed = [F, F, F, F]` (c→0)<br>`diag = [F, F, F, F, F, F, F]`<br>`anti = [F, F, F, F, F, F, F]`<br>`board = 4×4 table: [., ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]` |
| 11 | 17 | Row 0, c=1 is tried next. We mark colUsed[1], diag[0−1+3]=diag[2] and anti[1], and place a queen at (0,1). | `c = 1`<br>`colUsed = [F, T, F, F]` (c→1)<br>`diag = [F, F, T, F, F, F, F]`<br>`anti = [F, T, F, F, F, F, F]`<br>`board = 4×4 table: [., Q, ., .] [., ., ., .] [., ., ., .] [., ., ., .]` (q→[0,1]) |
| 12 | 17 | Row 1: c=0 hits anti[1], c=1 is a used column and c=2 hits diag[2]. c=3 is safe (diag[1] and anti[4] are free), so a queen goes on (1,3). | `r = 1`<br>`c = 3`<br>`colUsed = [F, T, F, T]` (c→3)<br>`diag = [F, T, T, F, F, F, F]`<br>`anti = [F, T, F, F, T, F, F]`<br>`board = 4×4 table: [., Q, ., .] [., ., ., Q] [., ., ., .] [., ., ., .]` (q→[1,3]) |
| 13 | 17 | Row 2, c=0 is safe because colUsed[0], diag[5] and anti[2] are false. A queen goes on (2,0). | `r = 2`<br>`c = 0`<br>`colUsed = [T, T, F, T]` (c→0)<br>`diag = [F, T, T, F, F, T, F]`<br>`anti = [F, T, T, F, T, F, F]`<br>`board = 4×4 table: [., Q, ., .] [., ., ., Q] [Q, ., ., .] [., ., ., .]` (q→[2,0]) |
| 14 | 17 | Row 3: columns 0 and 1 are used, and c=2 has colUsed[2], diag[4] and anti[5] all false. A queen goes on (3,2). | `r = 3`<br>`c = 2`<br>`colUsed = [T, T, T, T]` (c→2)<br>`diag = [F, T, T, F, T, T, F]`<br>`anti = [F, T, T, F, T, T, F]`<br>`board = 4×4 table: [., Q, ., .] [., ., ., Q] [Q, ., ., .] [., ., Q, .]` (q→[3,2]) |
| 15 | 11 | place(4) is called with r = n, so all 4 rows hold mutually safe queens. The board is copied into result. | `r = 4`<br>`colUsed = [T, T, T, T]`<br>`board = 4×4 table: [., Q, ., .] [., ., ., Q] [Q, ., ., .] [., ., Q, .]`<br>`result = [[.Q.., ...Q, Q..., ..Q.]]` |
| 16 | 8 | The rest of the search runs the same way (skipped). Starting from (0,2) it finds the mirror solution, and (0,3) finds nothing. Every flag is cleared on the way back, and result holds 2 boards. | `colUsed = [F, F, F, F]`<br>`diag = [F, F, F, F, F, F, F]`<br>`anti = [F, F, F, F, F, F, F]`<br>`board = 4×4 table: [., ., ., .] [., ., ., .] [., ., ., .] [., ., ., .]`<br>`result = [[.Q.., ...Q, Q..., ..Q.], [..Q., Q..., ...Q, .Q..]]` |

**Result:** [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]. Every column choice in every row was tried, and a branch was cut only when a flag proved an attack, so all valid boards and only valid boards were recorded.

**C++ solution**

```cpp
class Solution {
public:
    vector<vector<string>> ans;          // collected solutions
    vector<bool> colUsed, diag, anti;    // attack flags for columns, diagonals, anti-diagonals

    // O(1) check: is cell (r, c) attacked by a queen in rows 0..r-1?
    bool valid(vector<string>& s, int r, int c)
    {
        int n = s.size();
        return !colUsed[c] && !diag[r - c + n - 1] && !anti[r + c]; // r-c+n-1 shifts the diagonal id into [0, 2n-2]
    }

    // place a queen in row r, given that rows 0..r-1 are already filled safely
    void nqueen(vector<string>& s, int r, int n)
    {
        if (r == n)                      // all rows filled: s is a full solution
        {
            ans.push_back(s);            // store a copy of the board
            return;
        }
        for (int c = 0; c < n; c++)
        {
            if (!valid(s, r, c)) continue;          // attacked: skip this column
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = true; // claim column and both diagonals
            s[r][c] = 'Q';
            nqueen(s, r + 1, n);                    // fill the remaining rows
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = false; // undo so state covers rows 0..r-1 only
            s[r][c] = '.';
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        ans.clear();                                 // allow reuse of the same object
        colUsed.assign(n, false);                    // one flag per column
        diag.assign(2 * n - 1, false);               // 2n-1 diagonals (r-c constant)
        anti.assign(2 * n - 1, false);               // 2n-1 anti-diagonals (r+c constant)
        string s(n, '.');
        vector<string> v(n, s);                      // empty n x n board
        nqueen(v, 0, n);                             // start from row 0
        return ans;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

string boardsToString(const vector<vector<string>>& b) {
    string out = "[";
    for (size_t i = 0; i < b.size(); i++) {
        if (i) out += ",";
        out += "[";
        for (size_t j = 0; j < b[i].size(); j++) {
            if (j) out += ",";
            out += "\"" + b[i][j] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> ans;          // collected solutions
    vector<bool> colUsed, diag, anti;    // attack flags for columns, diagonals, anti-diagonals

    // O(1) check: is cell (r, c) attacked by a queen in rows 0..r-1?
    bool valid(vector<string>& s, int r, int c)
    {
        int n = s.size();
        return !colUsed[c] && !diag[r - c + n - 1] && !anti[r + c]; // r-c+n-1 shifts the diagonal id into [0, 2n-2]
    }

    // place a queen in row r, given that rows 0..r-1 are already filled safely
    void nqueen(vector<string>& s, int r, int n)
    {
        if (r == n)                      // all rows filled: s is a full solution
        {
            ans.push_back(s);            // store a copy of the board
            return;
        }
        for (int c = 0; c < n; c++)
        {
            if (!valid(s, r, c)) continue;          // attacked: skip this column
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = true; // claim column and both diagonals
            s[r][c] = 'Q';
            nqueen(s, r + 1, n);                    // fill the remaining rows
            colUsed[c] = diag[r - c + n - 1] = anti[r + c] = false; // undo so state covers rows 0..r-1 only
            s[r][c] = '.';
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        ans.clear();                                 // allow reuse of the same object
        colUsed.assign(n, false);                    // one flag per column
        diag.assign(2 * n - 1, false);               // 2n-1 diagonals (r-c constant)
        anti.assign(2 * n - 1, false);               // 2n-1 anti-diagonals (r+c constant)
        string s(n, '.');
        vector<string> v(n, s);                      // empty n x n board
        nqueen(v, 0, n);                             // start from row 0
        return ans;
    }
};

int main() {
    {
        Solution sol;
        auto res = sol.solveNQueens(4);
        cout << "n = 4\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\".Q..\",\"...Q\",\"Q...\",\"..Q.\"],[\"..Q.\",\"Q...\",\"...Q\",\".Q..\"]]\n\n";
    }
    {
        Solution sol;
        auto res = sol.solveNQueens(1);
        cout << "n = 1\nOutput:   " << boardsToString(res) << "\n";
        cout << "Expected: [[\"Q\"]]\n";
    }
    return 0;
}
```

</details>

**Why this is the best:** No polynomial algorithm is known for listing all solutions, and the output itself can be large, so exponential search is unavoidable. This approach removes all redundant checking. The cost is careful bookkeeping: every flag set on the way down must be undone on the way back.

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 1 of 8 | 2026-11-24 |

For comparison, the optimal approach (Backtracking with column/diagonal sets) runs in `O(n!) roughly` time and `O(n) besides output` space.

```cpp
class Solution {
public:
    vector<vector<string>> ans;
    bool valid(vector<string>& s, int r, int c)
    {
        int n = s.size();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(s[i][j]=='Q')
                {
                    if(i==r || (i+j == r+c) || (r-i == c-j) )
                        return false;
                }
            }
        }
        return true;
    }
    void nqueen(vector<string>& s, int c, int n)
    {
        if(c==n)
        {
            ans.push_back(s);
            return;
        }
        for(int i=0;i<n;i++)
        {
            s[i][c]='Q';
            if(valid(s,i,c))
                nqueen(s,c+1,n);
            s[i][c]='.';
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        string s(n,'.');
        vector<string> v(n,s);
        nqueen(v,0,n);
        return ans;
    }
};
```

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
