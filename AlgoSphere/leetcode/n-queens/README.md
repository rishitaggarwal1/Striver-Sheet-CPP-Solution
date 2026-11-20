# N-Queens

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/n-queens/)

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
