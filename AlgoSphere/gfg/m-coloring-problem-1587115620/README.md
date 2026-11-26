# M-Coloring Problem

**GeeksforGeeks** · **Medium** · [Open the problem](https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1) · Pattern: **Backtracking (constraint satisfaction)**

> Decide whether each of the V vertices can be given one of m colors so that every edge joins two different colors.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given an undirected graph consisting of V vertices represented by an adjacency list adj[][] and an integer m, check whether the graph can be colored using at most m different colors such that no two adjacent vertices have the same color.

Note: The graph uses 0-based indexing and may be connected or disconnected.

Examples:

Input: adj[][] = [[1, 3, 2], [0, 3], [3, 0], [1, 2, 0]], m = 3
Output: true
Explanation: It is possible to color the given graph using 3 colors, for example, one of the possible ways vertices can be colored as follows:

Vertex 0: Color 1
Vertex 1: Color 2
Vertex 2: Color 2
Vertex 3: Color 3

Input: adj[][] = [[1, 2], [0, 2], [0, 1]], m = 2
Output: false
Explanation: It is not possible to color the given graph using only 2 colors because vertices 0, 1, and 2 form a triangle.

Constraints:
1 ≤ V ≤ 10
1 ≤ E = edges.size() ≤ (V*(V-1))/2
0 ≤ edges[i][j] ≤ V-1
1 ≤ m ≤ V
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You must decide whether you can give every vertex one of `m` labels so that no edge joins two vertices with the same label. You only need a yes or no answer, not the actual coloring.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In the second example, vertices 0, 1 and 2 form a triangle, so they need three different colors. In general, once a vertex's neighbors are colored, only some of its color choices remain legal, and each choice limits the vertices that come after it.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

`V` is at most 10, so trying every assignment means at most `m^V` combinations, roughly `10^10` in the worst case. That is too many to enumerate blindly, but if you reject partial assignments as soon as they break a rule, the real search is tiny. Exponential time is fine here; polynomial time is not expected, because graph coloring is NP-complete.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking: build the assignment one decision at a time and undo a choice when it leads to a dead end. It fits because the constraints are local, so a conflict shows up the moment a bad color is placed.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Color the vertices in a fixed order, 0 through V-1. For each vertex, try only colors that no already-colored neighbor uses. If no color works, return to the previous vertex and try its next color.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep an array `color[v]`, where 0 means uncolored and 1 to `m` is the assigned color. To check whether color `c` is safe for vertex `v`, scan `adj[v]` and make sure no neighbor has `color[u] == c`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Start a recursive solve at vertex 0 with every vertex uncolored.
If the current index equals V, every vertex is colored, so return true.
For each color c from 1 to m, check whether c is safe for the current vertex.
If it is safe, assign it and recurse on the next vertex.
If the recursion returns true, propagate true upward.
Otherwise reset the vertex to uncolored and try the next color.
If no color works, return false.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is undoing the assignment (resetting `color[v]` to 0) after a failed branch, so later safety checks see correct state. Disconnected graphs and isolated vertices need no special handling, because the fixed vertex order reaches every vertex. If the input gives an edge list rather than an adjacency list, build the adjacency list first and add both directions. Time is `O(m^V * V)` in the worst case, but pruning makes it fast for V up to 10. Space is `O(V)` for the color array and the recursion stack.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| `1 ≤ V ≤ 10` and `m ≤ V` | the limits are tiny, which is a strong hint that exponential search over color assignments is intended. |
| "no two adjacent vertices have the same color" | each choice only constrains its neighbours, so a partial assignment can be checked one vertex at a time and abandoned as soon as it fails. |
| Example 2: the triangle 0-1-2 with m = 2 fails | graph coloring is NP-complete in general, and no greedy rule decides it. You must search, then prune. |
| "may be connected or disconnected" | process vertices by index 0..V-1 rather than by BFS from one source, so every component gets colored. |

### What the constraints tell you

V ≤ 10 and m ≤ 10 give at most m^V = 10^10 full assignments. That is too many to enumerate blindly in the worst case. Backtracking prunes a branch the moment a vertex clashes with an already-colored neighbour, so far fewer nodes are visited in practice. Target: exponential backtracking with an O(deg) safety check per placement.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most naive way to answer yes or no?**

<details>
<summary>Answer</summary>

Try every assignment of m colors to the V vertices, which is m^V of them, and check every edge for each. If any assignment has no edge with equal endpoint colors, return true.

</details>

**Q2. Is there a polynomial shortcut, like bipartite checking?**

<details>
<summary>Answer</summary>

Only when m = 2, where BFS 2-coloring works. For m ≥ 3, deciding k-colorability is NP-complete, so the tiny bound V ≤ 10 is telling us to search.

