/*
 * Problem   : Climbing Stairs (LeetCode, Easy)
 * Link      : https://leetcode.com/problems/climbing-stairs/
 * Pattern   : 1D DP (Fibonacci recurrence)
 * Approach  : Optimal: Bottom-up with two rolling variables
 * Complexity: Time O(n), Space O(1)
 *
 * Hold prev2 = ways(i − 2) and prev1 = ways(i − 1), starting from ways(0) =
 * 1 and ways(1) = 1. For each i from 2 to n, compute curr = prev1 + prev2,
 * then slide the window: prev2 takes the old prev1 and prev1 takes curr. The
 * invariant "before iteration i, prev1 = ways(i − 1) and prev2 = ways(i −
 * 2)" holds at the start and is restored by the slide, so after i = n the
 * value curr is ways(n). For n = 1 the loop would not run and curr would
 * still be 0, which is why prev1 = 1 is returned early.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        int prev2 = 1;            // ways(0): one way to be on the ground (no moves)
        int prev1 = 1;            // ways(1): a single 1-step
        if (n == 1) return prev1; // the loop starts at i = 2, so answer n = 1 directly
        int curr = 0;             // will hold ways(i) inside the loop
        for (int i = 2; i <= n; ++i) {
            curr = prev1 + prev2; // arrive by a 1-step from i - 1 or a 2-step from i - 2
            prev2 = prev1;        // ways(i - 1) becomes the "two back" value for step i + 1
            prev1 = curr;         // ways(i) becomes the "one back" value for step i + 1
        }
        return curr; // ways(n); at most 1836311903 for n = 45, which still fits in int
    }
};

int main() {
    Solution sol;

    int n1 = 2;
    cout << "Example 1: n = " << n1 << " -> " << sol.climbStairs(n1) << " (expected 2)\n";

    int n2 = 3;
    cout << "Example 2: n = " << n2 << " -> " << sol.climbStairs(n2) << " (expected 3)\n";

    return 0;
}
