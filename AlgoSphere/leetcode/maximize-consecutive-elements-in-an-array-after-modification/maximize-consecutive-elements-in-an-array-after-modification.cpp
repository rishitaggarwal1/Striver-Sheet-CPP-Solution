/*
 * Problem   : Maximize Consecutive Elements in an Array After Modification (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/
 * Pattern   : Sorting + Dynamic Programming
 * Approach  : Optimal: Sort + end-value DP
 * Complexity: Time O(n log n), Space O(n)
 *
 * Sort nums in non-decreasing order and maintain a map dp[v] representing
 * the length of the longest valid consecutive sequence ending at integer v.
 * Because nums is sorted, all elements capable of contributing to values < x
 * have already been processed before x. For each x, updating dp[x + 1] from
 * dp[x] + 1 before updating dp[x] from dp[x - 1] + 1 ensures x either
 * becomes x + 1 or stays x, never both, which makes the DP transition exact.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        // Sort so all elements <= x are processed before x + 1
        sort(nums.begin(), nums.end());
        // dp[v] stores the longest consecutive sequence ending at value v
        unordered_map<int, int> dp;
        for (int x : nums) {
            // Read existing chain lengths before updating dp so x cannot extend itself
            int prevSame = dp.count(x) ? dp[x] : 0;
            int prevLess = dp.count(x - 1) ? dp[x - 1] : 0;
            // Option 1: increment x to x + 1, extending any chain ending at x
            dp[x + 1] = max(dp[x + 1], prevSame + 1);
            // Option 2: keep x unchanged, extending any chain ending at x - 1
            dp[x] = max(prevSame, prevLess + 1);
        }
        int best = 0;
        // Scan all reachable ending values to find the maximum sequence length
        for (const auto& [val, len] : dp) {
            best = max(best, len);
        }
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 1, 5, 1, 1};
    cout << "Example 1: " << sol.maxSelectedElements(nums1) << " (expected 3)\n";

    vector<int> nums2 = {1, 4, 7, 10};
    cout << "Example 2: " << sol.maxSelectedElements(nums2) << " (expected 1)\n";

    return 0;
}
