/*
 * Problem   : Smallest Unique Subarray (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/smallest-unique-subarray/
 * Pattern   : Binary search on answer + rolling hash
 * Approach  : Optimal: Binary search on length + rolling hash
 * Complexity: Time O(n log n), Space O(n)
 *
 * Monotonicity: if the window at start i of length L is unique and L < n,
 * extend it by one element. Any other copy of the extension would contain a
 * second copy of the original window, so the extension is unique too.
 * Therefore has_unique is false up to the answer and true from it onward,
 * and has_unique(n) is always true. Binary search over [1, n], evaluating
 * has_unique(mid) with O(1) rolling-hash window fingerprints and a counting
 * map. (A suffix array with LCP, or a suffix automaton, also works: shortest
 * unique substring = min over suffixes of max(adjacent LCPs) + 1.)
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        // Two independent moduli (double hashing) make a false match astronomically unlikely
        const long long M1 = 1000000007LL, M2 = 1000000009LL;
        // Bases larger than the max value (1e5) so different arrays never alias before the mod
        const long long B1 = 100003LL, B2 = 100019LL;
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; i++) {
            H1[i + 1] = (H1[i] * B1 + nums[i]) % M1; // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B2 + nums[i]) % M2;
            P1[i + 1] = P1[i] * B1 % M1;             // B1^(i+1), used to shift prefixes
            P2[i + 1] = P2[i] * B2 % M2;
        }
        // Returns true if some window of length L occurs exactly once
        auto hasUnique = [&](int L) {
            unordered_map<unsigned long long, int> cnt;
            cnt.reserve(2 * (n - L + 1)); // avoid rehashing
            for (int i = 0; i + L <= n; i++) {
                // O(1) fingerprint of nums[i..i+L-1]; products stay below ~1e18, so they fit in long long
                long long a = ((H1[i + L] - H1[i] * P1[L]) % M1 + M1) % M1;
                long long b = ((H2[i + L] - H2[i] * P2[L]) % M2 + M2) % M2;
                // Both hashes are below 2^30, so pack them into one 64-bit key
                unsigned long long key = ((unsigned long long)a << 32) | (unsigned long long)b;
                cnt[key]++;
            }
            for (auto& p : cnt)
                if (p.second == 1) return true; // found a window occurring exactly once
            return false;
        };
        int lo = 1, hi = n; // hasUnique(n) is always true
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUnique(mid)) hi = mid; // answer <= mid (monotonic predicate)
            else lo = mid + 1;            // answer > mid
        }
        return lo;
    }
};

int main() {
    Solution sol;
    vector<pair<vector<int>, int>> tests = {
        {{3, 3, 3}, 3},
        {{2, 1, 2, 3, 3}, 1},
        {{1, 1, 2, 2, 1}, 2}
    };
    for (auto& t : tests) {
        vector<int> nums = t.first;
        int got = sol.smallestUniqueSubarray(nums);
        cout << "Output: " << got << "  Expected: " << t.second << (got == t.second ? "  OK" : "  MISMATCH") << "\n";
    }
    return 0;
}
