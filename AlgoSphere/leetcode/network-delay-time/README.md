# Network Delay Time

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/network-delay-time/)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (u_i, v_i, w_i), where u_i is the source node, v_i is the target node, and w_i is the time it takes for a signal to travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.

Example 1:

Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
Output: 2

Example 2:

Input: times = [[1,2,1]], n = 2, k = 1
Output: 1

Example 3:

Input: times = [[1,2,1]], n = 2, k = 2
Output: -1

Constraints:

- 1 <= k <= n <= 100

- 1 <= times.length <= 6000

- times[i].length == 3

- 1 <= u_i, v_i <= n

- u_i != v_i

- 0 <= w_i <= 100

- All the pairs (u_i, v_i) are unique. (i.e., no multiple edges.)
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

The signal spreads out from node `k` along one-way links, and each link takes some time to cross. Each node hears the signal at the earliest moment any path from `k` can reach it. The answer is the latest of those earliest arrival times, or -1 if some node can never be reached.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In Example 1, node 4 is reached via 2 -> 3 -> 4 at time 2, and that is the largest arrival time, so the answer is 2. The answer is a maximum taken over per-node minimums, so you first need the shortest travel time from `k` to every node. Edges are directed, which is exactly why Example 3 is unreachable.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n <= 100` and up to 6000 edges, even an `O(n * E)` relaxation approach (about 600k operations) or an `O(n^3)` all-pairs approach would pass. Trying every path explicitly is exponential, though, so you need a systematic shortest-path method. An `O(E log n)` approach is the cleanest choice.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is single-source shortest paths on a weighted directed graph with non-negative weights. That is exactly the setting where Dijkstra's algorithm applies, because weights of zero or more guarantee that a settled node never improves later.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Always expand the unvisited node with the smallest known arrival time. Because no edge can make a path shorter, that node's time is final, and you only need to try improving its neighbors through it. A min-heap makes picking that node fast.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Build an adjacency list where `adj[u]` holds pairs `(v, w)`. Keep a `dist` array of size `n+1`, starting at infinity, with `dist[k] = 0`. Use a min-heap of `(time, node)` entries, and track which nodes are finalized, either with a visited set or by skipping stale heap entries.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Build the adjacency list from `times`.
Push `(0, k)` into the heap.
Pop the smallest `(t, u)` and skip it if `u` is already finalized or `t > dist[u]`.
Mark `u` as finalized, then for each `(v, w)` in `adj[u]`, if `t + w < dist[v]`, update `dist[v]` and push `(dist[v], v)`.
Repeat until the heap is empty.
If any node 1..n still has infinite `dist`, return -1; otherwise return the max of `dist[1..n]`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is ignoring stale heap entries, since a node may be pushed several times with outdated larger times. Watch for 1-indexed labels, directed edges only, zero-weight edges (still fine for Dijkstra), and `n = 1`, which returns 0. Complexity is `O(E log E)` time and `O(n + E)` space.

</details>
