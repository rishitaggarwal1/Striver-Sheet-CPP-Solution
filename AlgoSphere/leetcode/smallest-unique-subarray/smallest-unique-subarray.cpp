/*
 * Problem   : Smallest Unique Subarray (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/smallest-unique-subarray/
 * Pattern   : Binary search on answer + rolling hash
 * Approach  : Brute force: Count tuples for each length
 * Complexity: Time O(n^3), Space O(n^2)
 *
 * For each length L from 1 upward, put every window nums[i..i+L-1], stored
 * as a tuple, into a hash map with its count. If any count is exactly 1, L
 * is the answer. The scan stops at the first such L, so the result is the
 * minimum. It always terminates because at L = n there is only one window.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Hash for a vector<int>, so whole windows can be used as unordered_map keys
    struct VecHash {
        size_t operator()(const vector<int>& v) const {
            size_t h = 1469598103934665603ULL;      // FNV-style starting seed
            for (int x : v) {
                h ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2); // mix in each element
            }
            return h;
        }
    };

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        for (int L = 1; L <= n; ++L) {                    // try lengths in increasing order
            unordered_map<vector<int>, int, VecHash> count; // fresh counts for this length
            for (int i = 0; i + L <= n; ++i) {            // every start of a length-L window
                vector<int> window(nums.begin() + i, nums.begin() + i + L); // copy the window as a tuple
                count[window]++;                          // a missing key starts at 0
            }
            for (auto& entry : count) {                   // look for a window seen exactly once
                if (entry.second == 1) return L;          // first such L is the minimum
            }
        }
        return n; // unreachable: at L = n there is a single window
    }
};

int main() {
    Solution s;
    vector<vector<int>> tests = {{3,3,3}, {2,1,2,3,3}, {1,1,2,2,1}};
    vector<int> expected = {3, 1, 2};
    for (size_t t = 0; t < tests.size(); ++t) {
        int got = s.smallestUniqueSubarray(tests[t]);
        cout << "Example " << t + 1 << ": output = " << got << ", expected = " << expected[t] << endl;
    }
    return 0;
}
