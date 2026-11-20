# Maximize Consecutive Elements in an Array After Modification

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/)

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
