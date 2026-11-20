# Climbing Stairs

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/climbing-stairs/) · Pattern: **1D DP (Fibonacci recurrence)**

> Count the ordered sequences of 1-steps and 2-steps whose total is exactly `n`.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Example 1:

Input: n = 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

Example 2:

Input: n = 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step

Constraints:

- 1 <= n <= 45
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You start on the ground and must land exactly on step `n`, moving up 1 or 2 steps at a time. Count how many different ordered sequences of moves do that; `1 + 2` and `2 + 1` count as two different ways.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Write out the answers for small `n`: `n = 1` gives 1, `n = 2` gives 2, `n = 3` gives 3, and by hand `n = 4` gives 5 (`1+1+1+1`, `1+1+2`, `1+2+1`, `2+1+1`, `2+2`). Look at how each answer relates to the two answers just before it.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

`n` is at most 45, which is tiny, but the answer for `n = 45` is 1,836,311,903, so listing every sequence one by one is hopeless. You need to count without enumerating; anything linear in `n` is instant, while anything exponential in `n` is not.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is one-dimensional dynamic programming with a Fibonacci-style recurrence: the count for a staircase of height `n` is built from the counts for shorter staircases, and those shorter counts are reused many times.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Group the ways by their last move. A way to reach step `n` either ends with a 1-step from step `n − 1` or with a 2-step from step `n − 2`, and no way is in both groups, so `ways(n) = ways(n − 1) + ways(n − 2)`.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Let `ways(i)` be the number of ways to stand exactly on step `i`, with `ways(0) = 1` (no moves) and `ways(1) = 1`. Because `ways(i)` reads only the two values below it, you only need two numbers: `prev1 = ways(i − 1)` and `prev2 = ways(i − 2)`.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `prev2` to 1 for step 0 and `prev1` to 1 for step 1.
If `n` is 1, the answer is 1.
For each step `i` from 2 up to `n`:
Let `curr` be `prev1 + prev2`.
Move `prev1` into `prev2`, then `curr` into `prev1`.
After the last step, `curr` is the answer.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest part is the slide order: copy `prev1` into `prev2` before overwriting `prev1`, or the old value is lost. `n = 1` must return 1 without entering the loop, and `n = 45` gives 1,836,311,903, just below the `int` limit of 2,147,483,647. Time is `O(n)` and extra space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "Each time you can either climb 1 or 2 steps" | every way has a last move that is one of only two options, so the count splits as `ways(n − 1) + ways(n − 2)`. |
| "In how many distinct ways" | we need a count, not the list of ways, so we can combine counts of smaller staircases instead of enumerating sequences. |
| Example outputs 2 for `n = 2` and 3 for `n = 3`, continuing 5, 8, 13 | each answer is the sum of the previous two, the Fibonacci pattern. |
| "1 <= n <= 45" | the answer tops out at 1,836,311,903, just under `INT_MAX`, and a linear loop of 44 steps is trivial. |

### What the constraints tell you

`n ≤ 45`: plain recursion makes `2·ways(45) − 1 ≈ 3.7·10^9` calls, far too slow, while an `O(n)` loop is 44 additions. The largest answer, 1,836,311,903, fits in a 32-bit `int` (limit 2,147,483,647), so the target is `O(n)` time and ideally `O(1)` space.

### Think it through

Answer each question yourself before opening it.

**Q1. Can I just list every sequence of 1s and 2s that sums to `n`?**

<details>
<summary>Answer</summary>

For `n = 3` that works: `1+1+1`, `1+2`, `2+1`. But the count grows by about 1.6× per extra step and reaches 1,836,311,903 for `n = 45`, so we must count the sequences without listing them.

</details>

**Q2. What can I say about the very last move of any way to reach step `n`?**

<details>
<summary>Answer</summary>

It is either a 1-step from step `n − 1` or a 2-step from step `n − 2`. Those two groups never overlap and together they cover every way.

</details>

**Q3. So how does the answer for `n` relate to smaller staircases?**

<details>
<summary>Answer</summary>

The first group has exactly `ways(n − 1)` members and the second `ways(n − 2)`, so `ways(n) = ways(n − 1) + ways(n − 2)` with `ways(0) = 1` and `ways(1) = 1`. Check: `ways(2) = 2` and `ways(3) = 3` match the examples.

</details>

