# Maximize Consecutive Elements in an Array After Modification

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/) · Pattern: **Sorting + Dynamic Programming**

> Given an array `nums` where each element can be increased by `0` or `1`, find the maximum number of elements you can choose whose modified values form a strictly consecutive integer sequence.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
You are given a 0-indexed array nums consisting of positive integers.

Initially, you can increase the value of any element in the array by at most 1.

After that, you need to select one or more elements from the final array such that those elements are consecutive when sorted in increasing order. For example, the elements [3, 4, 5] are consecutive while [3, 4, 6] and [1, 1, 2, 3] are not.

Return the maximum number of elements that you can select.

Example 1:

Input: nums = [2,1,5,1,1]
Output: 3
Explanation: We can increase the elements at indices 0 and 3. The resulting array is nums = [3,1,5,2,1].
We select the elements [3,1,5,2,1] and we sort them to obtain [1,2,3], which are consecutive.
It can be shown that we cannot select more than 3 consecutive elements.

Example 2:

Input: nums = [1,4,7,10]
Output: 1
Explanation: The maximum consecutive elements that we can select is 1.

Constraints:

- 1 <= nums.length <= 10^5

- 1 <= nums[i] <= 10^6
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You can optionally add 1 to any subset of elements in the array, and then pick as many elements as possible that form a strictly consecutive sequence like `k, k+1, k+2, ...` with no duplicates or gaps. You want to maximize the count of elements in that chosen sequence.

</details>

<details>
<summary>Hint 2 · Observation</summary>

The original order of `nums` does not matter because you sort your chosen elements anyway, and duplicate values can still be useful since one copy can stay as `x` while another becomes `x + 1`.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `nums.length` up to `10^5`, trying all `2^n` increment choices or checking every possible starting value and subset is far too slow; we need an `O(n log n)` or `O(n)` solution.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This problem fits Sorting combined with Dynamic Programming, because sorting lets us process numbers in increasing order and each number only affects consecutive chains ending right around its value.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

When processing sorted elements one by one, a number `x` can either stay `x` to extend a chain ending at `x - 1`, or increment to `x + 1` to extend a chain ending at `x`; updating the `x + 1` case before the `x` case ensures the same element is never used twice in one chain.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Maintain a hash map `dp` where `dp[v]` represents the length of the longest valid consecutive sequence ending at value `v` using only the elements seen so far, plus a variable tracking the overall maximum length.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Sort `nums` in non-decreasing order.
Initialize an empty hash map `dp` (defaulting missing values to `0`) and `ans = 0`.
For each element `x` in the sorted array:
Set `dp[x + 1]` to `dp[x] + 1` (using `x` incremented by 1).
Set `dp[x]` to `dp[x - 1] + 1` (using `x` unchanged).
Update `ans` with the larger of `dp[x]` and `dp[x + 1]`.
Return `ans` after processing all elements.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest detail is update order: computing `dp[x + 1]` before `dp[x]` prevents `x` from extending a chain that `x` itself just created, and handles duplicates like `[1, 1, 1]` (answer `2`) naturally alongside single-element or wide-gap inputs. Sorting takes `O(n log n)` time and the DP pass takes `O(n)` time, for `O(n log n)` total time and `O(n)` extra space for `dp`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "consecutive when sorted in increasing order" | The original order of `nums` does not matter, and duplicates are forbidden in the chosen subset, which points to sorting `nums` first. |
| "increase the value of any element ... by at most 1" | Each element `x` has only two candidate roles in the final sequence (`x` or `x + 1`), allowing a simple local state transition. |
| "1 <= nums.length <= 10^5" and "1 <= nums[i] <= 10^6" | An `O(n^2)` approach will time out, while sorting plus a linear DP pass in `O(n log n)` will pass comfortably. |

### What the constraints tell you

With `nums.length <= 10^5`, an exponential `O(2^n)` search over `+0/+1` choices is impossible, and an `O(n^2)` loop takes roughly `10^10` operations, which is far too slow. Sorting `nums` takes `O(n log n)` ≈ `1.7 * 10^6` operations, and a linear DP pass adds `O(n)` ≈ `10^5` operations. Therefore, we need an `O(n log n)` time algorithm (or `O(n + max(nums))` using counting).

### Think it through

Answer each question yourself before opening it.

**Q1. Do the original indices of `nums` matter after we modify elements?**

<details>
<summary>Answer</summary>

No, because we can select any subset and sort it to check consecutiveness. Moreover, if `x < y`, then `x`'s modified value (`x` or `x + 1`) is at most `y`, which can never strictly exceed `y`'s modified value (`y` or `y + 1`), so sorting `nums` lets us build consecutive chains strictly from smaller elements to larger ones.

</details>

**Q2. In Example 1 (`nums = [2, 1, 5, 1, 1]`), why do repeated values like `1` still help?**

<details>
<summary>Answer</summary>

