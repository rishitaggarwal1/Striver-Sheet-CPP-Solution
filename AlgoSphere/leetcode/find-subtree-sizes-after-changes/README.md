# Find Subtree Sizes After Changes

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/find-subtree-sizes-after-changes/)

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
