# Smallest Unique Subarray

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/smallest-unique-subarray/) · Pattern: **Binary search on answer + rolling hash**

> Find the smallest length `L` such that some contiguous subarray of `nums` of length `L` occurs at exactly one starting position.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| If `[1,1]` is unique in `[1,1,2,2,1]`, then `[1,1,2]` is unique too | the property 'some length-L subarray is unique' is monotone in `L`, so we can binary search on `L`. |
| Comparing subarrays of a fixed length for equality across all start positions | rolling (polynomial) hash turns each window into one number in O(1) amortised. |
| `nums.length <= 10^5` while the answer can be as large as `n` (example `[3,3,3]` gives 3) | scanning every `L` one by one is too slow; we need about `log n` checks. |
| The whole array (length `n`) appears only once | an answer always exists, so the search range is `[1, n]`. |

### What the constraints tell you

n = 10^5. Trying every `L` with an O(n) hashed check is O(n^2) ≈ 10^10, far too slow. Copying each window costs O(n^3) in the worst case. Binary search needs about 17 checks of O(n) each, so O(n log n) ≈ 1.7·10^6 hash operations, which is fine.

### Think it through

Answer each question yourself before opening it.

**Q1. What exactly makes a length-L subarray 'unique'?**

<details>
<summary>Answer</summary>

Its sequence of values must appear at only one start index. Overlapping copies count as well: in `[3,3,3]` the window `[3,3]` appears at index 0 and at index 1, so it is not unique.

</details>

**Q2. What is the naive way to answer?**

<details>
<summary>Answer</summary>

For `L = 1, 2, ...`, count every length-`L` window in a hash map and stop at the first `L` where some count equals 1. Building each window as a tuple costs O(L), which is what makes this slow.

</details>

**Q3. Can I compare windows faster than copying them?**

<details>
<summary>Answer</summary>

Yes. A polynomial rolling hash gives every length-`L` window a fingerprint in O(n) total for that `L`. That brings one check down to O(n), but walking `L` from 1 up to `n` is still O(n^2) when the answer is large, as with an all-equal array.

</details>

**Q4. Is there structure across different L that lets me skip lengths?**

<details>
<summary>Answer</summary>

Suppose the window starting at `i` with length `L` is unique and `L < n`. Extend it by one element, to the right if possible, otherwise to the left. Any other copy of the longer window would contain a copy of the original at a different start, which is impossible. So uniqueness at `L` implies uniqueness at `L+1`.

</details>

**Q5. How do I use that monotonicity?**

<details>
<summary>Answer</summary>

The predicate `has_unique(L)` is false, false, ..., true, true over `L = 1..n`, and it is always true at `L = n`. Binary search for the first true value, running the O(n) rolling-hash check at each midpoint.

</details>

**Q6. How do I keep the hashing trustworthy?**

<details>
<summary>Answer</summary>

