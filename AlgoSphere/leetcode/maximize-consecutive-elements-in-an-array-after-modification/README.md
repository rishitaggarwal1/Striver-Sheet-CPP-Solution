# Maximize Consecutive Elements in an Array After Modification

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/) · Pattern: **Sorting + Dynamic Programming**

> Given an array `nums` where each element can be increased by `0` or `1`, find the maximum number of elements you can choose whose modified values form a strictly consecutive integer sequence.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a 0-indexed array nums consisting of positive integers.

Initially, you can increase the value of any element in the array by at most 1.

After that, you need to select one or more elements from the final array such that those elements are consecutive when sorted in increasing order. For example, the elements [3, 4, 5] are consecutive while [3, 4, 6] and [1, 1, 2, 3] are not.

Return the maximum number of elements that you can select.

Example 1:

Input: nums = [2,1,5,1,1]
Output: 3
Explanation: We can increase the elements at indices 0 and 3. The resulting array is nums = [3,1,5,2,1].
We select the elements [3,1,5,2,1] and we sort them to obtain [1,2,3], which are consecutive.
It can be shown that we cannot select more than 3 consecutive elements.

Example 2:

Input: nums = [1,4,7,10]
Output: 1
Explanation: The maximum consecutive elements that we can select is 1.

Constraints:

- 1 <= nums.length <= 10^5

- 1 <= nums[i] <= 10^6
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You can optionally add 1 to any subset of elements in the array, and then pick as many elements as possible that form a strictly consecutive sequence like `k, k+1, k+2, ...` with no duplicates or gaps. You want to maximize the count of elements in that chosen sequence.

</details>

<details>
<summary>Hint 2 · Observation</summary>

The original order of `nums` does not matter because you sort your chosen elements anyway, and duplicate values can still be useful since one copy can stay as `x` while another becomes `x + 1`.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `nums.length` up to `10^5`, trying all `2^n` increment choices or checking every possible starting value and subset is far too slow; we need an `O(n log n)` or `O(n)` solution.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This problem fits Sorting combined with Dynamic Programming, because sorting lets us process numbers in increasing order and each number only affects consecutive chains ending right around its value.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

When processing sorted elements one by one, a number `x` can either stay `x` to extend a chain ending at `x - 1`, or increment to `x + 1` to extend a chain ending at `x`; updating the `x + 1` case before the `x` case ensures the same element is never used twice in one chain.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Maintain a hash map `dp` where `dp[v]` represents the length of the longest valid consecutive sequence ending at value `v` using only the elements seen so far, plus a variable tracking the overall maximum length.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Sort `nums` in non-decreasing order.
Initialize an empty hash map `dp` (defaulting missing values to `0`) and `ans = 0`.
For each element `x` in the sorted array:
Set `dp[x + 1]` to `dp[x] + 1` (using `x` incremented by 1).
Set `dp[x]` to `dp[x - 1] + 1` (using `x` unchanged).
Update `ans` with the larger of `dp[x]` and `dp[x + 1]`.
Return `ans` after processing all elements.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest detail is update order: computing `dp[x + 1]` before `dp[x]` prevents `x` from extending a chain that `x` itself just created, and handles duplicates like `[1, 1, 1]` (answer `2`) naturally alongside single-element or wide-gap inputs. Sorting takes `O(n log n)` time and the DP pass takes `O(n)` time, for `O(n log n)` total time and `O(n)` extra space for `dp`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "consecutive when sorted in increasing order" | The original order of `nums` does not matter, and duplicates are forbidden in the chosen subset, which points to sorting `nums` first. |
| "increase the value of any element ... by at most 1" | Each element `x` has only two candidate roles in the final sequence (`x` or `x + 1`), allowing a simple local state transition. |
| "1 <= nums.length <= 10^5" and "1 <= nums[i] <= 10^6" | An `O(n^2)` approach will time out, while sorting plus a linear DP pass in `O(n log n)` will pass comfortably. |

