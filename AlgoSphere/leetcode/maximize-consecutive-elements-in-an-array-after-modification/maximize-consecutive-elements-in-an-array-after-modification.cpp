/*
 * Problem   : Maximize Consecutive Elements in an Array After Modification (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/
 * Pattern   : Sorting + Dynamic Programming
 * Approach  : Brute force: Enumerate all +0/+1 choices
 * Complexity: Time O(2^n * n log n), Space O(n)
 *
 * Generate all 2^n modified arrays by deciding for each index i whether to
 * add 0 or 1. For each resulting array, sort it (or insert into a set) and
 * scan for the longest run of consecutive distinct integers. By exhaustively
 * checking every valid modification, the maximum run found across all arrays
 * is guaranteed to be optimal.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        int best = 1; // At least one element can always be selected
        vector<int> cur(n); // Holds the current +0/+1 modified array

        // Enumerate all 2^n +0/+1 modification choices recursively
        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                vector<int> vals = cur; // Copy cur so backtracking can overwrite cur safely
                sort(vals.begin(), vals.end()); // Order values to detect consecutive streaks
                vals.erase(unique(vals.begin(), vals.end()), vals.end()); // Remove duplicates because consecutive elements must be distinct

                int run = 1; // Current consecutive streak length
                for (int j = 1; j < (int)vals.size(); ++j) {
                    if (vals[j] == vals[j - 1] + 1) {
                        ++run; // Extend the streak when adjacent distinct values differ by 1
                        best = max(best, run); // Update the global maximum streak length
                    } else {
                        run = 1; // Reset streak when a gap larger than 1 occurs
                    }
                }
                return;
            }

            cur[i] = nums[i]; // Branch 1: keep nums[i] unchanged (+0)
            dfs(i + 1);

            cur[i] = nums[i] + 1; // Branch 2: increase nums[i] by 1 (+1)
            dfs(i + 1);
        };

        dfs(0); // Start exploring choices from index 0
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> ex1 = {2, 1, 5, 1, 1};
    cout << "Example 1: output = " << sol.maxSelectedElements(ex1) << " (expected: 3)\n";

    vector<int> ex2 = {1, 4, 7, 10};
    cout << "Example 2: output = " << sol.maxSelectedElements(ex2) << " (expected: 1)\n";

    return 0;
}