Pick a base larger than the maximum value `10^5`. Use a large modulus, ideally two independent hashes (double hashing) or a random base, so that two different windows are very unlikely to collide. A collision would wrongly make a unique window look repeated.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Count tuples for each length](#1-brute-force-count-tuples-for-each-length) | `O(n^3)` | `O(n^2)` |
| 2 | [Better: Linear scan over L with rolling hash](#2-better-linear-scan-over-l-with-rolling-hash) | `O(n^2)` | `O(n)` |
| 3 | [Optimal: Binary search on length + rolling hash](#3-optimal-binary-search-on-length--rolling-hash) | `O(n log n)` | `O(n)` |

### 1. Brute force: Count tuples for each length

> **Where you start:** The definition literally says 'count how often each subarray appears', so the first idea is to tabulate every window of each length and look for a count of 1.

**Idea.** For each length `L` from 1 upward, put every window `nums[i..i+L-1]`, stored as a tuple, into a hash map with its count. If any count is exactly 1, `L` is the answer. The scan stops at the first such `L`, so the result is the minimum. It always terminates because at `L = n` there is only one window.

**Steps**

1. For L from 1 to n:
2. Create an empty map from window contents to count.
3. For each start i from 0 to n-L, add the tuple `nums[i..i+L-1]` to the map.
4. If any value in the map equals 1, return L.
5. Return n (this line is reached only if the loop logic allows it; L = n always succeeds).

**Pseudocode**

```text
 1 │ function smallestUniqueSubarray(nums):
 2 │   n ← length(nums)
 3 │   for L ← 1 to n:
 4 │     count ← empty map from tuple to integer   // fresh counts for this length
 5 │     for i ← 0 to n − L:
 6 │       window ← tuple(nums[i..i+L−1])   // copy the L elements starting at i
 7 │       count[window] ← count[window] + 1   // a missing key counts as 0
 8 │     for each (window, c) in count:
 9 │       if c = 1:
10 │         return L   // lengths are tried in increasing order, so this is the minimum
11 │   return n   // unreachable: at L = n there is only one window, so its count is 1
```

**Time complexity: `O(n^3)`**

| Part | Cost | Why |
| --- | --- | --- |
| Outer loop over lengths (lines 3-10) | up to n iterations | In the worst case no unique window appears until L = n. |
| Building windows (lines 5-7) | (n−L+1) windows × O(L) per copy and hash | Each window copies L numbers and then hashes and compares those L numbers. |
| Scanning the map (lines 8-10) | at most (n−L+1) entries × O(1) | There is at most one map entry per window, and checking a count takes constant time. |

- **Adding it up:** Σ_{L=1..n} L·(n−L+1) = n(n+1)(n+2)/6 = O(n^3). The O(n) map scan per length adds only O(n^2), so the window-building work dominates.
- **Best vs worst case:** Best case: some value occurs exactly once (e.g. [2,1,2,3,3]). The loop stops at L = 1 after O(n) work. Worst case: all elements are equal (e.g. [3,3,…,3]). Every length up to n must be tried, which costs the full O(n^3).
- **At the maximum input:** n = 10^5 with all elements equal gives about n^3/6 ≈ 1.7·10^14 steps, which is hopelessly slow. This approach is only practical for n up to a few hundred.

**Space complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Map of windows (line 4, filled on line 7) | (n−L+1) tuples × L numbers each | The map can store every window of the current length as a full copy. The product L·(n−L+1) peaks near n^2/4 when L ≈ n/2. |
| Current window tuple (line 6) | O(L) ≤ O(n) | It is a temporary copy of one window. |

- **Adding it up:** O(n^2) + O(n) = O(n^2). Only one length's map exists at a time.
- **Not counted:** The input array is not counted. There is no recursion.

**Dry run** on `nums = [3,3,3]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 2 | Store the array length: n = 3. | `n = 3`<br>`nums = [3, 3, 3]` |
| 2 | 4 | Start with length L = 1 and an empty count map. | `L = 1`<br>`count = {}` |
| 3 | 7 | i = 0: the window is (3). It is new, so its count becomes 1. | `i = 0`<br>`window = (3)`<br>`nums = [3, 3, 3]` (i→0)<br>`count = {(3)→1}` |
| 4 | 7 | i = 1: the window is (3) again, so its count rises to 2. | `i = 1`<br>`nums = [3, 3, 3]` (i→1)<br>`count = {(3)→2}` |
| 5 | 7 | i = 2: the window is (3) a third time, so its count rises to 3. | `i = 2`<br>`nums = [3, 3, 3]` (i→2)<br>`count = {(3)→3}` |
| 6 | 9 | The only entry has c = 3, not 1. No length-1 window is unique. | `c = 3`<br>`nums = [3, 3, 3]` |
| 7 | 4 | Move to L = 2 and reset the map to empty. | `L = 2`<br>`count = {}` |
| 8 | 7 | i = 0: the window nums[0..1] = (3,3) gets count 1. | `i = 0`<br>`window = (3,3)`<br>`nums = [3, 3, 3]` (i→0)<br>`count = {(3,3)→1}` |
| 9 | 7 | i = 1: the window nums[1..2] = (3,3) is the same tuple, so its count becomes 2. The loop ends because n − L = 1. | `i = 1`<br>`nums = [3, 3, 3]` (i→1)<br>`count = {(3,3)→2}` |
| 10 | 9 | The only entry has c = 2, not 1. No length-2 window is unique. | `c = 2`<br>`nums = [3, 3, 3]` |
| 11 | 4 | Move to L = 3 and reset the map to empty. | `L = 3`<br>`count = {}` |
| 12 | 7 | i = 0 is the only start: the window (3,3,3) gets count 1. | `i = 0`<br>`window = (3,3,3)`<br>`nums = [3, 3, 3]` (i→0)<br>`count = {(3,3,3)→1}` |
| 13 | 9 | The entry (3,3,3) has c = 1, so the condition is true. | `c = 1`<br>`nums = [3, 3, 3]` |
| 14 | 10 | Return L = 3, the first length that has a unique window. | (no change) |

**Result:** 3. Every window of length 1 or 2 is repeated, and the single window of length 3 is unique; since lengths are checked in increasing order, 3 is the minimum.

**C++ solution**

```cpp
class Solution {
public:
    // Hash for a vector<int>, so whole windows can be used as unordered_map keys
    struct VecHash {
        size_t operator()(const vector<int>& v) const {
            size_t h = 1469598103934665603ULL;      // FNV-style starting seed
            for (int x : v) {
                h ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2); // mix in each element
            }
            return h;
        }
    };

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        for (int L = 1; L <= n; ++L) {                    // try lengths in increasing order
            unordered_map<vector<int>, int, VecHash> count; // fresh counts for this length
            for (int i = 0; i + L <= n; ++i) {            // every start of a length-L window
                vector<int> window(nums.begin() + i, nums.begin() + i + L); // copy the window as a tuple
                count[window]++;                          // a missing key starts at 0
            }
            for (auto& entry : count) {                   // look for a window seen exactly once
                if (entry.second == 1) return L;          // first such L is the minimum
            }
        }
        return n; // unreachable: at L = n there is a single window
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
    // Hash for a vector<int>, so whole windows can be used as unordered_map keys
    struct VecHash {
        size_t operator()(const vector<int>& v) const {
            size_t h = 1469598103934665603ULL;      // FNV-style starting seed
            for (int x : v) {
                h ^= (size_t)x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2); // mix in each element
            }
            return h;
        }
    };

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        for (int L = 1; L <= n; ++L) {                    // try lengths in increasing order
            unordered_map<vector<int>, int, VecHash> count; // fresh counts for this length
            for (int i = 0; i + L <= n; ++i) {            // every start of a length-L window
                vector<int> window(nums.begin() + i, nums.begin() + i + L); // copy the window as a tuple
                count[window]++;                          // a missing key starts at 0
            }
            for (auto& entry : count) {                   // look for a window seen exactly once
                if (entry.second == 1) return L;          // first such L is the minimum
            }
        }
        return n; // unreachable: at L = n there is a single window
    }
};

