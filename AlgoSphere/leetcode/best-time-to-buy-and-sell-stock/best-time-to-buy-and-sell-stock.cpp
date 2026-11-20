/*
 * Problem   : Best Time to Buy and Sell Stock (LeetCode, Easy)
 * Link      : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * Pattern   : Running minimum (one-pass prefix DP)
 * Approach  : Optimal: One pass with a running minimum
 * Complexity: Time O(n), Space O(1)
 *
 * Scan the days left to right, holding minPrice (the cheapest price on the
 * days before i) and best (the best profit so far). On day i, first try
 * selling: profit = prices[i] - minPrice, and raise best if it is larger.
 * Then let day i become a buy candidate by lowering minPrice if prices[i] is
 * cheaper. The invariant is that when day i is examined, minPrice =
 * min(prices[0..i-1]), so every sell day is paired with its best buy day,
 * exactly as in the prefix-array version.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int minPrice = prices[0];                // cheapest buy price seen so far (n >= 1)
        int best = 0;                            // not trading is allowed, so never below 0
        for (int i = 1; i < n; i++) {
            int profit = prices[i] - minPrice;   // profit if we sell today
            if (profit > best) {
                best = profit;                   // best sell seen so far
            }
            if (prices[i] < minPrice) {
                minPrice = prices[i];            // cheaper buy day for all later sells
            }
        }
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Example 1: " << sol.maxProfit(prices1) << " (expected 5)\n";

    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "Example 2: " << sol.maxProfit(prices2) << " (expected 0)\n";

    return 0;
}
