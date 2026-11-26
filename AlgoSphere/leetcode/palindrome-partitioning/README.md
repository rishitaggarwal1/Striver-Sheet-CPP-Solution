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

**Pseudocode**

```text
 1 │ function partition(s):
 2 │   n ← length(s)
 3 │   result ← empty list of lists
 4 │   for mask ← 0 to 2^(n−1) − 1:  // n−1 gaps, each either cut or not
 5 │     pieces ← empty list
 6 │     start ← 0  // first index of the current piece
 7 │     ok ← true
 8 │     for k ← 0 to n − 1:
 9 │       if k = n − 1 or bit k of mask = 1:  // piece ends at k (string end or cut after k)
10 │         lo ← start; hi ← k
11 │         while lo < hi and s[lo] = s[hi]:  // two-pointer palindrome check
12 │           lo ← lo + 1; hi ← hi − 1
13 │         if lo < hi:  // stopped early, so a mismatch was found
14 │           ok ← false
15 │           break  // this mask can't be valid; skip the rest
16 │         append s[start..k] to pieces
17 │         start ← k + 1  // the next piece begins right after the cut
18 │     if ok:
19 │       append pieces to result
20 │   return result
```

**Time complexity: `O(n · 2^n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Outer mask loop (lines 4-19) | 2^(n−1) iterations × (cost of one split) | Each of the n−1 gaps between characters is either cut or not, so there are exactly 2^(n−1) masks. |
| Index walk (lines 8-9, 17) | n iterations × O(1) per mask | Every index is visited once to decide whether a piece ends there. |
| Palindrome checks (lines 10-15) | O(n) total per mask | The pieces don't overlap, so the two-pointer checks together touch each character at most once. |
| Building pieces (line 16, line 19) | O(n) per mask | The substrings copied for one mask have total length n. |

- **Adding it up:** 2^(n−1) × (O(n) walk + O(n) checks + O(n) copying) = 2^(n−1) · O(n) = O(n · 2^n)
- **Best vs worst case:** Best case: a mask fails at its first piece, for example a long uncut prefix that isn't a palindrome, so the work for that mask stops early. Worst case: s = "aaaa…a". Every mask is valid, and each one does the full O(n) work plus an O(n) copy into the result.
- **At the maximum input:** n = 16 → 2^15 = 32,768 masks × about 16·3 operations ≈ 1.5·10^6 steps, well under a millisecond.

**Space complexity: `O(n)`**

| Part | Cost | Why |
| --- | --- | --- |
| pieces list (lines 5, 16) | O(n) | It holds the substrings of one split, whose total length is n. |
| Scalars mask, start, ok, k, lo, hi (lines 4-12) | O(1) | A fixed number of integers and booleans. |

- **Adding it up:** O(n) + O(1) = O(n)
- **Not counted:** The result list is not counted. It can hold up to 2^(n−1) partitions of total size O(n · 2^n). There is no recursion, so there is no stack depth to count.

**Dry run** on `s = "aab"`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 3 | n = 3, so there are 2 gaps and 2^2 = 4 masks (0..3) to try. The result starts empty. | `n = 3`<br>`s = [a, a, b]`<br>`result = []` |
| 2 | 7 | mask = 0 (binary 00) means no cuts at all. A fresh, empty pieces list is set up with start = 0 and ok = true. | `mask = 0`<br>`start = 0`<br>`ok = true`<br>`s = [a, a, b]` (start→0)<br>`pieces = []` |
| 3 | 14 | k = 0 and k = 1 have no cut bit. At k = 2 (string end) we check "aab": lo = 0, hi = 2, and 'a' ≠ 'b'. The check stops at once with lo < hi, so ok becomes false. | `ok = false`<br>`k = 2`<br>`lo = 0`<br>`hi = 2`<br>`s = [a, a, b]` (start→0, lo→0, hi→2, k→2) |
| 4 | 17 | mask = 1 (binary 01) means cut after index 0. At k = 0 the piece "a" is a palindrome, so it is appended and start moves to 1. | `mask = 1`<br>`start = 1`<br>`ok = true`<br>`k = 0`<br>`hi = 0`<br>`s = [a, a, b]` (start→1, k→0)<br>`pieces = ["a"]` |
| 5 | 14 | k = 1 has no cut bit. At k = 2 the piece is s[1..2] = "ab", and 'a' ≠ 'b', so ok = false. We break, and mask 1 is discarded. | `ok = false`<br>`k = 2`<br>`lo = 1`<br>`hi = 2`<br>`s = [a, a, b]` (start→1, lo→1, hi→2, k→2) |
| 6 | 17 | mask = 2 (binary 10) means cut after index 1. At k = 1 we check "aa": s[0] = s[1], so lo moves to 1 and hi to 0, and the loop ends with lo ≥ hi. The piece "aa" is appended and start = 2. | `mask = 2`<br>`start = 2`<br>`ok = true`<br>`k = 1`<br>`hi = 0`<br>`s = [a, a, b]` (start→2, k→1)<br>`pieces = ["aa"]` |
| 7 | 17 | At k = 2 (end), the piece "b" has length 1 and is trivially a palindrome. It is appended and start = 3. | `start = 3`<br>`k = 2`<br>`lo = 2`<br>`hi = 2`<br>`s = [a, a, b]` (k→2)<br>`pieces = ["aa", "b"]` |
| 8 | 19 | ok is still true, so every piece passed. ["aa","b"] is added to result. | `s = [a, a, b]`<br>`result = [[aa,b]]` |
| 9 | 17 | mask = 3 (binary 11) means cut after both index 0 and index 1. At k = 0 the piece "a" is appended and start = 1. | `mask = 3`<br>`start = 1`<br>`k = 0`<br>`lo = 0`<br>`hi = 0`<br>`s = [a, a, b]` (start→1, k→0)<br>`pieces = ["a"]` |
| 10 | 17 | At k = 1 bit 1 is set, so the piece s[1..1] = "a" is appended and start = 2. | `start = 2`<br>`k = 1`<br>`lo = 1`<br>`hi = 1`<br>`s = [a, a, b]` (start→2, k→1)<br>`pieces = ["a", "a"]` |
| 11 | 17 | At k = 2 (end), the piece "b" is appended and start = 3. | `start = 3`<br>`k = 2`<br>`lo = 2`<br>`hi = 2`<br>`s = [a, a, b]` (k→2)<br>`pieces = ["a", "a", "b"]` |
| 12 | 19 | All three pieces passed, so ["a","a","b"] is added to result. | `s = [a, a, b]`<br>`result = [[aa,b], [a,a,b]]` |
| 13 | 20 | All 4 masks have been tried, so the result is returned. | (no change) |

**Result:** [["aa","b"],["a","a","b"]]. This is the expected output in a different order, which LeetCode accepts. Every possible cut pattern was tried exactly once, and only those whose pieces are all palindromes were kept.

**C++ solution**

```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> result;
        // each of the n-1 gaps is cut (bit=1) or not (bit=0)
        for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
            vector<string> pieces;   // pieces of this split
            int start = 0;           // start index of current piece
            bool ok = true;          // all pieces palindromes so far?
            for (int k = 0; k < n; ++k) {
                // a piece ends at k if we're at the string end or there's a cut after k
                if (k == n - 1 || ((mask >> k) & 1)) {
                    int lo = start, hi = k;
                    // two-pointer palindrome check on s[start..k]
                    while (lo < hi && s[lo] == s[hi]) { ++lo; --hi; }
                    if (lo < hi) { ok = false; break; } // mismatch: reject this mask
                    pieces.push_back(s.substr(start, k - start + 1));
                    start = k + 1;   // next piece starts after the cut
                }
            }
            if (ok) result.push_back(pieces); // keep only fully valid splits
        }
        return result;
    }
};
```

<details>
<summary>Full program with <code>main()</code> (compile and run locally)</summary>

```cpp
#include <bits/stdc++.h>
using namespace std;