int main() {
    Solution s;
    vector<vector<int>> tests = {{3,3,3}, {2,1,2,3,3}, {1,1,2,2,1}};
    vector<int> expected = {3, 1, 2};
    for (size_t t = 0; t < tests.size(); ++t) {
        int got = s.smallestUniqueSubarray(tests[t]);
        cout << "Example " << t + 1 << ": output = " << got << ", expected = " << expected[t] << endl;
    }
    return 0;
}
```

</details>

**Why move on:** For n = 10^5 this is about 10^14 operations, hopeless. The waste is rehashing overlapping windows from scratch and checking every length in turn.

### 2. Better: Linear scan over L with rolling hash

> **How you get here:** Windows of length `L` at `i` and `i+1` share `L-1` elements, so recomputing each one from scratch wastes O(L) per window.

**Idea.** Precompute prefix hashes `H[i]` and powers `P[i]`, so the hash of `nums[l..r]` is `H[r+1] - H[l]*P[r-l+1]` (mod M) in O(1). For each `L`, count window hashes in a map and test for a count of 1. Correctness relies on equal windows having equal hashes, and, with a strong double hash, unequal windows almost surely differing.

**Steps**

1. Choose a base B > 10^5 and one or two large moduli.
2. Build prefix hash arrays H and power arrays P in one pass.
3. For L from 1 to n, compute the hash of every length-L window in O(1) each.
4. Count the hashes in a map.
5. Return the first L for which some hash has count 1.

**Pseudocode**

```text
 1 │ function smallestUniqueSubarray(nums):
 2 │   n ← length(nums)
 3 │   B ← 100003; M ← 1000000007  // B > every value, so different arrays act like different base-B numbers
 4 │   H ← array of n+1 zeros; P ← array of n+1 zeros; P[0] ← 1
 5 │   for i from 0 to n−1:
 6 │     H[i+1] ← (H[i]·B + nums[i]) mod M  // hash of prefix nums[0..i]
 7 │     P[i+1] ← (P[i]·B) mod M  // P[k] = B^k mod M
 8 │   for L from 1 to n:  // try lengths from shortest up
 9 │     count ← empty map  // window hash → how many windows have it
