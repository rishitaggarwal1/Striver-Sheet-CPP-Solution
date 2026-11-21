# Find Subtree Sizes After Changes

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/find-subtree-sizes-after-changes/) · Pattern: **DFS with per-character ancestor state (backtracking), then subtree-size accumulation**

> Re-hang every non-root node under its nearest original ancestor that has the same letter (if one exists), all at once, then report the subtree size of every node in the resulting tree.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a tree rooted at node 0 that consists of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.

You are also given a string s of length n, where s[i] is the character assigned to node i.

We make the following changes on the tree one time simultaneously for all nodes x from 1 to n - 1:

- Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].

- If node y does not exist, do nothing.

- Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.

Return an array answer of size n where answer[i] is the size of the subtree rooted at node i in the final tree.

Example 1:

Input: parent = [-1,0,0,1,1,1], s = "abaabc"

Output: [6,3,1,1,1,1]

Explanation:

The parent of node 3 will change from node 1 to node 0.

Example 2:

Input: parent = [-1,0,4,0,1], s = "abbba"

Output: [5,2,1,1,1]

Explanation:

The following changes will happen at the same time:

- The parent of node 4 will change from node 1 to node 0.

- The parent of node 2 will change from node 4 to node 1.

Constraints:

- n == parent.length == s.length

- 1 <= n <= 10^5

- 0 <= parent[i] <= n - 1 for all i >= 1.

- parent[0] == -1

- parent represents a valid tree.

- s consists only of lowercase English letters.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Each node may jump up and attach directly to the nearest ancestor that has the same letter as itself; if no such ancestor exists, it keeps its original parent. All jumps are decided using the original tree at the same time. After that, report how many nodes sit in each node's subtree.

</details>

<details>
<summary>Hint 2 · Observation</summary>

A node only ever moves upward along its own root-to-node path, and its new parent depends only on the letters on that path. In Example 2, node 2 looks for its nearest 'b' ancestor in the original tree (node 1), even though its original parent, node 4, is moving at the same moment.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n` up to `10^5`, the tree can be a long chain. Walking up the ancestors of every node can then cost `O(n^2)`, which is too slow. Aim for `O(n)` or `O(26n)` total work.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is DFS on a tree with path state, often described as backtracking over the current root-to-node path. During the DFS, the recursion stack is exactly the list of ancestors of the current node, so ancestor questions can be answered on the fly.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Since there are only 26 letters, you only need to know, for each letter, the deepest node on the current path that carries it. That node is exactly the closest same-letter ancestor. Subtree sizes in the new tree can then be accumulated by adding each finished node's size into its new parent's size.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep an array `last[26]` holding the most recent node of each letter on the current DFS path, with -1 meaning none. Keep a `newParent[i]` array and a `size[i]` array, where every size starts at 1. You also need child adjacency lists built from `parent`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Build children lists from the `parent` array.
Run a DFS from node 0 over the original tree.
On entering node x, set `newParent[x]` to `last[s[x]]` if that is not -1, otherwise to `parent[x]`.
Save the old value of `last[s[x]]`, set it to x, and recurse into the children.
When leaving x, restore `last[s[x]]` to the saved value.
Process nodes in post-order (children before parents) and add `size[x]` into `size[newParent[x]]`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is the size accumulation. You must add sizes in an order where every node's new descendants are finished first. Post-order of the original DFS works because the new parent is always an original ancestor. Remember to restore `last` on backtrack, and never reassign the root. Use an iterative DFS (or raise the recursion limit), since a chain of `10^5` nodes can overflow the call stack. `n = 1` simply returns [1]. Time is `O(n)` and space is `O(n + 26)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "closest node y ... such that y is an ancestor of x, and s[x] == s[y]" | while a DFS is at x, its ancestors are exactly the current root-to-x path. Keep, for each letter, the deepest node on that path with that letter. |
| "s consists only of lowercase English letters" | only 26 letters, so a fixed array `last[26]` (or 26 stacks) holds the whole path state. |
| "simultaneously for all nodes" | every new parent is looked up in the ORIGINAL tree, so all lookups can happen in one pass before any edge changes. |
| The new parent y is always an ancestor of x in the original tree | the original DFS preorder is still a valid topological order for the new tree, so sizes can be summed in reverse preorder. |

