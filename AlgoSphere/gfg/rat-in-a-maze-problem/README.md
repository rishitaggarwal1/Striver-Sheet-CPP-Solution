# Rat in Maze

**GeeksforGeeks** · **Medium** · [Open the problem](https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1)

**Contents:** [Problem](#problem) · [Hints](#hints) · [Test cases](#test-cases)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a square binary matrix maze[][] containing values 0 and 1, find all possible paths for a rat to travel from the top-left cell to the bottom-right cell. The rat can move in four directions: up(U), down(D), left(L), and right(R).

- 1 represents an open cell through which the rat can move.

- 0 represents a blocked cell that cannot be traversed.

The rat can move only through open cells and cannot visit the same cell more than once in a path. Return all valid paths as strings consisting of 'U', 'D', 'L', and 'R', representing the sequence of moves taken by the rat.

Note: Return the paths in lexicographically increasing order. If no valid path exists, return an empty list.

Examples:

Input: maze[][] = [[1, 0, 0, 0], [1, 1, 0, 1], [1, 1, 0, 0], [0, 1, 1, 1]]
Output: ["DDRDRR", "DRDDRR"]
Explanation: There are two valid paths from the source cell (0, 0) to the destination cell (3, 3).

Input: maze[][] = [[1, 0], [1, 0]]
Output: []
Explanation: No path exists as the destination cell (1, 1) is blocked.

Constraints:
2 ≤ n ≤ 5
0 ≤ maze[i][j] ≤ 1
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to list every distinct route from the top-left cell to the bottom-right cell that only steps on cells marked 1, moves one step up, down, left or right at a time, and never steps on the same cell twice in one route. Each route is written as its sequence of move letters, and the list must come out sorted alphabetically.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In the first example, both paths start with `D`, and the first place they differ is the second move, where `D` comes before `R`. Also notice that if the start cell or the destination cell is 0, the answer is empty right away, as in the second example.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n` at most 5 there are at most 25 cells, so exploring every simple path is affordable even though the count grows exponentially in general. That tiny bound is the hint: the problem expects exhaustive enumeration rather than a clever polynomial method, which could not list all paths anyway.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking (depth-first search that undoes its choices). You extend a partial path one step at a time, record it when it reaches the goal, and step back to try other options, because you need every complete path and not just one.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

If you always try the four moves in alphabetical order `D`, `L`, `R`, `U`, the paths are discovered already in lexicographic order, so no sort is needed. To keep each path simple, mark a cell as visited when you enter it and unmark it when you return, so other paths can still use it.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track the current cell `(r, c)`, the move string built so far, a visited grid (or temporarily set the maze cell to 0) showing which cells are on the current path, and a result list of finished paths. Keep a fixed list of direction steps paired with their letters: `D=(+1,0)`, `L=(0,-1)`, `R=(0,+1)`, `U=(-1,0)`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

If `maze[0][0]` or `maze[n-1][n-1]` is 0, return an empty list.
Start exploring from `(0,0)` with an empty move string and mark the start as visited.
When the current cell is `(n-1,n-1)`, add the move string to the results and go back.
Otherwise, for each direction in order D, L, R, U, compute the neighbor cell.
If the neighbor is inside the grid, open, and not visited, mark it, append the letter, and explore from it.
After that call returns, remove the letter and unmark the neighbor.
Return the result list.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is undoing your changes: forgetting to unmark a cell or to remove the last letter quietly loses valid paths or corrupts later ones. Check the edge cases: a blocked start or end gives an empty list, and an all-ones grid gives many paths, which is still fine for `n=5`. Time is exponential, roughly `O(4^(n^2))` in the worst case or about `O(3^(n^2))` since you never step straight back, and extra space is `O(n^2)` for the recursion depth and visited grid, not counting the output.

</details>

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| mat = [[1,1],[1,1]] | ["DR", "RD"] | Fully open 2x2 grid gives two paths. |
| mat = [[1,1,1],[1,0,1],[1,1,1]] | ["DDRR", "RRDD"] | Blocked center forces border paths. |
| mat = [[1,1,0],[1,1,0],[0,1,1]] | ["DRDR", "RDDR"] | Open 2x2 block with dead-end loops. |
| mat = [[1,1,1,1],[0,0,0,1],[1,1,1,1],[1,0,0,1]] | ["RRRDDD"] | Unique path with a dead-end branch. |
| mat = [[1,0,0],[1,1,1],[0,0,1]] | ["DRRD"] | Single winding corridor. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Blocked source | mat = [[0,1],[1,1]] | [] | No paths. |
| Blocked destination | mat = [[1,1],[1,0]] | [] | No paths. |
| Disconnected corners | mat = [[1,0],[0,1]] | [] | No route exists. |
| Edge corridor | mat = [[1,0,0],[1,0,0],[1,1,1]] | ["DDRR"] | Single path along left and bottom. |
| All open | mat = [[1,1,1],[1,1,1],[1,1,1]] | ["DDRR", "DDRURD", "DDRUURDD", "DRDR", "DRRD", "DRURDD", "RDDR", "RDLDRR", "RDRD", "RRDD", "RRDLDR", "RRDLLDRR"] | All 12 self-avoiding paths in sorted order. |
| All zeros | mat = [[0,0],[0,0]] | [] | No paths. |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
