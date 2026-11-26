# Palindrome Partitioning

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/palindrome-partitioning/) · Pattern: **Backtracking with precomputed palindrome DP table**

> List every way to cut the string `s` into consecutive pieces so that each piece reads the same forwards and backwards.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Example 1:

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:

Input: s = "a"
Output: [["a"]]

Constraints:

- 1 <= s.length <= 16

- s contains only lowercase English letters.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to list every way to cut the string into consecutive pieces so that each piece reads the same forwards and backwards. Every character must belong to exactly one piece, and the order of characters never changes.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Any partition is decided by choosing the first piece: a prefix that is a palindrome. Whatever remains after that prefix is a smaller version of the same problem. Single characters are always palindromes, so at least one valid partition always exists.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With length at most 16 there are only `2^15` ways to place cuts, and the output itself can be exponentially large (for example a string of all 'a's). So an exponential enumeration is expected and fine; the goal is just to avoid wasted work.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking: build a partition piece by piece, explore every choice, then undo the last choice and try the next one. It fits because the problem asks for all valid combinations, not a count or a single best answer.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

From a start index, only extend the search with an end index where `s[start..end]` is a palindrome. That prunes invalid branches immediately. To make each palindrome check `O(1)`, precompute a table `isPal[i][j]` using the rule that `s[i..j]` is a palindrome when `s[i]==s[j]` and either `j-i<2` or `isPal[i+1][j-1]` is true.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track the current list of chosen pieces (the path) and the current start index, meaning everything before it is already partitioned. Also keep the 2D boolean table `isPal[i][j]`, which says whether the substring from i to j inclusive is a palindrome, plus the result list.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Fill `isPal` with i going from the end of the string down to 0, and j from i up to the end.
Call a recursive explore(start) with an empty path.
If start equals the string length, add a copy of the path to the results.
Otherwise loop end from start to the last index.
If `isPal[start][end]` is true, append that substring to the path and explore(end+1).
After returning, remove the last piece from the path (backtrack).

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest parts are filling the DP table in an order where `isPal[i+1][j-1]` is already known, and saving a copy of the path rather than the reused list itself. A length-1 string yields just one partition, and an all-same-letter string produces the maximum `2^(n-1)` partitions. Time is `O(n * 2^n)` because building the output dominates; space is `O(n^2)` for the table plus `O(n)` recursion depth, not counting the output.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "Return all possible palindrome partitioning" | we must enumerate every answer, not count them, so the output itself can be exponential; this points to backtracking. |
| "1 <= s.length <= 16" | there are only n-1 = 15 cut positions, so 2^15 = 32768 cut patterns at most; exponential search is fine. |
| "every substring of the partition is a palindrome" | the same question "is `s[i..j]` a palindrome?" gets asked many times, so precompute it once in an n×n table. |
| Example "aab" gives ["a","a","b"] and ["aa","b"] | each answer is a choice of the first piece followed by a partition of the remaining suffix, which is a recursive structure. |

### What the constraints tell you

n ≤ 16, so there are at most 2^15 = 32768 partitions, and each has total length 16. Even O(n · 2^n) ≈ 16 · 65536 ≈ 10^6 operations is trivial. The real target is to avoid redundant work: O(n · 2^n) overall, with O(n^2) palindrome precomputation.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most naive way to see the answer space?**

<details>
<summary>Answer</summary>

Between each pair of adjacent characters we either cut or don't, so there are 2^(n-1) ways to split `s`. For "aab" that is 4 splits: aab, a|ab, aa|b, a|a|b. Keep those whose every piece is a palindrome.

</details>

**Q2. Can I prune instead of generating every split and filtering afterward?**

<details>
<summary>Answer</summary>

Yes. Build the split left to right: choose a first piece `s[start..end]`, and only continue if it is a palindrome. Then the bad prefix "ab" in "a|ab" is never extended.

</details>

**Q3. What does the recursive state look like?**

<details>
<summary>Answer</summary>

`start` is the index where the unpartitioned suffix begins, and `path` holds the pieces chosen so far. When `start == n`, `path` is a complete valid partition. Otherwise, try every `end` from `start` to n-1.

</details>

**Q4. Where is work being repeated?**

<details>
<summary>Answer</summary>

Checking `s[start..end]` with two pointers costs O(n), and the same (start, end) pair is checked again in many different branches. With 2^n branches, that is a lot of rescanning.

