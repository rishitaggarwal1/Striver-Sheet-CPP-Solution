# Smallest Unique Subarray

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/smallest-unique-subarray/)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given an integer array nums.

Find the minimum length of a subarray that is not identical to any other subarray in nums.

Return an integer denoting the minimum possible length of such a subarray.

Two subarrays are considered identical if they have the same length and the same elements in corresponding positions.

Example 1:

Input: nums = [3,3,3]

Output: 3

Explanation:

- Subarrays of length 1: [3] → appears 3 times

- Subarrays of length 2: [3, 3] → appears 2 times

- Subarrays of length 3: [3, 3, 3] → appears once

The subarray [3, 3, 3] is unique, so the smallest unique subarray length is 3.

Example 2:

Input: nums = [2,1,2,3,3]

Output: 1

Explanation:

Subarrays of length 1:

- [2] → appears 2 times

- [1] → appears once

- [3] → appears 2 times

The subarray [1] is unique, so the smallest unique subarray length is 1.

Example 3:

Input: nums = [1,1,2,2,1]

Output: 2

Explanation:

Subarrays of length 1:

- [1] → appears 3 times

- [2] → appears 2 times

Subarrays of length 2:

- [1, 1] → appears once

- [1, 2] → appears once

- [2, 2] → appears once

- [2, 1] → appears once

There is at least one subarray of length 2 that is unique, so the smallest unique subarray length is 2.

Constraints:

- 1 <= nums.length <= 10^5

- 1 <= nums[i] <= 10^5
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Among all contiguous pieces of the array, find the shortest one whose exact sequence of values occurs at only one starting position. The whole array always qualifies, so an answer always exists.

</details>

<details>
<summary>Hint 2 · Observation</summary>

If some subarray of length `L` is unique, then extending it by one element still gives a unique subarray, because any repeat of the longer piece would contain a repeat of the shorter one. So the answer is never more than `n`.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n` up to `10^5`, comparing all pairs of subarrays, or even listing every subarray of every length, is roughly `O(n^2)` or worse and too slow. You need about `O(n log n)` or `O(n log^2 n)`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is binary search on the answer combined with rolling hashing. A suffix array with LCP works too. Binary search fits because the property 'some subarray of length `L` is unique' is monotonic in `L`.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

For a fixed length `L`, compute a rolling hash of every window of length `L` and count how often each hash appears. A unique subarray exists exactly when some hash has count 1. Binary search for the smallest `L` where this holds.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Precompute prefix hashes and powers of the base modulo a large prime, preferably using two moduli or one 64-bit modulus to avoid collisions. During each check, keep a hash map from window hash to the number of occurrences.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Precompute prefix hashes and base powers.
Set `lo = 1` and `hi = n`.
While `lo < hi`, let `mid` be the midpoint.
Hash all windows of length `mid` and count each hash in a map.
If any count equals 1, set `hi = mid`; otherwise set `lo = mid + 1`.
Return `lo`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is hash collisions: a collision can make two different windows look identical and hide a unique one, so use double hashing or verify suspicious matches. Edge cases: `n = 1` gives 1, and an all-equal array gives `n`. Time is `O(n log n)` expected, and space is `O(n)`. A suffix array alternative computes, for each suffix, the maximum LCP with its neighbors and takes the minimum of that value plus 1 over valid suffixes.

</details>

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
