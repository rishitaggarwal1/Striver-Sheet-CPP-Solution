/*
 * Problem   : Find Subtree Sizes After Changes (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/find-subtree-sizes-after-changes/
 * Pattern   : DFS with per-character ancestor state (backtracking), then subtree-size accumulation
 * Approach  : Brute force: Walk up ancestors per node
 * Complexity: Time O(n^2), Space O(n)
 *
 * For each x from 1 to n-1, follow parent upward until a node with the same
 * letter appears. That node becomes newParent[x]; if none appears, keep
 * parent[x]. Build children lists for the new tree and compute subtree sizes
 * with a DFS from 0. It is correct because climbing checks the ancestors in
 * order of increasing distance, so the first match is the closest one.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

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
