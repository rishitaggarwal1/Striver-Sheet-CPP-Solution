# Maximum Subarray With Equal Products

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/maximum-subarray-with-equal-products/) · Pattern: **Prime-exponent reasoning + sliding window**

> Find the longest contiguous subarray of `nums` whose product equals its LCM times its GCD.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| `nums[i] <= 10` | only the primes 2, 3, 5, 7 can appear, and the product only needs to be tracked up to a small bound (LCM of 1..10 is 2520, so `lcm*gcd <= 25200`). |
| `prod(arr) == lcm(arr) * gcd(arr)` | compare prime exponents. Per prime, the product gives the sum of exponents, while lcm*gcd gives only max + min. |
| Example 1 answer `[1,2,1,1,1]` contains many 1s and a single 2 | elements that share no prime factor (pairwise coprime) are what make a subarray valid. |
| "longest subarray" plus a condition that breaks once a prime repeats | a sliding window that shrinks from the left, like longest substring without repeating characters. |

### What the constraints tell you

n <= 100, so even O(n^3) ≈ 10^6 operations is fine, and any approach passes. The real danger is overflow: the product of 100 values up to 10 is around 10^100. The instructive target is an O(n) window over the four primes 2, 3, 5, 7.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most literal approach?**

<details>
<summary>Answer</summary>

Try every subarray `[l..r]`, compute its product, gcd and lcm, and check equality. With n = 100 that is only about 5000 subarrays.

</details>

**Q2. What breaks in the literal approach?**

<details>
<summary>Answer</summary>

The product overflows 64-bit integers quickly. However, lcm*gcd can never exceed 2520*10 = 25200, and the product only grows as `r` increases. So once the product passes 25200, no longer subarray from this `l` can be valid and we can stop.

</details>

**Q3. What does the equation mean prime by prime?**

<details>
<summary>Answer</summary>

For a prime p with exponents e_1..e_k across the subarray, the product contributes sum(e_i) and lcm*gcd contributes max(e_i) + min(e_i). These are equal exactly when every exponent except the largest and smallest is zero.

</details>

**Q4. What does that force when the length k >= 3?**

<details>
<summary>Answer</summary>

If min > 0, every element has p, so a middle exponent is positive and the equation fails. So min = 0 and all the middle exponents are 0, meaning at most one element is divisible by p. A length-3+ subarray is valid exactly when its elements are pairwise coprime.

</details>

**Q5. What about length 2?**

<details>
<summary>Answer</summary>

For two numbers, a*b = lcm(a,b)*gcd(a,b) always holds. So the answer is at least 2 even for arrays like `[2,4]`, and the final answer is max(2, longest pairwise-coprime window).

</details>

**Q6. How do we find the longest pairwise-coprime window fast?**

<details>
<summary>Answer</summary>