Even though a consecutive sequence cannot contain duplicates, one `1` can stay `1` while a second `1` is increased to `2`. Notice the third `1` cannot become `3`, so duplicates beyond two occurrences of the same value cannot both extend the same chain at that value.

</details>

**Q3. If we sort `nums` and fix a starting value `start`, how would we check the longest chain starting at `start`?**

<details>
<summary>Answer</summary>

We can scan sorted `nums` left-to-right tracking the next integer `need` (initially `start`) and greedily match `x` or `x + 1` to `need`. However, trying all ~`2n` candidate values of `start` takes `O(n^2)` time, which repeats a lot of work across overlapping sequences.

</details>

**Q4. How can we compute all chains in a single pass over sorted `nums` instead of restarting for every `start`?**

<details>
<summary>Answer</summary>

Define `dp[v]` as the maximum length of a consecutive sequence ending at value `v` using elements processed so far. When we see `x`, it can extend a sequence ending at `x - 1` (by staying `x`) or a sequence ending at `x` (by becoming `x + 1`).

</details>

**Q5. When processing a single element `x`, how do we avoid using that same `x` twice?**

<details>
<summary>Answer</summary>

If we updated `dp[x]` before `dp[x + 1]`, then `dp[x + 1]` could read the newly updated `dp[x]` and effectively count the same `x` as both `x` and `x + 1`. Updating `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` first, and then `dp[x] = max(dp[x], dp[x - 1] + 1)`, guarantees `x` is used in at most one position.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Enumerate all +0/+1 choices](#1-brute-force-enumerate-all-01-choices) | `O(2^n * n log n)` | `O(n)` |
| 2 | [Better: Sort + greedy check per starting value](#2-better-sort--greedy-check-per-starting-value) | `O(n^2)` | `O(n)` |
| 3 | [Optimal: Sort + end-value DP](#3-optimal-sort--end-value-dp) | `O(n log n)` | `O(n)` |

### 1. Brute force: Enumerate all +0/+1 choices

> **Where you start:** Because every `nums[i]` independently has two options (`nums[i]` or `nums[i] + 1`), the most direct way to remove the modification freedom is to try every possible final array.

**Idea.** Generate all `2^n` modified arrays by deciding for each index `i` whether to add `0` or `1`. For each resulting array, sort it (or insert into a set) and scan for the longest run of consecutive distinct integers. By exhaustively checking every valid modification, the maximum run found across all arrays is guaranteed to be optimal.

**Steps**

1. Recurse over index `i` from `0` to `n - 1`, branching on keeping `nums[i]` or replacing it with `nums[i] + 1`.
2. At `i == n`, put all modified values into a sorted list or hash set to remove duplicates.
3. Scan the distinct sorted values to find the longest contiguous run where `val[j] == val[j - 1] + 1`.
4. Return the maximum run length seen across all `2^n` branches.

**Pseudocode**

```text
 1 │ function maxSelectedElements(nums)
 2 │   n ← length(nums)
 3 │   best ← 1  // at least one element can always be selected
 4 │   cur ← array of size n initialized to 0  // holds current +0/+1 modified array
 5 │   function dfs(i)
 6 │     if i = n
 7 │       sorted ← unique sorted copy of cur  // consecutive elements must be distinct
 8 │       run ← 1
 9 │       for j ← 1 to length(sorted) - 1
10 │         if sorted[j] = sorted[j - 1] + 1
11 │           run ← run + 1
12 │           if run > best
13 │             best ← run
14 │         else
15 │           run ← 1  // reset streak when gap exceeds 1
16 │       return
17 │     cur[i] ← nums[i]  // branch 1: keep nums[i] unchanged (+0)
18 │     dfs(i + 1)
19 │     cur[i] ← nums[i] + 1  // branch 2: increment nums[i] by 1 (+1)
20 │     dfs(i + 1)
21 │   dfs(0)
22 │   return best
```

**Time complexity: `O(2^n * n log n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Setup (lines 2-4) | 1 × O(n) | Allocates the working array cur of size n once before recursion begins. |
| DFS internal nodes (lines 5-6, 17-20) | (2^n - 1) calls × O(1) | Each of the 2^n - 1 non-leaf recursive calls assigns cur[i] twice and makes two recursive calls. |
| Leaf sorting and deduplication (line 7) | 2^n leaves × O(n log n) | Every one of the 2^n complete +0/+1 arrays is copied, sorted, and deduplicated. |
| Leaf consecutive-run scan (lines 8-15) | 2^n leaves × O(n) | Each deduplicated sorted array has at most n elements and is scanned once linearly. |

- **Adding it up:** O(n) + O(2^n) + 2^n · O(n log n) + 2^n · O(n) = O(2^n * n log n); sorting at every leaf dominates the recursion tree and linear scans
- **At the maximum input:** n = 10^5 is far beyond reach (2^100000 is astronomical); this brute-force approach is only practical up to about n = 20 (2^20 · 20 log2(20) ≈ 9·10^7 steps, roughly 0.5 s)

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Working array cur (line 4) | O(n) | Stores one modified value per index and is overwritten in place across branches. |
| Recursion call stack (lines 5, 18, 20) | O(n) | The DFS goes at most n levels deep before hitting the base case i = n. |
| Leaf sorted copy (line 7) | O(n) | Holds at most n elements for the current leaf and is freed on return before the next leaf. |

- **Adding it up:** O(n) + O(n) + O(n) = O(n) auxiliary space
- **Not counted:** The input array nums is not counted toward auxiliary space; the O(n) bound includes the recursion stack depth.

**Dry run** on `nums = [2, 1, 5, 1, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | Initialize n = 5, best = 1, and working array cur of 5 zeros before starting dfs(0). | `best = 1`<br>`n = 5`<br>`cur = [0, 0, 0, 0, 0]`<br>`nums = [2, 1, 5, 1, 1]` |
| 2 | 17 | Enter dfs(0) and take the +0 branch for index 0, setting cur[0] = nums[0] = 2. | `i = 0`<br>`cur = [2, 0, 0, 0, 0]` (i→0)<br>`nums = [2, 1, 5, 1, 1]` (i→0) |
| 3 | 17 | Continue taking the +0 branch down through indices 1, 2, 3, and 4; at i = 4, cur[4] becomes nums[4] = 1. | `i = 4`<br>`cur = [2, 1, 5, 1, 1]` (i→4)<br>`nums = [2, 1, 5, 1, 1]` (i→4) |
| 4 | 7 | Reach the base case i = 5 for the all-+0 choice; copy, sort, and deduplicate cur into sorted = [1, 2, 5]. | `i = 5`<br>`cur = [2, 1, 5, 1, 1]`<br>`nums = [2, 1, 5, 1, 1]`<br>`sorted = [1, 2, 5]` |
| 5 | 13 | At j = 1, sorted[1] (2) equals sorted[0] + 1 (1 + 1), so run increments to 2 and best updates from 1 to 2. | `best = 2`<br>`j = 1`<br>`run = 2`<br>`sorted = [1, 2, 5]` (j→1) |
| 6 | 15 | At j = 2, sorted[2] (5) is not 2 + 1, so the streak breaks and run resets to 1 before returning. | `j = 2`<br>`run = 1`<br>`sorted = [1, 2, 5]` (j→2) |
| 7 | 19 | Skip the remaining 15 leaves under cur[0] = 2 (none exceed best = 2, ending on [2, 2, 6, 2, 2]). Back at i = 0, take the +1 branch and set cur[0] = 3. | `i = 0`<br>`cur = [3, 2, 6, 2, 2]` (i→0)<br>`nums = [2, 1, 5, 1, 1]` (i→0) |
| 8 | 19 | After taking +0 at i = 1 (cur[1] = 1) and +0 at i = 2 (cur[2] = 5), skip the +0 branch at i = 3 and take +1 at i = 3, setting cur[3] = 2. | `i = 3`<br>`cur = [3, 1, 5, 2, 2]` (i→3)<br>`nums = [2, 1, 5, 1, 1]` (i→3) |
| 9 | 17 | At i = 4, take the +0 branch and set cur[4] = nums[4] = 1, forming [3, 1, 5, 2, 1]. | `i = 4`<br>`cur = [3, 1, 5, 2, 1]` (i→4)<br>`nums = [2, 1, 5, 1, 1]` (i→4) |
| 10 | 7 | Reach the base case i = 5; sorting and deduplicating cur = [3, 1, 5, 2, 1] produces sorted = [1, 2, 3, 5]. | `i = 5`<br>`cur = [3, 1, 5, 2, 1]`<br>`nums = [2, 1, 5, 1, 1]`<br>`sorted = [1, 2, 3, 5]` |
| 11 | 11 | At j = 1, sorted[1] (2) equals sorted[0] + 1, increasing run to 2; best remains 2 because 2 > 2 is false. | `j = 1`<br>`run = 2`<br>`sorted = [1, 2, 3, 5]` (j→1) |
| 12 | 13 | At j = 2, sorted[2] (3) equals sorted[1] + 1, so run increases to 3 and best updates to 3. | `best = 3`<br>`j = 2`<br>`run = 3`<br>`sorted = [1, 2, 3, 5]` (j→2) |
| 13 | 15 | At j = 3, sorted[3] (5) is not 3 + 1, so run resets to 1 before returning from this leaf. | `j = 3`<br>`run = 1`<br>`sorted = [1, 2, 3, 5]` (j→3) |
| 14 | 22 | Skip the remaining branches (none yield more than 3 consecutive values). All 32 combinations are complete, so return best = 3. | `cur = [3, 2, 6, 2, 2]` |

**Result:** 3 — incrementing indices 0 and 3 yields [3, 1, 5, 2, 1], whose distinct sorted values [1, 2, 3, 5] contain the longest possible consecutive run of length 3 across all 2^5 = 32 choices.

**C++ solution**

```cpp
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        int best = 1; // At least one element can always be selected
        vector<int> cur(n); // Holds the current +0/+1 modified array

        // Enumerate all 2^n +0/+1 modification choices recursively
        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                vector<int> vals = cur; // Copy cur so backtracking can overwrite cur safely
                sort(vals.begin(), vals.end()); // Order values to detect consecutive streaks
                vals.erase(unique(vals.begin(), vals.end()), vals.end()); // Remove duplicates because consecutive elements must be distinct

                int run = 1; // Current consecutive streak length
                for (int j = 1; j < (int)vals.size(); ++j) {
                    if (vals[j] == vals[j - 1] + 1) {
                        ++run; // Extend the streak when adjacent distinct values differ by 1
                        best = max(best, run); // Update the global maximum streak length
                    } else {
                        run = 1; // Reset streak when a gap larger than 1 occurs
                    }
                }
                return;
            }

            cur[i] = nums[i]; // Branch 1: keep nums[i] unchanged (+0)
            dfs(i + 1);

            cur[i] = nums[i] + 1; // Branch 2: increase nums[i] by 1 (+1)
            dfs(i + 1);
        };

        dfs(0); // Start exploring choices from index 0
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
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        int best = 1; // At least one element can always be selected
        vector<int> cur(n); // Holds the current +0/+1 modified array

        // Enumerate all 2^n +0/+1 modification choices recursively
        function<void(int)> dfs = [&](int i) {
            if (i == n) {
                vector<int> vals = cur; // Copy cur so backtracking can overwrite cur safely
                sort(vals.begin(), vals.end()); // Order values to detect consecutive streaks
                vals.erase(unique(vals.begin(), vals.end()), vals.end()); // Remove duplicates because consecutive elements must be distinct

                int run = 1; // Current consecutive streak length
                for (int j = 1; j < (int)vals.size(); ++j) {
                    if (vals[j] == vals[j - 1] + 1) {
                        ++run; // Extend the streak when adjacent distinct values differ by 1
                        best = max(best, run); // Update the global maximum streak length
                    } else {
                        run = 1; // Reset streak when a gap larger than 1 occurs
                    }
                }
                return;
            }

            cur[i] = nums[i]; // Branch 1: keep nums[i] unchanged (+0)
            dfs(i + 1);

            cur[i] = nums[i] + 1; // Branch 2: increase nums[i] by 1 (+1)
            dfs(i + 1);
        };

        dfs(0); // Start exploring choices from index 0
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> ex1 = {2, 1, 5, 1, 1};
    cout << "Example 1: output = " << sol.maxSelectedElements(ex1) << " (expected: 3)\n";

    vector<int> ex2 = {1, 4, 7, 10};
    cout << "Example 2: output = " << sol.maxSelectedElements(ex2) << " (expected: 1)\n";

    return 0;
}
```

</details>

**Why move on:** Completely infeasible beyond `n ≈ 20` because `2^n` explodes exponentially against the `n <= 10^5` constraint.

### 2. Better: Sort + greedy check per starting value

> **How you get here:** Instead of branching exponentially on every element, sorting `nums` first lets us greedily build the chain for any fixed starting integer `start` in one linear scan.

**Idea.** Sort `nums` in non-decreasing order. Any optimal consecutive sequence must start at some value `start` equal to `nums[i]` or `nums[i] + 1`. For a fixed `start`, scanning sorted `nums` and always taking the earliest element that can form `need` (either `x == need` or `x + 1 == need`) is optimal because delaying `need` to a later element can never yield a smaller `x` or unlock more choices.

**Steps**

1. Sort `nums` in increasing order.
2. Collect all distinct candidate starting values from `nums[i]` and `nums[i] + 1`.
3. For each candidate `start`, initialize `need = start`.
4. Scan `x` in sorted `nums`: if `x == need` or `x + 1 == need`, increment `need` by `1`.
5. Record `need - start` as the chain length for this `start`, and return the maximum length across all candidates.

**Pseudocode**

```text
 1 │ function maxSelectedElements(nums)
 2 │   sort(nums) // non-decreasing order so greedy picks earliest valid element
 3 │   candidates ← empty ordered set // distinct possible starting values
 4 │   for i ← 0 to length(nums) - 1
 5 │     add nums[i] to candidates // chain starting without incrementing nums[i]
 6 │     add nums[i] + 1 to candidates // chain starting by incrementing nums[i]
 7 │   best ← 0
 8 │   for each start in candidates
 9 │     need ← start // next consecutive integer needed in the chain
10 │     for i ← 0 to length(nums) - 1
11 │       x ← nums[i]
12 │       if x = need or x + 1 = need // earliest element that can form need
13 │         need ← need + 1 // greedily claim x for need
14 │     best ← max(best, need - start) // chain length formed is need - start
15 │   return best
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Sorting nums (line 2) | O(n log n) | Comparison-based sorting of n elements takes O(n log n) time. |
| Collecting candidates (lines 3-6) | n iterations × O(log n) = O(n log n) | Each element inserts at most two values into an ordered set of size at most 2n. |
| Greedy scan per candidate (lines 8-14) | at most 2n candidates × n iterations = O(n^2) | Each distinct starting value scans all n elements of the sorted array in O(n) time. |

- **Adding it up:** O(n log n) + O(n log n) + O(n^2) = O(n^2); the nested candidate-and-array scan dominates sorting and candidate collection.
- **Best vs worst case:** Best case is O(n log n) when all elements are equal (e.g., [1, 1, ..., 1]), producing only 2 candidates so lines 8-14 take O(n) and sorting dominates. Worst case is O(n^2) when elements are spaced by at least 2 (e.g., [1, 3, 5, ..., 2n-1]), producing 2n candidates that each scan n elements.
- **At the maximum input:** n = 10^5 -> up to 2·10^10 steps in the worst case, which exceeds a 1-second limit and explains why an O(n log n) DP approach is needed to pass all constraints.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Candidate set (line 3) | up to 2n integers = O(n) | Stores at most two distinct starting values (nums[i] and nums[i] + 1) per input element. |
| Sorting auxiliary stack/buffer (line 2) | O(log n) | In-place introsort uses O(log n) recursion stack space. |

- **Adding it up:** O(n) + O(log n) = O(n) auxiliary space.
- **Not counted:** The input array nums is modified in place and not counted toward auxiliary space; the output is a single scalar integer.

**Dry run** on `nums = [2, 1, 5, 1, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | Sort nums in non-decreasing order so the greedy scan encounters smaller values first. | `nums = [1, 1, 1, 2, 5]` |
| 2 | 6 | At i = 0 (nums[0] = 1), add 1 and 2 as candidate starting values. | `i = 0`<br>`nums = [1, 1, 1, 2, 5]` (i→0)<br>`candidates = {1, 2}` |
| 3 | 6 | Skipping repetitive i = 1..3 (which add duplicate 1, 2 and new 3), at i = 4 (nums[4] = 5) we add 5 and 6 to candidates. | `i = 4`<br>`nums = [1, 1, 1, 2, 5]` (i→4)<br>`candidates = {1, 2, 3, 5, 6}` |
| 4 | 9 | Initialize best = 0 and test the first candidate start = 1 with need = 1. | `best = 0`<br>`need = 1`<br>`start = 1`<br>`nums = [1, 1, 1, 2, 5]` |
| 5 | 13 | At i = 0, x = 1 equals need = 1, so we use it without incrementing and advance need to 2. | `i = 0`<br>`need = 2`<br>`x = 1`<br>`nums = [1, 1, 1, 2, 5]` (i→0) |
| 6 | 13 | At i = 1, x = 1 satisfies x + 1 = 2 = need, so we increment it to 2 and advance need to 3. | `i = 1`<br>`need = 3`<br>`nums = [1, 1, 1, 2, 5]` (i→1) |
| 7 | 12 | At i = 2, x = 1 can only form 1 or 2, neither of which equals need = 3, so we skip it. | `i = 2`<br>`nums = [1, 1, 1, 2, 5]` (i→2) |
| 8 | 13 | At i = 3, x = 2 satisfies x + 1 = 3 = need, so we increment it to 3 and advance need to 4. | `i = 3`<br>`need = 4`<br>`x = 2`<br>`nums = [1, 1, 1, 2, 5]` (i→3) |
| 9 | 14 | At i = 4, x = 5 cannot form 4. The chain for start = 1 has length 4 - 1 = 3, updating best to 3. | `best = 3`<br>`nums = [1, 1, 1, 2, 5]` |
| 10 | 9 | Test the next candidate start = 2 with need = 2. | `need = 2`<br>`start = 2` |
| 11 | 14 | For start = 2, nums[0] = 1 forms 2 and nums[3] = 2 forms 3, ending with need = 4 (length 4 - 2 = 2); best stays 3. | `need = 4` |
| 12 | 14 | Skipping remaining scans for start = 3, 5, and 6: each achieves chain length 1 (need = start + 1), leaving best = 3. | `need = 7`<br>`start = 6` |
| 13 | 15 | All candidate starting values have been tested, so return best = 3. | (no change) |

**Result:** 3 — Starting at 1, we greedily form [1, 2, 3] using nums[0]=1, nums[1]=1 (+1), and nums[3]=2 (+1), which is the longest possible consecutive sequence.

**C++ solution**

```cpp
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size(); // number of elements in the array
        sort(nums.begin(), nums.end()); // sort non-decreasingly so greedy picks earliest valid element
        set<int> candidates; // ordered set of distinct candidate starting values
        for (int i = 0; i < n; i++) {
            candidates.insert(nums[i]); // sequence can start at unmodified nums[i]
            candidates.insert(nums[i] + 1); // sequence can start at incremented nums[i] + 1
        }
        int best = 0; // maximum consecutive sequence length found
        for (int start : candidates) {
            int need = start; // next consecutive integer needed in the chain
            for (int i = 0; i < n; i++) {
                int x = nums[i];
                if (x == need || x + 1 == need) { // greedily claim earliest element that can form need
                    need++; // advance to the next required consecutive integer
                }
            }
            best = max(best, need - start); // need - start is the count of elements matched
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
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size(); // number of elements in the array
        sort(nums.begin(), nums.end()); // sort non-decreasingly so greedy picks earliest valid element
        set<int> candidates; // ordered set of distinct candidate starting values
        for (int i = 0; i < n; i++) {
            candidates.insert(nums[i]); // sequence can start at unmodified nums[i]
            candidates.insert(nums[i] + 1); // sequence can start at incremented nums[i] + 1
        }
        int best = 0; // maximum consecutive sequence length found
        for (int start : candidates) {
            int need = start; // next consecutive integer needed in the chain
            for (int i = 0; i < n; i++) {
                int x = nums[i];
                if (x == need || x + 1 == need) { // greedily claim earliest element that can form need
                    need++; // advance to the next required consecutive integer
                }
            }
            best = max(best, need - start); // need - start is the count of elements matched
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {2, 1, 5, 1, 1};
    cout << "Example 1: output = " << sol.maxSelectedElements(nums1) << ", expected = 3\n";
    vector<int> nums2 = {1, 4, 7, 10};
    cout << "Example 2: output = " << sol.maxSelectedElements(nums2) << ", expected = 1\n";
    return 0;
}
```

</details>

**Why move on:** Re-scans `nums` from scratch for every candidate `start`, resulting in ~`10^10` operations when `n = 10^5` and timing out.

### 3. Optimal: Sort + end-value DP

> **How you get here:** Rather than testing each starting value independently, we can track the longest consecutive chain ending at every value `v` in a single pass over sorted `nums`.

**Idea.** Sort `nums` in non-decreasing order and maintain a map `dp[v]` representing the length of the longest valid consecutive sequence ending at integer `v`. Because `nums` is sorted, all elements capable of contributing to values `< x` have already been processed before `x`. For each `x`, updating `dp[x + 1]` from `dp[x] + 1` before updating `dp[x]` from `dp[x - 1] + 1` ensures `x` either becomes `x + 1` or stays `x`, never both, which makes the DP transition exact.

**Steps**

1. Sort `nums` in increasing order.
2. Initialize an empty hash map (or array of size `max(nums) + 2`) `dp` where missing entries default to `0`.
3. For each `x` in sorted `nums`, update `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` first.
4. Next, update `dp[x] = max(dp[x], dp[x - 1] + 1)`.
5. Return the maximum value stored in `dp`.

**Pseudocode**

```text
 1 │ function maxSelectedElements(nums)
 2 │   n ← length(nums)
 3 │   sort(nums)  // ensure elements <= x are processed before x + 1
 4 │   dp ← empty hash map with default value 0  // dp[v] = longest consecutive chain ending at v
 5 │   for i ← 0 to n - 1
 6 │     x ← nums[i]
 7 │     dp[x + 1] ← max(dp[x + 1], dp[x] + 1)  // try incrementing x first so dp[x] excludes x itself
 8 │     dp[x] ← max(dp[x], dp[x - 1] + 1)  // try keeping x unchanged to extend chain from x - 1
 9 │   best ← 0
10 │   for each (val, len) in dp
11 │     if len > best
12 │       best ← len
13 │   return best
```

**Time complexity: `O(n log n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Sorting nums (line 3) | O(n log n) | Comparison-based sorting of n integers takes O(n log n) time. |
| DP transition loop (lines 5-8) | n iterations × O(1) expected | Each element performs a constant number of hash map lookups and updates. |
| Maximum scan over dp (lines 9-12) | at most 2n iterations × O(1) | Each of the n numbers can create at most two keys (x and x + 1) in dp. |

- **Adding it up:** O(n log n) + O(n) + O(n) = O(n log n); sorting dominates the linear-time DP loop and final scan.
- **At the maximum input:** n = 10^5 → roughly 1.7·10^6 comparison operations plus 2·10^5 hash updates, finishing in ~20–40 ms in C++.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Hash map dp (line 4) | O(n) space | Each element inserts at most two entries (x and x + 1), so dp stores at most 2n key-value pairs. |
| Sorting recursion stack (line 3) | O(log n) space | In-place introsort uses logarithmic auxiliary stack space. |

- **Adding it up:** O(n) + O(log n) = O(n); the hash map dominates the sorting stack.
- **Not counted:** The input array nums is sorted in place and not counted toward auxiliary space; the output is a single integer.

**Dry run** on `nums = [2, 1, 5, 1, 1]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | Sort nums in non-decreasing order so smaller values are always available before larger ones; nums becomes [1, 1, 1, 2, 5]. | `n = 5`<br>`nums = [1, 1, 1, 2, 5]` |
| 2 | 4 | Initialize an empty hash map dp where any missing key defaults to 0. | `dp = {}` |
| 3 | 7 | Iteration i = 0, x = 1: try incrementing 1 to 2, setting dp[2] = max(0, dp[1] + 1) = 1. | `i = 0`<br>`x = 1`<br>`nums = [1, 1, 1, 2, 5]` (i→0)<br>`dp = {2→1}` |
| 4 | 8 | Still at i = 0, x = 1: try keeping 1 unchanged, setting dp[1] = max(0, dp[0] + 1) = 1. | `dp = {1→1, 2→1}` |
| 5 | 7 | Iteration i = 1, x = 1: increment this second 1 to 2, extending dp[1] = 1 so dp[2] = max(1, 1 + 1) = 2. | `i = 1`<br>`nums = [1, 1, 1, 2, 5]` (i→1)<br>`dp = {1→1, 2→2}` |
| 6 | 8 | Still at i = 1, x = 1: keeping 1 gives dp[1] = max(1, dp[0] + 1) = 1, leaving dp[1] = 1. | (no change) |
| 7 | 7 | Iteration i = 2, x = 1: incrementing the third 1 to 2 yields max(2, 1 + 1) = 2, so dp[2] stays 2. | `i = 2`<br>`nums = [1, 1, 1, 2, 5]` (i→2) |
| 8 | 8 | Still at i = 2, x = 1: keeping 1 yields max(1, 0 + 1) = 1, so dp[1] stays 1. | (no change) |
| 9 | 7 | Iteration i = 3, x = 2: increment 2 to 3, extending dp[2] = 2 to dp[3] = max(0, 2 + 1) = 3. | `i = 3`<br>`x = 2`<br>`nums = [1, 1, 1, 2, 5]` (i→3)<br>`dp = {1→1, 2→2, 3→3}` |
| 10 | 8 | Still at i = 3, x = 2: keeping 2 gives dp[2] = max(2, dp[1] + 1) = 2, so dp[2] remains 2. | (no change) |
| 11 | 7 | Iteration i = 4, x = 5: increment 5 to 6, setting dp[6] = max(0, dp[5] + 1) = 1. | `i = 4`<br>`x = 5`<br>`nums = [1, 1, 1, 2, 5]` (i→4)<br>`dp = {1→1, 2→2, 3→3, 6→1}` |
| 12 | 8 | Still at i = 4, x = 5: keeping 5 sets dp[5] = max(0, dp[4] + 1) = 1. | `dp = {1→1, 2→2, 3→3, 5→1, 6→1}` |
| 13 | 13 | Lines 9–12 scan all entries in dp and find the maximum length best = 3 (at key 3); line 13 returns 3. | `best = 3`<br>`nums = [1, 1, 1, 2, 5]` |

**Result:** 3 — Two of the 1s form [1, 2] (keeping one and incrementing one), and incrementing 2 to 3 extends that chain to [1, 2, 3] of length 3.

**C++ solution**

```cpp
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        // Sort so all elements <= x are processed before x + 1
        sort(nums.begin(), nums.end());
        // dp[v] stores the longest consecutive sequence ending at value v
        unordered_map<int, int> dp;
        for (int x : nums) {
            // Read existing chain lengths before updating dp so x cannot extend itself
            int prevSame = dp.count(x) ? dp[x] : 0;
            int prevLess = dp.count(x - 1) ? dp[x - 1] : 0;
            // Option 1: increment x to x + 1, extending any chain ending at x
            dp[x + 1] = max(dp[x + 1], prevSame + 1);
            // Option 2: keep x unchanged, extending any chain ending at x - 1
            dp[x] = max(prevSame, prevLess + 1);
        }
        int best = 0;
        // Scan all reachable ending values to find the maximum sequence length
        for (const auto& [val, len] : dp) {
            best = max(best, len);
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
    int maxSelectedElements(vector<int>& nums) {
        // Sort so all elements <= x are processed before x + 1
        sort(nums.begin(), nums.end());
        // dp[v] stores the longest consecutive sequence ending at value v
        unordered_map<int, int> dp;
        for (int x : nums) {
            // Read existing chain lengths before updating dp so x cannot extend itself
            int prevSame = dp.count(x) ? dp[x] : 0;
            int prevLess = dp.count(x - 1) ? dp[x - 1] : 0;
            // Option 1: increment x to x + 1, extending any chain ending at x
            dp[x + 1] = max(dp[x + 1], prevSame + 1);
            // Option 2: keep x unchanged, extending any chain ending at x - 1
            dp[x] = max(prevSame, prevLess + 1);
        }
        int best = 0;
        // Scan all reachable ending values to find the maximum sequence length
        for (const auto& [val, len] : dp) {
            best = max(best, len);
        }
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 1, 5, 1, 1};
    cout << "Example 1: " << sol.maxSelectedElements(nums1) << " (expected 3)\n";

    vector<int> nums2 = {1, 4, 7, 10};
    cout << "Example 2: " << sol.maxSelectedElements(nums2) << " (expected 1)\n";

    return 0;
}
```

</details>

**Why this is the best:** Uses `O(n)` space for the DP table and requires sorting; if `max(nums)` were much smaller than `n`, counting sort could achieve `O(n + max(nums))`, though `O(n log n)` is already optimal for comparison-based processing and independent of the value range.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [8,10,6,12,9,11] | 6 | Bridges a single gap by incrementing the smallest element so all 6 elements form [7,8,9,10,11,12]. |
| nums = [3,3,4,4,6,6] | 5 | Uses duplicates to extend upward and bridge a gap of 2 between 4 and 6 to form [3,4,5,6,7]. |
| nums = [10,12,13,15,17] | 3 | Multiple candidate consecutive runs where incrementing cannot merge everything into one long sequence. |
| nums = [5,2,2,4,1,8,7] | 5 | Unsorted input with duplicates where the optimal sequence [1,2,3,4,5] beats the disjoint upper cluster. |
| nums = [4,1,3,1,3,5,8,7,7] | 9 | Cascading increments across multiple duplicate pairs allow all 9 elements to form [1,2,3,4,5,6,7,8,9]. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | nums = [1] | 1 | Minimum array length and minimum possible element value. |
| All equal | nums = [5,5,5,5] | 2 | More than two identical elements can still yield at most two consecutive values [5,6]. |
| Already consecutive | nums = [1,2,3,4,5] | 5 | No modifications needed to select the entire array. |
| Reverse-sorted step-2 gaps | nums = [9,7,5,3,1] | 2 | Adjacent pairs can connect to length 2, but cannot chain further without duplicates. |
| Maximum value boundary | nums = [1000000,999999,1000000] | 3 | Incrementing 10^6 produces 1000001; a full-scale 10^5-element array also tests O(n log n) time. |
| Large gaps | nums = [1,10,100,1000] | 1 | No two elements are within distance 2 so the longest consecutive sequence has length 1. |

## Mistakes and edge cases

**Common mistakes**

- Updating `dp[x]` before `dp[x + 1]`: if `dp[x]` increases first, then `dp[x + 1] = max(dp[x + 1], dp[x] + 1)` will chain onto the same element `x` twice, creating a phantom sequence of length 2 from a single number.
- Not sorting `nums` before running the DP: processing `2` before `1` means `1 -> 2` will not propagate forward to `3` from the already-processed `2`.
- Forgetting to take `max` in the DP updates (writing `dp[x + 1] = dp[x] + 1` directly): a third duplicate like `[1, 1, 1]` would overwrite `dp[2] = 2` with `dp[1] + 1` or corrupt an existing longer chain ending at `x + 1` if `x` had a shorter chain.
- Skipping duplicates when deduplicating `nums` upfront: keeping at most two copies of each value is necessary (for `x` and `x + 1`), so converting `nums` into a set loses valid extensions like `[1, 1]` forming `[1, 2]`.

**Edge cases to check**

- Single element (`nums = [5]`): must return `1`, checking that `dp` handles arrays of length `1` without returning `0`.
- All identical elements (`nums = [3, 3, 3, 3]`): can form `[3, 4]` of length `2`, verifying that duplicates beyond two do not artificially inflate `dp[4]` to `3` or `4`.
- Large gaps between elements (`nums = [1, 4, 7, 10]`): even after `+1`, consecutive gaps remain `>= 2`, so the answer must be `1`.
- Bridging a gap of 2 (`nums = [1, 3]`): `1` can become `2` while `3` stays `3`, yielding `[2, 3]` of length `2`; this verifies that `x` increasing to `x + 1` is correctly picked up by `x + 2` later in the sorted array.

## Practice next

- [Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/) · Finds the longest consecutive integer sequence without modifications, introducing the core idea of tracking chain lengths by value.
- [Longest Arithmetic Subsequence of Given Difference](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/) · Uses the exact same `dp[val] = dp[val - d] + 1` hash-map DP pattern for difference `d = 1`, without the `+0/+1` choice.
- [Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/) · Combines sorting with bounded element modifications to build consecutive integers `1, 2, ..., k` greedily.

## Takeaways

- When elements can shift by a small bounded amount (`+0` or `+1`), sorting first often restores a one-way dependency so DP can process elements in a single pass.
- Reverse-order updates (`dp[x + 1]` before `dp[x]`) are the standard 0/1-knapsack-style trick to prevent a single item from transitioning to itself multiple times in the same iteration.
- For sequence problems where you can pick any subset regardless of original positions, keying DP states by element value (`dp[value]`) is often much cleaner than keying by array index.