### What the constraints tell you

n ≤ 10^5. Walking up ancestor chains costs O(n^2) on a path-shaped tree, about 10^10 steps, which is far too slow. O(26·n) ≈ 2.6·10^6 is fine, and O(n) is ideal. Depth can also reach 10^5, so deep recursion is a real risk.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most literal way to find y for one node x?**

<details>
<summary>Answer</summary>

Walk `parent` upward from x until you reach a node with `s[y] == s[x]` or fall off the root. That costs O(depth) per node.

</details>

**Q2. Why is that too slow here?**

<details>
<summary>Answer</summary>

If parent forms a chain 0→1→2→… and s has all different letters, every walk goes to the root. That is about n^2/2 = 5·10^9 steps.

</details>

**Q3. What information do I actually need at node x?**

<details>
<summary>Answer</summary>

Only one fact: the deepest ancestor carrying letter s[x]. During a DFS the ancestors of x are exactly the current recursion path, and that path changes by one node per step.

</details>

**Q4. How do I maintain 'deepest ancestor per letter' as the DFS moves?**

<details>
<summary>Answer</summary>

Keep `last[c]`. On entering x, its new parent is `last[s[x]]` (if set). Save the old value, set `last[s[x]] = x`, visit the children, then restore the saved value when leaving x. This is standard backtracking.

</details>

**Q5. Do the changes interfere with each other because they are simultaneous?**

<details>
<summary>Answer</summary>

No. Every y is defined on the original tree, so all lookups use the original structure. In Example 2, node 4 moves to 0 and node 2 moves to 1, and both are computed from the original edges.

</details>

**Q6. How do I get subtree sizes of the new tree cheaply?**

<details>
<summary>Answer</summary>

