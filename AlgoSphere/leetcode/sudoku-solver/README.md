# Sudoku Solver

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/sudoku-solver/) · Pattern: **Backtracking with constraint bitmasks**

> Fill every '.' in a 9x9 grid with a digit 1-9 so that no digit repeats in any row, column or 3x3 box. Modify `board` in place; exactly one solution exists.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "Fill the empty cells" so that every row, column and box stays valid | this is a constraint-satisfaction search: place a digit, check it, and undo it on failure (backtracking). |
| "It is guaranteed that the input board has only one solution" | the search can stop at the first complete fill, and you never need to report "no solution" for the whole board. |
| Each digit must appear "exactly once in each row/column/box" with digits 1-9 | the state of each row, column and box fits in 9 bits, so legality checks become O(1) bit operations. |
| `board.length == 9` is fixed | classical complexity in n is meaningless; what matters is how hard the search tree is pruned. |

### What the constraints tell you

The grid is fixed at 9x9 with up to 81 empty cells. Blind enumeration of 9^81 fillings is impossible, but backtracking that rejects a digit as soon as it conflicts explores only a tiny fraction of that space. So the target is a pruned search with O(1) legality checks, and ideally a smart choice of which cell to fill next.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most naive way to solve this?**

<details>
<summary>Answer</summary>

Try every digit in every empty cell and check the whole board at the end. With up to 81 blanks that is 9^81 boards, so you must detect conflicts while placing digits, not after.

</details>

**Q2. How can I prune early?**

<details>
<summary>Answer</summary>

Fill cells one at a time. Before placing digit `d` at `(r,c)`, check that `d` is not already in row `r`, column `c`, or box `(r/3)*3 + c/3`. If no digit fits, return false so the previous cell tries its next digit.

</details>

**Q3. How do I make the check "is d legal here" cheap?**

<details>
<summary>Answer</summary>

Rescanning the row, column and box costs 27 reads per check. Instead keep `rows[9]`, `cols[9]` and `boxes[9]` (booleans or 9-bit masks), filled once from the given digits. Then the check is three lookups, and placing or undoing a digit is three updates.

</details>

**Q4. Does the order in which I fill cells matter?**

<details>
<summary>Answer</summary>

Yes, a lot. Filling left-to-right may hit a cell with 7 options while another cell has only 1. Choosing the empty cell with the fewest legal digits (minimum remaining values) cuts the branching factor. A cell with 0 options fails immediately, and a cell with 1 option is forced.

</details>

**Q5. How do I count a cell's candidates quickly?**

<details>
<summary>Answer</summary>

