# House Robber II

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/house-robber-ii/) · Pattern: **1D take/skip DP, run twice to break the circle**

> Given `nums` arranged in a ring, pick houses so that no two picked houses are neighbours (house `0` and house `n - 1` count as neighbours) and maximise the total money.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed. All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: nums = [2,3,2]
Output: 3
Explanation: You cannot rob house 1 (money = 2) and then rob house 3 (money = 2), because they are adjacent houses.

Example 2:

Input: nums = [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
Total amount you can rob = 1 + 3 = 4.

Example 3:

Input: nums = [1,2,3]
Output: 3

Constraints:

- 1 <= nums.length <= 100

- 0 <= nums[i] <= 1000
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Houses stand in a ring and you choose some of them to rob so that no two chosen houses are next to each other; because it is a ring, the first and the last house also count as next to each other. Return the largest total you can collect.

</details>

<details>
<summary>Hint 2 · Observation</summary>

In Example 1 (`[2,3,2]`) the two `2`s are not adjacent on a straight street, so a line would allow `2 + 2 = 4`, but on the ring houses `0` and `2` touch and the answer drops to `3`. The ring adds exactly one new forbidden pair: house `0` with house `n - 1`.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

`nums.length` is at most `100`, so trying every subset of houses (`2^100` of them) is hopeless. On the other hand even `O(n^2)` would be only `10^4` steps, so any polynomial idea passes and a single linear scan is the natural target.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is 1D dynamic programming with a take-or-skip choice per house (the House Robber pattern), because the decision at house `i` only depends on whether house `i - 1` was robbed. The ring just needs to be broken into straight-line pieces first.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

No legal plan robs both house `0` and house `n - 1`, so every plan skips at least one of them. Solve the straight street `0..n-2` (last house removed) and the straight street `1..n-1` (first house removed). The larger of the two answers is the answer for the ring.

</details>

<details>
<summary>Hint 6 · What to track</summary>

For one straight street, let `best[i]` be the most money from the street's start through house `i`, so `best[i] = max(best[i - 1], nums[i] + best[i - 2])`. Since only the last two values are ever read, keep just `prev1` (best through the previous house) and `prev2` (best through the house before that), both starting at `0`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

If there is only one house, return its value.
Run a straight-street pass over houses `0` to `n - 2`.
Run a second pass over houses `1` to `n - 1`.
In each pass start with `prev2 = 0` and `prev1 = 0`.
For each house, set `cur = max(prev1, nums[i] + prev2)`, then `prev2 = prev1` and `prev1 = cur`.
A pass's answer is `prev1` at the end.
Return the larger of the two pass answers.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trap is `n = 1`: both streets are empty and would give `0`, so return `nums[0]` directly; `n = 2` then correctly gives the larger of the two houses. Zeros and ties need no special handling, and the largest possible total, `50 · 1000 = 50,000`, fits in an `int`. Time is `O(n)` for two linear passes and extra space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "All houses at this place are arranged in a circle. That means the first house is the neighbor of the last one" | the only rule added to House Robber is the pair (`0`, `n - 1`), so split into the two straight streets that each drop one end. |
| "adjacent houses ... will automatically contact the police" | the choice at house `i` depends only on whether house `i - 1` was robbed, the classic take/skip DP state. |
| "1 <= nums.length <= 100" | enumerating subsets is hopeless but any polynomial method passes; `n = 1` is allowed and breaks a naive split. |
| "0 <= nums[i] <= 1000" | values are non-negative and the total is at most `50 · 1000 = 50,000`, so a plain `int` with no overflow worries. |

### What the constraints tell you

`n <= 100`: all subsets is `2^100 ≈ 1.3·10^30`, and the plain take/skip recursion makes about `1.4·10^21` calls over its two passes, far too slow. A linear DP does about `2 · 99 ≈ 200` updates (even `O(n^2) = 10^4` would pass), so the target is `O(n)` time, ideally with `O(1)` extra space.

### Think it through

Answer each question yourself before opening it.

**Q1. If the houses stood on a straight street, how would I decide house by house?**

<details>
<summary>Answer</summary>

At house `i` I either rob it, gaining `nums[i]` but forbidding house `i - 1`, or skip it and keep the best through `i - 1`. That gives `best(i) = max(best(i - 1), nums[i] + best(i - 2))`, the original House Robber recurrence.

</details>

**Q2. What exactly does the circle break in that recurrence?**

<details>
<summary>Answer</summary>

Only one pair becomes new neighbours: house `0` and house `n - 1`. In `nums = [2,3,2]` the straight-street answer `2 + 2 = 4` robs both ends, which is now illegal, so the answer drops to `3`.

</details>

**Q3. Can I avoid carrying a flag like 'house 0 was robbed' through the whole scan?**

<details>
<summary>Answer</summary>

Yes: no legal plan robs both house `0` and house `n - 1`, so at least one of them is skipped. If house `n - 1` is skipped the rest is the straight street `0..n-2`; if house `0` is skipped it is the straight street `1..n-1`.

</details>

**Q4. Is the larger of those two straight-street answers really the ring answer?**

<details>
<summary>Answer</summary>

Every legal ring plan is legal in at least one of the two streets, and every plan on either street is legal on the ring because it never robs both ends. So the maximum over the two cases is exactly the ring optimum; for `[1,2,3,1]` that is `max(4, 3) = 4`.

</details>

**Q5. How much memory does one straight-street pass need?**

<details>
<summary>Answer</summary>

`best(i)` reads only `best(i - 1)` and `best(i - 2)`, so two variables `prev1` and `prev2` replace the whole table, giving `O(1)` extra space per pass.

</details>

**Q6. What happens at the smallest size, `n = 1`?**

<details>
<summary>Answer</summary>

Both ranges `0..n-2` and `1..n-1` are empty and would return `0`, yet the single house has no neighbour at all. So `n = 1` must return `nums[0]` before splitting.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Plain recursion on the two straight streets](#1-brute-force-plain-recursion-on-the-two-straight-streets) | `O(2^n)` | `O(n)` |
| 2 | [Better: Bottom-up table per straight street](#2-better-bottom-up-table-per-straight-street) | `O(n)` | `O(n)` |
| 3 | [Optimal: Two rolling variables per straight street](#3-optimal-two-rolling-variables-per-straight-street) | `O(n)` | `O(1)` |

### 1. Brute force: Plain recursion on the two straight streets

> **Where you start:** Deciding rob-or-skip at every house is the most direct way to explore all legal plans, and splitting into 'last house excluded' and 'first house excluded' removes the circle without any extra state.

**Idea.** Define `best(lo, i)` as the most money from houses `lo..i` on a straight street. For house `i`, either rob it and add `best(lo, i - 2)`, or skip it and take `best(lo, i - 1)`; these two options cover every legal plan for `lo..i`, so their maximum is correct. Running it on `0..n-2` and `1..n-1` covers every ring plan, because none can rob both house `0` and house `n - 1`. Nothing is cached, so the same `best(lo, i)` is solved again and again.

**Steps**

1. If `n == 1`, return `nums[0]`.
2. Define `best(lo, i)`: return `0` if `i < lo`, and `nums[lo]` if `i == lo`.
3. Otherwise compute `take = nums[i] + best(lo, i - 2)` and `skip = best(lo, i - 1)`, and return the larger.
4. Compute `skipLast = best(0, n - 2)` and `skipFirst = best(1, n - 1)`.
5. Return `max(skipLast, skipFirst)`.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   if n = 1
 4 │     return nums[0]  // a lone house has no neighbour, circle or not
 5 │   skipLast ← best(nums, 0, n - 2)  // house n-1 never robbed: houses 0..n-2 are a straight street
 6 │   skipFirst ← best(nums, 1, n - 1)  // house 0 never robbed: houses 1..n-1 are a straight street
 7 │   return max(skipLast, skipFirst)  // every legal ring plan skips house 0 or house n-1
 8 │ function best(nums, lo, i)  // most money from houses lo..i on a straight street
 9 │   if i < lo
10 │     return 0  // no houses left in the range
11 │   if i = lo
12 │     return nums[lo]  // a single house: rob it
13 │   take ← nums[i] + best(nums, lo, i - 2)  // rob house i, so house i-1 is off limits
14 │   skip ← best(nums, lo, i - 1)  // leave house i, so house i-1 is free
15 │   return max(take, skip)
```

**Time complexity: `O(2^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Base cases (lines 9-12) | O(1) per call | An empty or single-house range returns immediately without recursing. |
| Two recursive calls (lines 13-14) | T(k) = T(k − 1) + T(k − 2) + 1 calls for a range of k houses | Each call branches into ranges one and two houses shorter, exactly like the Fibonacci recurrence. |
| Two top-level passes (lines 5-6) | 2 × T(n − 1) calls | The full recursion runs once on houses 0..n-2 and once on houses 1..n-1. |

- **Adding it up:** With T(0) = T(1) = 1, the recurrence solves to T(k) = 2·F(k + 1) − 1 (F = Fibonacci), which grows like 1.62^k; two passes give 2·(2·F(n) − 1) ≈ 1.8·1.62^n calls of O(1) work = O(1.62^n) ⊂ O(2^n).
- **At the maximum input:** n = 40 → about 4·10^8 calls (around a second); n = 45 → about 4.5·10^9; n = 100 → about 1.4·10^21 calls, which would never finish.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 13-14) | at most n − 1 frames × O(1) | The skip branch lowers i by one per level, so the deepest chain walks every house of a range of n − 1 houses. |

- **Adding it up:** Only one chain of calls is alive at a time, so the stack peaks at O(n) frames of O(1) each = O(n).
- **Not counted:** The input `nums` is read in place and not counted; no table is stored.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4 houses on the ring, so the single-house shortcut on line 3 does not apply and we split into two straight streets. | `n = 4`<br>`nums = [1, 2, 3, 1]`<br>`call stack = [rob(nums)] ← top` |
| 2 | 12 | Pass 1 calls best(lo=0, i=2), whose take branch first needs best(lo=0, i=0); only house 0 is left there, so it returns nums[0] = 1. | `lo = 0`<br>`i = 0`<br>`nums = [1, 2, 3, 1]` (lo→0, i→0)<br>`call stack = [rob(nums), best(lo=0, i=2), best(lo=0, i=0)] ← top` |
| 3 | 13 | Back in best(lo=0, i=2): take = nums[2] + best(lo=0, i=0) = 3 + 1 = 4. | `i = 2`<br>`take = 4`<br>`nums = [1, 2, 3, 1]` (lo→0, i→2)<br>`call stack = [rob(nums), best(lo=0, i=2): take=4] ← top` |
| 4 | 13 | best(lo=0, i=1): best(lo=0, i=-1) was an empty range (0), so take = nums[1] + 0 = 2. | `i = 1`<br>`take = 2`<br>`nums = [1, 2, 3, 1]` (lo→0, i→1)<br>`call stack = [rob(nums), best(lo=0, i=2): take=4, best(lo=0, i=1): take=2] ← top` |
| 5 | 12 | best(lo=0, i=0) is called AGAIN and returns 1 — the same subproblem as before, recomputed because nothing is cached. | `i = 0`<br>`nums = [1, 2, 3, 1]` (lo→0, i→0)<br>`call stack = [rob(nums), best(lo=0, i=2): take=4, best(lo=0, i=1): take=2, best(lo=0, i=0)] ← top` |
| 6 | 14 | best(lo=0, i=1): skip = best(lo=0, i=0) = 1. | `i = 1`<br>`take = 2`<br>`skip = 1`<br>`nums = [1, 2, 3, 1]` (lo→0, i→1)<br>`call stack = [rob(nums), best(lo=0, i=2): take=4, best(lo=0, i=1): take=2, skip=1] ← top` |
| 7 | 15 | best(lo=0, i=1) returns max(take = 2, skip = 1) = 2. | (no change) |
| 8 | 14 | best(lo=0, i=2): skip = best(lo=0, i=1) = 2. | `i = 2`<br>`take = 4`<br>`skip = 2`<br>`nums = [1, 2, 3, 1]` (lo→0, i→2)<br>`call stack = [rob(nums), best(lo=0, i=2): take=4, skip=2] ← top` |
| 9 | 15 | best(lo=0, i=2) returns max(take = 4, skip = 2) = 4. | (no change) |
| 10 | 5 | skipLast = 4: the best plan on houses 0..2 (house 3 left alone) robs houses 0 and 2. | `skipLast = 4`<br>`nums = [1, 2, 3, 1]`<br>`call stack = [rob(nums), skipLast=4] ← top` |
| 11 | 13 | Pass 2, best(lo=1, i=3): best(lo=1, i=1) returns nums[1] = 2, so take = nums[3] + 2 = 1 + 2 = 3. | `lo = 1`<br>`i = 3`<br>`take = 3`<br>`nums = [1, 2, 3, 1]` (lo→1, i→3)<br>`call stack = [rob(nums), skipLast=4, best(lo=1, i=3): take=3] ← top` |
| 12 | 15 | best(lo=1, i=2): take = nums[2] + best(lo=1, i=0) = 3 + 0 = 3 and skip = best(lo=1, i=1) = 2 (house 1 solved a second time), so it returns 3. | `i = 2`<br>`skip = 2`<br>`nums = [1, 2, 3, 1]` (lo→1, i→2)<br>`call stack = [rob(nums), skipLast=4, best(lo=1, i=3): take=3, best(lo=1, i=2): take=3, skip=2] ← top` |
| 13 | 15 | Back in best(lo=1, i=3): skip = best(lo=1, i=2) = 3, so it returns max(take = 3, skip = 3) = 3. | `i = 3`<br>`skip = 3`<br>`nums = [1, 2, 3, 1]` (lo→1, i→3)<br>`call stack = [rob(nums), skipLast=4, best(lo=1, i=3): take=3, skip=3] ← top` |
| 14 | 6 | skipFirst = 3: the best plan on houses 1..3 (house 0 left alone). | `skipFirst = 3`<br>`nums = [1, 2, 3, 1]`<br>`call stack = [rob(nums), skipLast=4, skipFirst=3] ← top` |
| 15 | 7 | Return max(skipLast = 4, skipFirst = 3) = 4. | (no change) |

**Result:** 4 — skipping the last house, robbing houses 0 and 2 gives 1 + 3 = 4, which beats the best 3 available once house 0 is skipped.

**C++ solution**

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // A lone house has no neighbour, and both ranges below would be empty
        if (n == 1) return nums[0];
        // Case 1: never rob the last house, so houses 0..n-2 form a straight street
        int skipLast = best(nums, 0, n - 2);
        // Case 2: never rob the first house, so houses 1..n-1 form a straight street
        int skipFirst = best(nums, 1, n - 1);
        // Every legal plan on the ring leaves house 0 or house n-1 alone
        return max(skipLast, skipFirst);
    }

private:
    // Most money from houses lo..i on a straight street, by plain recursion (no caching)
    int best(const vector<int>& nums, int lo, int i) {
        if (i < lo) return 0;                         // empty range: nothing to rob
        if (i == lo) return nums[lo];                 // one house: rob it
        int take = nums[i] + best(nums, lo, i - 2);   // rob house i, so i-1 is off limits
        int skip = best(nums, lo, i - 1);             // leave house i, so i-1 is free
        return max(take, skip);                       // the better of the two choices
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
        int n = nums.size();
        // A lone house has no neighbour, and both ranges below would be empty
        if (n == 1) return nums[0];
        // Case 1: never rob the last house, so houses 0..n-2 form a straight street
        int skipLast = best(nums, 0, n - 2);
        // Case 2: never rob the first house, so houses 1..n-1 form a straight street
        int skipFirst = best(nums, 1, n - 1);
        // Every legal plan on the ring leaves house 0 or house n-1 alone
        return max(skipLast, skipFirst);
    }

private:
    // Most money from houses lo..i on a straight street, by plain recursion (no caching)
    int best(const vector<int>& nums, int lo, int i) {
        if (i < lo) return 0;                         // empty range: nothing to rob
        if (i == lo) return nums[lo];                 // one house: rob it
        int take = nums[i] + best(nums, lo, i - 2);   // rob house i, so i-1 is off limits
        int skip = best(nums, lo, i - 1);             // leave house i, so i-1 is free
        return max(take, skip);                       // the better of the two choices
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
```

</details>

**Why move on:** `best(lo, i - 2)` is recomputed inside both branches of `best(lo, i)`, so `n = 45` already needs about `4.5·10^9` calls and `n = 100` about `1.4·10^21`; it times out for anything beyond roughly `n = 40`.

### 2. Better: Bottom-up table per straight street

> **How you get here:** In the recursion, `best(lo, i - 2)` is solved inside `best(lo, i)` and again inside `best(lo, i - 1)`, yet each range has only about `n` distinct values of `i`; computing each one once, from left to right, removes all the repeated work.

**Idea.** For a street `lo..hi`, let `dp[k]` be the most money from houses `lo..lo+k`. Start with `dp[0] = nums[lo]`, and for each later `k` set `dp[k] = max(dp[k - 1], nums[lo + k] + dp[k - 2])`, treating `dp[-1]` as `0`. Filling left to right guarantees both dependencies are ready, and the last entry is the street's answer. Running it on `0..n-2` and `1..n-1` and taking the larger gives the ring answer for the same reason as before.

**Steps**

1. If `n == 1`, return `nums[0]`.
2. For a street `lo..hi`, create `dp` of length `hi - lo + 1` and set `dp[0] = nums[lo]`.
3. For each `k` from `1`, set `dp[k] = max(dp[k - 1], nums[lo + k] + dp[k - 2])`, using `0` when `k - 2 < 0`.
4. The street's answer is the last entry of `dp`.
5. Run this on `0..n-2` and on `1..n-1` and return the larger result.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   if n = 1
 4 │     return nums[0]  // a lone house has no neighbour
 5 │   skipLast ← linear(nums, 0, n - 2)  // last house excluded
 6 │   skipFirst ← linear(nums, 1, n - 1)  // first house excluded
 7 │   return max(skipLast, skipFirst)
 8 │ function linear(nums, lo, hi)  // House Robber on the straight street lo..hi
 9 │   len ← hi - lo + 1
10 │   dp ← array of len zeros  // dp[k] = most money from houses lo..lo+k
11 │   dp[0] ← nums[lo]  // one house: rob it
12 │   for k ← 1 to len - 1
13 │     take ← nums[lo + k]  // rob house lo+k ...
14 │     if k ≥ 2
15 │       take ← take + dp[k - 2]  // ... plus the best that stops two houses back
16 │     skip ← dp[k - 1]  // leave house lo+k alone
17 │     dp[k] ← max(take, skip)
18 │   return dp[len - 1]
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Table setup (lines 9-11) | O(n) per pass | Allocating and zeroing `dp` touches each of its n − 1 cells once. |
| Fill loop (lines 12-17) | (n − 2) iterations × O(1) per pass | Each cell reads two earlier cells and does one comparison. |
| Two passes (lines 5-6) | 2 × the work above | The same routine runs on houses 0..n-2 and on houses 1..n-1. |

- **Adding it up:** 2 × [(n − 1) + (n − 2)] = 4n − 6 = O(n); the passes are linear and there are only two of them.
- **At the maximum input:** n = 100 → under 400 simple operations; effectively instant.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| dp array (line 10) | n − 1 integers per pass | One cell per house of the current straight street. |

- **Adding it up:** The first pass's table is released before the second is built, so the peak is n − 1 integers = O(n).
- **Not counted:** The input `nums` and the single returned integer are not counted.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4, so we run the straight-street table twice: once without the last house, once without the first. | `n = 4`<br>`nums = [1, 2, 3, 1]` |
| 2 | 10 | linear(lo=0, hi=2): len = 3 houses, so dp starts as 3 zeros. | `lo = 0`<br>`hi = 2`<br>`len = 3`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2)<br>`dp = [0, 0, 0]` |
| 3 | 11 | dp[0] = nums[0] = 1: with only house 0 available, rob it. | `dp = [1, 0, 0]` |
| 4 | 17 | k = 1, house 1: take = nums[1] = 2 (no dp[k - 2] yet), skip = dp[0] = 1, so dp[1] = max(2, 1) = 2. | `k = 1`<br>`take = 2`<br>`skip = 1`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2, lo+k→1)<br>`dp = [1, 2, 0]` (k→1) |
| 5 | 15 | k = 2, house 2: take = nums[2] + dp[0] = 3 + 1 = 4. | `k = 2`<br>`take = 4`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2, lo+k→2)<br>`dp = [1, 2, 0]` (k→2) |
| 6 | 17 | skip = dp[1] = 2, so dp[2] = max(4, 2) = 4. | `skip = 2`<br>`dp = [1, 2, 4]` (k→2) |
| 7 | 5 | linear(0, 2) returned dp[2] = 4, so skipLast = 4 (rob houses 0 and 2). | `skipLast = 4`<br>`nums = [1, 2, 3, 1]` |
| 8 | 10 | linear(lo=1, hi=3): len = 3 houses, so dp starts as 3 zeros. | `lo = 1`<br>`hi = 3`<br>`len = 3`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3)<br>`dp = [0, 0, 0]` |
| 9 | 11 | dp[0] = nums[1] = 2: with only house 1 available, rob it. | `dp = [2, 0, 0]` |
| 10 | 17 | k = 1, house 2: take = nums[2] = 3 (no dp[k - 2] yet), skip = dp[0] = 2, so dp[1] = max(3, 2) = 3. | `k = 1`<br>`take = 3`<br>`skip = 2`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3, lo+k→2)<br>`dp = [2, 3, 0]` (k→1) |
| 11 | 15 | k = 2, house 3: take = nums[3] + dp[0] = 1 + 2 = 3. | `k = 2`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3, lo+k→3)<br>`dp = [2, 3, 0]` (k→2) |
| 12 | 17 | skip = dp[1] = 3, so dp[2] = max(3, 3) = 3. | `skip = 3`<br>`dp = [2, 3, 3]` (k→2) |
| 13 | 6 | linear(1, 3) returned dp[2] = 3, so skipFirst = 3. | `skipFirst = 3`<br>`nums = [1, 2, 3, 1]` |
| 14 | 7 | Return max(skipLast = 4, skipFirst = 3) = 4. | (no change) |

**Result:** 4 — the street 0..2 ends with dp = [1, 2, 4] and the street 1..3 with dp = [2, 3, 3], and max(4, 3) = 4.

**C++ solution**

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        // A lone house has no neighbour, and both ranges below would be empty
        if (n == 1) return nums[0];
        // Break the ring: either the last house or the first house is never robbed
        int skipLast = robLine(nums, 0, n - 2);
        int skipFirst = robLine(nums, 1, n - 1);
        return max(skipLast, skipFirst);
    }

private:
    // Classic House Robber on nums[lo..hi] with a dp table
    int robLine(const vector<int>& nums, int lo, int hi) {
        int len = hi - lo + 1;
        vector<int> dp(len, 0);          // dp[k] = most money from houses lo..lo+k
        dp[0] = nums[lo];                // one house available: rob it
        for (int k = 1; k < len; ++k) {
            int take = nums[lo + k];     // rob house lo+k ...
            if (k >= 2) take += dp[k - 2]; // ... plus the best that stops two houses back
            int skip = dp[k - 1];        // or leave it and keep the best through lo+k-1
            dp[k] = max(take, skip);
        }
        return dp[len - 1];              // best over the whole range
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
        int n = nums.size();
        // A lone house has no neighbour, and both ranges below would be empty
        if (n == 1) return nums[0];
        // Break the ring: either the last house or the first house is never robbed
        int skipLast = robLine(nums, 0, n - 2);
        int skipFirst = robLine(nums, 1, n - 1);
        return max(skipLast, skipFirst);
    }

private:
    // Classic House Robber on nums[lo..hi] with a dp table
    int robLine(const vector<int>& nums, int lo, int hi) {
        int len = hi - lo + 1;
        vector<int> dp(len, 0);          // dp[k] = most money from houses lo..lo+k
        dp[0] = nums[lo];                // one house available: rob it
        for (int k = 1; k < len; ++k) {
            int take = nums[lo + k];     // rob house lo+k ...
            if (k >= 2) take += dp[k - 2]; // ... plus the best that stops two houses back
            int skip = dp[k - 1];        // or leave it and keep the best through lo+k-1
            dp[k] = max(take, skip);
        }
        return dp[len - 1];              // best over the whole range
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
```

</details>

**Why move on:** At `n = 100` this is instant, so it already meets the limits; the only waste is the `O(n)` `dp` array, since each cell is read by the next two cells and never again.

### 3. Optimal: Two rolling variables per straight street

> **How you get here:** `dp[k]` only ever reads `dp[k - 1]` and `dp[k - 2]`, so the whole table can be replaced by two variables that slide forward one house at a time.

**Idea.** Keep `prev1` = best loot through the previous house and `prev2` = best loot through the house before it, both starting at `0`. For each house `i` in the street, `cur = max(prev1, nums[i] + prev2)`: skip house `i` and keep `prev1`, or rob it and add the best total that avoids its left neighbour. Then shift `prev2 ← prev1` and `prev1 ← cur`, so the invariant 'prev1 is the best through the latest house' holds after every step. Doing this on `0..n-2` and `1..n-1` and taking the larger covers every legal ring plan.

**Steps**

1. If `n == 1`, return `nums[0]`.
2. For a street `lo..hi`, set `prev2 = 0` and `prev1 = 0`.
3. For each `i` from `lo` to `hi`, compute `cur = max(prev1, nums[i] + prev2)`.
4. Shift: set `prev2 = prev1`, then `prev1 = cur`.
5. After the loop, `prev1` is the street's answer.
6. Return the larger of the answers for `0..n-2` and `1..n-1`.

**Pseudocode**

```text
 1 │ function rob(nums)
 2 │   n ← length(nums)
 3 │   if n = 1
 4 │     return nums[0]  // both ranges below would be empty
 5 │   skipLast ← linear(nums, 0, n - 2)  // house n-1 never robbed
 6 │   skipFirst ← linear(nums, 1, n - 1)  // house 0 never robbed
 7 │   return max(skipLast, skipFirst)
 8 │ function linear(nums, lo, hi)  // House Robber on lo..hi with O(1) memory
 9 │   prev2 ← 0  // best loot through house i-2
10 │   prev1 ← 0  // best loot through house i-1
11 │   for i ← lo to hi
12 │     cur ← max(prev1, nums[i] + prev2)  // skip house i, or rob it
13 │     prev2 ← prev1  // slide the window one house to the right
14 │     prev1 ← cur
15 │   return prev1  // best loot for the whole range
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Split and combine (lines 2-7) | O(1) plus two calls | Reading n, the n = 1 check and the final max are constant work. |
| Scan loop (lines 11-14) | n − 1 iterations × O(1) per pass | Each house of the street does one max and two assignments. |
| Two passes (lines 5-6) | 2 × (n − 1) iterations | The loop runs on houses 0..n-2 and again on houses 1..n-1. |

- **Adding it up:** O(1) + 2·(n − 1)·O(1) = O(n); the two linear scans dominate.
- **At the maximum input:** n = 100 → 198 loop iterations; finishes in well under a microsecond of real work.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| prev2, prev1, cur, i (lines 9-12) | 4 integers | Only the last two best totals and the loop index are needed at any time. |
| skipLast, skipFirst, n (lines 2-6) | 3 integers | The two case answers are kept just long enough to compare them. |

- **Adding it up:** 4 + 3 = 7 integers regardless of n, so O(1).
- **Not counted:** No recursion and no arrays; the input `nums` is only read.

**Dry run** on `nums = [1, 2, 3, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | n = 4, so the ring is split into the straight streets 0..2 and 1..3. | `n = 4`<br>`nums = [1, 2, 3, 1]` |
| 2 | 10 | linear(lo=0, hi=2): prev2 = 0 and prev1 = 0 because no house has been considered yet. | `lo = 0`<br>`hi = 2`<br>`prev2 = 0`<br>`prev1 = 0`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2) |
| 3 | 12 | i = 0: cur = max(prev1 = 0, nums[0] + prev2 = 1 + 0) = 1, so robbing house 0 is best so far. | `i = 0`<br>`cur = 1`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2, i→0) |
| 4 | 14 | Shift for i = 0: prev2 = old prev1 = 0, prev1 = cur = 1; prev1 is now the best loot through house 0. | `prev1 = 1` |
| 5 | 14 | i = 1: cur = max(prev1 = 1, nums[1] + prev2 = 2 + 0) = 2; then shift: prev2 = 1, prev1 = 2. | `i = 1`<br>`prev2 = 1`<br>`prev1 = 2`<br>`cur = 2`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2, i→1) |
| 6 | 12 | i = 2: cur = max(prev1 = 2, nums[2] + prev2 = 3 + 1) = 4, so robbing house 2 is best so far. | `i = 2`<br>`cur = 4`<br>`nums = [1, 2, 3, 1]` (lo→0, hi→2, i→2) |
| 7 | 14 | Shift for i = 2: prev2 = old prev1 = 2, prev1 = cur = 4; prev1 is now the best loot through house 2. | `prev2 = 2`<br>`prev1 = 4` |
| 8 | 5 | linear(0, 2) returns prev1 = 4, so skipLast = 4 (houses 0 and 2: 1 + 3). | `skipLast = 4`<br>`nums = [1, 2, 3, 1]` |
| 9 | 10 | linear(lo=1, hi=3): prev2 = 0 and prev1 = 0 because no house has been considered yet. | `lo = 1`<br>`hi = 3`<br>`prev2 = 0`<br>`prev1 = 0`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3) |
| 10 | 14 | i = 1: cur = max(prev1 = 0, nums[1] + prev2 = 2 + 0) = 2; then shift: prev2 = 0, prev1 = 2. | `i = 1`<br>`prev1 = 2`<br>`cur = 2`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3, i→1) |
| 11 | 14 | i = 2: cur = max(prev1 = 2, nums[2] + prev2 = 3 + 0) = 3; then shift: prev2 = 2, prev1 = 3. | `i = 2`<br>`prev2 = 2`<br>`prev1 = 3`<br>`cur = 3`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3, i→2) |
| 12 | 12 | i = 3: cur = max(prev1 = 3, nums[3] + prev2 = 1 + 2) = 3, a tie between robbing and skipping house 3. | `i = 3`<br>`nums = [1, 2, 3, 1]` (lo→1, hi→3, i→3) |
| 13 | 14 | Shift for i = 3: prev2 = old prev1 = 3, prev1 = cur = 3; prev1 is now the best loot through house 3. | `prev2 = 3` |
| 14 | 6 | linear(1, 3) returns prev1 = 3, so skipFirst = 3. | `skipFirst = 3`<br>`nums = [1, 2, 3, 1]` |
| 15 | 7 | Return max(skipLast = 4, skipFirst = 3) = 4. | (no change) |