Each new parent is an original ancestor, so it appears earlier in the original preorder. Process nodes in reverse preorder and add `size[x]` into `size[newParent[x]]`. Each child is finished before its parent receives its total.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Walk up ancestors per node](#1-brute-force-walk-up-ancestors-per-node) | `O(n^2)` | `O(n)` |
| 2 | [Better: Per-node table of nearest ancestor per letter](#2-better-per-node-table-of-nearest-ancestor-per-letter) | `O(26·n)` | `O(26·n)` |
| 3 | [Optimal: DFS with backtracked last[26]](#3-optimal-dfs-with-backtracked-last26) | `O(n)` | `O(n)` |

### 1. Brute force: Walk up ancestors per node

> **Where you start:** The statement literally says 'find the closest ancestor', so climbing parent pointers is the direct translation.

**Idea.** For each x from 1 to n-1, follow `parent` upward until a node with the same letter appears. That node becomes newParent[x]; if none appears, keep parent[x]. Build children lists for the new tree and compute subtree sizes with a DFS from 0. It is correct because climbing checks the ancestors in order of increasing distance, so the first match is the closest one.

**Steps**

1. Copy parent into newParent.
2. For each x ≥ 1, set y = parent[x].
3. While y != -1 and s[y] != s[x], set y = parent[y].
4. If y != -1, set newParent[x] = y.
5. Build children lists from newParent.
6. Run a DFS (or reverse-order accumulation) from 0 to compute sizes.

**Pseudocode**

```text
 1 │ function findSubtreeSizes(parent, s):
 2 │   n ← length(parent)
 3 │   newParent ← copy of parent
 4 │   for x ← 1 to n − 1:
 5 │     y ← parent[x]
 6 │     while y ≠ −1 and s[y] ≠ s[x]:  // climb one step at a time, so the first match is the closest
 7 │       y ← parent[y]
 8 │     if y ≠ −1:
 9 │       newParent[x] ← y  // closest ancestor with the same letter
10 │   children ← array of n empty lists
11 │   for x ← 1 to n − 1:
12 │     append x to children[newParent[x]]
13 │   answer ← array of n values, all 1  // every node counts itself
14 │   order ← empty list; stack ← [0]
15 │   while stack is not empty:  // iterative DFS of the new tree (no recursion depth issues)
16 │     u ← pop(stack)
17 │     append u to order
18 │     for each c in children[u]:
19 │       push c onto stack
20 │   for i ← n − 1 down to 1:  // reverse preorder: every child is handled before its parent
21 │     u ← order[i]
22 │     answer[newParent[u]] ← answer[newParent[u]] + answer[u]  // pass the finished subtree size up
23 │   return answer
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Ancestor climbing (lines 4-9) | n−1 nodes × up to depth(x) = O(n) climbs each | A node may have to walk all the way to the root before it finds a matching letter or runs out of ancestors. |
| Building children lists (lines 10-12) | n−1 iterations × O(1) | Each node is appended exactly once to its new parent's list. |
| DFS preorder (lines 14-19) | n pops + n−1 pushes, O(1) each | Every node is pushed and popped once, and every edge is scanned once. |
| Reverse accumulation (lines 20-22) | n−1 iterations × O(1) | Each node adds its size to its parent once. |

- **Adding it up:** Σ depth(x) + O(n) + O(n) + O(n). In the worst case Σ depth(x) ≈ (n/2)·(n/2) = n²/4 = O(n^2), which dominates the linear work.
- **Best vs worst case:** Best case O(n): every node's parent already has the same letter (e.g. all letters 'a'), so each climb stops after one check. Worst case O(n^2): a 'broom' tree, a path of n/2 'a' nodes with n/2 'b' leaves hanging from its bottom. Each leaf climbs about n/2 steps.
- **At the maximum input:** n = 10^5 → worst case about 2.5·10^9 climb steps, which takes several seconds and will likely exceed the time limit. Random or shallow trees run fast.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| newParent copy (line 3) | n integers | It stores the reassigned parent of every node. |
| children lists (lines 10-12) | n lists holding n−1 entries in total | Each non-root node appears in exactly one list. |
| order and stack (lines 14-19) | at most n entries each | Each node enters each container at most once. |

- **Adding it up:** O(n) + O(n) + O(n) = O(n)
- **Not counted:** The output array answer (n ints) and the inputs are not counted. The DFS is iterative, so there is no recursion stack. A recursive DFS could reach depth 10^5 on a path-shaped tree.

**Dry run** on `parent = [-1,0,0,1,1,1], s = "abaabc"`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 6. newParent starts as an exact copy of parent; nodes only change if they find a matching ancestor. | `n = 6`<br>`parent = [-1, 0, 0, 1, 1, 1]`<br>`s = [a, b, a, a, b, c]`<br>`newParent = [-1, 0, 0, 1, 1, 1]` |
| 2 | 7 | x = 1 ('b'): y started at 0, but s[0] = 'a' ≠ 'b', so y climbs to parent[0] = -1. No 'b' ancestor exists, so node 1 keeps its parent. | `x = 1`<br>`y = -1`<br>`parent = [-1, 0, 0, 1, 1, 1]` (x→1)<br>`s = [a, b, a, a, b, c]` (x→1) |
| 3 | 9 | x = 2 ('a'): y = 0 and s[0] = 'a' matches immediately, so newParent[2] = 0. This is the same as before. | `x = 2`<br>`y = 0`<br>`parent = [-1, 0, 0, 1, 1, 1]` (x→2, y→0)<br>`s = [a, b, a, a, b, c]` (x→2, y→0) |
| 4 | 7 | x = 3 ('a'): y = 1 has 'b' ≠ 'a', so y climbs to parent[1] = 0. Now s[0] = 'a' matches, so the while loop stops. | `x = 3`<br>`parent = [-1, 0, 0, 1, 1, 1]` (x→3, y→0)<br>`s = [a, b, a, a, b, c]` (x→3, y→0) |
| 5 | 9 | y = 0 ≠ -1, so node 3 is re-attached: newParent[3] = 0. This is the change described in the example. | `parent = [-1, 0, 0, 1, 1, 1]` (x→3)<br>`newParent = [-1, 0, 0, 0, 1, 1]` |
| 6 | 9 | x = 4 ('b'): y = 1 has 'b', which matches at once, so newParent[4] = 1 (unchanged). | `x = 4`<br>`y = 1`<br>`parent = [-1, 0, 0, 1, 1, 1]` (x→4, y→1)<br>`s = [a, b, a, a, b, c]` (x→4, y→1) |
| 7 | 7 | x = 5 ('c'): y goes 1 ('b'), then 0 ('a'), then -1. There is no 'c' ancestor, so node 5 keeps parent 1. | `x = 5`<br>`y = -1`<br>`parent = [-1, 0, 0, 1, 1, 1]` (x→5)<br>`s = [a, b, a, a, b, c]` (x→5) |
| 8 | 12 | Children lists are built from newParent = [-1,0,0,0,1,1]. Node 0 now has children 1, 2, 3, and node 1 has children 4 and 5. | `children = {0→[1,2,3], 1→[4,5], 2→[], 3→[], 4→[], 5→[]}`<br>`newTree = tree [0, 1, 2, 3]` |
| 9 | 19 | The DFS pops 0, records it in order, and pushes its children 1, 2, 3. Node 3 is now on top of the stack. All answers start at 1. | `u = 0`<br>`answer = [1, 1, 1, 1, 1, 1]`<br>`order = [0]`<br>`stack = [1, 2, 3] ← top` |
| 10 | 19 | The DFS pops 3, then 2 (both have no children), then 1, and pushes node 1's children 4 and 5. | `u = 1`<br>`order = [0, 3, 2, 1]`<br>`stack = [4, 5] ← top` |
| 11 | 17 | The DFS pops 5, then 4. The stack is now empty and order = [0,3,2,1,5,4]. Every parent appears before its children. | `u = 4`<br>`order = [0, 3, 2, 1, 5, 4]`<br>`stack = []` |
| 12 | 22 | i = 5, u = order[5] = 4. Node 4's size (1) is added to its parent 1, so answer[1] = 2. | `i = 5`<br>`newParent = [-1, 0, 0, 0, 1, 1]` (u→4)<br>`answer = [1, 2, 1, 1, 1, 1]` (u→4)<br>`order = [0, 3, 2, 1, 5, 4]` (i→5) |
| 13 | 22 | i = 4 (u = 5) first made answer[1] = 3. Now i = 3, u = 1: node 1's finished size 3 is added to node 0, so answer[0] = 4. | `i = 3`<br>`u = 1`<br>`newParent = [-1, 0, 0, 0, 1, 1]` (u→1)<br>`answer = [4, 3, 1, 1, 1, 1]` (u→1)<br>`order = [0, 3, 2, 1, 5, 4]` (i→3) |
| 14 | 22 | i = 2 (u = 2) made answer[0] = 5. Then i = 1, u = 3 adds 1 more, so answer[0] = 6. | `i = 1`<br>`u = 3`<br>`newParent = [-1, 0, 0, 0, 1, 1]` (u→3)<br>`answer = [6, 3, 1, 1, 1, 1]` (u→3)<br>`order = [0, 3, 2, 1, 5, 4]` (i→1) |
| 15 | 23 | The loop has finished, so answer = [6,3,1,1,1,1] is returned. | `answer = [6, 3, 1, 1, 1, 1]` |

**Result:** [6,3,1,1,1,1]. Only node 3 moves (to node 0), so node 0's subtree holds all 6 nodes and node 1 keeps itself plus nodes 4 and 5.

**C++ solution**

```cpp
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<int> newParent(parent);          // start from the original parents
        for (int x = 1; x < n; ++x) {
            int y = parent[x];
            // climb upward one ancestor at a time; the first match is the closest
            while (y != -1 && s[y] != s[x]) y = parent[y];
            if (y != -1) newParent[x] = y;      // re-attach to closest same-letter ancestor
        }
        vector<vector<int>> children(n);
        for (int x = 1; x < n; ++x) children[newParent[x]].push_back(x); // adjacency of new tree
        vector<int> answer(n, 1);               // each node counts itself
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};                   // iterative DFS avoids deep recursion
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            order.push_back(u);                 // preorder: parent before children
            for (int c : children[u]) st.push_back(c);
        }
        // reverse preorder guarantees children are finished before their parent
        for (int i = n - 1; i >= 1; --i) {
            int u = order[i];
            answer[newParent[u]] += answer[u];  // push subtree size up to parent
        }
        return answer;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

string vecToString(const vector<int>& v) {
    string r = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) r += ",";
        r += to_string(v[i]);
    }
    return r + "]";
}

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<int> newParent(parent);          // start from the original parents
        for (int x = 1; x < n; ++x) {
            int y = parent[x];
            // climb upward one ancestor at a time; the first match is the closest
            while (y != -1 && s[y] != s[x]) y = parent[y];
            if (y != -1) newParent[x] = y;      // re-attach to closest same-letter ancestor
        }
        vector<vector<int>> children(n);
        for (int x = 1; x < n; ++x) children[newParent[x]].push_back(x); // adjacency of new tree
        vector<int> answer(n, 1);               // each node counts itself
        vector<int> order;
        order.reserve(n);
        vector<int> st = {0};                   // iterative DFS avoids deep recursion
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            order.push_back(u);                 // preorder: parent before children
            for (int c : children[u]) st.push_back(c);
        }
        // reverse preorder guarantees children are finished before their parent
        for (int i = n - 1; i >= 1; --i) {
            int u = order[i];
            answer[newParent[u]] += answer[u];  // push subtree size up to parent
        }
        return answer;
    }
};

