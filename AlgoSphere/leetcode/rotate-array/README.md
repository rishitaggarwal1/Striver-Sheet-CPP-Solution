# Rotate Array

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/rotate-array/) · ✅ Solved in C++

**Contents:** [Problem](#problem) · [Hints](#hints) · [My solution](#my-solution)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.

Example 1:

Input: nums = [1,2,3,4,5,6,7], k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]

Example 2:

Input: nums = [-1,-100,3,99], k = 2
Output: [3,99,-1,-100]
Explanation:
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]

Constraints:

- 1 <= nums.length <= 10^5

- -2^31 <= nums[i] <= 2^31 - 1

- 0 <= k <= 10^5

Follow up:

- Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.

- Could you do it in-place with O(1) extra space?
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Every element must end up `k` positions further to the right, and elements that fall off the end wrap around to the front. Equivalently, the last `k` elements move to the front and everything else shifts right, keeping its relative order.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Rotating by `n` (the array length) leaves the array unchanged, so only `k mod n` matters. Also notice that the output is just two blocks of the original array, the last `k` and then the first `n - k`, swapped in position while each block keeps its internal order.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n` and `k` up to `10^5`, shifting the whole array one step at a time `k` times costs `O(n*k)`, about `10^10` operations, which is far too slow. You need `O(n)`. Copying into a second array with `result[(i + k) mod n] = nums[i]` is linear, but it uses `O(n)` extra space, and the follow-up asks for `O(1)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is an in-place array manipulation problem solved with the reversal trick. Two-pointer reversals of whole ranges can reorder blocks without any extra buffer. (Cyclic replacement, following each index to `(i + k) mod n`, is another valid `O(1)` approach.)

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Reversing the entire array puts the last `k` elements at the front, but both blocks come out backwards. Reversing each block again restores its internal order, which leaves exactly the rotated array.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track only the effective shift `k = k mod n`, plus two indices `left` and `right` for each reversal, which swap toward each other until they meet. The three ranges to reverse are `[0, n-1]`, `[0, k-1]`, and `[k, n-1]`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Let n be the array length and set k = k mod n.
If k is 0, stop; the array is already correct.
Reverse the whole array from index 0 to n-1.
Reverse the first k elements, indices 0 to k-1.
Reverse the remaining elements, indices k to n-1.
The array is now rotated in place.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is remembering `k mod n`: when `k > n` (for example `n = 1`, `k = 5`), the reversal ranges become invalid without it. Check single-element arrays, `k = 0`, and `k` equal to a multiple of `n`, all of which should leave the array unchanged. Each element is swapped a constant number of times, so time is `O(n)` and extra space is `O(1)`.

</details>

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-20 |

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        
    }
};
```
