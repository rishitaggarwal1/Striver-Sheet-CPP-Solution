# House Robber

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/house-robber/) · Pattern: **1D DP on prefixes (pick / skip)**

> Choose houses with no two next to each other so that the sum of `nums` over the chosen houses is as large as possible.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 2:

Input: nums = [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
Total amount you can rob = 2 + 9 + 1 = 12.

Constraints:

- 1 <= nums.length <= 100

- 0 <= nums[i] <= 400
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You choose some houses along a line so that no two chosen houses are next to each other, and you want the largest possible total of the money in the chosen houses.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In Example 2, `[2,7,9,3,1]`, the best plan robs houses 0, 2 and 4 for 12, but the best plan does not always alternate: in `[2,1,1,2]` you should rob the first and last houses for 4, leaving two houses in a row untouched.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `nums.length` up to 100 there are up to `2^100` subsets of houses, so trying them all is impossible, while anything `O(n)` or even `O(n^2)` is instant. Totals never exceed `50 × 400 = 20000`, so `int` is enough.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is one-dimensional DP on prefixes, the pick / not-pick pattern: the best answer for the first `i + 1` houses can be built from the best answers for shorter prefixes, because a choice at house `i` only affects its neighbour.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Look at the last house `i` of a prefix: either you rob it, so house `i − 1` is off-limits and you add `nums[i]` to the best for houses `0..i − 2`, or you skip it and take the best for houses `0..i − 1`. The answer is the larger of those two.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Let `dp[i]` be the most money from houses `0..i`, whether or not house `i` itself is robbed. Since `dp[i]` reads only `dp[i − 1]` and `dp[i − 2]`, keep just `prev1` (best through house `i − 1`) and `prev2` (best through house `i − 2`).

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `prev2` to 0 (nothing before house 0) and `prev1` to `nums[0]`.
For each house `i` from 1 to the last:
The pick option is `nums[i] + prev2`.
The skip option is `prev1`.
Let `curr` be the larger of the two.
Move `prev1` into `prev2`, then `curr` into `prev1`.
At the end, `prev1` is the answer.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is the base case: with one house the loop never runs and the answer is `nums[0]`, so never read `nums[1]` unconditionally; also slide `prev1` into `prev2` before overwriting `prev1`. Zeros and equal values need no special handling. Time is `O(n)` and extra space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "adjacent houses ... will automatically contact the police" | robbing house `i` only rules out houses `i − 1` and `i + 1`, so each decision depends on just the neighbour, a pick / skip choice per house. |
| "return the maximum amount of money" | we optimise over exponentially many valid subsets, which points to DP over prefixes rather than enumeration. |
| Example 2 picks houses 0, 2 and 4, but `[2,1,1,2]` is best with houses 0 and 3 | the answer is not simply "even indices or odd indices", so a real recurrence is needed. |
| "1 <= nums.length <= 100" and "0 <= nums[i] <= 400" | `O(n)` is trivial, and the total is at most 20000, so `int` cannot overflow. |

### What the constraints tell you

`nums.length ≤ 100`: checking every subset is `2^100 ≈ 1.3·10^30` and the pick / skip recursion still makes about `1.1·10^21` calls, both hopeless, while an `O(n)` DP needs about 100 steps. The largest possible total is `50 · 400 = 20000`, so `int` is safe; the target is `O(n)` time, ideally with `O(1)` space.

### Think it through

Answer each question yourself before opening it.

**Q1. Why not just compare the sum of even-indexed houses with the sum of odd-indexed houses?**

<details>
<summary>Answer</summary>

Because the best plan can leave two houses in a row: for `[2,1,1,2]` both alternations give 3, but robbing houses 0 and 3 gives 4.

</details>

**Q2. Would greedily robbing the richest remaining house work?**

<details>
<summary>Answer</summary>

No. In `[2,3,2]` the richest house is 3, which blocks both 2s, but robbing the two 2s gives 4. A single local choice can block a better combination.

</details>

**Q3. What decision can I make about the last house `n − 1` without knowing the rest?**

<details>
<summary>Answer</summary>

Either it is robbed, in which case house `n − 2` is not and the rest is the best plan for `0..n − 3`, or it is not robbed and the rest is the best plan for `0..n − 2`.

</details>

**Q4. So what recurrence describes the best loot for a prefix?**

<details>
<summary>Answer</summary>

`best(i) = max(nums[i] + best(i − 2), best(i − 1))`, with `best(0) = nums[0]` and `best(i) = 0` for `i < 0`. For Example 1 this gives 1, 2, 4, 4.

</details>

**Q5. Why is that recursion slow, and how do I fix it?**

<details>
<summary>Answer</summary>

`best(i − 2)` is reached both directly and through `best(i − 1)`, so the call tree grows like Fibonacci, about `10^21` calls for 100 houses. There are only `n` distinct arguments, so store them in a `dp` array filled from left to right.

</details>

**Q6. Do I need the whole `dp` array?**

<details>
<summary>Answer</summary>

No. `dp[i]` reads only `dp[i − 1]` and `dp[i − 2]`, so two variables `prev1` and `prev2` are enough, giving `O(n)` time and `O(1)` space.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Pick / skip recursion](#1-brute-force-pick--skip-recursion) | `O(2^n)` | `O(n)` |
| 2 | [Better: Bottom-up DP table](#2-better-bottom-up-dp-table) | `O(n)` | `O(n)` |
| 3 | [Optimal: Two rolling variables](#3-optimal-two-rolling-variables) | `O(n)` | `O(1)` |

### 1. Brute force: Pick / skip recursion

> **Where you start:** Each house is a yes/no decision that only conflicts with its neighbours, so the first idea is to try both choices for the last house and recurse on whatever houses remain.

**Idea.** Let `best(i)` be the most money obtainable from houses `0..i`. For house `i` there are two options: rob it, earning `nums[i]` but making house `i − 1` off-limits, so add `best(i − 2)`; or skip it and take `best(i − 1)`. So `best(i) = max(nums[i] + best(i − 2), best(i − 1))`, with `best(0) = nums[0]` (amounts are never negative, so robbing the only house never hurts) and `best(i) = 0` for `i < 0`. It is correct because every valid plan either robs house `i` or does not, and in both cases the rest of the plan is a valid plan on a shorter prefix.

**Steps**

1. Define `best(i)` as the most money from houses `0..i`; the answer is `best(n − 1)`.
2. If `i < 0`, there are no houses, so return 0; if `i = 0`, return `nums[0]`.
3. Pick option: rob house `i`, giving `nums[i] + best(i − 2)` because house `i − 1` is now off-limits.
4. Skip option: leave house `i`, giving `best(i − 1)`.
5. Return the larger of the pick and skip options.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   return best(n − 1, nums)  // best loot from houses 0..n − 1
 4 │ function best(i, nums)
 5 │   if i < 0
 6 │     return 0  // no houses left: nothing to rob
 7 │   if i = 0
 8 │     return nums[0]  // only house 0 left; amounts are never negative, so rob it
 9 │   pick ← nums[i] + best(i − 2, nums)  // rob house i, so house i − 1 is off-limits
10 │   skip ← best(i − 1, nums)  // leave house i, house i − 1 is free to decide
11 │   return max(pick, skip)
```

**Time complexity: `O(2^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Base cases (lines 5-8) | O(1) per call | A comparison and a return; every leaf of the call tree ends here. |
| Two recursive calls (lines 9-10) | calls(i) = 1 + calls(i − 2) + calls(i − 1) calls in total | Each non-base call branches into the pick and skip subproblems, and nothing is cached. |
| Comparison (line 11) | O(1) per call | One max per non-base call. |

- **Adding it up:** With calls(−2) = calls(−1) = calls(0) = 1, the recurrence gives calls(1) = 3, calls(2) = 5, calls(3) = 9, growing by a factor of about φ ≈ 1.618 per house, so the total is Θ(φ^n) × O(1) ⊆ O(2^n).
- **At the maximum input:** n = 100 → about 1.1·10^21 calls; even at 10^9 calls per second that is over 30,000 years.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 9-10) | at most n frames × O(1) | The skip chain best(n − 1) → best(n − 2) → … → best(0) is the deepest path, and each frame holds only i, pick and skip. |

- **Adding it up:** The stack is the only thing that grows: O(n).
- **Not counted:** nums is passed by reference and not copied, so it is not counted; 100 frames at most is no risk of stack overflow.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4 houses with nums = [1, 2, 3, 1]. Nothing is on the call stack yet. | `n = 4`<br>`nums = [1, 2, 3, 1]`<br>`call stack = []` |
| 2 | 4 | rob calls best(3). best(3) is not a base case, so line 9 tries robbing house 3 (money 1), which needs best(1), the best loot from houses 0..1. | `i = 1`<br>`nums = [1, 2, 3, 1]` (i→1)<br>`call stack = [best(3), best(1)] ← top` |
| 3 | 6 | best(1) tries robbing house 1, which needs best(-1); no houses are left, so line 6 returns 0. | `i = -1`<br>`nums = [1, 2, 3, 1]`<br>`call stack = [best(3), best(1), best(-1)] ← top` |
| 4 | 9 | pick = nums[1] + best(-1) = 2 + 0 = 2: rob house 1 alone, since no house lies before house 0. | `i = 1`<br>`pick = 2`<br>`nums = [1, 2, 3, 1]` (i→1)<br>`call stack = [best(3), best(1): pick=2] ← top` |
| 5 | 8 | best(1) now tries skipping house 1 and calls best(0); with only house 0 left, line 8 returns nums[0] = 1. | `i = 0`<br>`nums = [1, 2, 3, 1]` (i→0)<br>`call stack = [best(3), best(1): pick=2, best(0)] ← top` |
| 6 | 11 | skip = best(0) = 1, so best(1) returns max(pick, skip) = max(2, 1) = 2: robbing house 1 is better. | `i = 1`<br>`pick = 2`<br>`skip = 1`<br>`nums = [1, 2, 3, 1]` (i→1)<br>`call stack = [best(3), best(1): pick=2, skip=1] ← top` |
| 7 | 9 | Back in best(3): pick = nums[3] + best(1) = 1 + 2 = 3. | `i = 3`<br>`pick = 3`<br>`nums = [1, 2, 3, 1]` (i→3)<br>`call stack = [best(3): pick=3] ← top` |
| 8 | 4 | best(3) now tries skipping house 3, so line 10 calls best(2), the best loot from houses 0..2. | `i = 2`<br>`nums = [1, 2, 3, 1]` (i→2)<br>`call stack = [best(3): pick=3, best(2)] ← top` |
| 9 | 8 | best(2) tries robbing house 2, which needs best(0); line 8 returns nums[0] = 1 (already computed once before, but plain recursion does not remember it). | `i = 0`<br>`nums = [1, 2, 3, 1]` (i→0)<br>`call stack = [best(3): pick=3, best(2), best(0)] ← top` |
| 10 | 9 | pick = nums[2] + best(0) = 3 + 1 = 4: rob house 2 plus the best loot from house 0. | `i = 2`<br>`pick = 4`<br>`nums = [1, 2, 3, 1]` (i→2)<br>`call stack = [best(3): pick=3, best(2): pick=4] ← top` |
| 11 | 11 | skip = best(1) = 2, but best(1) was already solved earlier: line 10 re-explores its whole subtree from scratch. best(2) returns max(4, 2) = 4. | `skip = 2`<br>`call stack = [best(3): pick=3, best(2): pick=4, skip=2] ← top` |
| 12 | 11 | skip = best(2) = 4, so best(3) returns max(pick, skip) = max(3, 4) = 4: leaving house 3 is better. | `i = 3`<br>`pick = 3`<br>`skip = 4`<br>`nums = [1, 2, 3, 1]` (i→3)<br>`call stack = [best(3): pick=3, skip=4] ← top` |
| 13 | 3 | rob returns best(3) = 4 after 9 calls, robbing houses 0 and 2 (1 + 3). | `n = 4`<br>`nums = [1, 2, 3, 1]`<br>`call stack = []` |

**Result:** 4: rob house 0 (1) and house 2 (3); the alternative that robs house 3 reaches only 1 + 2 = 3.

**C++ solution**

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        return best(n - 1, nums); // best loot from houses 0..n-1
    }

private:
    // best(i) = most money from houses 0..i without robbing two adjacent houses
    int best(int i, vector<int>& nums) {
        if (i < 0) return 0;                      // no houses left: nothing to rob
        if (i == 0) return nums[0];               // only house 0 left; amounts are >= 0, so rob it
        int pick = nums[i] + best(i - 2, nums);   // rob house i, so house i - 1 is off-limits
        int skip = best(i - 1, nums);             // leave house i, house i - 1 is free to decide
        return max(pick, skip);                   // keep the better of the two plans
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
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        return best(n - 1, nums); // best loot from houses 0..n-1
    }

private:
    // best(i) = most money from houses 0..i without robbing two adjacent houses
    int best(int i, vector<int>& nums) {
        if (i < 0) return 0;                      // no houses left: nothing to rob
        if (i == 0) return nums[0];               // only house 0 left; amounts are >= 0, so rob it
        int pick = nums[i] + best(i - 2, nums);   // rob house i, so house i - 1 is off-limits
        int skip = best(i - 1, nums);             // leave house i, house i - 1 is free to decide
        return max(pick, skip);                   // keep the better of the two plans
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
```

</details>

**Why move on:** The bottleneck is recomputation: even for `[1,2,3,1]` the subproblem `best(1)` is solved twice, and the waste grows exponentially, so 100 houses can never finish although there are only 100 distinct subproblems.

### 2. Better: Bottom-up DP table

> **How you get here:** The recursion's answer depends only on `i`, and `best(i)` only ever asks for `best(i − 1)` and `best(i − 2)`; so there are just `n` distinct subproblems, and solving them from left to right means each one finds its inputs already computed.

**Idea.** Create `dp` of length `n` where `dp[i]` is the most money from houses `0..i`. Set `dp[0] = nums[0]`, then for `i = 1..n − 1` compute `pick = nums[i] + dp[i − 2]` (treating `dp[−1]` as 0, which is why line 7 checks `i ≥ 2`) and `skip = dp[i − 1]`, and store `dp[i] = max(pick, skip)`. Filling left to right guarantees both inputs are final when `dp[i]` is computed, and the answer is `dp[n − 1]`. Top-down memoisation of the recursion gives the same `O(n)` time but adds a recursion stack; the table avoids it.

**Steps**

1. Create `dp` of length `n`; `dp[i]` will hold the most money from houses `0..i`.
2. Set `dp[0] = nums[0]`.
3. For each `i` from 1 to `n − 1`, start `pick` at `nums[i]` and add `dp[i − 2]` when `i ≥ 2`.
4. Set `skip = dp[i − 1]`.
5. Store `dp[i] = max(pick, skip)`.
6. Return `dp[n − 1]`.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   dp ← array of n zeros  // dp[i] = most money from houses 0..i
 4 │   dp[0] ← nums[0]  // a single house: rob it
 5 │   for i ← 1 to n − 1
 6 │     pick ← nums[i]  // rob house i ...
 7 │     if i ≥ 2
 8 │       pick ← pick + dp[i − 2]  // ... plus the best loot that ends before house i − 1
 9 │     skip ← dp[i − 1]  // leave house i: best loot through house i − 1
10 │     dp[i] ← max(pick, skip)
11 │   return dp[n − 1]
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table allocation and base case (lines 2-4) | n cells × O(1) | dp is zero-filled once and dp[0] is set. |
| Main loop (lines 5-10) | n − 1 iterations × O(1) | Each house does one optional addition, two reads and one max. |
| Return (line 11) | O(1) | A single read of dp[n − 1]. |

- **Adding it up:** O(n) + (n − 1) · O(1) + O(1) = O(n).
- **At the maximum input:** n = 100 → 99 loop iterations, a fraction of a microsecond.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp array (line 3) | n ints | One cell per prefix 0..i. |
| Loop variables (lines 5-9) | O(1) | i, pick and skip. |

- **Adding it up:** O(n) + O(1) = O(n); the table dominates.
- **Not counted:** The input nums is not counted; there is no recursion.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4 houses. | `n = 4`<br>`nums = [1, 2, 3, 1]` |
| 2 | 3 | dp has 4 cells, all 0; dp[i] will hold the most money from houses 0..i. | `dp = [0, 0, 0, 0]` |
| 3 | 4 | dp[0] = nums[0] = 1: with only house 0, rob it. | `dp = [1, 0, 0, 0]` |
| 4 | 6 | i = 1: pick = nums[1] = 2, the money from robbing house 1. | `i = 1`<br>`pick = 2`<br>`nums = [1, 2, 3, 1]` (i→1)<br>`dp = [1, 0, 0, 0]` (i→1) |
| 5 | 9 | i = 1 < 2, so line 8 is skipped (there is no house -1). skip = dp[0] = 1, the best loot if house 1 is left alone. | `skip = 1` |
| 6 | 10 | dp[1] = max(pick, skip) = max(2, 1) = 2, so for houses 0..1 the better choice at house 1 is to rob it. | `dp = [1, 2, 0, 0]` (i→1) |
| 7 | 8 | i = 2: pick starts at nums[2] = 3 (line 6), and since i ≥ 2 line 8 adds dp[0] = 1, so pick = 4. | `i = 2`<br>`pick = 4`<br>`nums = [1, 2, 3, 1]` (i→2)<br>`dp = [1, 2, 0, 0]` (i→2) |
| 8 | 9 | skip = dp[1] = 2, the best loot if house 2 is left alone. | `skip = 2` |
| 9 | 10 | dp[2] = max(pick, skip) = max(4, 2) = 4, so for houses 0..2 the better choice at house 2 is to rob it. | `dp = [1, 2, 4, 0]` (i→2) |
| 10 | 8 | i = 3: pick starts at nums[3] = 1 (line 6), and since i ≥ 2 line 8 adds dp[1] = 2, so pick = 3. | `i = 3`<br>`pick = 3`<br>`nums = [1, 2, 3, 1]` (i→3)<br>`dp = [1, 2, 4, 0]` (i→3) |
| 11 | 9 | skip = dp[2] = 4, the best loot if house 3 is left alone. | `skip = 4` |
| 12 | 10 | dp[3] = max(pick, skip) = max(3, 4) = 4, so for houses 0..3 the better choice at house 3 is to skip it. | `dp = [1, 2, 4, 4]` (i→3) |
| 13 | 11 | The table is complete; rob returns dp[3] = 4. | `nums = [1, 2, 3, 1]`<br>`dp = [1, 2, 4, 4]` |

**Result:** 4: dp = [1, 2, 4, 4], and dp[3] = 4 comes from skipping house 3 and keeping the plan 1 + 3 through house 2.

**C++ solution**

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n, 0); // dp[i] = most money from houses 0..i
        dp[0] = nums[0];      // a single house: rob it
        for (int i = 1; i < n; ++i) {
            int pick = nums[i];            // rob house i ...
            if (i >= 2) pick += dp[i - 2]; // ... plus the best loot that ends before house i - 1
            int skip = dp[i - 1];          // leave house i: keep the best loot through house i - 1
            dp[i] = max(pick, skip);       // both inputs are final because we fill left to right
        }
        return dp[n - 1]; // best loot over all houses
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
    int rob(vector<int>& nums) {
        int n = (int)nums.size();
        vector<int> dp(n, 0); // dp[i] = most money from houses 0..i
        dp[0] = nums[0];      // a single house: rob it
        for (int i = 1; i < n; ++i) {
            int pick = nums[i];            // rob house i ...
            if (i >= 2) pick += dp[i - 2]; // ... plus the best loot that ends before house i - 1
            int skip = dp[i - 1];          // leave house i: keep the best loot through house i - 1
            dp[i] = max(pick, skip);       // both inputs are final because we fill left to right
        }
        return dp[n - 1]; // best loot over all houses
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
```

</details>

**Why move on:** It easily meets `n ≤ 100`, but it stores all `n` values of `dp` while each step reads only the last two, so the `O(n)` space is more than the recurrence needs.

### 3. Optimal: Two rolling variables

> **How you get here:** In the table, computing `dp[i]` reads only `dp[i − 1]` and `dp[i − 2]`, and older cells are never read again; so two variables can replace the whole array.

**Idea.** Keep `prev1` = best through house `i − 1` and `prev2` = best through house `i − 2`, starting with `prev1 = nums[0]` and `prev2 = 0` (nothing before house 0). For each `i` from 1, `curr = max(nums[i] + prev2, prev1)`; then shift `prev2 ← prev1` and `prev1 ← curr`. The invariant "before iteration `i`, `prev1 = dp[i − 1]` and `prev2 = dp[i − 2]`" is exactly the table's recurrence, so after the last house `prev1 = dp[n − 1]`. A single house needs no special case: the loop does not run and `prev1 = nums[0]` is returned.

**Steps**

1. Set `prev2 = 0` (best before house 0) and `prev1 = nums[0]` (best through house 0).
2. For each house `i` from 1 to `n − 1`, compute `pick = nums[i] + prev2` and `skip = prev1`.
3. Let `curr` be the larger of `pick` and `skip`.
4. Shift the window: `prev2` takes `prev1`, then `prev1` takes `curr`.
5. After the last house, return `prev1`.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   prev2 ← 0  // best loot through house i − 2 (nothing before house 0)
 4 │   prev1 ← nums[0]  // best loot through house i − 1; starts as house 0 alone
 5 │   for i ← 1 to n − 1
 6 │     pick ← nums[i] + prev2  // rob house i on top of the best plan that skips i − 1
 7 │     skip ← prev1  // leave house i
 8 │     curr ← max(pick, skip)  // best loot through house i
 9 │     prev2 ← prev1  // slide the window before prev1 is overwritten
10 │     prev1 ← curr
11 │   return prev1  // best loot through house n − 1
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Initialisation (lines 2-4) | O(1) | Three assignments. |
| Main loop (lines 5-10) | n − 1 iterations × O(1) | Each house does one addition, one max and two copies. |

- **Adding it up:** O(1) + (n − 1) · O(1) = O(n); the loop dominates.
- **At the maximum input:** n = 100 → 99 iterations, effectively instant.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| prev2, prev1, pick, skip, curr, i (lines 3-8) | 6 ints | Only the two most recent prefix answers and the current house's options are kept. |

- **Adding it up:** A constant number of ints: O(1).
- **Not counted:** The input nums is read but not copied, and the answer is a single int.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4 houses. | `n = 4`<br>`nums = [1, 2, 3, 1]` |
| 2 | 3 | prev2 = 0: before house 0 there is nothing to rob. | `prev2 = 0` |
| 3 | 4 | prev1 = nums[0] = 1: the best loot through house 0 is to rob it. | `prev1 = 1` |
| 4 | 6 | i = 1: pick = nums[1] + prev2 = 2 + 0 = 2, robbing house 1 alone (prev2 = 0 because no house lies before house 0). | `i = 1`<br>`pick = 2`<br>`nums = [1, 2, 3, 1]` (i→1) |
| 5 | 8 | skip = prev1 = 1 (line 7), so curr = max(2, 1) = 2, the best loot through house 1. | `skip = 1`<br>`curr = 2` |
| 6 | 10 | Lines 9-10 slide the window one house right: prev2 = 1 (best through house 0), prev1 = 2 (best through house 1). | `prev2 = 1`<br>`prev1 = 2` |
| 7 | 6 | i = 2: pick = nums[2] + prev2 = 3 + 1 = 4, robbing house 2 on top of the best plan through house 0. | `i = 2`<br>`pick = 4`<br>`nums = [1, 2, 3, 1]` (i→2) |
| 8 | 8 | skip = prev1 = 2 (line 7), so curr = max(4, 2) = 4, the best loot through house 2. | `skip = 2`<br>`curr = 4` |
| 9 | 10 | Lines 9-10 slide the window one house right: prev2 = 2 (best through house 1), prev1 = 4 (best through house 2). | `prev2 = 2`<br>`prev1 = 4` |
| 10 | 6 | i = 3: pick = nums[3] + prev2 = 1 + 2 = 3, robbing house 3 on top of the best plan through house 1. | `i = 3`<br>`pick = 3`<br>`nums = [1, 2, 3, 1]` (i→3) |
| 11 | 8 | skip = prev1 = 4 (line 7), so curr = max(3, 4) = 4, the best loot through house 3. | `skip = 4`<br>`curr = 4` |
| 12 | 10 | Lines 9-10 slide the window one house right: prev2 = 4 (best through house 2), prev1 = 4 (best through house 3). | `prev2 = 4` |
| 13 | 11 | All houses are processed, so rob returns prev1 = 4, the best loot through house 3. | `nums = [1, 2, 3, 1]` |

**Result:** 4: the window passes through the same values as the table (1, 2, 4, 4) but never holds more than two of them.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Every house must be read at least once, so `O(n)` time is a lower bound, and `O(1)` extra space cannot be improved. What it gives up is the full `dp` table, which you would need to reconstruct which houses were robbed.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [2,1,1,2] | 4 | Rob the first and last houses (2 + 2); both pure alternations give only 3. |
| nums = [5,3,4,11,2] | 16 | Rob 5 and 11, skipping two houses in between; greedy alternation from either end does worse. |
| nums = [6,7,1,30,8,2,4] | 41 | Rob 7, 30 and 4; starting with the smaller first house loses to starting at house 1. |
| nums = [4,1,2,7,5,3,1] | 14 | Rob 4, 7 and 3; checks that a big middle value (7) forces skipping its neighbours 2 and 5. |
| nums = [1,3,1,3,100] | 103 | A huge last house: the best plan must end with 100 and pick 3 from the front. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single house | nums = [5] | 5 | The loop never runs and the answer is nums[0]; code must not read nums[1]. |
| Two houses | nums = [3,8] | 8 | They are adjacent, so only the larger one can be robbed. |
| All zeros | nums = [0,0,0,0] | 0 | The minimum value everywhere, so the best loot is 0. |
| All equal at the maximum value | nums = [400,400,400,400,400] | 1200 | Rob houses 0, 2 and 4; at 100 such houses the answer is 20000, still within int. |
| Strictly increasing, even length | nums = [1,2,3,4,5,6] | 12 | Rob the odd indices 2 + 4 + 6, ending at the last house. |
| Zeros between two big houses | nums = [400,0,0,400] | 800 | Skipping two houses in a row gives 800. |

## Mistakes and edge cases

**Common mistakes**

- Comparing only the even-index sum with the odd-index sum, which fails on `[2,1,1,2]` (returns 3 instead of 4).
- Greedily robbing the richest available house first, which fails on `[2,3,2]` (returns 3 instead of 4).
- Setting `dp[1] = max(nums[0], nums[1])` without checking the length, which reads past the end of `nums` when there is only one house.
- Defining `dp[i]` as "best loot when house `i` is robbed" and returning `dp[n − 1]`, which misses every plan that leaves the last house alone (for `[1,2,3,1]` it returns 3 instead of 4).

**Edge cases to check**

- A single house such as `[5]`: the answer is `nums[0]`, and any code that touches `nums[1]` or `dp[1]` goes out of bounds.
- Two houses such as `[3,8]`: they are adjacent, so the answer is the larger one, 8, not the sum.
- All zeros such as `[0,0,0,0]`: the answer is 0, which checks the base cases do not invent money.
- Plans that skip two houses in a row, such as `[2,1,1,2]` → 4, which break alternation-based shortcuts.
- 100 houses of 400 each: the answer 20000 is the largest possible and still fits easily in `int`.

## Practice next

- [House Robber II](https://leetcode.com/problems/house-robber-ii/) · The same street bent into a circle: run this exact DP twice, once without the first house and once without the last.
- [Delete and Earn](https://leetcode.com/problems/delete-and-earn/) · After summing points per value, taking value `v` forbids `v − 1` and `v + 1`, which is House Robber over the value line.
- [House Robber III](https://leetcode.com/problems/house-robber-iii/) · The same pick / skip choice, but the houses form a binary tree, so each node returns a (robbed, not robbed) pair.
- [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/) · The same `dp[i]` from `dp[i − 1]` and `dp[i − 2]` shape, with a sum instead of a max, and the same two-variable optimisation.

## Takeaways

- For "choose a subset with no two adjacent" problems, decide pick or skip for the last element and recurse on the prefix that remains.
- Define the DP state as "best answer using a prefix" rather than "best answer that uses element `i`", so the final answer is simply the last cell.
- Test greedy or alternating shortcuts against tiny counterexamples like `[2,1,1,2]` and `[2,3,2]` before trusting them.
- When a recurrence only looks back a fixed number of steps, replace the table with that many rolling variables.
