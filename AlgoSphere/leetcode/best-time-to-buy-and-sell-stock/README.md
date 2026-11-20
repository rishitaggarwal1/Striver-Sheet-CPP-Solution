# Best Time to Buy and Sell Stock

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · Pattern: **Running minimum (one-pass prefix DP)**

> Choose a buy day `i` and a later sell day `j` to maximise `prices[j] - prices[i]`, returning 0 if no such pair makes money.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given an array prices where prices[i] is the price of a given stock on the i^th day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.

Constraints:

- 1 <= prices.length <= 10^5

- 0 <= prices[i] <= 10^4
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You pick one day to buy and a strictly later day to sell, and want the largest `sell price - buy price`. If no later price is ever higher than an earlier one, you simply do not trade and the answer is 0.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In Example 1 the best sale (price 6 at index 4) is paired with the cheapest price that came before it (1 at index 1). For any sell day, the best buy day is the cheapest earlier day; the global minimum is useless if it comes after the sale, as in `[2,4,1]` where the answer is 2, not 3.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `prices.length` up to `10^5`, checking every buy/sell pair is about `5·10^9` operations, far too slow. You need a single linear pass, `O(n)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a prefix-minimum (one-state DP) pattern: as you sweep left to right, the best buy for today depends only on a summary of the days before it, which can be updated in constant time per day.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Fix the sell day `i`: the best profit from selling then is `prices[i] - min(prices[0..i-1])`. The answer is the largest of these values (or 0), and the prefix minimum can be maintained incrementally instead of recomputed.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track two numbers: `minPrice`, the cheapest price on the days before the current one (starts as `prices[0]`), and `best`, the largest profit found so far (starts at 0).

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `minPrice` to `prices[0]` and `best` to 0.
For each day `i` from 1 to `n - 1`:
Compute `profit = prices[i] - minPrice`.
If `profit` is larger than `best`, store it in `best`.
If `prices[i]` is lower than `minPrice`, store it in `minPrice`.
Return `best`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

Never reset `best` when a new minimum appears (in `[3,8,1,2]` the answer stays 5), and start `best` at 0 so falling prices like Example 2 return 0. A single day `[5]` skips the loop and returns 0, and equal prices give 0 because the profit is never greater than 0. Time is `O(n)` and extra space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "choosing a different day in the future to sell that stock" | only earlier days can be the buy day for a given sell day, so each day needs a summary of the prefix before it. |
| "a single day to buy ... a different day ... to sell" | exactly one pair, so the answer is the best over sell days of the price minus the cheapest earlier price. |
| "1 <= prices.length <= 10^5" | checking all `n(n - 1)/2` pairs is about `5·10^9`, so one linear pass is needed. |
| "If you cannot achieve any profit, return 0" | start the answer at 0; falling prices like Example 2 must return 0, not a negative number. |

### What the constraints tell you

With `n = 10^5`, all pairs is `n(n - 1)/2 ≈ 5·10^9` checks, far too slow; sorting would destroy the day order anyway. One pass is `10^5` constant-time steps, so the target is `O(n)` time and ideally `O(1)` extra space.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the simplest correct method?**

<details>
<summary>Answer</summary>

Try every buy day `i` and every later sell day `j`, keeping the largest `prices[j] - prices[i]`. Example 1 has 15 pairs, and the best is `6 - 1 = 5`.

</details>

**Q2. If I fix the sell day `j`, which buy day should I pair it with?**

<details>
<summary>Answer</summary>

The cheapest day before `j`, because a lower buy price always means more profit for the same sell price. For selling at 6 (index 4) in Example 1, the cheapest earlier price is 1 (index 1), which is the statement's "buy on day 2, sell on day 5" in 1-based days.

</details>

**Q3. Why not just buy at the global minimum and sell at the global maximum?**

<details>
<summary>Answer</summary>

The minimum may come after the maximum. In `[2,4,1]` the global minimum 1 is the last day, so the real answer is `4 - 2 = 2`, not `4 - 1 = 3`.

</details>

**Q4. How do I get the cheapest earlier price for every day without rescanning?**

<details>
<summary>Answer</summary>

The cheapest price on days `0..i` is `min(cheapest on days 0..i-1, prices[i])`, so a prefix-minimum array `minLeft` can be filled in one left-to-right pass.

</details>

**Q5. Do I need to keep the whole `minLeft` array?**

<details>
<summary>Answer</summary>

No. Day `i` only reads `minLeft[i - 1]`, once. So a single variable `minPrice` works: compute today's profit against it, then lower it if today is cheaper. That gives `O(n)` time and `O(1)` space.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Check every buy/sell pair](#1-brute-force-check-every-buysell-pair) | `O(n^2)` | `O(1)` |
| 2 | [Better: Prefix minimum array](#2-better-prefix-minimum-array) | `O(n)` | `O(n)` |
| 3 | [Optimal: One pass with a running minimum](#3-optimal-one-pass-with-a-running-minimum) | `O(n)` | `O(1)` |

### 1. Brute force: Check every buy/sell pair

> **Where you start:** The answer is the largest `prices[j] - prices[i]` over pairs with `i < j`, so the obvious first move is to try every pair of days.

**Idea.** An outer loop picks the buy day `i` and an inner loop tries every later sell day `j`, computing `prices[j] - prices[i]` and keeping the largest value in `best`. Starting `best` at 0 covers the case where every pair loses money, as in Example 2. It is correct because it examines every legal transaction, so the maximum cannot be missed.

**Steps**

1. Set `best` to 0.
2. For each buy day `i` from 0 to `n - 2`, read `buy = prices[i]`.
3. For each sell day `j` from `i + 1` to `n - 1`, compute `profit = prices[j] - buy`.
4. If `profit` is larger than `best`, store it in `best`.
5. After all pairs, return `best`.

**Pseudocode**

```text
 1 │ function maxProfit(prices)
 2 │   n ← length(prices)
 3 │   best ← 0  // not trading is allowed, so the answer is never below 0
 4 │   for i ← 0 to n - 2  // buy on day i
 5 │     buy ← prices[i]
 6 │     for j ← i + 1 to n - 1  // sell on a strictly later day j
 7 │       sell ← prices[j]
 8 │       profit ← sell - buy
 9 │       if profit > best
