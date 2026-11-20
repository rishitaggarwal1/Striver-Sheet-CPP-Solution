# K-th of Two Sorted Arrays

**GeeksforGeeks** · **Medium** · [Open the problem](https://www.geeksforgeeks.org/problems/k-th-element-of-two-sorted-array1317/1)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given two sorted arrays a[] and b[] and an element k, find the element that would be at the k^th position of the combined sorted array.

Examples :

Input: a[] = [2, 3, 6, 7, 9], b[] = [1, 4, 8, 10], k = 5
Output: 6
Explanation: The final combined sorted array would be [1, 2, 3, 4, 6, 7, 8, 9, 10]. The 5th element of this array is 6.

Input: a[] = [1, 4, 8, 10, 12], b[] = [5, 7, 11, 15, 17], k = 6
Output: 10
Explanation: Combined sorted array is [1, 4, 5, 7, 8, 10, 11, 12, 15, 17]. The 6th element of this array is 10.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You have two lists that are each already in increasing order. Imagine combining them into one sorted list without actually building it, and report the value that sits at position `k`, counting from 1.

</details>

<details>
<summary>Hint 2 · Observation</summary>

The first `k` elements of the combined list must be made of some prefix of `a` plus some prefix of `b`, and the two prefix lengths add up to exactly `k`. In example 1 with `k = 5`, those elements are [2, 3, 6] from `a` and [1, 4] from `b`.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

Array lengths can reach around `10^6`, so merging step by step until position `k` costs `O(k)`, which works but is not the intended answer. Because both arrays are sorted, you can aim for logarithmic time, for example `O(log(min(n, m)))`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is binary search on a partition point. You search over how many elements are taken from the smaller array, and every guess automatically fixes how many come from the other array.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Suppose you take `i` elements from `a` and `k - i` from `b`. The split is correct exactly when the last taken element of `a` is no larger than the first untaken element of `b`, and the last taken element of `b` is no larger than the first untaken element of `a`. The answer is then the larger of the two last taken elements.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track a search range `[low, high]` for `i`, the count taken from `a`. Use `low = max(0, k - m)` and `high = min(k, n)`, where `n` is the length of `a` and `m` is the length of `b`. For each guess, look at four boundary values: `a[i-1]`, `a[i]`, `b[k-i-1]` and `b[k-i]`. Treat a missing left neighbour as minus infinity and a missing right neighbour as plus infinity.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Make `a` the shorter array, swapping if needed.
Set `low = max(0, k - m)` and `high = min(k, n)`.
Pick `i` as the middle of the range and set `j = k - i`.
Read the four boundary values, using sentinels where an index is out of range.
If `a[i-1] > b[j]`, too many come from `a`, so set `high = i - 1`.
Else if `b[j-1] > a[i]`, too few come from `a`, so set `low = i + 1`.
Otherwise return `max(a[i-1], b[j-1])`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is the bounds. If you leave out the `max(0, k - m)` and `min(k, n)` limits, `j` can become negative or exceed `m`. Use sentinels when `i` or `j` is 0, or when it equals the array length. Edge cases to test: one array is empty, `k = 1`, `k = n + m`, and duplicate values. The solution runs in `O(log(min(n, m)))` time with `O(1)` extra space.

</details>
