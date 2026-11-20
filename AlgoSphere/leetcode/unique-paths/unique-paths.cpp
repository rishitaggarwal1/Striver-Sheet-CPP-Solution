/*
 * Problem   : Unique Paths (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/unique-paths/
 * Pattern   : Grid DP for counting paths, which collapses to a binomial coefficient
 * Approach  : Optimal: Binomial coefficient C(m + n − 2, m − 1)
 * Complexity: Time O(min(m, n)), Space O(1)
 *
 * A path is fully described by which of its N = m + n - 2 moves are Downs,
 * and any choice of m - 1 positions gives a valid path, so the count is C(N,
 * m - 1) = C(N, n - 1). Using k = min(m, n) - 1 keeps the loop as short as
 * possible. Building it as res = res × (N - k + i) / i for i = 1..k keeps
 * every intermediate equal to the whole number C(N - k + i, i), so integer
 * division never loses anything, and a 64-bit res absorbs the temporary
 * product before each division.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // Every path has exactly m-1 Downs and n-1 Rights, so it is fixed by choosing
        // which of the N = m+n-2 moves are Downs: answer = C(N, m-1) = C(N, n-1)
        int N = m + n - 2;
        int k = min(m - 1, n - 1);      // use the smaller side so the loop is shortest
        long long res = 1;              // 64-bit: res * (N-k+i) can exceed 2^31 - 1
        for (int i = 1; i <= k; ++i) {
            res = res * (N - k + i);    // multiply first ...
            res /= i;                   // ... then divide: res is now C(N-k+i, i), exact
        }
        return (int)res;                // the problem guarantees the answer <= 2 * 10^9
    }
};

int main() {
    Solution sol;

    cout << "Example 1: " << sol.uniquePaths(3, 7) << " (expected 28)\n";
    cout << "Example 2: " << sol.uniquePaths(3, 2) << " (expected 3)\n";

    return 0;
}