10 │         best ← profit  // new best pair (i, j)
11 │   return best
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Buy-day loop (lines 4-5) | n − 1 iterations × O(1) | Every day except the last is tried as the buy day. |
| Sell-day loop (lines 6-10) | n − 1 − i iterations × O(1) for buy day i | Every later day is tried as the sell day, with a subtraction and a comparison each. |

- **Adding it up:** (n − 1) + (n − 2) + … + 1 = n(n − 1)/2 = O(n^2); the inner loop dominates the O(n) outer loop.
- **At the maximum input:** n = 10^5 → about 5·10^9 pair checks, several seconds even in C++, so it gets Time Limit Exceeded.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| Scalars n, best, i, buy, j, sell, profit (lines 2-8) | O(1) | A fixed number of variables regardless of n. |

- **Adding it up:** O(1).
- **Not counted:** The input prices is only read and the output is a single integer.

**Dry run** on `prices = [7,1,5,3,6,4]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | There are n = 6 days and no trade has been made, so best = 0. | `n = 6`<br>`best = 0`<br>`prices = [7, 1, 5, 3, 6, 4]` |
| 2 | 8 | Buy day i = 0 (price 7), sell day j = 1 (price 1): profit = 1 - 7 = -6, which is not > 0, so best stays 0. | `i = 0`<br>`buy = 7`<br>`j = 1`<br>`sell = 1`<br>`profit = -6`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→0, j→1) |
| 3 | 8 | Skipping j = 2..4 for i = 0: profits 5-7, 3-7 and 6-7 are all negative. At j = 5 profit = 4 - 7 = -3; buying at 7 never pays, best stays 0. | `j = 5`<br>`sell = 4`<br>`profit = -3`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→0, j→5) |
| 4 | 10 | 4 > 0, so best = 4: buying at 1 (index 1) and selling at 5 (index 2) is the best pair so far. | `best = 4`<br>`i = 1`<br>`buy = 1`<br>`j = 2`<br>`sell = 5`<br>`profit = 4`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1, j→2) |
| 5 | 8 | i = 1, j = 3: profit = 3 - 1 = 2, not > 4; best stays 4. | `j = 3`<br>`sell = 3`<br>`profit = 2`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1, j→3) |
| 6 | 10 | 5 > 4, so best = 5: buy at 1 (index 1), sell at 6 (index 4). | `best = 5`<br>`j = 4`<br>`sell = 6`<br>`profit = 5`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1, j→4) |
| 7 | 8 | i = 1, j = 5: profit = 4 - 1 = 3, not > 5. All sell days for buy index 1 are done. | `j = 5`<br>`sell = 4`<br>`profit = 3`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1, j→5) |
| 8 | 8 | Buy day i = 2 (price 5): j = 3 gives -2, j = 4 gives 1, and j = 5 gives profit = 4 - 5 = -1; none beats 5. | `i = 2`<br>`buy = 5`<br>`profit = -1`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→2, j→5) |
| 9 | 8 | Buy day i = 3 (price 3): j = 4 gives 3 and j = 5 gives profit = 4 - 3 = 1; none beats 5. | `i = 3`<br>`buy = 3`<br>`profit = 1`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→3, j→5) |
| 10 | 8 | Last pair: buy at 6 (index 4), sell at 4 (index 5), profit = -2; best stays 5. | `i = 4`<br>`buy = 6`<br>`profit = -2`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→4, j→5) |
| 11 | 11 | All 15 pairs have been checked; return best = 5. | `prices = [7, 1, 5, 3, 6, 4]` |

**Result:** 5 — the pair buy at 1 (index 1), sell at 6 (index 4) has the largest difference among all 15 pairs with buy before sell.

**C++ solution**

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int best = 0;                            // not trading gives profit 0
        for (int i = 0; i < n - 1; i++) {        // buy on day i
            int buy = prices[i];
            for (int j = i + 1; j < n; j++) {    // sell on a strictly later day j
                int sell = prices[j];
                int profit = sell - buy;         // profit of the pair (i, j)
                if (profit > best) {
                    best = profit;               // new best pair found
                }
            }
        }
        return best;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int best = 0;                            // not trading gives profit 0
        for (int i = 0; i < n - 1; i++) {        // buy on day i
            int buy = prices[i];
            for (int j = i + 1; j < n; j++) {    // sell on a strictly later day j
                int sell = prices[j];
                int profit = sell - buy;         // profit of the pair (i, j)
                if (profit > best) {
                    best = profit;               // new best pair found
                }
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
```