### What the constraints tell you

With `nums.length <= 10^5`, an exponential `O(2^n)` search over `+0/+1` choices is impossible, and an `O(n^2)` loop takes roughly `10^10` operations, which is far too slow. Sorting `nums` takes `O(n log n)` ≈ `1.7 * 10^6` operations, and a linear DP pass adds `O(n)` ≈ `10^5` operations. Therefore, we need an `O(n log n)` time algorithm (or `O(n + max(nums))` using counting).

### Think it through

Answer each question yourself before opening it.

**Q1. Do the original indices of `nums` matter after we modify elements?**

<details>
<summary>Answer</summary>

No, because we can select any subset and sort it to check consecutiveness. Moreover, if `x < y`, then `x`'s modified value (`x` or `x + 1`) is at most `y`, which can never strictly exceed `y`'s modified value (`y` or `y + 1`), so sorting `nums` lets us build consecutive chains strictly from smaller elements to larger ones.

</details>

**Q2. In Example 1 (`nums = [2, 1, 5, 1, 1]`), why do repeated values like `1` still help?**

<details>
<summary>Answer</summary>

Even though a consecutive sequence cannot contain duplicates, one `1` can stay `1` while a second `1` is increased to `2`. Notice the third `1` cannot become `3`, so duplicates beyond two occurrences of the same value cannot both extend the same chain at that value.

</details>

**Q3. If we sort `nums` and fix a starting value `start`, how would we check the longest chain starting at `start`?**

<details>
<summary>Answer</summary>

We can scan sorted `nums` left-to-right tracking the next integer `need` (initially `start`) and greedily match `x` or `x + 1` to `need`. However, trying all ~`2n` candidate values of `start` takes `O(n^2)` time, which repeats a lot of work across overlapping sequences.

</details>

**Q4. How can we compute all chains in a single pass over sorted `nums` instead of restarting for every `start`?**

<details>
<summary>Answer</summary>

Define `dp[v]` as the maximum length of a consecutive sequence ending at value `v` using elements processed so far. When we see `x`, it can extend a sequence ending at `x - 1` (by staying `x`) or a sequence ending at `x` (by becoming `x + 1`).

</details>

**Q5. When processing a single element `x`, how do we avoid using that same `x` twice?**

<details>
<summary>Answer</summary>