Each prime 2, 3, 5, 7 may appear in at most one element of the window. Slide `r` forward and add `nums[r]`'s primes; while some prime is now used twice, remove `nums[l]` and advance `l`. This mirrors 'no repeated characters', where the 'characters' are the primes.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Recompute every subarray](#1-brute-force-recompute-every-subarray) | `O(n^3)` | `O(1)` |
| 2 | [Better: Incremental extension with early break](#2-better-incremental-extension-with-early-break) | `O(n^2 log 10)` | `O(1)` |
| 3 | [Optimal: Sliding window over primes 2,3,5,7](#3-optimal-sliding-window-over-primes-2357) | `O(n)` | `O(1)` |

### 1. Brute force: Recompute every subarray

> **Where you start:** The definition hands you three functions to compare, so the first instinct is to evaluate them on every subarray.

**Idea.** For every pair (l, r), compute the product, gcd and lcm of `nums[l..r]` from scratch, using big integers or a capped product. Record the length whenever product == lcm*gcd. This is correct because it checks the definition directly on every candidate.

**Steps**

1. Loop `l` from 0 to n-1.
2. Loop `r` from `l` to n-1.
3. Walk `nums[l..r]` to compute the product, gcd and lcm.
4. If product == lcm*gcd, update the best length with r-l+1.
5. Return the best length.

**Pseudocode**

```text
 1 │ function maxLength(nums):
 2 │   n ← length(nums)
 3 │   best ← 0
 4 │   CAP ← 1000000  // larger than any possible lcm*gcd (2520*10 = 25200)
 5 │   for l ← 0 to n-1:
 6 │     for r ← l to n-1:
 7 │       prod ← 1
 8 │       g ← 0  // gcd(0, x) = x, so 0 is the neutral start
 9 │       lc ← 1  // lcm(1, x) = x
10 │       for k ← l to r:  // recompute everything from scratch
11 │         prod ← min(prod * nums[k], CAP)  // cap so the product never overflows; a capped value can never match
12 │         g ← gcd(g, nums[k])
13 │         lc ← lcm(lc, nums[k])
14 │       if prod = lc * g:
15 │         best ← max(best, r - l + 1)
16 │   return best
```

**Time complexity: `O(n^3)`**

| Part | Cost | Why |
| --- | --- | --- |
| Pair loops over (l, r) (lines 5-6) | n(n+1)/2 pairs | Every contiguous subarray is one (l, r) pair with l ≤ r. |
| Inner walk over nums[l..r] (lines 10-13) | (r-l+1) iterations × O(log 10) per gcd/lcm | Product, gcd and lcm are rebuilt element by element for each subarray. With values at most 10, a gcd costs only a few steps. |
| Check and update (lines 14-15) | n(n+1)/2 × O(1) | This is one comparison per subarray. |

- **Adding it up:** Σ over all subarrays of their length = n(n+1)(n+2)/6 ≈ n^3/6 = O(n^3). The O(n^2) checks are dominated by this.
- **At the maximum input:** n = 100 → 100·101·102/6 = 171,700 inner steps, which finishes instantly.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| Scalars n, best, CAP, l, r, k, prod, g, lc (lines 2-13) | O(1) | Only a fixed number of counters and accumulators are kept, no matter how large n is. |

- **Adding it up:** This is a constant number of variables, so O(1).
- **Not counted:** The input array is not counted.

**Dry run** on `nums = [1,2,1,2,1,1,1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n is 7 and best starts at 0. | `n = 7`<br>`best = 0`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` |
| 2 | 4 | The cap is set to 10^6. Any product that hits it is far above the largest possible lcm*gcd, so it can never pass the check. | `CAP = 1000000` |
| 3 | 13 | l=0, r=0: the walk covers only nums[0]=1, giving prod=1, g=1, lc=1. | `l = 0`<br>`r = 0`<br>`k = 0`<br>`prod = 1`<br>`g = 1`<br>`lc = 1`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→0, k→0) |
| 4 | 15 | 1 = 1*1, so [1] is product equivalent and best becomes 1. | `best = 1`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→0) |
| 5 | 15 | l=0, r=1: the walk over [1,2] gives prod=2, g=1, lc=2. Since 2 = 2*1, best becomes 2. | `best = 2`<br>`r = 1`<br>`k = 1`<br>`prod = 2`<br>`lc = 2`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→1) |
| 6 | 15 | l=0, r=2: [1,2,1] gives prod=2, g=1, lc=2. It matches, so best becomes 3. | `best = 3`<br>`r = 2`<br>`k = 2`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→2) |
| 7 | 13 | l=0, r=3: after k=3 the walk over [1,2,1,2] holds prod=4, g=1, lc=2. | `r = 3`<br>`k = 3`<br>`prod = 4`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→3, k→3) |
| 8 | 14 | 4 ≠ 2*1, so this subarray is skipped. The remaining r=4..6 for l=0 also contain both 2s and fail the same way. | `nums = [1, 2, 1, 2, 1, 1, 1]` (l→0, r→3) |
| 9 | 13 | l=1, r=1: the single element [2] gives prod=2, g=2, lc=2. | `l = 1`<br>`r = 1`<br>`k = 1`<br>`prod = 2`<br>`g = 2`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→1, r→1, k→1) |
| 10 | 14 | 2 ≠ 2*2 = 4, so [2] alone is not product equivalent. The other subarrays for l=1 are never longer than 3 when they pass, so best stays 3. | `nums = [1, 2, 1, 2, 1, 1, 1]` (l→1, r→1) |
| 11 | 13 | Skipping ahead to l=2, r=6: the walk over [1,2,1,1,1] ends with prod=2, g=1, lc=2. | `l = 2`<br>`r = 6`<br>`k = 6`<br>`g = 1`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→2, r→6, k→6) |
| 12 | 15 | 2 = 2*1, so the check passes and best becomes max(3, 6-2+1) = 5. | `best = 5`<br>`nums = [1, 2, 1, 2, 1, 1, 1]` (l→2, r→6) |
| 13 | 16 | The remaining starts l=3..6 can only make subarrays of length 4 or less, so best stays 5 and is returned. | `nums = [1, 2, 1, 2, 1, 1, 1]` |