10 │     for l from 0 to n−L:
11 │       h ← (H[l+L] − H[l]·P[L]) mod M, made non-negative  // O(1): remove the prefix before l
12 │       count[h] ← count[h] + 1
13 │     for each (h, c) in count:
14 │       if c = 1:
15 │         return L  // first length that has a window seen exactly once
16 │   return n  // unreachable: the single window of length n is always unique
17 │ // The C++ code runs the same hash with a second modulus and combines both, making false matches practically impossible
```

**Time complexity: `O(n^2)`**

| Part | Cost | Why |
| --- | --- | --- |
| Prefix hash and power build (lines 4-7) | n iterations × O(1) | Each prefix hash extends the previous one by one multiply and one add. |
| Window hashing for one length L (lines 9-12) | (n−L+1) windows × O(1) expected | Each window hash is one subtraction and one multiply, and each map increment is expected O(1). |
| Scan of the map (lines 13-15) | at most n−L+1 entries × O(1) | The map never holds more distinct hashes than there are windows. |
| Outer loop over L (lines 8-15) | up to n iterations | In the worst case, such as all-equal arrays, no length below n has a unique window. |

- **Adding it up:** O(n) build + Σ_{L=1..ans} O(n−L+1). In the worst case ans = n, giving n + (n−1) + … + 1 = n(n+1)/2 = O(n^2). This dominates the O(n) setup.
- **Best vs worst case:** Best case: some value appears exactly once (e.g. [2,1,2,3,3]). The loop stops at L = 1 after O(n) work. Worst case: all elements are equal (e.g. [3,3,…,3]). The answer is n and every length is processed, about n^2/2 window hashes.
- **At the maximum input:** n = 10^5 in the worst case → about 5·10^9 hash-map operations, many seconds and too slow. When the answer is small it finishes in a few milliseconds, which is why the optimal approach binary-searches L instead.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Prefix arrays H and P (line 4) | 2·(n+1) integers (×2 with the second modulus) | One prefix hash and one power for each position. |
| count map (line 9) | up to n−L+1 entries | It holds at most one entry per window of the current length, and it is rebuilt for each L. |

- **Adding it up:** O(n) + O(n) = O(n), because only one map is alive at a time.
- **Not counted:** The input array is not counted. There is no recursion.

**Dry run** on `nums = [3,3,3]`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 4 | n = 3. We pick base 100003 and modulus 10^9+7, and allocate H and P with P[0] = 1. | `n = 3`<br>`B = 100003`<br>`M = 1000000007`<br>`nums = [3, 3, 3]`<br>`H = [0, 0, 0, 0]`<br>`P = [1, 0, 0, 0]` |
| 2 | 7 | i = 0: H[1] = 0·100003 + 3 = 3, and P[1] = 100003. | `i = 0`<br>`nums = [3, 3, 3]` (i→0)<br>`H = [0, 3, 0, 0]`<br>`P = [1, 100003, 0, 0]` |
| 3 | 7 | i = 1: H[2] = 3·100003 + 3 = 300012. P[2] = 100003² mod M = 10000600009 − 10·M = 599939. | `i = 1`<br>`nums = [3, 3, 3]` (i→1)<br>`H = [0, 3, 300012, 0]`<br>`P = [1, 100003, 599939, 0]` |
| 4 | 7 | i = 2: H[3] = (300012·100003 + 3) mod M = 30002100039 − 30·M = 2099829. P[3] = 599939·100003 mod M = 995699404. | `i = 2`<br>`nums = [3, 3, 3]` (i→2)<br>`H = [0, 3, 300012, 2099829]`<br>`P = [1, 100003, 599939, 995699404]` |
| 5 | 9 | Start with length L = 1 and an empty count map. | `L = 1`<br>`nums = [3, 3, 3]`<br>`count = {}` |
| 6 | 12 | l = 0: h = H[1] − H[0]·P[1] = 3 − 0 = 3. count[3] becomes 1. | `l = 0`<br>`h = 3`<br>`nums = [3, 3, 3]` (l→0)<br>`count = {3→1}` |
| 7 | 12 | l = 1: h = H[2] − H[1]·P[1] = 300012 − 300009 = 3. This is the same window [3], so count[3] becomes 2. | `l = 1`<br>`nums = [3, 3, 3]` (l→1)<br>`count = {3→2}` |
| 8 | 12 | l = 2: H[2]·P[1] mod M = 2099826, so h = 2099829 − 2099826 = 3. count[3] becomes 3. | `l = 2`<br>`nums = [3, 3, 3]` (l→2)<br>`count = {3→3}` |
| 9 | 14 | Scan the map for L = 1. The only entry has c = 3, not 1, so no length-1 window is unique. Move on to L = 2. | `c = 3`<br>`nums = [3, 3, 3]` |
| 10 | 12 | L = 2, with the map reset. l = 0: h = H[2] − H[0]·P[2] = 300012. count[300012] becomes 1. | `L = 2`<br>`l = 0`<br>`h = 300012`<br>`nums = [3, 3, 3]` (l→0)<br>`count = {300012→1}` |
| 11 | 12 | l = 1: h = H[3] − H[1]·P[2] = 2099829 − 3·599939 = 2099829 − 1799817 = 300012. count[300012] becomes 2. | `l = 1`<br>`nums = [3, 3, 3]` (l→1)<br>`count = {300012→2}` |
| 12 | 14 | The only length-2 hash has c = 2, so [3,3] appears twice and is not unique. Move on to L = 3. | `c = 2`<br>`nums = [3, 3, 3]` |
| 13 | 12 | L = 3, with the map reset. The only window is l = 0: h = H[3] − H[0]·P[3] = 2099829. count[2099829] becomes 1. | `L = 3`<br>`l = 0`<br>`h = 2099829`<br>`nums = [3, 3, 3]` (l→0)<br>`count = {2099829→1}` |
| 14 | 15 | The map scan finds c = 1, so a length-3 window is unique and we return L = 3. | `c = 1`<br>`nums = [3, 3, 3]` |

**Result:** 3. Lengths 1 and 2 each produced only repeated hashes, and length 3 is the first length with a window whose hash appears exactly once.

**C++ solution**

```cpp
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const long long B = 100003;            // base larger than any value (max 1e5)
        const long long M1 = 1000000007LL;     // first modulus
        const long long M2 = 998244353LL;      // second modulus: double hash makes collisions negligible
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            H1[i + 1] = (H1[i] * B + nums[i]) % M1;   // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B + nums[i]) % M2;
            P1[i + 1] = (P1[i] * B) % M1;              // B^(i+1)
            P2[i + 1] = (P2[i] * B) % M2;
        }
        for (int L = 1; L <= n; ++L) {                 // try lengths from shortest up
            unordered_map<long long, int> cnt;
            cnt.reserve(2 * (n - L + 1));              // avoid rehashing
            for (int l = 0; l + L <= n; ++l) {
                // O(1) window hash: strip the prefix before l, shifted by B^L
                long long h1 = (H1[l + L] - H1[l] * P1[L] % M1 + M1) % M1;
                long long h2 = (H2[l + L] - H2[l] * P2[L] % M2 + M2) % M2;
                long long key = (h1 << 32) | h2;       // combine both hashes into one 64-bit key
                ++cnt[key];
            }
            for (auto& kv : cnt)
                if (kv.second == 1) return L;          // a window occurring exactly once
        }
        return n;                                      // unreachable: length n is always unique
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
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const long long B = 100003;            // base larger than any value (max 1e5)
        const long long M1 = 1000000007LL;     // first modulus
        const long long M2 = 998244353LL;      // second modulus: double hash makes collisions negligible
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            H1[i + 1] = (H1[i] * B + nums[i]) % M1;   // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B + nums[i]) % M2;
            P1[i + 1] = (P1[i] * B) % M1;              // B^(i+1)
            P2[i + 1] = (P2[i] * B) % M2;
        }
        for (int L = 1; L <= n; ++L) {                 // try lengths from shortest up
            unordered_map<long long, int> cnt;
            cnt.reserve(2 * (n - L + 1));              // avoid rehashing
            for (int l = 0; l + L <= n; ++l) {
                // O(1) window hash: strip the prefix before l, shifted by B^L
                long long h1 = (H1[l + L] - H1[l] * P1[L] % M1 + M1) % M1;
                long long h2 = (H2[l + L] - H2[l] * P2[L] % M2 + M2) % M2;
                long long key = (h1 << 32) | h2;       // combine both hashes into one 64-bit key
                ++cnt[key];
            }
            for (auto& kv : cnt)
                if (kv.second == 1) return L;          // a window occurring exactly once
        }
        return n;                                      // unreachable: length n is always unique
    }
};

