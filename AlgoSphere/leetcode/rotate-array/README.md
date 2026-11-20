# Rotate Array

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/rotate-array/) · Pattern: **Array reversal (three reverses)** · ✅ Solved in C++

> Shift every element of `nums` k positions to the right, with the last elements wrapping around to the front, modifying the array in place.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [My solution](#my-solution) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "rotate the array to the right by k steps" with k up to 10^5 while n can be as small as 1 | k may exceed n, so only `k % n` matters. |
| Output [5,6,7,1,2,3,4] is the last k block followed by the first n-k block | the task is swapping two contiguous blocks, which reversals can do. |
| Follow-up "in-place with O(1) extra space" | rules out a copy array and points to reversal or cyclic replacement. |
| Element at index i lands at index (i + k) % n | a direct index-mapping formula exists, so each element needs to move only once. |

### What the constraints tell you

n and k are both up to 10^5. Rotating one step at a time, k times, costs O(n·k) ≈ 10^10 operations, far too slow. O(n) ≈ 10^5 is trivial, so the target is O(n) time, and O(1) space for the follow-up.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most literal way to do this?**

<details>
<summary>Answer</summary>

Follow the example: pop the last element and insert it at the front, k times. Each step shifts all n elements, giving O(n·k).

</details>

**Q2. Does k = 10^5 really mean 10^5 rotations?**

<details>
<summary>Answer</summary>

No. Rotating by n returns the original array, so replace k with `k % n`. For nums = [1,2], k = 3 this becomes k = 1.

</details>

**Q3. Can I compute each element's final position directly?**

<details>
<summary>Answer</summary>

Yes. `nums[i]` moves to index `(i + k) % n`. Writing into a second array of size n does it in one pass, but that uses O(n) extra space.

</details>

**Q4. How does the result relate to the original in terms of blocks?**

<details>
<summary>Answer</summary>

Split [1,2,3,4,5,6,7] into A = [1,2,3,4] (first n-k) and B = [5,6,7] (last k). The answer is B followed by A, so the problem is swapping two adjacent blocks of different lengths.

</details>

**Q5. How can I swap two adjacent blocks in place?**

<details>
<summary>Answer</summary>

Reversing the whole array gives reverse(B) followed by reverse(A): [7,6,5,4,3,2,1]. Reversing each block back in place then yields B followed by A: [5,6,7,1,2,3,4]. Each reverse is a two-pointer swap using O(1) space.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Rotate one step k times](#1-brute-force-rotate-one-step-k-times) | `O(n·k)` | `O(1)` |
| 2 | [Better: Extra array with index mapping](#2-better-extra-array-with-index-mapping) | `O(n)` | `O(n)` |
| 3 | [Optimal: Three reversals](#3-optimal-three-reversals) | `O(n)` | `O(1)` |

### 1. Brute force: Rotate one step k times

> **Where you start:** It literally simulates the problem statement's explanation, one right-shift per step.

**Idea.** In each of k rounds, save the last element, shift every other element one index right, and put the saved value at index 0. After k rounds every element has moved k places right with wraparound. Using `k % n` rounds avoids redundant full cycles.

**Steps**

1. Set k = k % n.
2. Repeat k times:
3. Save temp = nums[n-1].
4. For i from n-1 down to 1, set nums[i] = nums[i-1].
5. Set nums[0] = temp.

**Complexity:** time `O(n·k)`, space `O(1)`. The nested shifting dominates: each of up to k rounds touches all n elements. Only one temp variable is used.

**Why move on:** With n near 10^5 and k % n near 10^5, this is about 10^10 element moves. That times out even though it is in place.

### 2. Better: Extra array with index mapping

> **How you get here:** The brute force moves each element k times, but its final index `(i + k) % n` is known up front, so it can be placed once.

**Idea.** Allocate `res` of size n and set `res[(i + k) % n] = nums[i]` for every i, then copy `res` back into nums. This is correct because rotating right by k is exactly the bijection i → (i + k) mod n. Each element is written once.

**Steps**

1. Let n = nums.length and k = k % n.
2. Create res of length n.
3. For each i, set res[(i + k) % n] = nums[i].
4. Copy res back into nums element by element.

**Complexity:** time `O(n)`, space `O(n)`. Two linear passes, one to fill res and one to copy back, dominate. The res array uses n extra slots.

**Why move on:** Time is optimal, but the O(n) buffer fails the follow-up's O(1) extra space requirement.

### 3. Optimal: Three reversals

> **How you get here:** The buffer is needed only because we write elements into fresh slots. Seeing the answer as the block swap A·B → B·A lets reversals rearrange the blocks in place.

**Idea.** Let A be the first n-k elements and B the last k. Reversing the whole array gives rev(B)·rev(A), with each block already in its final region but backwards. Reversing the first k elements and then the last n-k elements restores each block's order, giving B·A. Each reverse is a two-pointer swap, so no buffer is needed.

**Steps**

1. Let n = nums.length and k = k % n. If k is 0, stop.
2. Reverse nums[0..n-1].
3. Reverse nums[0..k-1].
4. Reverse nums[k..n-1].
5. Each reverse: put pointers at both ends, swap, move them inward until they meet.

**Complexity:** time `O(n)`, space `O(1)`. Each element is swapped about twice across the three reversals, so about 2n operations. Only two pointers and a swap temp are used.

**Why this is the best:** Every element must be written at least once, so O(n) time and O(1) space cannot be beaten. Cyclic replacement (following i → (i+k)%n cycles, gcd(n,k) of them) also achieves this with fewer writes, but its cycle handling is easy to get wrong.

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-20 |

For comparison, the optimal approach (Three reversals) runs in `O(n)` time and `O(1)` space.

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        
    }
};
```

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [1,2,3,4,5]<br>k = 2 | [4,5,1,2,3] | Basic rotation of odd-length array by 2. |
| nums = [10,20,30,40,50,60]<br>k = 4 | [30,40,50,60,10,20] | Rotation where k shares a common factor with n (cyclic replacement check). |
| nums = [3,-2,7,0,5]<br>k = 1 | [5,3,-2,7,0] | Single-step rotation with mixed signs and zero. |
| nums = [1,2,3,4,5,6,7,8]<br>k = 5 | [4,5,6,7,8,1,2,3] | Rotation by more than half the length. |
| nums = [9,8,7]<br>k = 7 | [8,7,9] | k larger than length requires k mod n (7 mod 3 = 1). |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | nums = [42]<br>k = 100000 | [42] | Any k leaves array unchanged. |
| Zero steps | nums = [1,2,3,4]<br>k = 0 | [1,2,3,4] | Array unchanged. |
| k equals length | nums = [1,2,3,4]<br>k = 4 | [1,2,3,4] | Full rotation returns original. |
| Extreme values | nums = [-2147483648,2147483647]<br>k = 1 | [2147483647,-2147483648] | 32-bit min and max swapped. |
| All equal | nums = [5,5,5,5]<br>k = 3 | [5,5,5,5] | Rotation has no visible effect. |
| Maximum k | nums = [1,2,3,4,5,6]<br>k = 100000 | [3,4,5,6,1,2] | 100000 mod 6 = 4; a huge n=10^5 array with k=10^5 should also be tested for O(n) time. |

## Mistakes and edge cases

**Common mistakes**

- Forgetting `k % n`. With nums = [1,2], k = 3, the reverse of indices 0..k-1 runs out of bounds.
- Reversing the blocks in the wrong order or with wrong lengths, for example reversing the first n-k elements first. That rotates left instead of right.
- Returning a new array instead of modifying nums. LeetCode checks the original array, and reassigning a local reference does not change it.
- In cyclic replacement, assuming one cycle covers all elements. When gcd(n,k) > 1 (for example n = 6, k = 2) some elements are never moved unless you start new cycles.

**Edge cases to check**

- k = 0 or k a multiple of n: the array must stay unchanged, and `k % n = 0` should exit early or reverse harmlessly.
- k > n (for example n = 4, k = 6): you must reduce k to 2, or indexing breaks.
- n = 1: any k gives the same array, and `k % 1 = 0`.
- gcd(n,k) > 1 (for example [1,2,3,4,5,6], k = 2): this breaks naive single-cycle juggling, while reversal handles it uniformly.
- Values at the int extremes (-2^31, 2^31-1): only swaps happen, so there is no overflow risk. Never use arithmetic-based swaps like a = a + b.

## Practice next

- [Rotate List](https://leetcode.com/problems/rotate-list/) · Same right rotation by k with `k % length`, on a linked list. You find the new tail and reconnect it.
- [Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/) · Same trick: reverse the whole sequence, then reverse each piece to fix its internal order.
- [Rotate String](https://leetcode.com/problems/rotate-string/) · Asks whether one string is a rotation of another. It uses the same block-swap view of rotation (s + s contains every rotation).
- [Rotate Image](https://leetcode.com/problems/rotate-image/) · In-place rotation achieved by composing simple reversible transforms (transpose, then reverse each row).

## Takeaways

- Rotation is periodic, so reduce the shift with `k % n` before doing anything.
- Swapping two adjacent blocks A·B → B·A in place takes three reversals: reverse all, then reverse each part.
- When an element's final index is a closed-form formula, place it directly instead of simulating steps. Then ask whether reversals or cycles can remove the extra buffer.
- Composing simple in-place operations (reverse, transpose) often achieves a complex rearrangement with O(1) space.
