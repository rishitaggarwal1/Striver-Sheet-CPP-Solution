# Count Inversions

**GeeksforGeeks** · **Medium** · [Open the problem](https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given an array of integers arr[]. You have to find the Inversion Count of the array. Inversion count is the number of pairs of elements (i, j) such that i < j and arr[i] > arr[j].

Examples:

Input: arr[] = [2, 4, 1, 3, 5]
Output: 3
Explanation: The sequence 2, 4, 1, 3, 5 has three inversions (2, 1), (4, 1), (4, 3).

Input: arr[] = [2, 3, 4, 5, 6]
Output: 0
Explanation: As the sequence is already sorted so there is no inversion count.

Input: arr[] = [10, 10, 10]
Output: 0
Explanation: As all the elements of array are same, so there is no inversion count.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to count how many pairs of positions have a larger number appearing before a smaller one. Equal values do not count, and a sorted array has zero such pairs.

</details>

<details>
<summary>Hint 2 · Observation</summary>

A sorted array gives 0 and a strictly decreasing array of length `n` gives the maximum, `n*(n-1)/2`. The count is really a measure of how far the array is from sorted, which suggests that the act of sorting could reveal it.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

GeeksforGeeks allows `n` up to about `10^5`, so checking every pair in `O(n^2)` means roughly `10^10` operations, which is too slow. Aim for `O(n log n)`, and keep the answer in a 64-bit integer, since it can reach about `5*10^9`.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is divide and conquer, specifically a modified merge sort. Every inversion either lies inside the left half, inside the right half, or crosses between them. The first two kinds are counted recursively, and the crossing kind can be counted during the merge.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

While merging two sorted halves, suppose the current right element is strictly smaller than the current left element `L[i]`. Then it is also smaller than every remaining element of the left half, because that half is sorted. So it forms `(size of left half - i)` inversions in one step.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track a running inversion total, a temporary buffer for merging, and two pointers `i` and `j` into the sorted left and right halves. The value `mid - i + 1` (or left length minus `i`) is how many left elements are still waiting, and each of them is greater than the right element being placed.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Split the array at `mid` and recursively sort and count each half.
Merge the halves with pointers `i` (left) and `j` (right).
If `left[i] <= right[j]`, place `left[i]` and advance `i` (no inversions).
Otherwise place `right[j]`, add the number of remaining left elements to the count, and advance `j`.
Copy any leftovers, then write the merged result back.
Return left count + right count + merge count.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is using `<=` for the comparison, so equal elements (as in `[10,10,10]`) are not counted as inversions. Handle arrays of length 0 or 1 by returning 0, and use a 64-bit counter. Time is `O(n log n)` and extra space is `O(n)` for the buffer plus `O(log n)` for recursion. A Fenwick tree over compressed values is an equally fast alternative.

</details>

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