If we updated `dp[x]` before `dp[x + 1]`, then `dp[x + 1]` could read the newly updated `dp[x]` and effectively count the same `x` as both `x` and `x + 1`. Updating `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` first, and then `dp[x] = max(dp[x], dp[x - 1] + 1)`, guarantees `x` is used in at most one position.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Enumerate all +0/+1 choices](#1-brute-force-enumerate-all-01-choices) | `O(2^n * n log n)` | `O(n)` |
| 2 | [Better: Sort + greedy check per starting value](#2-better-sort--greedy-check-per-starting-value) | `O(n^2)` | `O(n)` |
| 3 | [Optimal: Sort + end-value DP](#3-optimal-sort--end-value-dp) | `O(n log n)` | `O(n)` |

### 1. Brute force: Enumerate all +0/+1 choices

> **Where you start:** Because every `nums[i]` independently has two options (`nums[i]` or `nums[i] + 1`), the most direct way to remove the modification freedom is to try every possible final array.

**Idea.** Generate all `2^n` modified arrays by deciding for each index `i` whether to add `0` or `1`. For each resulting array, sort it (or insert into a set) and scan for the longest run of consecutive distinct integers. By exhaustively checking every valid modification, the maximum run found across all arrays is guaranteed to be optimal.

**Steps**

1. Recurse over index `i` from `0` to `n - 1`, branching on keeping `nums[i]` or replacing it with `nums[i] + 1`.
2. At `i == n`, put all modified values into a sorted list or hash set to remove duplicates.
3. Scan the distinct sorted values to find the longest contiguous run where `val[j] == val[j - 1] + 1`.
4. Return the maximum run length seen across all `2^n` branches.

**Complexity:** time `O(2^n * n log n)`, space `O(n)`. There are `2^n` leaf states in the recursion tree, and each leaf takes `O(n log n)` to sort (or `O(n)` with a hash set) to measure the longest consecutive sequence. Extra space is `O(n)` for the recursion stack and the temporary modified array.

**Why move on:** Completely infeasible beyond `n ≈ 20` because `2^n` explodes exponentially against the `n <= 10^5` constraint.

### 2. Better: Sort + greedy check per starting value

> **How you get here:** Instead of branching exponentially on every element, sorting `nums` first lets us greedily build the chain for any fixed starting integer `start` in one linear scan.

**Idea.** Sort `nums` in non-decreasing order. Any optimal consecutive sequence must start at some value `start` equal to `nums[i]` or `nums[i] + 1`. For a fixed `start`, scanning sorted `nums` and always taking the earliest element that can form `need` (either `x == need` or `x + 1 == need`) is optimal because delaying `need` to a later element can never yield a smaller `x` or unlock more choices.

**Steps**

1. Sort `nums` in increasing order.
2. Collect all distinct candidate starting values from `nums[i]` and `nums[i] + 1`.
3. For each candidate `start`, initialize `need = start`.
4. Scan `x` in sorted `nums`: if `x == need` or `x + 1 == need`, increment `need` by `1`.
5. Record `need - start` as the chain length for this `start`, and return the maximum length across all candidates.

**Complexity:** time `O(n^2)`, space `O(n)`. Sorting takes `O(n log n)`, while collecting up to `2n` candidate starts and running an `O(n)` scan for each takes `O(n^2)` time, which dominates. Storing the candidate set uses `O(n)` auxiliary space.

**Why move on:** Re-scans `nums` from scratch for every candidate `start`, resulting in ~`10^10` operations when `n = 10^5` and timing out.

### 3. Optimal: Sort + end-value DP

> **How you get here:** Rather than testing each starting value independently, we can track the longest consecutive chain ending at every value `v` in a single pass over sorted `nums`.

**Idea.** Sort `nums` in non-decreasing order and maintain a map `dp[v]` representing the length of the longest valid consecutive sequence ending at integer `v`. Because `nums` is sorted, all elements capable of contributing to values `< x` have already been processed before `x`. For each `x`, updating `dp[x + 1]` from `dp[x] + 1` before updating `dp[x]` from `dp[x - 1] + 1` ensures `x` either becomes `x + 1` or stays `x`, never both, which makes the DP transition exact.

**Steps**

1. Sort `nums` in increasing order.
2. Initialize an empty hash map (or array of size `max(nums) + 2`) `dp` where missing entries default to `0`.
3. For each `x` in sorted `nums`, update `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` first.
4. Next, update `dp[x] = max(dp[x], dp[x - 1] + 1)`.
5. Return the maximum value stored in `dp`.

**Complexity:** time `O(n log n)`, space `O(n)`. Sorting `nums` in `O(n log n)` dominates the running time, since the DP loop performs `O(1)` expected hash map lookups and updates per element (`O(n)` total). The `dp` hash map stores at most `2n` keys, using `O(n)` auxiliary space.

**Why this is the best:** Uses `O(n)` space for the DP table and requires sorting; if `max(nums)` were much smaller than `n`, counting sort could achieve `O(n + max(nums))`, though `O(n log n)` is already optimal for comparison-based processing and independent of the value range.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [8,10,6,12,9,11] | 6 | Bridges a single gap by incrementing the smallest element so all 6 elements form [7,8,9,10,11,12]. |
| nums = [3,3,4,4,6,6] | 5 | Uses duplicates to extend upward and bridge a gap of 2 between 4 and 6 to form [3,4,5,6,7]. |
| nums = [10,12,13,15,17] | 3 | Multiple candidate consecutive runs where incrementing cannot merge everything into one long sequence. |
| nums = [5,2,2,4,1,8,7] | 5 | Unsorted input with duplicates where the optimal sequence [1,2,3,4,5] beats the disjoint upper cluster. |
| nums = [4,1,3,1,3,5,8,7,7] | 9 | Cascading increments across multiple duplicate pairs allow all 9 elements to form [1,2,3,4,5,6,7,8,9]. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | nums = [1] | 1 | Minimum array length and minimum possible element value. |
| All equal | nums = [5,5,5,5] | 2 | More than two identical elements can still yield at most two consecutive values [5,6]. |
| Already consecutive | nums = [1,2,3,4,5] | 5 | No modifications needed to select the entire array. |
| Reverse-sorted step-2 gaps | nums = [9,7,5,3,1] | 2 | Adjacent pairs can connect to length 2, but cannot chain further without duplicates. |
| Maximum value boundary | nums = [1000000,999999,1000000] | 3 | Incrementing 10^6 produces 1000001; a full-scale 10^5-element array also tests O(n log n) time. |
| Large gaps | nums = [1,10,100,1000] | 1 | No two elements are within distance 2 so the longest consecutive sequence has length 1. |

## Mistakes and edge cases

**Common mistakes**

- Updating `dp[x]` before `dp[x + 1]`: if `dp[x]` increases first, then `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` will chain onto the same element `x` twice, creating a phantom sequence of length 2 from a single number.
- Not sorting `nums` before running the DP: processing `2` before `1` means `1 -> 2` will not propagate forward to `3` from the already-processed `2`.
- Forgetting to take `max` in the DP updates (writing `dp[x + 1] = dp[x] + 1` directly): a third duplicate like `[1, 1, 1]` would overwrite `dp[2] = 2` with `dp[1] + 1` or corrupt an existing longer chain ending at `x + 1` if `x` had a shorter chain.
- Skipping duplicates when deduplicating `nums` upfront: keeping at most two copies of each value is necessary (for `x` and `x + 1`), so converting `nums` into a set loses valid extensions like `[1, 1]` forming `[1, 2]`.

**Edge cases to check**

- Single element (`nums = [5]`): must return `1`, checking that `dp` handles arrays of length `1` without returning `0`.
- All identical elements (`nums = [3, 3, 3, 3]`): can form `[3, 4]` of length `2`, verifying that duplicates beyond two do not artificially inflate `dp[4]` to `3` or `4`.
- Large gaps between elements (`nums = [1, 4, 7, 10]`): even after `+1`, consecutive gaps remain `>= 2`, so the answer must be `1`.
- Bridging a gap of 2 (`nums = [1, 3]`): `1` can become `2` while `3` stays `3`, yielding `[2, 3]` of length `2`; this verifies that `x` increasing to `x + 1` is correctly picked up by `x + 2` later in the sorted array.

## Practice next

- [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) · Finds the longest consecutive integer sequence without modifications, introducing the core idea of tracking chain lengths by value.
- [Longest Arithmetic Subsequence of Given Difference](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/) · Uses the exact same `dp[val] = dp[val - d] + 1` hash-map DP pattern for difference `d = 1`, without the `+0/+1` choice.
- [Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/) · Combines sorting with bounded element modifications to build consecutive integers `1, 2, ..., k` greedily.

## Takeaways

- When elements can shift by a small bounded amount (`+0` or `+1`), sorting first often restores a one-way dependency so DP can process elements in a single pass.
- Reverse-order updates (`dp[x + 1]` before `dp[x]`) are the standard 0/1-knapsack-style trick to prevent a single item from transitioning to itself multiple times in the same iteration.
- For sequence problems where you can pick any subset regardless of original positions, keying DP states by element value (`dp[value]`) is often much cleaner than keying by array index.
