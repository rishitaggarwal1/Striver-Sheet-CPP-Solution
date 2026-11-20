/*
 * Problem   : House Robber (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/house-robber/
 * Pattern   : 1D DP on prefixes (pick / skip)
 * Approach  : Optimal: Two rolling variables
 * Complexity: Time O(n), Space O(1)
 *
 * Keep prev1 = best through house i − 1 and prev2 = best through house i −
 * 2, starting with prev1 = nums[0] and prev2 = 0 (nothing before house 0).
 * For each i from 1, curr = max(nums[i] + prev2, prev1); then shift prev2 ←
 * prev1 and prev1 ← curr. The invariant "before iteration i, prev1 = dp[i −
 * 1] and prev2 = dp[i − 2]" is exactly the table's recurrence, so after the
 * last house prev1 = dp[n − 1]. A single house needs no special case: the
 * loop does not run and prev1 = nums[0] is returned.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        int prev2 = 0;       // best loot through house i - 2 (nothing exists before house 0)
        int prev1 = nums[0]; // best loot through house i - 1; with one house, rob it
        for (int i = 1; i < n; ++i) {
            int pick = nums[i] + prev2; // rob house i, so house i - 1 must stay untouched
            int skip = prev1;           // leave house i and keep the best through house i - 1
            int curr = max(pick, skip); // best loot through house i
            prev2 = prev1;              // slide the window: house i - 1 becomes the new "two back"
            prev1 = curr;               // and house i becomes the new "one back"
        }
        return prev1; // best loot through the last house (nums[0] when n == 1)
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Example 1: " << sol.rob(nums1) << " (expected 4)\n";

    vector<int> nums2 = {2, 7, 9, 3, 1};
    cout << "Example 2: " << sol.rob(nums2) << " (expected 12)\n";

    return 0;
}