**Result:** 5. Every subarray was tested directly against the definition, and the longest one that passes is [1,2,1,1,1] (prod 2 = lcm 2 × gcd 1).

**C++ solution**

```cpp
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int best = 0;                       // longest product-equivalent length found so far
        const long long CAP = 1000000;      // > max lcm*gcd (2520*10), so a capped product never matches
        for (int l = 0; l < n; ++l) {       // every start index
            for (int r = l; r < n; ++r) {   // every end index
                long long p = 1;            // product of nums[l..r], capped
                long long g = 0;            // gcd(0, x) = x, neutral start
                long long lc = 1;           // lcm(1, x) = x, neutral start
                for (int k = l; k <= r; ++k) {          // recompute from scratch
                    p = min(p * nums[k], CAP);         // cap keeps p small and avoids overflow
                    g = std::gcd(g, (long long)nums[k]);
                    lc = std::lcm(lc, (long long)nums[k]); // at most 2520 for values <= 10
                }
                if (p == lc * g)                       // definition of product equivalent
                    best = max(best, r - l + 1);
            }
        }
        return best;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int best = 0;                       // longest product-equivalent length found so far
        const long long CAP = 1000000;      // > max lcm*gcd (2520*10), so a capped product never matches
        for (int l = 0; l < n; ++l) {       // every start index
            for (int r = l; r < n; ++r) {   // every end index
                long long p = 1;            // product of nums[l..r], capped
                long long g = 0;            // gcd(0, x) = x, neutral start
                long long lc = 1;           // lcm(1, x) = x, neutral start
                for (int k = l; k <= r; ++k) {          // recompute from scratch
                    p = min(p * nums[k], CAP);         // cap keeps p small and avoids overflow
                    g = std::gcd(g, (long long)nums[k]);
                    lc = std::lcm(lc, (long long)nums[k]); // at most 2520 for values <= 10
                }
                if (p == lc * g)                       // definition of product equivalent
                    best = max(best, r - l + 1);
            }
        }
        return best;
    }
};

int main() {
    vector<vector<int>> tests = {{1,2,1,2,1,1,1}, {2,3,4,5,6}, {1,2,3,1,4,5,1}};
    vector<int> expected = {5, 3, 5};
    for (size_t i = 0; i < tests.size(); ++i) {
        Solution s;
        int out = s.maxLength(tests[i]);
        cout << "Example " << i + 1 << ": output = " << out << ", expected = " << expected[i] << "\n";
    }
    return 0;
}
```

</details>

**Why move on:** It wastes O(n) per subarray recomputing values that differ from the previous subarray by a single element. It also needs care to avoid overflow, and it would not scale past a few hundred elements.

### 2. Better: Incremental extension with early break

> **How you get here:** `nums[l..r]` differs from `nums[l..r-1]` by one element, so product, gcd and lcm can all be updated in O(1)-ish steps instead of rescanned.

**Idea.** Fix `l` and extend `r`, updating `prod *= nums[r]`, `g = gcd(g, nums[r])` and `L = lcm(L, nums[r])`. Since lcm*gcd <= 2520*10 and the product never decreases, stop extending once `prod` exceeds that bound. This keeps numbers small and stays correct, because no further extension can satisfy the equation.