**Q4. Why is the direct recursion too slow?**

<details>
<summary>Answer</summary>

`ways(n − 2)` is computed once directly and again inside `ways(n − 1)`, and this doubling repeats at every level, giving `2·ways(n) − 1` calls. For `n = 45` that is about 3.7 billion calls.

</details>

**Q5. How many different subproblems are really there?**

<details>
<summary>Answer</summary>

Only `n + 1`: `ways(0)` up to `ways(n)`. Caching each one in `memo` the first time it is computed brings the work down to `O(n)`.

</details>

**Q6. What does computing `ways(i)` actually need?**

<details>
<summary>Answer</summary>

Only `ways(i − 1)` and `ways(i − 2)`. So we can compute the values in increasing `i` and keep just two variables, `prev1` and `prev2`, for `O(n)` time and `O(1)` space.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Plain recursion on the last move](#1-brute-force-plain-recursion-on-the-last-move) | `O(2^n)` | `O(n)` |
| 2 | [Better: Top-down recursion with a memo array](#2-better-top-down-recursion-with-a-memo-array) | `O(n)` | `O(n)` |
| 3 | [Optimal: Bottom-up with two rolling variables](#3-optimal-bottom-up-with-two-rolling-variables) | `O(n)` | `O(1)` |

### 1. Brute force: Plain recursion on the last move

> **Where you start:** Splitting the ways by their final move turns the question straight into a recursive function, so writing `ways(i) = ways(i − 1) + ways(i − 2)` as plain recursion is the first thing anyone tries.

**Idea.** Let `ways(i)` be the number of move sequences that end exactly on step `i`. Every such sequence ends with either a 1-step from step `i − 1` or a 2-step from step `i − 2`, and no sequence ends both ways, so `ways(i) = ways(i − 1) + ways(i − 2)`. The base cases are `ways(0) = 1` (the empty sequence) and `ways(1) = 1` (a single 1-step); together they give `ways(2) = 2` and `ways(3) = 3`, matching both examples. The recursion counts every sequence exactly once, but it never remembers a result, so in Example 2 (`n = 3`) `ways(1)` is computed twice.

**Steps**

1. Treat step 0 as the ground and let `ways(i)` count the move sequences that end exactly on step `i`.
2. If `i` is 0, return 1 for the empty sequence; if `i` is 1, return 1 for the single 1-step.
3. Otherwise count the sequences whose last move is a 1-step by calling `ways(i − 1)`.
4. Count the sequences whose last move is a 2-step by calling `ways(i − 2)`.
5. Return the sum of the two counts, and answer `ways(n)`.

**Pseudocode**

```text
 1 │ function climbStairs(n)
 2 │   return ways(n)  // ways(i) = number of move sequences that end exactly on step i
 3 │ function ways(i)
 4 │   if i = 0
 5 │     return 1  // already on the ground: the empty sequence counts once
 6 │   if i = 1
 7 │     return 1  // only a single 1-step reaches step 1
 8 │   oneBack ← ways(i − 1)  // sequences whose last move is a 1-step from i − 1
 9 │   twoBack ← ways(i − 2)  // sequences whose last move is a 2-step from i − 2
10 │   return oneBack + twoBack  // the two groups never overlap, so add them
```

**Time complexity: `O(2^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Base cases (lines 4-7) | O(1) per call | Two comparisons and a return; every leaf of the call tree ends here. |
| Two recursive calls (lines 8-9) | calls(i) = 1 + calls(i − 1) + calls(i − 2) calls in total | Every non-base call spawns two more and nothing is cached, so identical subtrees are re-expanded. |
| Addition and return (line 10) | O(1) per call | One addition per non-base call. |

- **Adding it up:** calls(0) = calls(1) = 1 and calls(i) = 1 + calls(i − 1) + calls(i − 2) solve to calls(n) = 2·ways(n) − 1 (n = 3: 5 calls, n = 4: 9 calls). ways(n) grows like φ^n with φ ≈ 1.618, so the total is Θ(φ^n) × O(1) ⊆ O(2^n).
- **At the maximum input:** n = 45 → 2 · 1,836,311,903 − 1 ≈ 3.7·10^9 calls, several seconds even in C++, so it gets Time Limit Exceeded.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Recursion stack (lines 8-9) | at most n frames × O(1) | The deepest chain is ways(n) → ways(n − 1) → … → ways(1), and each frame holds only i, oneBack and twoBack. |

- **Adding it up:** The stack is the only thing that grows: O(n).
- **Not counted:** No arrays are allocated. For n = 45 the stack is at most 45 frames deep, so the danger here is time, not stack overflow.

**Dry run** on `n = 3`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | climbStairs(3) calls ways(3), the number of move sequences that end exactly on step 3. | `n = 3`<br>`call stack = [ways(3)] ← top` |
| 2 | 3 | ways(3) is not a base case, so line 8 calls ways(2) to count the ways whose last move is a 1-step from step 2; a new frame is pushed. | `i = 2`<br>`call stack = [ways(3), ways(2)] ← top` |
| 3 | 3 | ways(2) is not a base case, so line 8 calls ways(1) to count the ways whose last move is a 1-step from step 1; a new frame is pushed. | `i = 1`<br>`call stack = [ways(3), ways(2), ways(1)] ← top` |
| 4 | 7 | ways(1) is a base case: the only way to reach step 1 is a single 1-step, so it returns 1. | (no change) |
| 5 | 8 | ways(1) returned 1, so oneBack = 1: 1 way to reach step 2 ends with a 1-step from step 1. | `i = 2`<br>`oneBack = 1`<br>`call stack = [ways(3), ways(2): oneBack=1] ← top` |
| 6 | 3 | Back in ways(2), line 9 calls ways(0) for the 2-step case; a new frame is pushed. | `i = 0`<br>`call stack = [ways(3), ways(2): oneBack=1, ways(0)] ← top` |
| 7 | 5 | ways(0) is a base case: being on the ground already is one way (no moves), so it returns 1. | (no change) |
| 8 | 9 | ways(0) returned 1, so twoBack = 1: 1 way ends with a 2-step from step 0. | `i = 2`<br>`oneBack = 1`<br>`twoBack = 1`<br>`call stack = [ways(3), ways(2): oneBack=1, twoBack=1] ← top` |
| 9 | 10 | ways(2) returns oneBack + twoBack = 1 + 1 = 2; the two groups never overlap, so adding is exact. | (no change) |
| 10 | 8 | ways(2) returned 2, so oneBack = 2: 2 ways to reach step 3 end with a 1-step from step 2. | `i = 3`<br>`oneBack = 2`<br>`call stack = [ways(3): oneBack=2] ← top` |
| 11 | 3 | ways(3) line 9 calls ways(1) for the 2-step case. ways(1) was already solved inside an earlier call, but plain recursion remembers nothing, so it starts over. | `i = 1`<br>`call stack = [ways(3): oneBack=2, ways(1)] ← top` |
| 12 | 7 | ways(1) is a base case: the only way to reach step 1 is a single 1-step, so it returns 1. | (no change) |
| 13 | 9 | ways(1) returned 1, so twoBack = 1: 1 way ends with a 2-step from step 1. | `i = 3`<br>`oneBack = 2`<br>`twoBack = 1`<br>`call stack = [ways(3): oneBack=2, twoBack=1] ← top` |
| 14 | 10 | ways(3) returns oneBack + twoBack = 2 + 1 = 3; the two groups never overlap, so adding is exact. | (no change) |
| 15 | 2 | ways(3) returned 3, so climbStairs returns 3. It took 5 calls, and ways(1) was computed twice: that repeated work is what makes plain recursion exponential. | `n = 3`<br>`call stack = []` |

**Result:** 3: the ways are 1+1+1 and 2+1 (ending with a 1-step, counted by ways(2) = 2) plus 1+2 (ending with a 2-step, counted by ways(1) = 1).

**C++ solution**

```cpp
class Solution {
public:
    int climbStairs(int n) {
        return ways(n); // count the move sequences that end exactly on step n
    }

private:
    // ways(i) = number of distinct sequences of 1-steps and 2-steps that end exactly on step i
    int ways(int i) {
        if (i == 0) return 1;      // already on the ground: the empty sequence counts once
        if (i == 1) return 1;      // only a single 1-step reaches step 1
        int oneBack = ways(i - 1); // sequences whose last move is a 1-step from step i - 1
        int twoBack = ways(i - 2); // sequences whose last move is a 2-step from step i - 2
        return oneBack + twoBack;  // the two groups never overlap, so their sizes add up
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
    int climbStairs(int n) {
        return ways(n); // count the move sequences that end exactly on step n
    }

private:
    // ways(i) = number of distinct sequences of 1-steps and 2-steps that end exactly on step i
    int ways(int i) {
        if (i == 0) return 1;      // already on the ground: the empty sequence counts once
        if (i == 1) return 1;      // only a single 1-step reaches step 1
        int oneBack = ways(i - 1); // sequences whose last move is a 1-step from step i - 1
        int twoBack = ways(i - 2); // sequences whose last move is a 2-step from step i - 2
        return oneBack + twoBack;  // the two groups never overlap, so their sizes add up
    }
};

int main() {
    Solution sol;

    int n1 = 2;
    cout << "Example 1: n = " << n1 << " -> " << sol.climbStairs(n1) << " (expected 2)\n";

    int n2 = 3;
    cout << "Example 2: n = " << n2 << " -> " << sol.climbStairs(n2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why move on:** The bottleneck is recomputing the same subproblems: `n = 45` makes about `3.7·10^9` calls, far beyond the time limit, even though only 46 distinct values `ways(0..45)` exist.

### 2. Better: Top-down recursion with a memo array

> **How you get here:** In the brute-force call tree `ways(i)` depends only on `i`, yet `ways(1)` is solved twice for `n = 3` and the duplicates multiply as `n` grows; there are only `n + 1` distinct arguments, so remembering each answer removes every repeated subtree.

**Idea.** Keep the same recurrence but add an array `memo` of size `n + 1` filled with -1, meaning not computed yet. Base cases `i ≤ 1` still return 1 directly; for larger `i`, check `memo[i]` first and return it if it is set, otherwise compute `ways(i − 1) + ways(i − 2)`, store it in `memo[i]` and return it. This is correct because `ways(i)` is a pure function of `i`, so a cached value is exactly what recomputing would produce. Each state `2..n` is expanded only once, which turns the exponential tree into a chain of `2n − 1` calls.

**Steps**

1. Create `memo` of size `n + 1` filled with -1.
2. In `ways(i)`, return 1 immediately when `i` is 0 or 1.
3. If `memo[i]` is not -1, return the stored value without recursing.
4. Otherwise compute `ways(i − 1) + ways(i − 2)` recursively.
5. Store the sum in `memo[i]` before returning it.
6. Return `ways(n)` from `climbStairs`.

**Pseudocode**

```text
 1 │ function climbStairs(n)
 2 │   memo ← array of size n + 1 filled with −1  // −1 means "not computed yet"
 3 │   return ways(n, memo)
 4 │ function ways(i, memo)
 5 │   if i ≤ 1
 6 │     return 1  // ways(0) = 1 (no moves), ways(1) = 1 (one 1-step)
 7 │   if memo[i] ≠ −1
 8 │     return memo[i]  // already solved: reuse it instead of re-expanding the subtree
 9 │   oneBack ← ways(i − 1, memo)  // last move was a 1-step from i − 1
10 │   twoBack ← ways(i − 2, memo)  // last move was a 2-step from i − 2
11 │   memo[i] ← oneBack + twoBack  // store before returning so later calls are O(1)
12 │   return memo[i]
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Memo allocation (line 2) | n + 1 cells × O(1) | Every cell is set to −1 once. |
| First evaluation of ways(i) for i = 2..n (lines 9-12) | n − 1 states × O(1) | memo[i] is filled before returning, so lines 9-11 never run twice for the same i. |
| Calls answered by a base case or the memo (lines 5-8) | n calls × O(1) | Each of the n − 1 expanded states makes 2 calls, and n of all these calls stop immediately at line 6 or line 8. |

- **Adding it up:** Total calls = 1 + 2(n − 1) = 2n − 1 (n = 4: 7 calls instead of 9), each O(1), plus the O(n) allocation: O(n) + O(n) = O(n).
- **At the maximum input:** n = 45 → 89 calls and 46 memo cells: a few microseconds.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| memo array (line 2) | n + 1 ints | One cell per possible argument 0..n. |
| Recursion stack (lines 9-10) | at most n frames × O(1) | The first descent ways(n) → ways(n − 1) → … → ways(1) is n frames deep. |

- **Adding it up:** O(n) + O(n) = O(n).
- **Not counted:** memo[0] and memo[1] are never written because the base cases answer them; the output is a single int.

**Dry run** on `n = 4 (the examples n = 2 and n = 3 never reach a memo hit, so one step higher shows the cache working)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | memo has n + 1 = 5 cells, all -1 (not computed yet). Nothing is on the call stack yet. | `n = 4`<br>`memo = [-1, -1, -1, -1, -1]`<br>`call stack = []` |
| 2 | 6 | No base case or memo entry applies to ways(4), ways(3) or ways(2), so each pauses at line 9 and calls the next: ways(4) → ways(3) → ways(2) → ways(1). ways(1) is a base case and returns 1. | `i = 1`<br>`memo = [-1, -1, -1, -1, -1]` (i→1)<br>`call stack = [ways(4), ways(3), ways(2), ways(1)] ← top` |
| 3 | 9 | Back in ways(2): ways(1) returned 1, so oneBack = 1. | `i = 2`<br>`oneBack = 1`<br>`memo = [-1, -1, -1, -1, -1]` (i→2)<br>`call stack = [ways(4), ways(3), ways(2): oneBack=1] ← top` |
| 4 | 6 | ways(2) line 10 calls ways(0) for the 2-step case. It is a base case (checked before the memo), so line 6 returns 1. | `i = 0`<br>`memo = [-1, -1, -1, -1, -1]` (i→0)<br>`call stack = [ways(4), ways(3), ways(2): oneBack=1, ways(0)] ← top` |
| 5 | 10 | ways(0) returned 1, so twoBack = 1. | `i = 2`<br>`oneBack = 1`<br>`twoBack = 1`<br>`memo = [-1, -1, -1, -1, -1]` (i→2)<br>`call stack = [ways(4), ways(3), ways(2): oneBack=1, twoBack=1] ← top` |
| 6 | 11 | memo[2] = oneBack + twoBack = 1 + 1 = 2. It is stored before returning, so every later call to ways(2) costs O(1). | `memo = [-1, -1, 2, -1, -1]` (i→2) |
| 7 | 9 | Back in ways(3): ways(2) returned 2, so oneBack = 2. | `i = 3`<br>`oneBack = 2`<br>`memo = [-1, -1, 2, -1, -1]` (i→3)<br>`call stack = [ways(4), ways(3): oneBack=2] ← top` |
| 8 | 6 | ways(3) line 10 calls ways(1) for the 2-step case. It is a base case (checked before the memo), so line 6 returns 1. | `i = 1`<br>`memo = [-1, -1, 2, -1, -1]` (i→1)<br>`call stack = [ways(4), ways(3): oneBack=2, ways(1)] ← top` |
| 9 | 10 | ways(1) returned 1, so twoBack = 1. | `i = 3`<br>`oneBack = 2`<br>`twoBack = 1`<br>`memo = [-1, -1, 2, -1, -1]` (i→3)<br>`call stack = [ways(4), ways(3): oneBack=2, twoBack=1] ← top` |
| 10 | 11 | memo[3] = oneBack + twoBack = 2 + 1 = 3. It is stored before returning, so every later call to ways(3) costs O(1). | `memo = [-1, -1, 2, 3, -1]` (i→3) |
| 11 | 9 | Back in ways(4): ways(3) returned 3, so oneBack = 3. | `i = 4`<br>`oneBack = 3`<br>`memo = [-1, -1, 2, 3, -1]` (i→4)<br>`call stack = [ways(4): oneBack=3] ← top` |
| 12 | 8 | ways(4) line 10 calls ways(2). memo[2] = 2 is already filled, so line 8 returns 2 immediately; without the memo this call would re-expand ways(1) and ways(0). | `i = 2`<br>`memo = [-1, -1, 2, 3, -1]` (i→2)<br>`call stack = [ways(4): oneBack=3, ways(2)] ← top` |
| 13 | 10 | ways(2) returned 2, so twoBack = 2. | `i = 4`<br>`oneBack = 3`<br>`twoBack = 2`<br>`memo = [-1, -1, 2, 3, -1]` (i→4)<br>`call stack = [ways(4): oneBack=3, twoBack=2] ← top` |
| 14 | 11 | memo[4] = oneBack + twoBack = 3 + 2 = 5. It is stored before returning, so every later call to ways(4) costs O(1). | `memo = [-1, -1, 2, 3, 5]` (i→4) |
| 15 | 3 | climbStairs returns ways(4) = 5. Only 7 calls were made (plain recursion needs 9); memo[0] and memo[1] stay -1 because the base cases answer them directly. | `n = 4`<br>`memo = [-1, -1, 2, 3, 5]`<br>`call stack = []` |

**Result:** 5: ways(4) = ways(3) + ways(2) = 3 + 2, and the second request for ways(2) was answered from memo[2] instead of being recomputed.

**C++ solution**

```cpp
class Solution {
public:
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1); // memo[i] = ways(i) once computed; -1 means not computed yet
        return ways(n, memo);
    }

private:
    int ways(int i, vector<int>& memo) {
        if (i <= 1) return 1;              // ways(0) = 1 (no moves) and ways(1) = 1 (one 1-step)
        if (memo[i] != -1) return memo[i]; // already solved: reuse it instead of re-expanding the subtree
        int oneBack = ways(i - 1, memo);   // last move was a 1-step from step i - 1
        int twoBack = ways(i - 2, memo);   // last move was a 2-step from step i - 2
        memo[i] = oneBack + twoBack;       // store before returning so later calls cost O(1)
        return memo[i];
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
    int climbStairs(int n) {
        vector<int> memo(n + 1, -1); // memo[i] = ways(i) once computed; -1 means not computed yet
        return ways(n, memo);
    }

private:
    int ways(int i, vector<int>& memo) {
        if (i <= 1) return 1;              // ways(0) = 1 (no moves) and ways(1) = 1 (one 1-step)
        if (memo[i] != -1) return memo[i]; // already solved: reuse it instead of re-expanding the subtree
        int oneBack = ways(i - 1, memo);   // last move was a 1-step from step i - 1
        int twoBack = ways(i - 2, memo);   // last move was a 2-step from step i - 2
        memo[i] = oneBack + twoBack;       // store before returning so later calls cost O(1)
        return memo[i];
    }
};

int main() {
    Solution sol;

    int n1 = 2;
    cout << "Example 1: n = " << n1 << " -> " << sol.climbStairs(n1) << " (expected 2)\n";

    int n2 = 3;
    cout << "Example 2: n = " << n2 << " -> " << sol.climbStairs(n2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why move on:** It is fast enough for `n ≤ 45`, but it keeps `n + 1` memo cells and up to `n` stack frames even though `ways(i)` only ever reads the two values just below `i`; for a much larger `n` the deep recursion could also overflow the stack.

### 3. Optimal: Bottom-up with two rolling variables

> **How you get here:** The memoised recursion ends up filling `memo[2], memo[3], …, memo[n]` in increasing order, and `memo[i]` reads only `memo[i − 1]` and `memo[i − 2]`; so we can loop upward and keep just the last two values instead of the array and the call stack.

**Idea.** Hold `prev2 = ways(i − 2)` and `prev1 = ways(i − 1)`, starting from `ways(0) = 1` and `ways(1) = 1`. For each `i` from 2 to `n`, compute `curr = prev1 + prev2`, then slide the window: `prev2` takes the old `prev1` and `prev1` takes `curr`. The invariant "before iteration `i`, `prev1 = ways(i − 1)` and `prev2 = ways(i − 2)`" holds at the start and is restored by the slide, so after `i = n` the value `curr` is `ways(n)`. For `n = 1` the loop would not run and `curr` would still be 0, which is why `prev1 = 1` is returned early.

**Steps**

1. Set `prev2 = 1` for `ways(0)` and `prev1 = 1` for `ways(1)`.
2. If `n` is 1, return 1 immediately.
3. For `i` from 2 to `n`, compute `curr = prev1 + prev2`.
4. Copy `prev1` into `prev2`, then `curr` into `prev1`, so they describe steps `i − 1` and `i` for the next round.
5. After the loop, return `curr`, which equals `ways(n)`.

**Pseudocode**

```text
 1 │ function climbStairs(n)
 2 │   prev2 ← 1  // ways(0): one way to be on the ground
 3 │   prev1 ← 1  // ways(1): a single 1-step
 4 │   if n = 1
 5 │     return prev1  // the loop below starts at i = 2
 6 │   curr ← 0  // will hold ways(i)
 7 │   for i ← 2 to n
 8 │     curr ← prev1 + prev2  // a 1-step from i − 1 or a 2-step from i − 2
 9 │     prev2 ← prev1  // must happen before prev1 is overwritten
10 │     prev1 ← curr  // now prev2 = ways(i − 1), prev1 = ways(i)
11 │   return curr  // after i = n, curr = ways(n)
```

**Time complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Initialisation and n = 1 check (lines 2-6) | O(1) | A fixed number of assignments and one comparison. |
| Main loop (lines 7-10) | n − 1 iterations × O(1) | Each iteration does one addition and two copies. |

- **Adding it up:** O(1) + (n − 1) · O(1) = O(n); the loop dominates.
- **Best vs worst case:** Best case n = 1 returns at line 5 without looping; every other n runs exactly n − 1 iterations.
- **At the maximum input:** n = 45 → 44 iterations, effectively instant.

**Space complexity: `O(1)`**

| Part | Cost | Why |
| --- | --- | --- |
| prev2, prev1, curr, i (lines 2-7) | 4 ints | The window holds only the two most recent counts plus the loop counter. |

- **Adding it up:** A constant number of ints: O(1).
- **Not counted:** No array and no recursion; the input n and the int answer are not counted.

**Dry run** on `n = 4 (Example 1, n = 2, finishes in a single iteration, so a slightly taller staircase shows the window sliding)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | prev2 = 1 stands for ways(0): there is exactly one way to be on the ground, making no moves. | `n = 4`<br>`prev2 = 1` |
| 2 | 3 | prev1 = 1 stands for ways(1): a single 1-step. | `prev1 = 1` |
| 3 | 6 | n = 4 is not 1, so line 4's check fails and the early return is skipped. curr starts at 0. | `curr = 0` |
| 4 | 8 | i = 2: curr = prev1 + prev2 = 1 + 1 = 2, the number of ways to reach step 2. | `curr = 2`<br>`i = 2` |
| 5 | 10 | Lines 9-10 slide the window: prev2 = 1 (ways(1)) and prev1 = 2 (ways(2)). | `prev1 = 2` |
| 6 | 8 | i = 3: curr = prev1 + prev2 = 2 + 1 = 3, the number of ways to reach step 3. | `curr = 3`<br>`i = 3` |
| 7 | 9 | prev2 = prev1 = 2. This must happen before prev1 is overwritten, otherwise ways(2) would be lost. | `prev2 = 2` |
| 8 | 10 | prev1 = curr = 3. Now prev2 = ways(2) and prev1 = ways(3), ready for i = 4. | `prev1 = 3` |
| 9 | 8 | i = 4: curr = prev1 + prev2 = 3 + 2 = 5, the number of ways to reach step 4. | `curr = 5`<br>`i = 4` |
| 10 | 10 | Lines 9-10 slide the window: prev2 = 3 (ways(3)) and prev1 = 5 (ways(4)). | `prev2 = 3`<br>`prev1 = 5` |
| 11 | 11 | The loop ends after i = 4, so climbStairs returns curr = 5 = ways(4). | (no change) |

**Result:** 5: the loop produced ways(2) = 2, ways(3) = 3 and ways(4) = 5, the same values the memo held, using only two variables.

**C++ solution**

```cpp
class Solution {
public:
    int climbStairs(int n) {
        int prev2 = 1;            // ways(0): one way to be on the ground (no moves)
        int prev1 = 1;            // ways(1): a single 1-step
        if (n == 1) return prev1; // the loop starts at i = 2, so answer n = 1 directly
        int curr = 0;             // will hold ways(i) inside the loop
        for (int i = 2; i <= n; ++i) {
            curr = prev1 + prev2; // arrive by a 1-step from i - 1 or a 2-step from i - 2
            prev2 = prev1;        // ways(i - 1) becomes the "two back" value for step i + 1
            prev1 = curr;         // ways(i) becomes the "one back" value for step i + 1
        }
        return curr; // ways(n); at most 1836311903 for n = 45, which still fits in int
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
    int climbStairs(int n) {
        int prev2 = 1;            // ways(0): one way to be on the ground (no moves)
        int prev1 = 1;            // ways(1): a single 1-step
        if (n == 1) return prev1; // the loop starts at i = 2, so answer n = 1 directly
        int curr = 0;             // will hold ways(i) inside the loop
        for (int i = 2; i <= n; ++i) {
            curr = prev1 + prev2; // arrive by a 1-step from i - 1 or a 2-step from i - 2
            prev2 = prev1;        // ways(i - 1) becomes the "two back" value for step i + 1
            prev1 = curr;         // ways(i) becomes the "one back" value for step i + 1
        }
        return curr; // ways(n); at most 1836311903 for n = 45, which still fits in int
    }
};

int main() {
    Solution sol;

    int n1 = 2;
    cout << "Example 1: n = " << n1 << " -> " << sol.climbStairs(n1) << " (expected 2)\n";

    int n2 = 3;
    cout << "Example 2: n = " << n2 << " -> " << sol.climbStairs(n2) << " (expected 3)\n";

    return 0;
}
```

</details>

**Why this is the best:** With `O(1)` space and at most 44 additions for `n ≤ 45` it is effectively optimal here. Matrix exponentiation of `[[1,1],[1,0]]` reaches `O(log n)` time and Binet's formula is `O(1)` but needs floating point that loses exactness for large `n`; neither pays off at this input size.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| n = 4 | 5 | Five sequences: 1+1+1+1, 1+1+2, 1+2+1, 2+1+1 and 2+2; the first n where the count is not just n. |
| n = 5 | 8 | Checks the recurrence one more level: ways(4) + ways(3) = 5 + 3 = 8. |
| n = 7 | 21 | Mid-sized staircase where hand-listing gets error prone; 13 + 8 = 21. |
| n = 10 | 89 | Two-digit n; the count keeps following the Fibonacci sequence. |
| n = 20 | 10946 | Larger n where unmemoised recursion already makes over 20,000 calls. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum n | n = 1 | 1 | Only one 1-step; the loop must not run and the answer must not be 0. |
| Maximum n | n = 45 | 1836311903 | The answer is just under INT_MAX (2,147,483,647), so int is enough but nothing smaller is. |
| Near maximum | n = 44 | 1134903170 | The last addition for n = 45 combines this value with ways(43); checks no intermediate overflows. |
| Recursion trap | n = 40 | 165580141 | Plain recursion needs about 3.3·10^8 calls here and times out. |
| Medium-large n | n = 35 | 14930352 | Still fine for O(n), but already about 3·10^7 calls for unmemoised recursion. |

## Mistakes and edge cases

**Common mistakes**

- Counting unordered combinations instead of ordered sequences: treating `1+2` and `2+1` as one way gives 2 for `n = 3` instead of 3.
- Wrong base cases, such as `ways(0) = 0`, which makes `ways(2) = 1` instead of 2, or checking only `i == 1` so the recursion reaches `ways(-1)` and never stops.
- Submitting the plain recursion: it passes the examples but makes hundreds of millions of calls from around `n = 40` and gets Time Limit Exceeded.
- Sliding the window in the wrong order (`prev1 = curr` before `prev2 = prev1`), which copies the new value into both variables and doubles the count every step.

**Edge cases to check**

- `n = 1`: the answer is 1 and the loop never runs, so code that returns a `curr` initialised to 0 must handle it separately.
- `n = 2`: the smallest staircase with two different ways (`1+1` and `2`), confirming the base cases add up correctly.
- `n = 45`: the answer 1,836,311,903 is close to `INT_MAX`, so `int` is fine but any extra iteration (computing `ways(46)`) would overflow.
- `n` around 40 to 45 with unmemoised recursion: correct answers but billions of calls, the exact case that separates the brute force from the DP.

## Practice next

- [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/) · The identical recurrence `F(n) = F(n − 1) + F(n − 2)`, only with base cases 0 and 1.
- [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) · Same 1-or-2 step staircase, but each state takes the minimum cost of the two previous states instead of summing counts.
- [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/) · The same rolling-window DP with a window of three previous values.
- [Decode Ways](https://leetcode.com/problems/decode-ways/) · Counts ways to consume a string 1 or 2 characters at a time, the climbing-stairs recurrence with validity checks on each move.

## Takeaways

- For counting problems, split the possibilities by the last choice made; if the groups are disjoint and complete, their counts add up to a recurrence.
- When a recursion keeps solving the same arguments, memoise it: the cost drops from the size of the call tree to the number of distinct states.
- If each DP state depends only on a fixed window of earlier states, keep just that window in variables to cut space to `O(1)`.
- Always check whether order matters: ordered sequences (this problem) and unordered combinations (Coin Change II) need different DPs.