**Result:** 4 — without the last house the best is 1 + 3 = 4 (houses 0 and 2), without the first house it is 3, so the ring answer is 4.

**C++ solution**

```cpp
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
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
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
```

</details>

**Why this is the best:** Any house's value can change the answer, so every correct algorithm must read all `n` values: `O(n)` time with `O(1)` space cannot be beaten. The only cost is that the middle houses `1..n-2` are scanned twice.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [2,7,9,3,1] | 11 | The straight-street best `2 + 9 + 1 = 12` robs houses 0 and 4, which touch on the ring, so the answer falls to `2 + 9 = 11`. |
| nums = [1,3,1,3,100] | 103 | A huge last house: robbing it forbids house 0, and `3 + 100` beats anything from houses 0..3. |
| nums = [200,3,140,20,10] | 340 | A huge first house: the street without the last house wins with `200 + 140`. |
| nums = [4,1,2,7,5,3,1] | 14 | The best plan `4 + 7 + 3` skips two houses in a row, so simply alternating houses is wrong. |
| nums = [6,6,4,8,4,3,3,10] | 27 | Even ring of 8: once house 0 is dropped, `6 + 8 + 3 + 10 = 27` through the last house wins. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single house | nums = [5] | 5 | Both two-pass streets are empty, so this must be special-cased to return the one house. |
| Two houses | nums = [2,9] | 9 | They are neighbours, so only the larger one can be robbed. |
| All zeros | nums = [0,0,0] | 0 | Every choice ties at `0`. |
|   | nums = [1000,1000,1000] | 1000 | All equal at the maximum value in a ring of 3: every pair is adjacent, so only one house; a 100-house ring of `1000`s would give `50000`. |
| All equal, even ring | nums = [5,5,5,5] | 10 | Rob every other house (0 and 2, or 1 and 3). |
| Maximum values at both ends | nums = [1000,1,1,1000] | 1001 | The two `1000`s are neighbours through the wrap-around, so only one of them can be taken. |
| Odd alternating ring | nums = [1,0,1,0,1] | 2 | The every-other pick 0, 2, 4 would rob houses 4 and 0, which touch. |