</details>

**Why move on:** For `n = 10^5` that is about `5·10^9` pairs, far beyond the time limit. For every sell day it effectively rescans all earlier days to find the cheapest one, repeating the same minimum search again and again.

### 2. Better: Prefix minimum array

> **How you get here:** For a fixed sell day `j`, the brute force scans every earlier day, yet the only one that matters is the cheapest, `min(prices[0..j-1])`, and those prefix minimums can be computed for all days in one pass.

**Idea.** Precompute `minLeft[i]`, the cheapest price on days `0..i`, with `minLeft[i] = min(minLeft[i - 1], prices[i])`. Selling on day `i` then earns at most `prices[i] - minLeft[i - 1]`, and the answer is the largest of these values, or 0. This is correct because for a fixed sell price a lower buy price always gives a higher profit, so the cheapest earlier day is the best partner for every sell day.

**Steps**

1. Create `minLeft` of length `n` and set `minLeft[0] = prices[0]`.
2. For `i` from 1 to `n - 1`, set `minLeft[i]` to the smaller of `minLeft[i - 1]` and `prices[i]`.
3. Set `best` to 0.
4. For each sell day `i` from 1 to `n - 1`, compute `profit = prices[i] - minLeft[i - 1]`.
5. Keep the largest `profit` in `best`, then return `best`.

**Pseudocode**

