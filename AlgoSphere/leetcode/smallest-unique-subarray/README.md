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

**Complexity:** time `O(n^3)`, space `O(n^2)`. There are up to n lengths, each with about n windows, and hashing or copying each window costs O(L). An all-equal input forces every length to be checked, giving roughly n^3/6 work. The map can hold about n windows of length up to n.

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

**Complexity:** time `O(n^2)`, space `O(n)`. Each length costs O(n) for hashing and counting, and in the worst case (answer near n) all n lengths are tried. The prefix arrays and the per-length map use O(n) memory.

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

**Complexity:** time `O(n log n)`, space `O(n)`. About log2(10^5) ≈ 17 calls to has_unique, each O(n) for hashing and map counting. Memory is the prefix and power arrays plus one hash map of at most n entries.

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
