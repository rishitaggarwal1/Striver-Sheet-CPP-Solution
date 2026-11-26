/*
 * Problem   : Palindrome Partitioning (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/palindrome-partitioning/
 * Pattern   : Backtracking with precomputed palindrome DP table
 * Approach  : Brute force: Enumerate all cut masks, then filter
 * Complexity: Time O(n · 2^n), Space O(n)
 *
 * Loop over every mask from 0 to 2^(n-1)-1, where bit k means "cut after
 * index k". Split s into pieces according to the mask, then check each piece
 * with two pointers. Keep the split only if every piece is a palindrome. It
 * is correct because every partition corresponds to exactly one mask.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

string show(const vector<vector<string>>& v) {
    string out = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) out += ",";
        out += "[";
        for (size_t j = 0; j < v[i].size(); ++j) {
            if (j) out += ",";
            out += "\"" + v[i][j] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> result;
        // each of the n-1 gaps is cut (bit=1) or not (bit=0)
        for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
            vector<string> pieces;   // pieces of this split
            int start = 0;           // start index of current piece
            bool ok = true;          // all pieces palindromes so far?
            for (int k = 0; k < n; ++k) {
                // a piece ends at k if we're at the string end or there's a cut after k
                if (k == n - 1 || ((mask >> k) & 1)) {
                    int lo = start, hi = k;
                    // two-pointer palindrome check on s[start..k]
                    while (lo < hi && s[lo] == s[hi]) { ++lo; --hi; }
                    if (lo < hi) { ok = false; break; } // mismatch: reject this mask
                    pieces.push_back(s.substr(start, k - start + 1));
                    start = k + 1;   // next piece starts after the cut
                }
            }
            if (ok) result.push_back(pieces); // keep only fully valid splits
        }
        return result;
    }
};

int main() {
    Solution sol;
    cout << "Example 1: " << show(sol.partition("aab")) << "  expected (any order): [[\"a\",\"a\",\"b\"],[\"aa\",\"b\"]]" << endl;
    cout << "Example 2: " << show(sol.partition("a")) << "  expected: [[\"a\"]]" << endl;
    return 0;
}