int main() {
    Solution s;
    vector<vector<int>> tests = {{3, 3, 3}, {2, 1, 2, 3, 3}, {1, 1, 2, 2, 1}};
    vector<int> expected = {3, 1, 2};
    for (size_t t = 0; t < tests.size(); ++t) {
        int got = s.smallestUniqueSubarray(tests[t]);
        cout << "Example " << t + 1 << ": output = " << got << ", expected = " << expected[t] << "\n";
    }
    return 0;
}
```

</details>

**Why move on:** On `[3,3,...,3]` with n = 10^5 the answer is n, so this does about 10^10 hash operations, which is too slow. It ignores that uniqueness is monotone in `L`.

### 3. Optimal: Binary search on length + rolling hash

> **How you get here:** The scan over `L` checks lengths one by one even though `has_unique(L)` flips from false to true exactly once, so binary search needs only about log n checks.

**Idea.** Monotonicity: if the window at start i of length L is unique and L < n, extend it by one element. Any other copy of the extension would contain a second copy of the original window, so the extension is unique too. Therefore `has_unique` is false up to the answer and true from it onward, and `has_unique(n)` is always true. Binary search over `[1, n]`, evaluating `has_unique(mid)` with O(1) rolling-hash window fingerprints and a counting map. (A suffix array with LCP, or a suffix automaton, also works: shortest unique substring = min over suffixes of max(adjacent LCPs) + 1.)

**Steps**

1. Build prefix hashes and powers, using double hashing to avoid collisions.
2. Define has_unique(L): count the hashes of all n-L+1 windows of length L and report whether any count equals 1.
3. Set lo = 1, hi = n.
4. While lo < hi: let mid = (lo + hi) / 2.
5. If has_unique(mid), set hi = mid; otherwise set lo = mid + 1.
6. Return lo.

**Pseudocode**

```text
 1 │ function hasUnique(L):
 2 │   count ← empty map // fingerprint pair → number of windows with it
 3 │   for i from 0 to n − L:
 4 │     key ← ((H1[i+L] − H1[i]·P1[L]) mod M1, (H2[i+L] − H2[i]·P2[L]) mod M2) // O(1) hash of nums[i..i+L−1]
 5 │     count[key] ← count[key] + 1
 6 │   for each (key, c) in count:
 7 │     if c = 1: return true // some window of length L occurs exactly once
 8 │   return false
 9 │ function smallestUniqueSubarray(nums):
