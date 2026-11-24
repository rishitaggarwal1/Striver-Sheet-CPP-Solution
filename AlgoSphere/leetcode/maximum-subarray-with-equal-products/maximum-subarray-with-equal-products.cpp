/*
 * Problem   : Maximum Subarray With Equal Products (LeetCode, Easy)
 * Link      : https://leetcode.com/problems/maximum-subarray-with-equal-products/
 * Pattern   : Prime-exponent reasoning + sliding window
 * Approach  : Brute force: Recompute every subarray
 * Complexity: Time O(n^3), Space O(1)
 *
 * For every pair (l, r), compute the product, gcd and lcm of nums[l..r] from
 * scratch, using big integers or a capped product. Record the length
 * whenever product == lcm*gcd. This is correct because it checks the
 * definition directly on every candidate.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int best = 0;                       // longest product-equivalent length found so far
        const long long CAP = 1000000;      // > max lcm*gcd (2520*10), so a capped product never matches
        for (int l = 0; l < n; ++l) {       // every start index
            for (int r = l; r < n; ++r) {   // every end index
                long long p = 1;            // product of nums[l..r], capped
                long long g = 0;            // gcd(0, x) = x, neutral start
                long long lc = 1;           // lcm(1, x) = x, neutral start
                for (int k = l; k <= r; ++k) {          // recompute from scratch
                    p = min(p * nums[k], CAP);         // cap keeps p small and avoids overflow
                    g = std::gcd(g, (long long)nums[k]);
                    lc = std::lcm(lc, (long long)nums[k]); // at most 2520 for values <= 10
                }
                if (p == lc * g)                       // definition of product equivalent
                    best = max(best, r - l + 1);
            }
        }
        return best;
    }
};

int main() {
    vector<vector<int>> tests = {{1,2,1,2,1,1,1}, {2,3,4,5,6}, {1,2,3,1,4,5,1}};
    vector<int> expected = {5, 3, 5};
    for (size_t i = 0; i < tests.size(); ++i) {
        Solution s;
        int out = s.maxLength(tests[i]);
        cout << "Example " << i + 1 << ": output = " << out << ", expected = " << expected[i] << "\n";
    }
    return 0;
}
