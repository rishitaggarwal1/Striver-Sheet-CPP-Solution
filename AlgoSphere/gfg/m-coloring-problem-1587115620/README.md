# M-Coloring Problem

**GeeksforGeeks** · **Medium** · [Open the problem](https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1)

**Contents:** [Problem](#problem) · [Hints](#hints) · [Test cases](#test-cases)

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