10 │   n ← length(nums)
11 │   H1[0] ← 0; H2[0] ← 0; P1[0] ← 1; P2[0] ← 1 // B1, B2 > 10^5 so values never alias; M1, M2 large primes
12 │   for i from 0 to n − 1:
13 │     H1[i+1] ← (H1[i]·B1 + nums[i]) mod M1
14 │     H2[i+1] ← (H2[i]·B2 + nums[i]) mod M2
15 │     P1[i+1] ← P1[i]·B1 mod M1; P2[i+1] ← P2[i]·B2 mod M2 // powers to shift a prefix hash
16 │   lo ← 1; hi ← n // hasUnique(n) is always true, so the answer is in [1, n]
17 │   while lo < hi:
18 │     mid ← floor((lo + hi) / 2)
19 │     if hasUnique(mid):
20 │       hi ← mid // mid works, and by monotonicity the answer is ≤ mid
21 │     else:
22 │       lo ← mid + 1 // no length ≤ mid works
23 │   return lo
```

**Time complexity: `O(n log n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Prefix hash and power build (lines 11-15) | n iterations × O(1) | Each prefix hash and power comes from the previous one with one multiply and one add. |
| One call of hasUnique (lines 1-8) | (n − L + 1) windows × O(1) expected, plus a scan of at most n map entries | Each window fingerprint is computed in constant time from the prefix hashes, and inserting it into a hash map costs O(1) on average. |
| Binary search loop (lines 16-22) | ⌈log2 n⌉ iterations × O(n) | Each iteration halves the range [lo, hi] and makes one hasUnique call. |

- **Adding it up:** O(n) + log2(n) · O(n) = O(n log n); the binary search dominates the linear setup
- **Best vs worst case:** Roughly the same for every input. The binary search always runs about log2 n rounds, and each round scans all n − mid + 1 windows. Only hash-map behaviour (collisions) could make it slower, and that is unlikely in practice.
- **At the maximum input:** n = 10^5 → about 17 rounds × 10^5 window hashes ≈ 1.7·10^6 map operations, well under 0.1 s

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Arrays H1, H2, P1, P2 (lines 11-15) | 4 × (n + 1) integers | One prefix hash and one power per position, for each of the two moduli. |
| count map inside hasUnique (line 2) | up to n − L + 1 entries | In the worst case every window is distinct. The map is thrown away after each call. |

- **Adding it up:** O(n) + O(n) = O(n)
- **Not counted:** The input array is not counted. There is no recursion; hasUnique only lives inside one binary-search round at a time.

**Dry run** on `nums = [3,3,3]  (B1 = 100003, M1 = 10^9+7, B2 = 100019, M2 = 10^9+9)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 10 | Read the length of the array: n = 3. | `n = 3`<br>`nums = [3, 3, 3]` |
| 2 | 11 | Initialise the empty-prefix hashes to 0 and the zeroth powers to 1. | `H1 = [0, -, -, -]`<br>`H2 = [0, -, -, -]`<br>`P1 = [1, -, -, -]`<br>`P2 = [1, -, -, -]` |
| 3 | 15 | i = 0: H1[1] = 0·100003 + 3 = 3 and H2[1] = 3. The powers become P1[1] = 100003 and P2[1] = 100019. | `i = 0`<br>`nums = [3, 3, 3]` (i→0)<br>`H1 = [0, 3, -, -]`<br>`H2 = [0, 3, -, -]`<br>`P1 = [1, 100003, -, -]`<br>`P2 = [1, 100019, -, -]` |
| 4 | 15 | i = 1: H1[2] = 3·100003 + 3 = 300012 and H2[2] = 3·100019 + 3 = 300060. The squared powers taken mod M1 and M2 are 599939 and 3800271. | `i = 1`<br>`nums = [3, 3, 3]` (i→1)<br>`H1 = [0, 3, 300012, -]`<br>`H2 = [0, 3, 300060, -]`<br>`P1 = [1, 100003, 599939, -]`<br>`P2 = [1, 100019, 3800271, -]` |
| 5 | 15 | i = 2: H1[3] = (300012·100003 + 3) mod M1 = 2099829 and H2[3] = 11700873. The cubed powers are 995699404 and 99301729. | `i = 2`<br>`nums = [3, 3, 3]` (i→2)<br>`H1 = [0, 3, 300012, 2099829]`<br>`H2 = [0, 3, 300060, 11700873]`<br>`P1 = [1, 100003, 599939, 995699404]`<br>`P2 = [1, 100019, 3800271, 99301729]` |
| 6 | 16 | The answer lies in [1, 3], because the whole array is always unique. | `lo = 1`<br>`hi = 3`<br>`nums = [3, 3, 3]` |
| 7 | 18 | lo = 1 < hi = 3, so the loop runs and mid = (1 + 3) / 2 = 2. Next we test whether some length-2 window is unique. | `mid = 2` |
| 8 | 5 | In hasUnique(2) with i = 0, window [3,3] has key (300012 − 0·599939, 300060 − 0·3800271) = (300012, 300060). Its count becomes 1. | `L = 2`<br>`i = 0`<br>`key = (300012,300060)`<br>`nums = [3, 3, 3]` (i→0)<br>`count = {(300012,300060)→1}` |
| 9 | 5 | With i = 1, the key is (2099829 − 3·599939, 11700873 − 3·3800271) = (300012, 300060). That is the same fingerprint, because the window is again [3,3], so its count rises to 2. | `i = 1`<br>`nums = [3, 3, 3]` (i→1)<br>`count = {(300012,300060)→2}` |
| 10 | 8 | The only entry has count 2, so no length-2 window is unique and hasUnique(2) returns false. | `nums = [3, 3, 3]` |
| 11 | 22 | Length 2 fails, so by monotonicity length 1 fails too. Set lo = mid + 1 = 3. | `lo = 3` |
| 12 | 17 | The check lo = 3 < hi = 3 is false, so the search range has shrunk to a single length and the loop ends. | (no change) |
| 13 | 23 | Return lo = 3. | (no change) |

**Result:** 3. No subarray of length 2 (and hence of length 1) is unique, while the full array of length 3 always is, so 3 is the smallest unique length.

**C++ solution**

```cpp
class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        // Two independent moduli (double hashing) make a false match astronomically unlikely
        const long long M1 = 1000000007LL, M2 = 1000000009LL;
        // Bases larger than the max value (1e5) so different arrays never alias before the mod
        const long long B1 = 100003LL, B2 = 100019LL;
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; i++) {
            H1[i + 1] = (H1[i] * B1 + nums[i]) % M1; // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B2 + nums[i]) % M2;
            P1[i + 1] = P1[i] * B1 % M1;             // B1^(i+1), used to shift prefixes
            P2[i + 1] = P2[i] * B2 % M2;
        }
        // Returns true if some window of length L occurs exactly once
        auto hasUnique = [&](int L) {
            unordered_map<unsigned long long, int> cnt;
            cnt.reserve(2 * (n - L + 1)); // avoid rehashing
            for (int i = 0; i + L <= n; i++) {
                // O(1) fingerprint of nums[i..i+L-1]; products stay below ~1e18, so they fit in long long
                long long a = ((H1[i + L] - H1[i] * P1[L]) % M1 + M1) % M1;
                long long b = ((H2[i + L] - H2[i] * P2[L]) % M2 + M2) % M2;
                // Both hashes are below 2^30, so pack them into one 64-bit key
                unsigned long long key = ((unsigned long long)a << 32) | (unsigned long long)b;
                cnt[key]++;
            }
            for (auto& p : cnt)
                if (p.second == 1) return true; // found a window occurring exactly once
            return false;
        };
        int lo = 1, hi = n; // hasUnique(n) is always true
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUnique(mid)) hi = mid; // answer <= mid (monotonic predicate)
            else lo = mid + 1;            // answer > mid
        }
        return lo;
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
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        // Two independent moduli (double hashing) make a false match astronomically unlikely
        const long long M1 = 1000000007LL, M2 = 1000000009LL;
        // Bases larger than the max value (1e5) so different arrays never alias before the mod
        const long long B1 = 100003LL, B2 = 100019LL;
        vector<long long> H1(n + 1, 0), H2(n + 1, 0), P1(n + 1, 1), P2(n + 1, 1);
        for (int i = 0; i < n; i++) {
            H1[i + 1] = (H1[i] * B1 + nums[i]) % M1; // prefix hash of nums[0..i]
            H2[i + 1] = (H2[i] * B2 + nums[i]) % M2;
            P1[i + 1] = P1[i] * B1 % M1;             // B1^(i+1), used to shift prefixes
            P2[i + 1] = P2[i] * B2 % M2;
        }
        // Returns true if some window of length L occurs exactly once
        auto hasUnique = [&](int L) {
            unordered_map<unsigned long long, int> cnt;
            cnt.reserve(2 * (n - L + 1)); // avoid rehashing
            for (int i = 0; i + L <= n; i++) {
                // O(1) fingerprint of nums[i..i+L-1]; products stay below ~1e18, so they fit in long long
                long long a = ((H1[i + L] - H1[i] * P1[L]) % M1 + M1) % M1;
                long long b = ((H2[i + L] - H2[i] * P2[L]) % M2 + M2) % M2;
                // Both hashes are below 2^30, so pack them into one 64-bit key
                unsigned long long key = ((unsigned long long)a << 32) | (unsigned long long)b;
                cnt[key]++;
            }
            for (auto& p : cnt)
                if (p.second == 1) return true; // found a window occurring exactly once
            return false;
        };
        int lo = 1, hi = n; // hasUnique(n) is always true
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUnique(mid)) hi = mid; // answer <= mid (monotonic predicate)
            else lo = mid + 1;            // answer > mid
        }
        return lo;
    }
};