</details>

**Q3. Where does the naive enumeration waste work?**

<details>
<summary>Answer</summary>

Suppose vertices 0 and 1 are adjacent and both got color 1. Brute force still enumerates all m^(V-2) completions of that already-broken prefix before rejecting each one.

</details>

**Q4. How do we detect a conflict early?**

<details>
<summary>Answer</summary>

Color vertices in order 0, 1, 2, and so on. Before giving vertex v color c, scan adj[v] and reject c if any already-colored neighbour has c. A failure therefore cuts off the whole subtree under that prefix.

</details>

**Q5. What makes the backtracking correct?**

<details>
<summary>Answer</summary>

Invariant: when we reach vertex v, vertices 0..v-1 form a valid partial coloring. If no color in 1..m keeps it valid, this prefix cannot be extended, so we undo it and try the next color for v-1. If we reach v == V, a full valid coloring exists.

</details>

**Q6. Can we prune more?**

<details>
<summary>Answer</summary>

Symmetry breaking helps: a vertex never needs a color more than one above the highest color used so far, because the color names are interchangeable. Return true immediately if m ≥ V. These are optimisations, but the core is the safe-check backtracking.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Enumerate all m^V colorings](#1-brute-force-enumerate-all-mv-colorings) | `O(m^V · (V+E))` | `O(V)` |
| 2 | [Better: Backtracking with full check at each step](#2-better-backtracking-with-full-check-at-each-step) | `O(m^V · E) worst case` | `O(V)` |
| 3 | [Optimal: Backtracking with local isSafe check](#3-optimal-backtracking-with-local-issafe-check) | `O(m^V · V) worst case, heavily pruned in practice` | `O(V)` |

### 1. Brute force: Enumerate all m^V colorings

> **Where you start:** The question is about existence over a finite set of assignments, so the obvious move is to try them all and test each one.

**Idea.** Treat the coloring as a V-digit number in base m and iterate over all m^V values. For each full assignment, check every edge (u, w) in adj and require color[u] != color[w]. It is correct because it literally checks every possibility. It does no pruning at all.

**Steps**

1. Create an array color of size V, initially all color 0.
2. Loop over every assignment by incrementing color like a base-m counter.
3. For each assignment, scan every vertex u and every w in adj[u].
4. If any color[u] == color[w], this assignment is invalid; move on.
5. If an assignment passes all edges, return true.
6. After all m^V assignments, return false.

**Complexity:** time `O(m^V · (V+E))`, space `O(V)`. There are m^V assignments, and each one gets a full edge scan of O(V+E). The only extra memory is the color array.

**Why move on:** With m = V = 10 this is 10^10 assignments times up to 45 edges each, which is far too slow. Invalid prefixes are expanded completely before being rejected.

### 2. Better: Backtracking with full check at each step

> **How you get here:** Most assignments are already doomed after a few vertices. Building the coloring incrementally lets us stop at the first clash instead of finishing it.

**Idea.** Recursively assign colors to vertices 0..V-1. After placing a color on v, verify the whole partial coloring by scanning all edges among the colored vertices. If it is invalid, try the next color; if no color works, backtrack. Pruning makes the search much smaller, but each validity check costs O(E).

**Steps**

1. Call solve(0) with color all unset.
2. In solve(v): if v == V, return true.
3. For each c in 1..m, set color[v] = c.
4. Scan all edges among vertices 0..v and reject if two endpoints share a color.
5. If the check is valid and solve(v+1) returns true, return true.
6. Reset color[v] and return false after all colors fail.

**Complexity:** time `O(m^V · E) worst case`, space `O(V)`. The search tree is pruned, but each node pays O(E) to recheck every edge. Memory is the color array plus a recursion stack of depth V.

**Why move on:** Rechecking every edge repeats work. Only the edges touching v can have become invalid, because everything before v was already validated.

### 3. Optimal: Backtracking with local isSafe check

> **How you get here:** The prefix 0..v-1 is already valid by the invariant, so the only new conflicts can come from the edges of vertex v. Checking just adj[v] is enough.

**Idea.** Assign vertices in index order, which covers disconnected components too. For vertex v, try each color c in 1..m and accept it only if no neighbour in adj[v] already holds c (uncolored neighbours are 0, so they never clash). Recurse to v+1, and undo on failure. The invariant that 0..v-1 is always properly colored makes the local check sufficient, and reaching v == V proves a valid coloring exists. Optional speedups: return true at once if m ≥ V, and do not try a color more than one above the maximum color used so far, because color names are interchangeable.

**Steps**

1. If m ≥ V, return true right away.
2. Create an array color of size V, all set to 0 (uncolored).
3. solve(v): if v == V, return true.
4. For c from 1 to m: check every u in adj[v]; c is safe if no color[u] == c.
5. If c is safe, set color[v] = c and return true if solve(v+1) succeeds.
6. Otherwise reset color[v] = 0 and try the next c.
7. Return false if no color worked; the answer is solve(0).

**Complexity:** time `O(m^V · V) worst case, heavily pruned in practice`, space `O(V)`. The worst case is the size of the search tree, up to m^V leaves, with an O(deg(v)) ≤ O(V) safety check at each node. Memory is the color array and a recursion depth of V.

**Why this is the best:** It is still exponential, which is unavoidable because m-colorability is NP-complete. DP over subsets of independent sets, O(2^V·V) or O(3^V), is an alternative, but at V ≤ 10 backtracking is simpler and fast enough.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| adj = [[1,3],[0,2],[1,3],[2,0]]<br>m = 2 | true | 4-cycle is bipartite, so 2 colors suffice. |
| adj = [[1,4],[0,2],[1,3],[2,4],[3,0]]<br>m = 2 | false | Odd 5-cycle cannot be 2-colored. |
| adj = [[1,4],[0,2],[1,3],[2,4],[3,0]]<br>m = 3 | true | Odd 5-cycle can be 3-colored. |
| adj = [[1,2,3],[0,2,3],[0,1,3],[0,1,2]]<br>m = 3 | false | K4 needs 4 colors. |
| adj = [[1,2],[0,2],[0,1],[4],[3]]<br>m = 3 | true | Disconnected graph with a triangle and an edge. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single color | adj = [[1],[0]]<br>m = 1 | false | One edge cannot be colored with one color. |
| Minimal graph | adj = [[1],[0]]<br>m = 2 | true | Two vertices, one edge, two colors. |
| Complete graph | adj = [[1,2,3],[0,2,3],[0,1,3],[0,1,2]]<br>m = 4 | true | K4 with m equal to V. |
| Star graph | adj = [[1,2,3,4],[0],[0],[0],[0]]<br>m = 2 | true | Bipartite, 2 colors suffice. |
| Odd wheel | adj = [[1,2,3,4,5],[0,2,5],[0,1,3],[0,2,4],[0,3,5],[0,4,1]]<br>m = 3 | false | Hub plus 5-cycle needs 4 colors. |
| Max V | adj = [[1],[0],[3],[2],[5],[4],[7],[6],[9],[8]]<br>m = 2 | true | Ten vertices as five disjoint edges. |

## Mistakes and edge cases

**Common mistakes**

- Using a greedy coloring (the smallest available color per vertex) and declaring false if it uses more than m colors. Greedy can use more colors than needed, so you must backtrack when it fails.
- Forgetting to reset color[v] = 0 when backtracking. Stale colors then make later isSafe checks reject valid choices.
- Coloring only one component via BFS/DFS from vertex 0. The graph may be disconnected, so iterate over all vertex indices.
- Letting 0 mean both "uncolored" and a real color. Uncolored neighbours then falsely clash; use colors 1..m with 0 as unset.

**Edge cases to check**

- A vertex with an empty adjacency list (isolated): any color works, and it must not crash the loop over adj[v].
- m = 1 with at least one edge: the answer must be false. With no edges at all it is true.
- m ≥ V: the answer is always true, since every vertex can get its own color. This is a useful shortcut against worst-case search.
- A complete graph K_V with m = V-1: this explores a large tree before returning false, so it stress-tests the pruning.
- A triangle with m = 2, as in example 2: an odd cycle needs 3 colors even though every vertex has degree 2.

## Practice next

- [N-Queens](https://leetcode.com/problems/n-queens/) · Place items one at a time with a local safety check against earlier placements, and backtrack when stuck.
- [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) · This is graph coloring with 9 colors on a fixed constraint graph, solved by the same try-check-undo loop.
- [Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/) · The special case m = 2, which becomes polynomial via BFS/DFS 2-coloring.
- [Flower Planting With No Adjacent](https://leetcode.com/problems/flower-planting-with-no-adjacent/) · Coloring where degree ≤ 3 and 4 colors guarantee that greedy works. It shows when search is unnecessary.

## Takeaways

- Tiny limits like V ≤ 10 on an NP-hard decision problem signal exponential search with pruning.
- Keep the invariant "the prefix is valid" so that each new choice needs only a local check of its own constraints, not a global recheck.
- Every backtracking routine has three parts: choose, check, recurse, and undo the choice when the recursion fails.
- Symmetry breaking (treating colors as interchangeable labels) and trivial-case shortcuts (m ≥ V) can cut the search space dramatically.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
