# Max Circular Subarray Sum

**GeeksforGeeks** · **Hard** · [Open the problem](https://www.geeksforgeeks.org/problems/max-circular-subarray-sum-1587115620/1)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a circular array arr[] of integers, find the maximum possible sum of a non-empty subarray. In a circular array, the subarray can start at the end and wrap around to the beginning. Return the maximum non-empty subarray sum, considering both non-wrapping and wrapping cases.

Examples:

Input: arr[] = [8, -8, 9, -9, 10, -11, 12]
Output: 22
Explanation: Starting from the last element of the array, i.e, 12, and moving in a circular fashion, we have max subarray as 12, 8, -8, 9, -9, 10, which gives maximum sum as 22.

Input: arr[] = [10, -3, -4, 7, 6, 5, -4, -1]
Output: 23
Explanation: Maximum sum of the circular subarray is 23. The subarray is [7, 6, 5, -4, -1, 10].

Input: arr[] = [5, -2, 3, 4]
Output: 12
Explanation: The circular subarray [3, 4, 5] gives the maximum sum of 12.

Constraints:
0 ≤ arr.size() ≤ 10^5
-10^4 ≤ arr[i] ≤ 10^4
```

</details>

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| arr = [3,-1,2,-1] | 4 | Both the non-wrapping subarray [3,-1,2] and the wrapping subarray [2,-1,3] achieve the maximum sum. |
| arr = [4,-5,6,7,-8,9] | 21 | Wrapping around via [9,4,-5,6,7] excludes the single large negative -8 and beats the non-wrapping max of 14. |
| arr = [-2,4,-1,5,-3] | 8 | Non-wrapping subarray [4,-1,5] gives a strictly larger sum than any wrapping subarray. |
| arr = [1,-2,3,-2] | 3 | Single positive element [3] outweighs wrapping around through negative neighbors when total sum is zero. |
| arr = [2,1,-5,4,-3,1,-3,4,-1] | 6 | Wrapping subarray [4,-1,2,1] avoids a multi-element negative middle segment [-5,4,-3,1,-3] of sum -6. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | arr = [-10] | -10 | Minimum non-empty array with a negative value must return that element rather than 0. |
| All negative | arr = [-5,-2,-8,-1,-4] | -1 | Total minus minimum subarray equals 0, so the algorithm must return the largest negative element. |
| All positive | arr = [1,2,3,4,5] | 15 | Maximum circular subarray is the entire array without wrapping twice. |
| All zeros | arr = [0,0,0,0] | 0 | Every non-empty subarray sums to 0. |
| Zeros and negatives | arr = [0,-3,0,-2,0] | 0 | Maximum sum is 0 from a single zero element rather than a negative total. |
| Boundary values | arr = [10000,-10000,10000,10000] | 30000 | Uses constraint extremes -10^4 and 10^4 wrapping around to sum 30000 (a large 10^5-element array of 10^4s reaches 10^9). |