int main() {
    Solution sol;
    vector<pair<vector<int>, int>> tests = {
        {{3, 3, 3}, 3},
        {{2, 1, 2, 3, 3}, 1},
        {{1, 1, 2, 2, 1}, 2}
    };
    for (auto& t : tests) {
        vector<int> nums = t.first;
        int got = sol.smallestUniqueSubarray(nums);
        cout << "Output: " << got << "  Expected: " << t.second << (got == t.second ? "  OK" : "  MISMATCH") << "\n";
    }
    return 0;
}
```

</details>

**Why this is the best:** It is probabilistic: a hash collision could merge two different windows. Double hashing makes this negligible. A suffix automaton gives a deterministic O(n) solution but is much harder to implement. Any solution must read all n values, so log n is the only gap from linear.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| nums = [1,2,1,2] | 2 | Alternating pattern; [2,1] is unique. |
| nums = [5,5,5,5,1] | 1 | Single unique element at the end. |
| nums = [1,2,1,2,1] | 3 | Overlapping repeats force length 3. |
| nums = [4,4,7,4,4,7] | 2 | Repeated block; the junction pair is unique. |
| nums = [1,2,3,1,2,3] | 2 | Doubled sequence; the wrap pair [3,1] is unique. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single element | nums = [7] | 1 | Whole array is unique. |
| Two equal elements | nums = [2,2] | 2 | Only the full array is unique. |
| All equal | nums = [1,1,1,1,1] | 5 | Answer equals n. |
| Max and min values | nums = [100000,1] | 1 | Both elements are unique. |
| All distinct | nums = [1,2,3,4,5] | 1 | Any single element is unique. |
| Long periodic array | nums = [1,2,1,2,1,2] | 4 | Uniqueness appears only at length 4. |

## Mistakes and edge cases

**Common mistakes**

- Counting only non-overlapping occurrences. In `[3,3,3]` the window `[3,3]` appears at indices 0 and 1, so it is not unique, and the answer is 3, not 2.
- Using a base no larger than the maximum element (values go up to 10^5) or a single small modulus. Collisions then make a truly unique window look repeated and push the answer too high.
- Treating 'distinct' as 'unique'. The test is whether some window has count exactly 1, not whether the number of distinct windows equals n-L+1.
- Binary searching without justifying monotonicity, or setting hi below n. The answer can be n itself (all-equal array), and length n is always unique.

**Edge cases to check**

- n = 1, e.g. `[5]`: the only window is unique, so the answer is 1. This checks the search bounds lo = hi = 1.
- All elements equal, e.g. `[3,3,3]`: every shorter length repeats, so the answer is n. This is the worst case for the linear scan and checks that hi starts at n.
- All elements distinct: every single element is unique, so the answer is 1 immediately.
- A unique element that only appears in the middle, e.g. `[2,1,2,3,3]`: the answer is 1 even though most values repeat. The check must look for any count of 1, not all.
- Periodic arrays like `[1,2,1,2,1,2]`: uniqueness appears only at large L near the ends, which tests overlapping-window counting.

## Practice next

- [Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/) · It is the mirror problem: binary search on length plus a rolling hash, looking for a repeated window instead of a unique one.
- [Maximum Length of Repeated Subarray](https://leetcode.com/problems/maximum-length-of-repeated-subarray/) · It binary searches on length and compares rolling hashes of integer subarrays across two arrays.
- [Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/) · It counts fixed-length windows with a rolling fingerprint and filters by occurrence count, which is exactly the has_unique check.
- [Longest Repeating Substring](https://leetcode.com/problems/longest-repeating-substring/) · The same monotone length property makes binary search plus hashing, or a suffix array, the standard solution.

## Takeaways

- When the question is 'smallest or largest length with property X' and X is monotone in length (extending a unique window keeps it unique), binary search on the answer with an O(n) checker.
- Rolling polynomial hashes turn 'compare all windows of length L' into O(n) integer work. Use a base larger than the alphabet and double hashing for safety.
- Prove monotonicity explicitly with an extension or containment argument before binary searching. Here, any copy of the extended window would contain a copy of the original.
- Substring-uniqueness and repetition questions on arrays are string problems in disguise, so suffix arrays, LCP and suffix automata are deterministic alternatives.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
