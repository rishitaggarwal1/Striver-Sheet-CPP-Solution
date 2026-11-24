# Sudoku Solver

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/sudoku-solver/)

## Problem

<details>
<summary>Problem statement</summary>

```text
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

- Each of the digits 1-9 must occur exactly once in each row.

- Each of the digits 1-9 must occur exactly once in each column.

- Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.

The '.' character indicates empty cells.

Example 1:

Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
Explanation: The input board is shown above and the only valid solution is shown below:

Constraints:

- board.length == 9

- board[i].length == 9

- board[i][j] is a digit or '.'.

- It is guaranteed that the input board has only one solution.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You are given a partially filled 9x9 grid and must fill every empty cell with a digit 1-9 so that no digit repeats in any row, any column, or any of the nine 3x3 boxes. You modify the board in place, and exactly one valid completion exists.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Each empty cell's legal digits are limited by three groups at once: its row, its column, and its box. In the example, some cells have only one digit not already used by those groups. Also, choosing a digit for one cell immediately shrinks the options for every cell that shares a group with it.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

The board is always 9x9, so input size is not the issue; the size of the search is. Trying all 9 digits in every empty cell blindly is about `9^k` combinations for `k` empty cells, which is hopeless. You need to throw away a bad partial assignment the moment it breaks a rule, instead of only checking full boards.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking, a depth-first search over choices with undo. It fits because you make one decision per cell, can detect a conflict right away, and must be able to reverse a decision when it leads to a dead end.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Place a digit only if it is currently legal for that cell's row, column, and box, then recurse to the next empty cell. If some later cell has no legal digit, undo the most recent placement and try that cell's next digit. Checking legality must be `O(1)` so the search stays fast.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep three 9-entry lookup tables, each entry being a set of used digits: one per row, one per column, and one per box, where the box index is `(r / 3) * 3 + (c / 3)`. Also keep a list of the empty cell positions so the recursion can walk through them by index. Optionally, store each table entry as a 9-bit mask, so the free digits of a cell are the bits set in none of its row, column, or box masks.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Scan the board once, recording the given digits in the row, column, and box tables and collecting the empty cells.
Define a recursive step that takes an index into the empty-cell list.
If the index equals the list length, every cell is filled, so report success.
For the current cell, try each digit 1-9 that is unused in its row, column, and box.
Place the digit on the board, mark it in all three tables, and recurse on the next index.
If the recursion succeeds, return success right away; otherwise unmark the digit and restore the cell to '.'.
If no digit works, return failure so the caller backtracks.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is undoing correctly: on failure, remove the digit from all three tables and reset the cell. Also stop the search as soon as a full solution is found, or later backtracking will erase it. A board that starts completely filled should succeed immediately. A big speedup is to always branch next on the empty cell with the fewest legal digits (most constrained first). The worst-case time is exponential, roughly `O(9^k)` for `k` empty cells, but pruning makes it very fast on a 9x9 board. Extra space is `O(1)` for the fixed-size tables plus recursion depth up to 81.

</details>

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
