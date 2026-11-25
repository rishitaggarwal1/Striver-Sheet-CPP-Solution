/*
 * Problem   : Smallest Unique Subarray (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/smallest-unique-subarray/
 * Pattern   : Binary search on answer + rolling hash
 * Approach  : Better: Linear scan over L with rolling hash
 * Complexity: Time O(n^2), Space O(n)
 *
 * Precompute prefix hashes H[i] and powers P[i], so the hash of nums[l..r]
 * is H[r+1] - H[l]*P[r-l+1] (mod M) in O(1). For each L, count window hashes
 * in a map and test for a count of 1. Correctness relies on equal windows
 * having equal hashes, and, with a strong double hash, unequal windows
 * almost surely differing.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const long long B = 100003;            // base larger than any value (max 1e5)
        const long long M1 = 1000000007LL;     // first modulus
        const long long M2 = 998244353LL;      // second modulus: double hash makes collisions negligible
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            H1[i + 1] = (H1[i] * B + nums[i]) % M1;   // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B + nums[i]) % M2;
            P1[i + 1] = (P1[i] * B) % M1;              // B^(i+1)
            P2[i + 1] = (P2[i] * B) % M2;
        }
        for (int L = 1; L <= n; ++L) {                 // try lengths from shortest up
            unordered_map<long long, int> cnt;
            cnt.reserve(2 * (n - L + 1));              // avoid rehashing
            for (int l = 0; l + L <= n; ++l) {
                // O(1) window hash: strip the prefix before l, shifted by B^L
                long long h1 = (H1[l + L] - H1[l] * P1[L] % M1 + M1) % M1;
                long long h2 = (H2[l + L] - H2[l] * P2[L] % M2 + M2) % M2;
                long long key = (h1 << 32) | h2;       // combine both hashes into one 64-bit key
                ++cnt[key];
            }
            for (auto& kv : cnt)
                if (kv.second == 1) return L;          // a window occurring exactly once
        }
        return n;                                      // unreachable: length n is always unique
    }
};

int main() {
    Solution s;
    vector<vector<int>> tests = {{3, 3, 3}, {2, 1, 2, 3, 3}, {1, 1, 2, 2, 1}};
    vector<int> expected = {3, 1, 2};
    for (size_t t = 0; t < tests.size(); ++t) {
        int got = s.smallestUniqueSubarray(tests[t]);
        cout << "Example " << t + 1 << ": output = " << got << ", expected = " << expected[t] << "\n";
    }
    return 0;
}
