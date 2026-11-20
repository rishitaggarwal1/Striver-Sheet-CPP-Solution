/*
 * Problem   : Network Delay Time (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/network-delay-time/
 * Pattern   : Single-source shortest paths (Dijkstra)
 * Approach  : Better: Bellman-Ford relaxation
 * Complexity: Time O(n·E), Space O(n)
 *
 * Set dist[k] = 0 and everything else to infinity. Do n-1 rounds; in each
 * round, for every edge (u, v, w), set dist[v] = min(dist[v], dist[u] + w).
 * After round i, every node whose shortest path has at most i edges has its
 * correct distance. A shortest path in a graph without negative cycles has
 * at most n-1 edges, so n-1 rounds suffice.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int INF = 1e9;                    // sentinel meaning 'not reached yet'
        vector<int> dist(n + 1, INF);           // dist[i] = best known arrival time at node i (index 0 unused)
        dist[k] = 0;                            // signal starts at k at time 0
        for (int round = 1; round <= n - 1; round++) {   // a shortest path has at most n-1 edges
            bool changed = false;               // tracks whether this round improved anything
            for (int i = 0; i < (int)times.size(); i++) {
                int u = times[i][0];
                int v = times[i][1];
                int w = times[i][2];
                // relax only from reached nodes, and only if it gives a shorter time
                if (dist[u] != INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    changed = true;
                }
            }
            if (!changed) break;                // no update means all distances are final
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INF) return -1;      // some node never gets the signal
            ans = max(ans, dist[i]);            // the slowest node determines the total time
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<vector<int>> t1 = {{2,1,1},{2,3,1},{3,4,1}};
    cout << "Example 1: " << s.networkDelayTime(t1, 4, 2) << " (expected 2)" << endl;
    vector<vector<int>> t2 = {{1,2,1}};
    cout << "Example 2: " << s.networkDelayTime(t2, 2, 1) << " (expected 1)" << endl;
    vector<vector<int>> t3 = {{1,2,1}};
    cout << "Example 3: " << s.networkDelayTime(t3, 2, 2) << " (expected -1)" << endl;
    return 0;
}