</details>

**Q5. How do I answer "is s[i..j] a palindrome" in O(1)?**

<details>
<summary>Answer</summary>

Precompute `isPal[i][j]` = `s[i]==s[j]` and (`j-i<2` or `isPal[i+1][j-1]`). Fill it with i going from n-1 down to 0, so that `isPal[i+1][j-1]` is already computed when it is needed.

</details>

**Q6. Is the remaining cost unavoidable?**

<details>
<summary>Answer</summary>

Mostly. The string "aaaa…a" has 2^(n-1) valid partitions, and copying each one costs O(n). So O(n · 2^n) is the size of the output itself, and the backtracking with O(1) checks matches it.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Enumerate all cut masks, then filter](#1-brute-force-enumerate-all-cut-masks-then-filter) | `O(n · 2^n)` | `O(n) besides output` |
| 2 | [Better: Backtracking with on-the-fly palindrome checks](#2-better-backtracking-with-on-the-fly-palindrome-checks) | `O(n^2 · 2^n) worst case` | `O(n) recursion besides output` |
| 3 | [Optimal: Backtracking + isPal DP table](#3-optimal-backtracking--ispal-dp-table) | `O(n · 2^n)` | `O(n^2) besides output` |

### 1. Brute force: Enumerate all cut masks, then filter

> **Where you start:** Each partition is just a set of cut positions, and a bitmask over n-1 gaps is the most mechanical way to list them all.

**Idea.** Loop over every mask from 0 to 2^(n-1)-1, where bit k means "cut after index k". Split `s` into pieces according to the mask, then check each piece with two pointers. Keep the split only if every piece is a palindrome. It is correct because every partition corresponds to exactly one mask.

**Steps**

1. Let n = length of `s`.
2. For each mask in [0, 2^(n-1)), walk the indices and cut after index k whenever bit k is set.
3. For each resulting piece, run a two-pointer palindrome check.
4. If all pieces pass, add the list of pieces to the result.
5. Return the result.

**Complexity:** time `O(n · 2^n)`, space `O(n) besides output`. There are 2^(n-1) masks, and each needs O(n) work to split and check. Extra memory is only the current list of pieces.

**Why move on:** It always does the full 2^(n-1) work, even when almost nothing is a palindrome. For example, "abcd…" has only one valid partition, yet every mask is still built and checked. It is fine at n=16, but it prunes nothing.

### 2. Better: Backtracking with on-the-fly palindrome checks

> **How you get here:** Masks whose first piece is not a palindrome are all doomed. Deciding pieces left to right lets us abandon a whole family of masks at the first bad piece.

**Idea.** Define `dfs(start, path)`. If `start == n`, record a copy of `path`. Otherwise, for each `end` in [start, n-1], check `s[start..end]` with two pointers. If it is a palindrome, push it, recurse on `dfs(end+1)`, then pop. Correctness: every valid partition has a palindromic first piece followed by a valid partition of the suffix, and the loop tries every possible first piece.

**Steps**

1. Start with `dfs(0, [])`.
2. If `start == n`, append a copy of `path` to the result and return.
3. For each `end` from `start` to n-1, test whether `s[start..end]` is a palindrome by comparing characters inward.
4. If it is, push the substring, call `dfs(end+1)`, then pop it (backtrack).
5. Return the result.

**Complexity:** time `O(n^2 · 2^n) worst case`, space `O(n) recursion besides output`. Each recursive node loops over up to n ends and runs an O(n) check for each, which multiplies the exponential node count by up to n^2 instead of n. Memory is the recursion stack plus `path`, both depth ≤ n.

**Why move on:** The same substring, such as `s[2..5]`, is re-verified in every branch that reaches start=2. That wastes an O(n) factor.

### 3. Optimal: Backtracking + isPal DP table

> **How you get here:** The two-pointer checks in the Better approach recompute answers for the same (start, end) pairs across branches. There are only n^2 such pairs, so compute them all once.

**Idea.** First build the boolean table `isPal[i][j]`, which is true iff `s[i]==s[j]` and the inside `s[i+1..j-1]` is a palindrome (or has length < 2). Fill i from n-1 down to 0 and j from i up to n-1, so inner entries are ready. Then run the same backtracking, but each palindrome test is an O(1) lookup. The search tree still explores exactly the valid prefixes, so the result is identical.

**Steps**

1. Create an n×n boolean table `isPal`.
2. For i from n-1 down to 0, and j from i to n-1: set `isPal[i][j] = s[i]==s[j] && (j-i<2 || isPal[i+1][j-1])`.
3. Call `dfs(0, [])`.
4. In `dfs(start)`, if `start == n`, save a copy of `path`.
5. Otherwise, for each `end` with `isPal[start][end]` true, push `s[start..end]`, recurse on `end+1`, then pop.
6. Return all saved partitions.

**Complexity:** time `O(n · 2^n)`, space `O(n^2) besides output`. The table costs O(n^2). The backtracking produces up to 2^(n-1) partitions, each costing O(n) to build and copy, so this term dominates. The table uses O(n^2) memory, and the recursion uses O(n).

**Why this is the best:** The output alone can be Θ(n · 2^n) characters (all 'a's), so no algorithm can do better asymptotically. The only cost is O(n^2) extra memory for the table.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| s = "aba" | [["a","b","a"],["aba"]] | Odd-length palindrome as a whole string. |
| s = "abba" | [["a","b","b","a"],["a","bb","a"],["abba"]] | Even-length palindrome with a nested palindrome. |
| s = "abc" | [["a","b","c"]] | No multi-character palindromes, so only single characters. |
| s = "efe" | [["e","f","e"],["efe"]] | Short string that is itself a palindrome. |
| s = "abbab" | [["a","b","b","a","b"],["a","b","bab"],["a","bb","a","b"],["abba","b"]] | Overlapping palindromes across different positions. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single character | s = "z" | [["z"]] | Only one partition exists. |
| Two equal characters | s = "aa" | [["a","a"],["aa"]] | Two partitions. |
| Two distinct characters | s = "ab" | [["a","b"]] | Only the single-character split. |
| All equal characters | s = "aaa" | [["a","a","a"],["a","aa"],["aa","a"],["aaa"]] | Every split is valid, giving 2^(n-1) partitions. |
| Max length all-equal | s = "aaaaaaaaaaaaaaaa" | 32768 partitions (every split of the 16 a's is valid) | Produces 2^15 = 32768 partitions; full list omitted. |
| Max length all-distinct | s = "abcdefghijklmnop" | [["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p"]] | Only one partition, into single characters. |

## Mistakes and edge cases

**Common mistakes**

- Appending `path` itself instead of a copy. Later backtracking pops mutate it, so every saved answer ends up empty or identical.
- Filling `isPal` with i increasing. Then `isPal[i+1][j-1]` has not been computed yet and reads as false, so palindromes like "aba" are missed.
- Forgetting to pop after the recursive call. Pieces from an earlier branch leak into later partitions.
- Using an off-by-one substring end, for example `s.substring(start, end)` where `end+1` is needed, which drops the last character of each piece.

**Edge cases to check**

- `s = "a"`: the single-character base case must return [["a"]], not [].
- `s = "aaaa…a"` with length 16: every substring is a palindrome, so 2^15 partitions are produced. This is the worst case for time and output size.
- `s = "abcdef"`: no multi-letter palindromes exist, so only the all-singletons partition remains. This checks that pruning works.
- `s = "aba"`: the length-3 palindrome depends on the inner entry `isPal[1][1]`. This verifies the DP fill order.

## Practice next

- [Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/) · Same `isPal` table and the same "choose a palindromic first piece" structure, but you minimise cuts with DP instead of enumerating.
- [Word Break II](https://leetcode.com/problems/word-break-ii/) · Same idea of enumerating all ways to split a string into valid pieces with backtracking from a start index.
- [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) · Uses the identical `isPal[i][j]` recurrence based on the inner substring.
- [Subsets](https://leetcode.com/problems/subsets/) · Same choose / recurse / un-choose backtracking template over a small n with 2^n outputs.

## Takeaways

- When asked to return all solutions and n is tiny (≤ 16 to 20), exponential backtracking is expected. Focus on pruning and on cheap per-node work.
- Partitioning a string usually recurses on "pick the first piece, then solve the suffix starting at `start`".
- If a predicate on a substring (i, j) is queried repeatedly, precompute an n×n table. Make sure the fill order computes dependencies such as `[i+1][j-1]` first.
- When saving a result from a mutable backtracking path, always store a copy.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
