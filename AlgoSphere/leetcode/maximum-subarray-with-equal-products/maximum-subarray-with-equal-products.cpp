/*
 * Problem   : Maximum Subarray With Equal Products (LeetCode, Easy)
 * Link      : https://leetcode.com/problems/maximum-subarray-with-equal-products/
 * Pattern   : Prime-exponent reasoning + sliding window
 * Approach  : Better: Incremental extension with early break
 * Complexity: Time O(n^2 log 10), Space O(1)
 *
 * Fix l and extend r, updating prod *= nums[r], g = gcd(g, nums[r]) and L =
 * lcm(L, nums[r]). Since lcm*gcd <= 2520*10 and the product never decreases,
 * stop extending once prod exceeds that bound. This keeps numbers small and
 * stays correct, because no further extension can satisfy the equation.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Euclid's gcd; gcd(0, x) = x, which lets g start at 0
    int gcd(long long a, long long b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int best = 0;                          // longest valid length seen so far
        for (int l = 0; l < n; l++) {          // fix the left end
            long long prod = 1;                // product of nums[l..r]
            long long g = 0;                   // gcd of nums[l..r] (0 is the gcd identity)
            long long L = 1;                   // lcm of nums[l..r] (1 is the lcm identity)
            for (int r = l; r < n; r++) {      // extend the right end
                prod *= nums[r];
                g = gcd(g, nums[r]);
                L = L / gcd(L, nums[r]) * nums[r]; // lcm update; divide first to stay small
                if (prod == L * g)             // subarray is product equivalent
                    best = max(best, r - l + 1);
                if (prod > 25200)              // L*g <= 2520*10 and prod never shrinks
                    break;                     // no longer subarray from l can match
            }
        }
        return best;
    }
};

int main() {
    vector<vector<int>> tests = {{1,2,1,2,1,1,1}, {2,3,4,5,6}, {1,2,3,1,4,5,1}};
    vector<int> expected = {5, 3, 5};
    for (size_t i = 0; i < tests.size(); i++) {
        Solution s;
        int out = s.maxLength(tests[i]);
        cout << "Example " << i + 1 << ": output = " << out << ", expected = " << expected[i] << endl;
    }
    return 0;
}
