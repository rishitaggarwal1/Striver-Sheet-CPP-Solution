# Palindrome Partitioning

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/palindrome-partitioning/)

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
