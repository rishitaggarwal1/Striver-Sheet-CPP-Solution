# Network Delay Time

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/network-delay-time/) · Pattern: **Single-source shortest paths (Dijkstra)** · ✅ Solved in C++

> In a directed graph with non-negative edge weights, find the largest shortest-path distance from node `k` to any node, or return -1 if some node cannot be reached.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [My solution](#my-solution) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "minimum time for all n nodes to receive the signal" | the signal spreads along every path at once, so node `v` hears it at `dist(k, v)`. Everyone has heard it at `max over v of dist(k, v)`. |
| `0 <= w_i <= 100`: weights are never negative | Dijkstra's greedy finalisation is valid, and no negative-cycle handling is needed. |
| Directed edges `(u_i, v_i)` with one fixed source `k` | this is single-source shortest paths, not all-pairs. Edges must only be added in the `u → v` direction. |
| Example 3 (k = 2, only edge 1 | 2) returns -1 → an unreachable node leaves its distance at infinity, and that must map to -1. |

### What the constraints tell you

n ≤ 100 and E ≤ 6000. Bellman-Ford O(n·E) ≈ 6·10^5, Floyd-Warshall O(n^3) = 10^6 and Dijkstra O(E log n) ≈ 6000·7 ≈ 4·10^4 all pass easily. Only exponential path enumeration is dangerous. Target O(E log n), which is the standard and scales to large graphs.

### Think it through

Answer each question yourself before opening it.

**Q1. What does 'time for all nodes to receive' actually measure?**

<details>
<summary>Answer</summary>

Each node gets the signal at the earliest possible arrival, which is its shortest-path distance from `k`. The answer is the maximum of these distances. In Example 1, distances from 2 are {1:1, 3:1, 4:2}, so the answer is 2.

</details>

**Q2. Naively, could I just try every path from k?**

<details>
<summary>Answer</summary>

Yes: DFS from `k`, carrying the elapsed time, and record the best arrival at each node. But the number of simple paths can be exponential in a dense graph with 6000 edges.

</details>

**Q3. How do I avoid re-exploring paths?**

<details>
<summary>Answer</summary>

Keep `dist[v]` and only relax an edge `u→v` if `dist[u] + w < dist[v]`. Repeating this relaxation over all edges n-1 times is Bellman-Ford. It is correct because any shortest path uses at most n-1 edges.

</details>

**Q4. Bellman-Ford relaxes every edge in every round. Is that wasted?**

<details>
<summary>Answer</summary>

Yes. Most edges in a round leave from nodes whose distance did not change. Since weights are non-negative, the unvisited node with the smallest tentative distance can never be improved later, so its distance is final.

</details>

**Q5. So what's the key insight?**

<details>
<summary>Answer</summary>

Dijkstra: repeatedly pop the closest unfinalised node from a min-heap, finalise it, and relax only its outgoing edges. When the heap empties, if fewer than n nodes were finalised return -1. Otherwise return the largest distance, which is the distance of the last node popped.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: DFS over all paths](#1-brute-force-dfs-over-all-paths) | `Exponential worst case` | `O(n + E)` |
| 2 | [Better: Bellman-Ford relaxation](#2-better-bellman-ford-relaxation) | `O(n·E)` | `O(n)` |
| 3 | [Optimal: Dijkstra with a min-heap](#3-optimal-dijkstra-with-a-min-heap) | `O(E log E), i.e. O(E log n)` | `O(n + E)` |

### 1. Brute force: DFS over all paths

> **Where you start:** Simulating the signal walking every route from `k` and keeping the earliest arrival per node is the most literal reading of the problem.

**Idea.** Run DFS from `k` with the current elapsed time. When you reach node `v` with time `t`, continue only if `t < best[v]`; then set `best[v] = t` and recurse into the neighbours. It is correct because every path from `k` is either explored or pruned by a path that is at least as fast. However, without an ordering a node can be improved and re-expanded many times.

**Steps**

1. Build an adjacency list from `times`, using `u → (v, w)` only.
2. Initialise `best[1..n] = infinity`.
3. DFS(node, t): if `t >= best[node]` return; else set `best[node] = t`.
4. Recurse to each neighbour with `t + w`.
5. Call DFS(k, 0).
6. If any `best` is infinity return -1, else return the max of `best`.

**Pseudocode**

```text
 1 │ function networkDelayTime(times, n, k)
 2 │   adj ← array of n+1 empty lists
 3 │   for each (u, v, w) in times
 4 │     append (v, w) to adj[u]   // directed edge u → v only
 5 │   for u ← 1 to n
 6 │     sort adj[u] by w ascending   // heuristic: try cheap edges first so later paths get pruned more
 7 │   best ← array[0..n] filled with INF   // best[x] = fastest arrival time found so far
 8 │   dfs(k, 0)
 9 │   answer ← 0
10 │   for node ← 1 to n
11 │     if best[node] = INF
12 │       return -1   // node was never reached
13 │     answer ← max(answer, best[node])   // the last node to hear the signal decides the answer
14 │   return answer
15 │ function dfs(node, t)
16 │   if t ≥ best[node]
17 │     return   // a path at least as fast already reached node, so this one cannot help
18 │   best[node] ← t
19 │   for each (v, w) in adj[node]
20 │     dfs(v, t + w)   // extend the current path by edge node → v
```

**Time complexity: `Exponential worst case (O(E log E) setup + number of DFS expansions × degree)`**

| Part | Cost | Why |
| --- | --- | --- |
| Build adjacency list (lines 2-4) | E iterations × O(1) | Each edge is appended exactly once. |
| Sort neighbour lists (lines 5-6) | O(E log E) in total | Sorting all the lists together costs at most as much as sorting E items. |
| DFS (lines 8, 15-20) | (number of times a node's best improves) × O(out-degree) per improvement | A node is re-expanded every time a strictly faster path reaches it. In an adversarial graph the fast paths are found last, so this can happen exponentially many times. |
| Final scan (lines 9-14) | n iterations × O(1) | One look at each best value. |

- **Adding it up:** O(E) + O(E log E) + (expansions × degree) + O(n). The DFS term dominates. It is O(E) when every node is settled on its first visit, and it can blow up exponentially in n when nodes keep getting improved.
- **Best vs worst case:** Best case: a tree, or any graph where the first path found to each node is already the shortest. Each node is then expanded once, giving O(E log E). Worst case: a layered or dense graph where expensive paths are explored first and cheaper ones keep arriving later. Every improvement re-expands the whole subtree below that node.
- **At the maximum input:** n = 100, E = 6000. The theoretical worst case is astronomically large. With the cheap-edges-first sort, LeetCode's tests still run in a few milliseconds. Dijkstra is the safe choice when guarantees matter.

**Space complexity: `O(n + E)`**

| Part | Cost | Why |
| --- | --- | --- |
| Adjacency list adj (lines 2-4) | O(n + E) | n+1 list headers plus one entry per edge. |
| best array (line 7) | O(n) | One slot per node. |
| Recursion stack (lines 15-20) | O(n) | A recursive call only goes deeper when t < best[node]. A revisited node on the current path already holds a smaller or equal time, so every active path is simple and has at most n frames. |

- **Adding it up:** O(n + E) + O(n) + O(n) = O(n + E).
- **Not counted:** The input times array is not counted. Recursion depth is at most n = 100.

**Dry run** on `times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | All 3 edges have been added as directed lists (iterations collapsed). Node 2 points to 1 and 3, and node 3 points to 4. Sorting on lines 5-6 changes nothing because all weights are 1. | `n = 4`<br>`k = 2`<br>`adj = {1→[], 2→[(1,1),(3,1)], 3→[(4,1)], 4→[]}`<br>`network: 4 nodes` |
| 2 | 7 | best is filled with INF. Index 0 is unused because nodes are labelled 1..4. | `best = [-, INF, INF, INF, INF]` |
| 3 | 18 | dfs(2, 0) is called. Since 0 < INF, the check on line 16 passes and best[2] becomes 0, because the source hears the signal at time 0. | `node = 2`<br>`t = 0`<br>`best = [-, INF, 0, INF, INF]` (node→2)<br>`callStack = [dfs(2,0)] ← top`<br>`network: node→2` |
| 4 | 18 | The first neighbour of 2 is (1,1), so dfs(1, 0+1) runs. Since 1 < INF, best[1] becomes 1. Node 1 has no outgoing edges, so this call returns right away. | `node = 1`<br>`t = 1`<br>`best = [-, 1, 0, INF, INF]` (node→1)<br>`callStack = [dfs(2,0), dfs(1,1)] ← top`<br>`network: node→1; visited {2}; edge 2→1` |
| 5 | 18 | Back in dfs(2,0), the next neighbour is (3,1), so dfs(3, 1) runs. Since 1 < INF, best[3] becomes 1. | `node = 3`<br>`best = [-, 1, 0, 1, INF]` (node→3)<br>`callStack = [dfs(2,0), dfs(3,1)] ← top`<br>`network: node→3; visited {2, 1}; edge 2→3` |
| 6 | 18 | From 3, the edge (4,1) leads to dfs(4, 1+1). Since 2 < INF, best[4] becomes 2. Node 4 has no outgoing edges. | `node = 4`<br>`t = 2`<br>`best = [-, 1, 0, 1, 2]` (node→4)<br>`callStack = [dfs(2,0), dfs(3,1), dfs(4,2)] ← top`<br>`network: node→4; visited {2, 1, 3}; edge 3→4` |
| 7 | 8 | All recursive calls have returned, so dfs(2,0) is finished. No node was ever improved twice, so nothing was re-expanded. | `best = [-, 1, 0, 1, 2]`<br>`callStack = []`<br>`network: visited {1, 2, 3, 4}` |
| 8 | 13 | Scan with node = 1. best[1] = 1 is not INF, so answer = max(0, 1) = 1. | `node = 1`<br>`answer = 1`<br>`best = [-, 1, 0, 1, 2]` (node→1)<br>`network: node→1; visited {1, 2, 3, 4}` |
| 9 | 13 | Nodes 2 and 3 have times 0 and 1, so answer stays 1 (iterations collapsed). At node = 4, best[4] = 2, so answer = max(1, 2) = 2. | `node = 4`<br>`answer = 2`<br>`best = [-, 1, 0, 1, 2]` (node→4)<br>`network: node→4; visited {1, 2, 3, 4}` |
| 10 | 14 | Every node was reached, so the function returns answer = 2. | `best = [-, 1, 0, 1, 2]`<br>`network: visited {1, 2, 3, 4}` |

**Result:** 2. Node 4 is the farthest node, reached via 2→3→4 at time 2. Every other node hears the signal no later than that.

**C++ solution**

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // adjacency list: adj[u] holds (v, w) pairs for directed edges u -> v
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& e : times) adj[e[0]].push_back({e[1], e[2]});
        // heuristic: explore cheap edges first so faster paths are found early and prune more
        for (int u = 1; u <= n; ++u)
            sort(adj[u].begin(), adj[u].end(),
                 [](const pair<int,int>& a, const pair<int,int>& b) { return a.second < b.second; });
        best.assign(n + 1, INT_MAX); // INT_MAX means 'not reached yet'
        dfs(k, 0, adj);              // signal starts at k at time 0
        int answer = 0;
        for (int node = 1; node <= n; ++node) {
            if (best[node] == INT_MAX) return -1;   // some node never got the signal
            answer = max(answer, best[node]);      // the slowest node decides the total time
        }
        return answer;
    }
private:
    vector<int> best; // best[x] = fastest arrival time found so far for node x

    void dfs(int node, int t, const vector<vector<pair<int,int>>>& adj) {
        if (t >= best[node]) return; // an equally fast or faster path already reached node: prune
        best[node] = t;              // record the improvement
        for (auto& [v, w] : adj[node])
            dfs(v, t + w, adj);      // extend the path along edge node -> v
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // adjacency list: adj[u] holds (v, w) pairs for directed edges u -> v
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& e : times) adj[e[0]].push_back({e[1], e[2]});
        // heuristic: explore cheap edges first so faster paths are found early and prune more
        for (int u = 1; u <= n; ++u)
            sort(adj[u].begin(), adj[u].end(),
                 [](const pair<int,int>& a, const pair<int,int>& b) { return a.second < b.second; });
        best.assign(n + 1, INT_MAX); // INT_MAX means 'not reached yet'
        dfs(k, 0, adj);              // signal starts at k at time 0
        int answer = 0;
        for (int node = 1; node <= n; ++node) {
            if (best[node] == INT_MAX) return -1;   // some node never got the signal
            answer = max(answer, best[node]);      // the slowest node decides the total time
        }
        return answer;
    }
private:
    vector<int> best; // best[x] = fastest arrival time found so far for node x

    void dfs(int node, int t, const vector<vector<pair<int,int>>>& adj) {
        if (t >= best[node]) return; // an equally fast or faster path already reached node: prune
        best[node] = t;              // record the improvement
        for (auto& [v, w] : adj[node])
            dfs(v, t + w, adj);      // extend the path along edge node -> v
    }
};

int main() {
    vector<vector<int>> t1 = {{2,1,1},{2,3,1},{3,4,1}};
    vector<vector<int>> t2 = {{1,2,1}};
    vector<vector<int>> t3 = {{1,2,1}};
    Solution s1, s2, s3;
    cout << "Example 1: " << s1.networkDelayTime(t1, 4, 2) << " (expected 2)" << endl;
    cout << "Example 2: " << s2.networkDelayTime(t2, 2, 1) << " (expected 1)" << endl;
    cout << "Example 3: " << s3.networkDelayTime(t3, 2, 2) << " (expected -1)" << endl;
    return 0;
}
```

</details>

**Why move on:** Exploration order is arbitrary, so the same node may be finalised many times. On dense graphs with 6000 edges this can blow up.

### 2. Better: Bellman-Ford relaxation

> **How you get here:** The DFS redoes work because it updates in a random order. Systematic rounds of relaxing every edge bound the total work.

**Idea.** Set `dist[k] = 0` and everything else to infinity. Do n-1 rounds; in each round, for every edge `(u, v, w)`, set `dist[v] = min(dist[v], dist[u] + w)`. After round i, every node whose shortest path has at most i edges has its correct distance. A shortest path in a graph without negative cycles has at most n-1 edges, so n-1 rounds suffice.

**Steps**

1. Initialise `dist[1..n] = infinity` and `dist[k] = 0`.
2. Repeat n-1 times: for each edge `(u, v, w)` with `dist[u]` finite, relax `dist[v]`.
3. Stop early if a full round changes nothing.
4. If any `dist` is infinity return -1.
5. Otherwise return the max of `dist`.

**Complexity:** time `O(n·E)`, space `O(n)`. The double loop of n-1 rounds over E edges dominates: about 100·6000 = 6·10^5 relaxations. Only the `dist` array is extra memory, since the edge list is used directly.

**Why move on:** It fits these limits easily. But it rescans edges from nodes whose distance has not changed, so it does not scale: with n = 10^5 and E = 10^5 it would need 10^10 operations.

### 3. Optimal: Dijkstra with a min-heap

> **How you get here:** With non-negative weights, the closest not-yet-finalised node can never get a shorter path later. So each node needs to be finalised only once, and only its own edges need relaxing.

**Idea.** Push `(0, k)` onto a min-heap. Pop the smallest `(d, u)`; skip it if `u` is already finalised; otherwise finalise `dist[u] = d` and push `(d + w, v)` for each edge `u→v`. The invariant is that the popped minimum is the true shortest distance, because any alternative path must leave the finalised set through a node whose tentative distance is at least `d`, and weights are at least 0. The last node finalised has the largest distance.

**Steps**

1. Build an adjacency list `u → [(v, w)]` from `times`.
2. Push `(0, k)` onto a min-heap and create an empty finalised set.
3. Pop `(d, u)`; if `u` is already finalised, continue.
4. Mark `u` finalised and record `answer = d`.
5. For each `(v, w)` out of `u` with `v` not finalised, push `(d + w, v)`.
6. When the heap is empty, return `answer` if all n nodes were finalised, else -1.

**Complexity:** time `O(E log E), i.e. O(E log n)`, space `O(n + E)`. Each edge causes at most one push, and each push or pop costs log of the heap size, so about 6000·13 operations. Memory holds the adjacency list (E entries), the heap (up to E entries) and the finalised set (n entries).

**Why this is the best:** Every edge must be read at least once, so the bound is optimal up to the log factor. The price is the heap and the requirement of non-negative weights; a negative weight would break it, and that is guaranteed not to happen here.

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 5 | 2 of 8 | 2026-11-20 |

For comparison, the optimal approach (Dijkstra with a min-heap) runs in `O(E log E), i.e. O(E log n)` time and `O(n + E)` space.

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for(int i=0;i<times.size();i++)
        {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            adj[u].push_back({v,w});
        }
        vector<int> dist(n+1,1e9);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[k]=0;
        pq.push({0,k});
        while(!pq.empty())
        {
            int wt = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for(auto it: adj[node])
            {
                int x = it.first;
                int w = it.second;
                if(dist[x]>wt + w)
                {
                    dist[x] = wt+w;
                    pq.push({dist[x],x});
                }
            }
        }
        int ans = -1;
        for(int i = 1;i<=n;i++)
        {
            if(dist[i]==1e9)    return -1;
            if(dist[i]>ans) ans = dist[i];
        }
        return ans;
    }
};
```

<details>
<summary>Earlier accepted versions (2)</summary>

**C++ · 2026-11-20**

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        Hello
    }
};
```

**C++ · 2026-11-20**

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        submit
    }
};
```

</details>

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| times = [[1,2,4],[1,3,1],[3,2,1],[2,4,1]]<br>n = 4<br>k = 1 | 3 | Indirect path 1->3->2 is shorter than the direct edge 1->2. |
| times = [[1,2,1],[2,3,2],[1,3,4]]<br>n = 3<br>k = 1 | 3 | The relaxed path 1->2->3 (cost 3) beats the direct edge (cost 4). |
| times = [[3,1,5],[3,2,2],[2,1,2],[1,4,1],[2,5,10],[4,5,1]]<br>n = 5<br>k = 3 | 6 | Distances from 3 are 1:4, 2:2, 4:5, 5:6, so the maximum is 6. |
| times = [[1,2,1],[2,3,1],[3,4,1],[4,5,1]]<br>n = 5<br>k = 1 | 4 | Chain graph where the answer is the full path length. |
| times = [[2,1,3],[2,3,7],[1,3,2],[3,4,1],[4,1,10]]<br>n = 4<br>k = 2 | 6 | A cycle is present and node 3 is reached via 2->1->3 with cost 5. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single node | times = [[1,2,1]]<br>n = 1<br>k = 1 | 0 | No travel is needed, so the answer is 0. The edge references a node outside 1..n, so this violates the constraints and is only an illustrative extreme. |
| Zero weights | times = [[1,2,0],[2,3,0]]<br>n = 3<br>k = 1 | 0 | Every node is reached at time 0. |
| Disconnected | times = [[1,2,1],[3,4,1]]<br>n = 4<br>k = 1 | -1 | Nodes 3 and 4 are unreachable from 1. |
| Edge direction | times = [[2,1,1],[3,1,1]]<br>n = 3<br>k = 1 | -1 | Edges only point into the source, so nothing else is reachable. |
| Max weights | times = [[1,2,100],[2,3,100]]<br>n = 3<br>k = 1 | 200 | The path accumulates weight-100 edges. |
| Two-cycle | times = [[1,2,1],[2,1,1]]<br>n = 2<br>k = 2 | 1 | The source is the last label and both directions exist. |

## Mistakes and edge cases

**Common mistakes**

- Returning the sum of the edge weights, or the distance to node n, instead of the maximum shortest distance over all nodes.
- Adding edges in both directions. The graph is directed, and Example 3 returns -1 only because 2→1 does not exist.
- Using 0-indexed arrays of size n while nodes are labelled 1..n, which causes an off-by-one error or an out-of-bounds access on node n.
- Not skipping stale heap entries. Re-processing an already finalised node with a larger `d` can overwrite `answer` with a wrong maximum.

**Edge cases to check**

- Some node is unreachable from `k` (Example 3): its distance stays infinite, so you must return -1, not a large number.
- n = 1: only `k` exists, so the answer is 0 even though `times` may contain no edge leaving it.
- Edges with `w = 0`: Dijkstra still works, but the code must not treat a distance of 0 as 'unvisited'.
- A longer path in edges is faster than a direct one, for example 1→3 with weight 10 versus 1→2→3 with weight 2: this checks that the code really finds the shortest distance, not just the first one found.

## Practice next

- [Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/) · Dijkstra on a grid, where the path cost is the maximum edge cost instead of a sum.
- [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/) · Shortest path with an edge-count limit, where Bellman-Ford rounds fit naturally.
- [Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/) · The same Dijkstra greedy with a max-heap over multiplied probabilities.
- [Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/) · Dijkstra extended to count how many shortest paths exist.

## Takeaways

- 'Time for everything to finish when spreading in parallel' usually means the maximum over all targets of their shortest-path distances.
- Non-negative weights unlock Dijkstra's greedy finalisation. With negative weights, or with a limit on the number of edges, use Bellman-Ford.
- Lazy Dijkstra (pushing duplicates and skipping stale pops) is simpler than decrease-key and has the same complexity.
- Check reachability by counting finalised nodes. This gives the -1 answer without a separate scan for infinite distances.