int main() {
    Solution sol;
    vector<int> p1 = {-1,0,0,1,1,1};
    vector<int> r1 = sol.findSubtreeSizes(p1, "abaabc");
    cout << "Example 1: " << vecToString(r1) << "  expected: [6,3,1,1,1,1]" << endl;
    vector<int> p2 = {-1,0,4,0,1};
    vector<int> r2 = sol.findSubtreeSizes(p2, "abbba");
    cout << "Example 2: " << vecToString(r2) << "  expected: [5,2,1,1,1]" << endl;
    return 0;
}
```

</details>

**Why move on:** A chain of 10^5 nodes with no letter matches makes about 5·10^9 steps, which is far over the time limit.

### 2. Better: Per-node table of nearest ancestor per letter

> **How you get here:** Sibling nodes repeat exactly the same climb above their shared parent. That shared answer can be computed once at the parent and inherited by its children.

**Idea.** Define `near[x][c]` as the nearest node on the path from root to x (including x) with letter c. Then `near[x] = near[parent[x]]` with entry s[x] replaced by x. The new parent of x is `near[parent[x]][s[x]]`. Filling the table in BFS or preorder guarantees each parent row exists before its children read it.

**Steps**

1. Build children lists and get a BFS or preorder order from 0.
2. Set near[0] all to -1, then set near[0][s[0]] = 0.
3. For each x in order: read y = near[parent[x]][s[x]] and record it as newParent[x] if y != -1.
4. Copy near[parent[x]] into near[x] and set near[x][s[x]] = x.
5. Accumulate sizes in reverse order along newParent.

**Complexity:** time `O(26·n)`, space `O(26·n)`. Copying a 26-entry row per node dominates, about 2.6·10^6 operations. The table itself stores 26·n integers.

**Why move on:** The time is acceptable, but storing 2.6 million ints is wasteful, because only the current root-to-node path ever needs to be remembered.

### 3. Optimal: DFS with backtracked last[26]

> **How you get here:** In the table, row x is just row parent[x] with one entry changed. A single shared array can therefore be updated on entry and restored on exit.

**Idea.** Do an (iterative) DFS from 0 and keep `last[c]`, the deepest node on the current path with letter c. On entering x, newParent[x] = last[s[x]] if that is set, otherwise parent[x]. Then save old = last[s[x]], set last[s[x]] = x, explore the children, and restore old on exit. The invariant is that, whenever x is entered, last holds exactly the information about x's ancestors. Record the preorder as you go. Every newParent is an ancestor, so it comes earlier in that order, and reverse-preorder accumulation of size[x] into size[newParent[x]] gives the correct sizes.

**Steps**

1. Build children lists from parent.
2. Initialize last[26] = -1 and size[i] = 1 for every node.
3. Run an iterative DFS from 0 with explicit enter/exit events.
4. On enter x: set newParent[x] = last[s[x]] if it is not -1, else parent[x]. Push x to the preorder list, save the old last[s[x]], and set it to x.
5. On exit x: restore last[s[x]] to the saved value.
6. Go through preorder in reverse; for x ≠ 0, add size[x] to size[newParent[x]].
7. Return size.

**Complexity:** time `O(n)`, space `O(n)`. Each node is entered and exited once with O(1) work, and the accumulation pass is linear. Memory goes to the children lists, the DFS stack, the saved values, newParent and the preorder list.

**Why this is the best:** Every node must be read at least once, so O(n) is optimal. The only cost is careful bookkeeping of save/restore in an iterative DFS, needed to avoid recursion overflow at depth 10^5.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| parent = [-1,0,1,2]<br>s = "abab" | [4,3,1,1] | Chain where node 2 moves to node 0 and node 3 moves to node 1. |
| parent = [-1,0,0,1,2]<br>s = "abcde" | [5,2,2,1,1] | All characters distinct, so the tree is unchanged. |
| parent = [-1,0,1,1,2]<br>s = "abcbb" | [5,4,1,1,1] | Nodes 3 and 4 both re-attach to node 1, and node 4 skips past node 2. |
| parent = [-1,0,0,1,1,2,2]<br>s = "abbaabb" | [7,1,3,1,1,1,1] | Nodes 3 and 4 move up to the root, and nodes 5 and 6 stay under node 2. |
| parent = [-1,0,1,2,3]<br>s = "abcba" | [5,3,2,1,1] | Node 3 moves to node 1 and node 4 moves to node 0, both at the same time. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single node | parent = [-1]<br>s = "a" | [1] | Only the root exists. |
| All equal chain | parent = [-1,0,1,2]<br>s = "aaaa" | [4,3,2,1] | Each node's closest match is its own parent, so nothing changes. |
| Star with all equal characters | parent = [-1,0,0,0]<br>s = "aaaa" | [4,1,1,1] | The tree is unchanged. |
| Two nodes with different characters | parent = [-1,0]<br>s = "ab" | [2,1] | No change. |
| Repeated characters in a chain | parent = [-1,0,1,2,3]<br>s = "abbbb" | [5,4,3,2,1] | Each node's closest match is already its parent. |
| Parent indices not in order | parent = [-1,2,0,1]<br>s = "abca" | [4,1,2,1] | Node 3 jumps up to the root. |

## Mistakes and edge cases

**Common mistakes**

- Applying changes one at a time and looking up ancestors in the partially modified tree. The statement says simultaneous, so all lookups must use the original parent array.
- Forgetting to restore last[s[x]] on exit. A node in a sibling branch then picks a non-ancestor (a 'cousin') as its new parent.
- Using recursive DFS in Python or Java on a 10^5-deep chain, which crashes with a stack overflow or recursion limit. Use an explicit stack.
- Accumulating sizes in index order 0..n-1. Indices are not a topological order (in Example 2, node 2's parent is 4), so sizes must follow reverse preorder or come from a DFS of the new tree.

**Edge cases to check**

- n = 1: the answer is [1] and no changes happen.
- All letters equal, e.g. a chain 'aaaa': every node's closest match is its own parent, so the tree is unchanged.
- Chain with distinct letters: nothing moves. This is the worst case for the brute-force climb and for recursion depth.
- Star with root 'a' and children mixing 'a' and 'b' whose own children are 'a': the grandchildren jump to the root. This checks that sizes are recomputed on the new tree and not reused from the old one.

## Practice next

- [Tree of Coprimes](https://leetcode.com/problems/tree-of-coprimes/) · Finds the nearest ancestor satisfying a value condition, using per-value stacks maintained during DFS and backtracking. This is the same technique.
- [Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/) · Uses per-letter counts over a tree DFS with 26 lowercase labels.
- [Count Good Nodes in Binary Tree](https://leetcode.com/problems/count-good-nodes-in-binary-tree/) · Carries root-to-node path state down the DFS and answers each node from it in O(1).

## Takeaways

- 'Nearest ancestor with property P' becomes path state in a DFS: update on entry, restore on exit.
- A small alphabet (26 letters) means the path state can be a fixed array instead of a per-node table.
- If every new parent is an original ancestor, the original preorder is still a topological order, so sizes can be accumulated in reverse preorder without building a new tree.
- With n up to 10^5 and possible chain-shaped trees, use an iterative DFS.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