string show(const vector<vector<string>>& v) {
    string out = "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) out += ",";
        out += "[";
        for (size_t j = 0; j < v[i].size(); ++j) {
            if (j) out += ",";
            out += "\"" + v[i][j] + "\"";
        }
        out += "]";
    }
    return out + "]";
}

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        vector<vector<string>> result;
        // each of the n-1 gaps is cut (bit=1) or not (bit=0)
        for (int mask = 0; mask < (1 << (n - 1)); ++mask) {
            vector<string> pieces;   // pieces of this split
            int start = 0;           // start index of current piece
            bool ok = true;          // all pieces palindromes so far?
            for (int k = 0; k < n; ++k) {
                // a piece ends at k if we're at the string end or there's a cut after k
                if (k == n - 1 || ((mask >> k) & 1)) {
                    int lo = start, hi = k;
                    // two-pointer palindrome check on s[start..k]
                    while (lo < hi && s[lo] == s[hi]) { ++lo; --hi; }
                    if (lo < hi) { ok = false; break; } // mismatch: reject this mask
                    pieces.push_back(s.substr(start, k - start + 1));
                    start = k + 1;   // next piece starts after the cut
                }
            }
            if (ok) result.push_back(pieces); // keep only fully valid splits
        }
        return result;
    }
};

int main() {
    Solution sol;
    cout << "Example 1: " << show(sol.partition("aab")) << "  expected (any order): [[\"a\",\"a\",\"b\"],[\"aa\",\"b\"]]" << endl;
    cout << "Example 2: " << show(sol.partition("a")) << "  expected: [[\"a\"]]" << endl;
    return 0;
}
```

</details>

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