**Steps**

1. For each `l`, set prod = 1, g = 0, L = 1.
2. Extend `r` from `l`, updating prod, g and L with `nums[r]`.
3. If prod == L*g, update the best length with r-l+1.
4. If prod > 25200, break out of the inner loop.
5. Return the best length.

**Complexity:** time `O(n^2 log 10)`, space `O(1)`. There are O(n^2) (l, r) pairs, each needing one gcd/lcm step on tiny numbers. In practice the early break triggers after a handful of elements greater than 1. Only running scalars are kept.

**Why move on:** It is still quadratic in the worst case, for example an array of many 1s, because it never exploits the structure of the condition. It works here, but it ignores the fact that validity means pairwise coprime.

### 3. Optimal: Sliding window over primes 2,3,5,7

> **How you get here:** Prime-exponent analysis shows a length-3+ subarray is valid iff no prime divides two of its elements, so validity is monotone and fits a two-pointer window.

**Idea.** Keep a count for each of the primes 2, 3, 5, 7 over the window `nums[l..r]`. Adding `nums[r]` increments the counts of its primes; while any count exceeds 1, decrement the counts for `nums[l]` and advance `l`. Every window kept this way is pairwise coprime, hence valid, and it is the longest valid window ending at `r`. Length-2 subarrays are always valid, so return max(2, best).

**Steps**

1. Set up counts for primes 2, 3, 5, 7, with l = 0 and best = 0.
2. For each r, add 1 to the count of each prime dividing `nums[r]`.
3. While any prime count is greater than 1, subtract `nums[l]`'s primes and increment `l`.
4. Update best with r-l+1.
5. Return max(best, 2).

**Complexity:** time `O(n)`, space `O(1)`. Each index enters and leaves the window at most once, and each step checks only 4 primes, so the total is linear. Memory is a fixed array of 4 counters.

**Why this is the best:** Every element must be read once, so O(n) cannot be beaten. The cost is the extra mathematical step (pairwise-coprime equivalence plus the special case for length 2) that you must justify yourself.

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

## Mistakes and edge cases

**Common mistakes**

- Multiplying the product without a cap. 100 elements of value 10 overflow any fixed-width integer and give false equalities or crashes.
- Using only the pairwise-coprime window and forgetting that any length-2 subarray is valid. For `[2,4,8]` the window gives 1, but the answer is 2.
- Breaking the inner loop at the first invalid subarray of length 1 or 2. Invalidity only becomes permanent once the length is 3 or more, or once prod > 25200.
- Writing the shrink step as a single `if` instead of a `while`, which can leave a shared prime in the window.

**Edge cases to check**

- `nums = [2,4]`: no coprime pair, but the answer is 2 because a*b = lcm*gcd always holds for two elements.
- All ones, e.g. `[1,1,...,1]`: the whole array is valid, so the answer is n. This tests that 1 contributes no primes.
- Value 6 or 10: these carry two primes, so adding 6 must block both 2 and 3 in the window.
- `[2,3,4,5,6]` (Example 2): the window must shrink correctly when 4 conflicts with 2, giving `[3,4,5]` with length 3.

## Practice next

- [Longest Nice Subarray](https://leetcode.com/problems/longest-nice-subarray/) · Same structure: the longest window where no bit is shared by two elements. Here no prime is shared.
- [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · The classic shrink-on-duplicate sliding window. Primes play the role of characters.
- [Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/) · A sliding window driven by a product that only grows as the window extends, like the early-break bound in the Better approach.

## Takeaways

- When a condition involves product, gcd and lcm, rewrite it per prime as sum vs max+min of exponents. It often collapses into a simple combinatorial rule.
- Small value bounds (`nums[i] <= 10`) cap quantities like the LCM, which lets you prune or avoid overflow.
- Once a property holds for a window and all its sub-windows (here, 'pairwise coprime'), the longest-window problem becomes two pointers with counts.
- Always check tiny lengths separately. Identities like a*b = lcm*gcd make length 2 special.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