```text
 1 │ function maxProfit(prices)
 2 │   n ← length(prices)
 3 │   minLeft ← array of n values  // minLeft[i] = cheapest price on days 0..i
 4 │   minLeft[0] ← prices[0]
 5 │   for i ← 1 to n - 1
 6 │     minLeft[i] ← min(minLeft[i - 1], prices[i])  // extend the prefix by one day
 7 │   best ← 0  // doing nothing earns 0
 8 │   for i ← 1 to n - 1
 9 │     profit ← prices[i] - minLeft[i - 1]  // sell on day i, buy at the cheapest earlier day
10 │     if profit > best
11 │       best ← profit
12 │   return best
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Prefix-minimum fill (lines 4-6) | n − 1 iterations × O(1) | Each minLeft[i] is one min of two numbers. |
| Profit scan (lines 8-11) | n − 1 iterations × O(1) | Each sell day does one subtraction and one comparison. |

- **Adding it up:** (n − 1) + (n − 1) = 2n − 2 = O(n); two linear passes stay linear.
- **At the maximum input:** n = 10^5 → about 2·10^5 simple steps, well under a millisecond.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Array minLeft (line 3) | n integers | One prefix minimum is stored per day. |
| Scalars n, best, i, profit | O(1) | A fixed number of variables. |

- **Adding it up:** n + O(1) = O(n); the minLeft array dominates.
- **Not counted:** The input prices is not counted.

**Dry run** on `prices = [7,1,5,3,6,4]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | Allocate minLeft (unfilled cells shown as -) and set minLeft[0] = prices[0] = 7: at index 0 the only price seen is 7. | `n = 6`<br>`prices = [7, 1, 5, 3, 6, 4]`<br>`minLeft = [7, -, -, -, -, -]` |
| 2 | 6 | i = 1: minLeft[1] = min(minLeft[0] 7, prices[1] 1) = 1; index 1 is the new cheapest day. | `i = 1`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1)<br>`minLeft = [7, 1, -, -, -, -]` (i→1) |
| 3 | 6 | i = 2: minLeft[2] = min(1, 5) = 1; 5 is not cheaper, so the minimum stays 1. | `i = 2`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→2)<br>`minLeft = [7, 1, 1, -, -, -]` (i→2) |
| 4 | 6 | i = 3..5 (skipped to the last one): prices 3, 6 and 4 are all above 1, so minLeft[3], minLeft[4] and minLeft[5] all stay 1. minLeft = [7, 1, 1, 1, 1, 1]. | `i = 5`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→5)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→5) |
| 5 | 7 | minLeft is complete. Start best at 0, the profit of not trading. | `best = 0`<br>`prices = [7, 1, 5, 3, 6, 4]`<br>`minLeft = [7, 1, 1, 1, 1, 1]` |
| 6 | 9 | i = 1: profit = prices[1] - minLeft[0] = 1 - 7 = -6; selling at index 1 loses money, best stays 0. | `i = 1`<br>`profit = -6`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→1) |
| 7 | 11 | i = 2: profit = prices[2] - minLeft[1] = 5 - 1 = 4 > previous best, so best = 4. | `best = 4`<br>`i = 2`<br>`profit = 4`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→2)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→2) |
| 8 | 9 | i = 3: profit = prices[3] - minLeft[2] = 3 - 1 = 2, not > 4; best stays 4. | `i = 3`<br>`profit = 2`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→3)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→3) |
| 9 | 11 | i = 4: profit = prices[4] - minLeft[3] = 6 - 1 = 5 > previous best, so best = 5. | `best = 5`<br>`i = 4`<br>`profit = 5`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→4)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→4) |
| 10 | 9 | i = 5: profit = prices[5] - minLeft[4] = 4 - 1 = 3, not > 5; best stays 5. | `i = 5`<br>`profit = 3`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→5)<br>`minLeft = [7, 1, 1, 1, 1, 1]` (i→5) |
| 11 | 12 | Every sell day was paired with its cheapest earlier day; return best = 5. | `prices = [7, 1, 5, 3, 6, 4]`<br>`minLeft = [7, 1, 1, 1, 1, 1]` |

**Result:** 5 — minLeft = [7,1,1,1,1,1], and the best sell day is index 4: prices[4] - minLeft[3] = 6 - 1 = 5.

