# Median of Two Sorted Arrays

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/median-of-two-sorted-arrays/)

**Contents:** [Problem](#problem) · [Hints](#hints) · [Test cases](#test-cases)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).

Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Constraints:

- nums1.length == m

- nums2.length == n

- 0 <= m <= 1000

- 0 <= n <= 1000

- 1 <= m + n <= 2000

- -10^6 <= nums1[i], nums2[i] <= 10^6
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Imagine merging the two sorted lists into one big sorted list; you want its middle value, or the average of the two middle values if the total length is even. The catch is you must find it without actually building that merged list.

</details>

<details>
<summary>Hint 2 · Observation</summary>

The median splits the combined elements into a left half and a right half where every left element is at most every right element. If you take the first `i` elements of `nums1` for the left half, the number you must take from `nums2` is forced, because the left half must hold exactly `(m + n + 1) / 2` elements.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With at most 2000 elements, a linear merge in `O(m + n)` would actually run fast, but the problem explicitly demands `O(log(m + n))`. That rules out walking through elements one by one, and it means you need to discard a large fraction of the candidates at every step.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is binary search, applied not to a value but to a partition position in the shorter array. It fits because once you fix how many elements the shorter array contributes, you can tell whether you took too many or too few, and that check is monotonic.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Choose a cut `i` in the shorter array `A` and the matching cut `j = half - i` in `B`. The cut is correct exactly when `A[i-1] <= B[j]` and `B[j-1] <= A[i]`. If `A[i-1] > B[j]`, then `i` is too large; otherwise, if the second condition fails, `i` is too small.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track a search range `lo..hi` for `i` over `0..len(A)`, plus `half = (m + n + 1) / 2`. At each candidate cut, look at four boundary values: `leftA = A[i-1]`, `rightA = A[i]`, `leftB = B[j-1]`, `rightB = B[j]`. Treat any out-of-range index as negative or positive infinity.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Make `A` the shorter array, swapping the inputs if needed.
Set `lo = 0`, `hi = len(A)`, and `half = (m + n + 1) / 2`.
Repeat: `i = (lo + hi) / 2`, `j = half - i`, then read the four boundary values.
If `leftA > rightB`, set `hi = i - 1`.
Else if `leftB > rightA`, set `lo = i + 1`.
Otherwise the partition is valid: if the total is odd, return `max(leftA, leftB)`.
If the total is even, return the average of `max(leftA, leftB)` and `min(rightA, rightB)`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is handling cuts at the very ends (`i = 0`, `i = len(A)`, `j = 0`, `j = len(B)`) with infinity sentinels, which also covers the case where one array is empty. Searching on the shorter array guarantees `j` always stays within `0..len(B)`, and the `+1` in `half` puts the odd median on the left side. Use floating-point division for the even-length average. Time is `O(log(min(m, n)))`, which beats the required bound, and space is `O(1)`.

</details>

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums1 = [1,5,9]<br>nums2 = [2,3,10,11] | 5.00000 | Odd total length with interleaved values; merged [1,2,3,5,9,10,11]. |
| nums1 = [1,2,3]<br>nums2 = [4,5,6] | 3.50000 | Disjoint ranges, even total; merged [1,2,3,4,5,6]. |
| nums1 = [-5,-3,0,7]<br>nums2 = [-4,2] | -1.50000 | Negatives mixed in; merged [-5,-4,-3,0,2,7], median (-3+0)/2. |
| nums1 = [10,20,30,40,50]<br>nums2 = [15] | 25.00000 | Very unequal lengths; merged [10,15,20,30,40,50]. |
| nums1 = [1,4,7]<br>nums2 = [2,6,8,9,12] | 6.50000 | Interleaved, even total; merged [1,2,4,6,7,8,9,12]. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | nums1 = []<br>nums2 = [1] | 1.00000 | First array empty. |
| Empty second array | nums1 = [2]<br>nums2 = [] | 2.00000 | Median is the sole element. |
|   | nums1 = []<br>nums2 = [2,3] | 2.50000 | Empty first array with even length. |
| All equal | nums1 = [3,3,3]<br>nums2 = [3,3] | 3.00000 | Duplicates throughout. |
| Extreme values | nums1 = [-1000000]<br>nums2 = [1000000] | 0.00000 | Min and max bounds average to zero. |
| Max values | nums1 = [1000000,1000000]<br>nums2 = [1000000] | 1000000.00000 | No overflow when duplicates at upper bound. |
| Partition crossing | nums1 = [1,2]<br>nums2 = [-1,3] | 1.50000 | Median spans both arrays; merged [-1,1,2,3]. |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