With masks, the used digits at `(r,c)` are `rows[r] | cols[c] | boxes[b]`. The free digits are the complement within 9 bits, and popcount gives how many there are. Scanning all empty cells for the minimum costs at most 81 cheap operations per search node.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Backtracking with full rescans](#1-brute-force-backtracking-with-full-rescans) | `O(9^m · 27) where m is the number of empty cells` | `O(m) recursion depth` |
| 2 | [Better: Backtracking with row/col/box lookup tables](#2-better-backtracking-with-rowcolbox-lookup-tables) | `O(9^m) worst case, with O(1) work per tried digit` | `O(81) for tables plus O(m) recursion` |
| 3 | [Optimal: Bitmask backtracking with fewest-candidates-first](#3-optimal-bitmask-backtracking-with-fewest-candidates-first) | `Exponential worst case, but each node costs O(m) and in practice only a few hundred nodes are explored` | `O(m) recursion plus 27 integers` |

### 1. Brute force: Backtracking with full rescans

> **Where you start:** The natural recursive idea is "find the next '.', try 1-9, recurse". The simplest validity check is to scan the row, the column and the 3x3 box directly on `board`.

**Idea.** Walk the cells in row-major order. At an empty cell, try each digit 1-9 and check its row, column and box by scanning `board`. If the digit is legal, write it and recurse; if the recursion fails, reset the cell to '.' and try the next digit. Every complete filling reached this way is valid by construction, and the search tries every consistent partial assignment, so it must find the unique solution.

**Steps**

1. Find the first cell containing '.' in row-major order; if there is none, return true.
2. For each digit d from '1' to '9', scan row r, column c and the box for d.
3. If d is not found, set board[r][c] = d and recurse.
4. If the recursion returns true, propagate true upward.
5. Otherwise restore board[r][c] = '.' and try the next digit.
6. If all 9 digits fail, return false.

**Complexity:** time `O(9^m · 27) where m is the number of empty cells`, space `O(m) recursion depth`. The running time is dominated by the size of the search tree. Each node also pays a 27-cell scan per digit tried, plus a rescan to find the next empty cell. The only extra memory is the recursion stack, at most 81 frames deep.

**Why move on:** It works on typical puzzles, but every legality check repeats work that a few counters could remember. Adversarial puzzles built against row-major order can make it explore millions of nodes.

### 2. Better: Backtracking with row/col/box lookup tables

> **How you get here:** The brute force rescans 27 cells to answer "is d used in this row, column or box?", yet that answer only changes when a digit is placed or removed. Store it instead.

**Idea.** Precompute `rows[r][d]`, `cols[c][d]` and `boxes[b][d]` from the given digits, and collect the list of empty cells once. Recurse over that list by index. At each cell try digits whose three flags are all false; set the flags and the board cell, recurse, then clear them on backtrack. The flags always mirror the current board exactly, so the check is correct and costs O(1).

**Steps**

1. Initialise three 9x9 boolean tables and an empty-cell list by scanning board once.
2. Define solve(i): if i equals the list length, return true.
3. Take cell (r,c) = empties[i] and compute b = (r/3)*3 + c/3.
4. For each d with rows[r][d], cols[c][d] and boxes[b][d] all false, mark the three flags and write d.
5. Recurse solve(i+1); return true if it succeeds.
6. Otherwise unmark the flags, reset the cell to '.' and continue; return false after the loop.

**Complexity:** time `O(9^m) worst case, with O(1) work per tried digit`, space `O(81) for tables plus O(m) recursion`. Each search node now costs at most 9 constant-time checks, so the running time is just the number of nodes. The extra memory is the three 81-entry tables and the empty-cell list.

**Why move on:** Each node is cheap, but the tree can still be huge because the fixed fill order ignores how constrained each cell is. One bad early guess in a loose cell can hide a contradiction for a long time.

### 3. Optimal: Bitmask backtracking with fewest-candidates-first

> **How you get here:** The Better version branches 9 ways on whatever cell comes next, even when another empty cell has only one legal digit. Always branching on the most constrained cell shrinks the tree dramatically.

**Idea.** Store `rows[r]`, `cols[c]` and `boxes[b]` as 9-bit masks of used digits. At each step, scan the remaining empty cells and compute free = ~(rows[r]|cols[c]|boxes[b]) & 0x1FF. Pick the cell with the smallest popcount. If that count is 0, fail at once; if it is 1, the move is forced. Iterate over the set bits of free (lowbit trick), placing and undoing via XOR. This is still a complete search, so correctness holds, and it reaches dead ends as early as possible.

**Steps**

1. Build the three masks and the empty-cell list from board.
2. If no empty cells remain, return true.
3. For each remaining empty cell, compute its free mask and keep the cell with the fewest set bits.
4. If that cell has zero candidates, return false.
5. For each set bit in its free mask, toggle the bit in its row, column and box masks, write the digit, and mark the cell filled.
6. Recurse; on success return true; otherwise toggle the bits back and restore '.'.
7. Return false when the candidates are exhausted.

**Complexity:** time `Exponential worst case, but each node costs O(m) and in practice only a few hundred nodes are explored`, space `O(m) recursion plus 27 integers`. Each node pays an O(m) ≤ 81 scan to choose a cell, and that scan is what makes the branching factor close to 1 on most steps. The memory is 27 masks, the empty list and the recursion stack.

**Why this is the best:** Sudoku is NP-complete in general, so no polynomial guarantee exists. MRV trades an O(81) scan per node for a far smaller tree. Adding constraint propagation (naked or hidden singles) or Dancing Links can prune more, at the cost of more code.

## Mistakes and edge cases

**Common mistakes**

- Using the wrong box index, for example r/3 + c/3 instead of (r/3)*3 + c/3. This merges different boxes, so valid digits get rejected or invalid ones accepted.
- Forgetting to undo the row, column and box marks (or to reset the cell to '.') when backtracking. The tables then disagree with the board and the search wrongly prunes valid branches.
- Continuing the loop after a recursive call returns true. Later trials overwrite the solved cells, so you must return immediately on success.
- Comparing chars and ints carelessly: board holds '1'-'9', so the digit index is board[r][c] - '1', not board[r][c] itself.

**Edge cases to check**

- {"case":"A board with very few givens (for example 17 clues)","why":"The search is deepest here, so the performance of fill-order heuristics matters most."}
- {"case":"A board that is already complete","why":"The recursion must return true immediately without modifying anything."}
- {"case":"A cell with exactly one candidate early on","why":"MRV should take it as a forced move. A fixed order might branch elsewhere first and waste work."}
- {"case":"Puzzles designed against row-major order (the first row's solution is 987654321)","why":"These make the naive solver try many wrong digits in the first cells, which exposes slow implementations."}

## Practice next

- [Valid Sudoku](https://leetcode.com/problems/valid-sudoku/) · Uses the same row/column/box bookkeeping and the (r/3)*3 + c/3 index, without the search.
- [N-Queens](https://leetcode.com/problems/n-queens/) · Backtracking with O(1) conflict tracking per column and diagonal, placing one item per row and undoing it.
- [Word Search](https://leetcode.com/problems/word-search/) · Grid backtracking where you mark state, recurse, and unmark on return.
- [Permutations](https://leetcode.com/problems/permutations/) · The basic choose, recurse, un-choose template that Sudoku solving builds on.

## Takeaways

- In backtracking, keep incremental state (sets or bitmasks) that you update on place and undo, so legality checks are O(1) instead of rescans.
- Branch on the most constrained variable first (minimum remaining values); finding dead ends early shrinks the search tree enormously.
- When the domain is tiny (digits 1-9), bitmasks give free set operations: union with OR, complement with a mask, iterating with lowbit, and counting with popcount.
- When the input size is fixed, judge the algorithm by search-tree pruning, not by asymptotic growth in n.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
