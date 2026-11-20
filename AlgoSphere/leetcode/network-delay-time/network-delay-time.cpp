/*
 * Problem   : Network Delay Time (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/network-delay-time/
 * Pattern   : Single-source shortest paths (Dijkstra)
 * Approach  : Brute force: DFS over all paths
 * Complexity: Time Exponential worst case (O(E log E) setup + number of DFS expansions × degree), Space O(n + E)
 *
 * Run DFS from k with the current elapsed time. When you reach node v with
 * time t, continue only if t < best[v]; then set best[v] = t and recurse
 * into the neighbours. It is correct because every path from k is either
 * explored or pruned by a path that is at least as fast. However, without an
 * ordering a node can be improved and re-expanded many times.
 */

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