## Mistakes and edge cases

**Common mistakes**

- Running plain House Robber on the whole array: for `[2,3,2]` it returns `4` by robbing houses `0` and `2`, which are neighbours on the ring.
- Forgetting `n == 1`: both ranges `0..n-2` and `1..n-1` are empty, so the two-pass method returns `0` for `[5]` instead of `5`.
- Assuming the best plan simply alternates houses: for `[5,1,1,5,1,1]` both alternating sums are `7`, but robbing houses `0` and `3` gives `10`, because skipping two houses in a row can pay off.
- Shifting in the wrong order: writing `prev1 = cur` before `prev2 = prev1` makes `prev2` equal `cur`, so the next house adds onto a total that already includes its neighbour.

**Edge cases to check**

- `nums = [7]`: a single house must return `7`; the two-pass split would see two empty streets and return `0`.
- `nums = [2,9]`: the two houses are neighbours both ways round, so the answer is `9`, never `11`.
- `nums = [1000,1000,1000]`: in a 3-house ring every pair is adjacent, so only one house can be robbed and the answer is `1000`.
- `nums = [1000,1,1,1000]`: the two big houses touch through the wrap-around, so the answer is `1001`, not `2000`.
- `n = 100` with every value `1000`: the answer `50000` checks the loop bounds of both passes and confirms an `int` is enough.

## Practice next

- [House Robber](https://leetcode.com/problems/house-robber/) · The straight-street version; this problem runs its O(1)-space DP twice on two overlapping ranges.
- [House Robber III](https://leetcode.com/problems/house-robber-iii/) · The same rob-or-skip choice with 'neighbour' meaning parent and child in a binary tree, solved with a pair of DP values per node.
- [Delete and Earn](https://leetcode.com/problems/delete-and-earn/) · After bucketing equal values, choosing value `v` forbids `v - 1` and `v + 1`, which is exactly House Robber on the buckets.
- [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/) · Another circular array handled by splitting into cases (wrapping or not) and reusing a linear-array algorithm.

## Takeaways

- A circular constraint that links only the first and last elements can often be removed by solving 'first excluded' and 'last excluded' as two linear problems and taking the better one.
- When `dp[i]` depends only on `dp[i - 1]` and `dp[i - 2]`, two rolling variables replace the whole table, turning `O(n)` space into `O(1)`.
- After any case split, re-check the smallest inputs (`n = 1`, `n = 2`): the split can create empty ranges that need a special case.
