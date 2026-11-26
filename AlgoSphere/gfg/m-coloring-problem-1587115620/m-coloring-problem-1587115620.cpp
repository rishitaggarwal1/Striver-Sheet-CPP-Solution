/*
 * Problem   : M-Coloring Problem (GeeksforGeeks, Medium)
 * Link      : https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1
 * Pattern   : Backtracking (constraint satisfaction)
 * Approach  : Brute force: Enumerate all m^V colorings
 * Complexity: Time O(m^V · (V+E)), Space O(V)
 *
 * Treat the coloring as a V-digit number in base m and iterate over all m^V
 * values. For each full assignment, check every edge (u, w) in adj and
 * require color[u] != color[w]. It is correct because it literally checks
 * every possibility. It does no pruning at all.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool graphColoring(vector<vector<int>> &adj, int m) {
        int V = adj.size();                 // number of vertices
        vector<int> color(V, 0);            // current assignment, read as a base-m counter (color[0] = lowest digit)
        while (true) {
            bool valid = true;              // assume valid until a conflicting edge is found
            for (int u = 0; u < V && valid; u++) {      // scan every vertex
                for (int w : adj[u]) {                  // and every neighbour of it
                    if (color[u] == color[w]) {         // both ends of edge (u, w) share a color
                        valid = false;                  // this assignment is invalid
                        break;
                    }
                }
            }
            if (valid) return true;         // every edge has different colors at its two ends
            int pos = 0;                    // add 1 to the base-m counter
            while (pos < V && color[pos] == m - 1) {
                color[pos] = 0;             // digit overflows: reset it and carry
                pos++;
            }
            if (pos == V) return false;     // counter wrapped around: all m^V assignments failed
            color[pos]++;                   // increment the first digit that can absorb the carry
        }
    }
};

int main() {
    Solution sol;
    vector<vector<int>> adj1 = {{1, 3, 2}, {0, 3}, {3, 0}, {1, 2, 0}};
    bool r1 = sol.graphColoring(adj1, 3);
    cout << "Example 1: " << (r1 ? "true" : "false") << " (expected true)" << endl;
    vector<vector<int>> adj2 = {{1, 2}, {0, 2}, {0, 1}};
    bool r2 = sol.graphColoring(adj2, 2);
    cout << "Example 2: " << (r2 ? "true" : "false") << " (expected false)" << endl;
    return 0;
}
