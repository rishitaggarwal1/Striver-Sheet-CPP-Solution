/*
 * Problem   : House Robber II (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/house-robber-ii/
 * Pattern   : 1D take/skip DP, run twice to break the circle
 * Approach  : Optimal: Two rolling variables per straight street
 * Complexity: Time O(n), Space O(1)
 *
 * Keep prev1 = best loot through the previous house and prev2 = best loot
 * through the house before it, both starting at 0. For each house i in the
 * street, cur = max(prev1, nums[i] + prev2): skip house i and keep prev1, or
 * rob it and add the best total that avoids its left neighbour. Then shift
 * prev2 ← prev1 and prev1 ← cur, so the invariant 'prev1 is the best through
 * the latest house' holds after every step. Doing this on 0..n-2 and 1..n-1
 * and taking the larger covers every legal ring plan.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // A lone house has no neighbour, and both ranges below would be empty
        if (n == 1) return nums[0];
        // Case 1: never rob the last house, so houses 0..n-2 form a straight street
        int skipLast = robLine(nums, 0, n - 2);
        // Case 2: never rob the first house, so houses 1..n-1 form a straight street
        int skipFirst = robLine(nums, 1, n - 1);
        // Every legal plan on the ring leaves house 0 or house n-1 alone
        return max(skipLast, skipFirst);
    }

private:
    // Classic House Robber on nums[lo..hi] using two rolling variables
    int robLine(const vector<int>& nums, int lo, int hi) {
        int prev2 = 0;  // best loot through house i-2
        int prev1 = 0;  // best loot through house i-1
        for (int i = lo; i <= hi; ++i) {
            // Either skip house i (keep prev1) or rob it (nums[i] + prev2)
            int cur = max(prev1, nums[i] + prev2);
            prev2 = prev1;  // slide the window one house to the right
            prev1 = cur;
        }
        return prev1;  // best loot for the whole range
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 3, 2};
    cout << "Example 1: " << sol.rob(nums1) << " (expected 3)\n";

    vector<int> nums2 = {1, 2, 3, 1};
    cout << "Example 2: " << sol.rob(nums2) << " (expected 4)\n";

    vector<int> nums3 = {1, 2, 3};
    cout << "Example 3: " << sol.rob(nums3) << " (expected 3)\n";

    return 0;
}