**C++ solution**

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // minLeft[i] = cheapest price on days 0..i
        vector<int> minLeft(n);
        minLeft[0] = prices[0];                  // day 0 is the only price seen so far
        for (int i = 1; i < n; i++) {
            minLeft[i] = min(minLeft[i - 1], prices[i]);  // extend the prefix by day i
        }
        int best = 0;                            // doing nothing earns 0
        for (int i = 1; i < n; i++) {
            // sell on day i, buying at the cheapest strictly earlier day
            int profit = prices[i] - minLeft[i - 1];
            if (profit > best) {
                best = profit;
            }
        }
        return best;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // minLeft[i] = cheapest price on days 0..i
        vector<int> minLeft(n);
        minLeft[0] = prices[0];                  // day 0 is the only price seen so far
        for (int i = 1; i < n; i++) {
            minLeft[i] = min(minLeft[i - 1], prices[i]);  // extend the prefix by day i
        }
        int best = 0;                            // doing nothing earns 0
        for (int i = 1; i < n; i++) {
            // sell on day i, buying at the cheapest strictly earlier day
            int profit = prices[i] - minLeft[i - 1];
            if (profit > best) {
                best = profit;
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
```

</details>

**Why move on:** It meets the time limit, but it stores `n` prefix minimums even though each `minLeft[i - 1]` is read exactly once, right when day `i` is processed.

### 3. Optimal: One pass with a running minimum

> **How you get here:** Since `minLeft[i - 1]` is only needed at day `i`, we can keep just the latest prefix minimum in one variable `minPrice` and fold both passes into one.

**Idea.** Scan the days left to right, holding `minPrice` (the cheapest price on the days before `i`) and `best` (the best profit so far). On day `i`, first try selling: `profit = prices[i] - minPrice`, and raise `best` if it is larger. Then let day `i` become a buy candidate by lowering `minPrice` if `prices[i]` is cheaper. The invariant is that when day `i` is examined, `minPrice = min(prices[0..i-1])`, so every sell day is paired with its best buy day, exactly as in the prefix-array version.

**Steps**

1. Set `minPrice` to `prices[0]` and `best` to 0.
2. For each day `i` from 1 to `n - 1`, compute `profit = prices[i] - minPrice`.
3. If `profit` is larger than `best`, store it in `best`.
4. If `prices[i]` is smaller than `minPrice`, store it in `minPrice`.
5. Return `best`.

**Pseudocode**

```text
 1 │ function maxProfit(prices)
 2 │   n ← length(prices)
 3 │   minPrice ← prices[0]  // cheapest buy price seen so far
 4 │   best ← 0  // not trading is allowed, so the answer is never negative
 5 │   for i ← 1 to n - 1
 6 │     profit ← prices[i] - minPrice  // best profit if we sell on day i
 7 │     if profit > best
 8 │       best ← profit
 9 │     if prices[i] < minPrice
10 │       minPrice ← prices[i]  // later sell days can buy at this cheaper price
11 │   return best
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Initialisation (lines 2-4) | O(1) | Three assignments. |
| Single loop (lines 5-10) | n − 1 iterations × O(1) | Each day does one subtraction and at most two comparisons and two assignments. |

- **Adding it up:** O(1) + (n − 1)·O(1) = O(n).
- **At the maximum input:** n = 10^5 → 10^5 iterations, well under a millisecond.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| Scalars n, minPrice, best, i, profit (lines 2-6) | O(1) | No array is built; the prefix minimum lives in one variable. |

- **Adding it up:** O(1).
- **Not counted:** The input prices is only read and the output is a single integer.

**Dry run** on `prices = [7,1,5,3,6,4]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | Day 0 is the only day seen, so minPrice = prices[0] = 7 and best = 0. | `n = 6`<br>`minPrice = 7`<br>`best = 0`<br>`prices = [7, 1, 5, 3, 6, 4]` |
| 2 | 6 | i = 1: profit = prices[1] - minPrice = 1 - 7 = -6; selling at index 1 would lose money, so best stays 0. | `i = 1`<br>`profit = -6`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→1) |
| 3 | 10 | prices[1] = 1 is below the old minPrice 7, so minPrice = 1: every later day can now buy at 1. | `minPrice = 1` |
| 4 | 6 | i = 2: profit = prices[2] - minPrice = 5 - 1 = 4, which is greater than best = 0. | `i = 2`<br>`profit = 4`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→2) |
| 5 | 8 | So best = 4: selling at 5 (index 2) after buying at 1 is the best trade so far; 5 is not a new minimum, so minPrice will stay 1. | `best = 4` |
| 6 | 6 | i = 3: profit = 3 - 1 = 2, not > 4. Price 3 is not below minPrice 1, so nothing else changes. | `i = 3`<br>`profit = 2`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→3) |
| 7 | 6 | i = 4: profit = prices[4] - minPrice = 6 - 1 = 5, which is greater than best = 4. | `i = 4`<br>`profit = 5`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→4) |
| 8 | 8 | So best = 5: selling at 6 (index 4) after buying at 1 is the best trade so far; 6 is not a new minimum, so minPrice will stay 1. | `best = 5` |
| 9 | 6 | i = 5: profit = 4 - 1 = 3, not > 5, and 4 is not a new minimum. The loop ends. | `i = 5`<br>`profit = 3`<br>`prices = [7, 1, 5, 3, 6, 4]` (i→5) |
| 10 | 11 | Return best = 5. | `prices = [7, 1, 5, 3, 6, 4]` |

**Result:** 5 — minPrice became 1 at index 1, and selling at 6 at index 4 gave the largest profit 6 - 1 = 5; no later day did better.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Every price must be read at least once, since any unread day could be a new minimum or a better sale, so `O(n)` time is optimal, and `O(1)` space cannot be improved.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| prices = [3,8,2,9,1,4] | 7 | The global minimum 1 comes late; the best pair is 2 then 9. |
| prices = [2,4,1] | 2 | The minimum is on the last day, so max(prices) - min(prices) = 3 would be wrong. |
| prices = [5,11,3,50,60,90] | 87 | A new minimum 3 appears after an early small gain and leads to the best sale at 90. |
| prices = [10,7,5,8,11,9] | 6 | Prices fall first, then rise: buy at the bottom 5 and sell at the peak 11. |
| prices = [4,7,2,6,3,8,1,5] | 6 | Several dips and peaks; buy at 2 and sell at 8 beats every adjacent swing. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single day | prices = [5] | 0 | There is no later day to sell, so the answer is 0. |
| Strictly decreasing | prices = [9,7,4,1] | 0 | Every trade loses money, so not trading gives 0. |
| All equal | prices = [3,3,3,3] | 0 | Every profit is 0, so the answer is 0. |
| Two days, increasing | prices = [1,2] | 1 | The only possible trade earns 1. |
| Value bounds | prices = [0,10000] | 10000 | Buy at the minimum price 0 and sell at the maximum 10^4. |
| Strictly increasing | prices = [1,2,3,4,5] | 4 | Buy on the first day and sell on the last; at n = 10^5 this still needs an O(n) pass. |

## Mistakes and edge cases

**Common mistakes**

- Returning `max(prices) - min(prices)` while ignoring the order of days: `[2,4,1]` gives 3, but the minimum comes after the maximum, so the real answer is 2.
- Starting `best` at `INT_MIN` or at `prices[1] - prices[0]`: for falling prices such as Example 2 this returns a negative number instead of 0.
- Resetting `best` when a new minimum price appears: in `[3,8,1,2]` the profit 5 from buying at 3 must survive even after `minPrice` drops to 1.
- Summing every positive day-to-day rise, which solves the unlimited-transactions version: `[1,2,3,1,5]` would give 6, but with one transaction the answer is 4.

**Edge cases to check**

- `prices = [5]`: the loop never runs, so the answer is 0; reading `prices[0]` is safe because `prices.length >= 1`.
- Strictly decreasing prices like `[9,7,4,1]`: every profit is negative, so `best` must stay at its starting value 0.
- All equal prices like `[3,3,3,3]`: every profit is exactly 0, and since `0 > 0` is false, `best` stays 0.
- A new minimum after the best pair, like `[3,8,1,2]`: `minPrice` drops to 1 but the answer is still 5, which catches solutions that reset `best`.

## Practice next

- [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/) · Same price array with unlimited transactions, which turns the answer into the sum of every positive day-to-day rise.
- [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/) · At most two transactions, solved by extending this running-state idea into a small DP over buy/sell states.
- [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) · Kadane's algorithm keeps a running best in one pass; this problem is the maximum subarray sum of the day-to-day price differences.
- [Maximum Difference Between Increasing Elements](https://leetcode.com/problems/maximum-difference-between-increasing-elements/) · Almost the same task, `max nums[j] - nums[i]` with `i < j` and `nums[i] < nums[j]`, solved with the same running minimum.

## Takeaways

- For "best pair with `i < j`" problems, fix the right end `j` and ask what the best left partner is; that turns an `O(n^2)` pair search into a prefix query.
- A prefix array that is only read at the current index can be collapsed into one running variable, cutting space from `O(n)` to `O(1)`.
- Initialise the answer to the value of "doing nothing" (here 0) when the problem allows not acting.
- Order of updates inside a one-pass loop matters: use the state of the earlier days before letting the current day update it.
