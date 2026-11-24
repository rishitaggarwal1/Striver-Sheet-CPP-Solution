# Maximum Subarray With Equal Products

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/maximum-subarray-with-equal-products/)

**Contents:** [Problem](#problem) · [Hints](#hints) · [Test cases](#test-cases)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given an array of positive integers nums.

An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:

- prod(arr) is the product of all elements of arr.

- gcd(arr) is the GCD of all elements of arr.

- lcm(arr) is the LCM of all elements of arr.

Return the length of the longest product equivalent subarray of nums.

Example 1:

Input: nums = [1,2,1,2,1,1,1]

Output: 5

Explanation:

The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.

Example 2:

Input: nums = [2,3,4,5,6]

Output: 3

Explanation:

The longest product equivalent subarray is [3, 4, 5].

Example 3:

Input: nums = [1,2,3,1,4,5,1]

Output: 5

Constraints:

- 2 <= nums.length <= 100

- 1 <= nums[i] <= 10
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Among all contiguous pieces of the array, find the longest one where multiplying every element together gives the same number as the LCM of the piece times its GCD.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Any subarray of length 2 always works, because for two numbers `a*b = lcm(a,b)*gcd(a,b)`. So the answer is at least 2. Notice also that values are tiny (at most 10), and 1s never change the product or the LCM.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n <= 100`, there are only about 5000 subarrays, so checking every one is fine. You can extend each subarray one element at a time and update its product, GCD and LCM in constant time, giving `O(n^2)` overall. The only risk is that the product can grow huge.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is brute-force enumeration of subarrays with incremental (running) aggregates. Fix a start index, sweep the end index to the right, and keep the product, GCD and LCM up to date as you go.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

The product can never be smaller than `lcm * gcd`, and the LCM of numbers up to 10 is at most 2520. So once the product passes a safe bound (such as `2520 * 10`), no longer subarray from that start can match, and you can stop extending it. This keeps the numbers small.

</details>

<details>
<summary>Hint 6 · What to track</summary>

For a fixed start `i`, track three running values for the subarray `nums[i..j]`: `prod`, the product so far; `g`, the GCD so far; and `l`, the LCM so far. Also keep a global `best` for the longest valid length found.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set best = 2.
For each start i, set prod, g and l from nums[i].
For each end j > i, multiply prod by nums[j].
Update g = gcd(g, nums[j]) and l = lcm(l, nums[j]).
If prod == l * g, set best = max(best, j - i + 1).
If prod exceeds the bound, stop this start and move on to the next i.
Return best.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is computing the LCM safely: use `l / gcd(l, x) * x`, and stop early when the product grows too large. A long run of 1s still works, because 1s never change prod or lcm. Remember that a single element `x` fails unless `x == 1`, which is why the answer starts at 2. Time is `O(n^2 log 10)`, effectively `O(n^2)`, and space is `O(1)`.

</details>

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [2,4,8] | 2 | Powers of two share factors, so only pairs qualify. |
| nums = [3,5,7,2] | 4 | Pairwise coprime values make the whole array valid. |
| nums = [6,10,15] | 2 | gcd of all three is 1 but they are not pairwise coprime, so the triple fails. |
| nums = [1,1,1,1] | 4 | All ones form a valid array. |
| nums = [2,3,1,4,5,6] | 4 | The best window is [3,1,4,5] in the middle. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum length | nums = [1,1] | 2 | Two ones. |
| Maximum values | nums = [10,10] | 2 | Any length-2 subarray is always product equivalent. |
| Duplicates | nums = [2,2,2] | 2 | The triple gives 8 versus 4, so only pairs qualify. |
| All equal values greater than 1 | nums = [7,7,7,7,7] | 2 | Answer stays at 2. |
| Whole array valid | nums = [1,2,3,5,7,1,1] | 7 | Ones mixed with distinct primes. |
| Minimum length with non-coprime pair | nums = [2,4] | 2 | Still valid since a*b equals lcm*gcd. |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
