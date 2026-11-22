# Check if All A's Appears Before All B's

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/) · ✅ Solved in C++

**Contents:** [Problem](#problem) · [Hints](#hints) · [My solution](#my-solution) · [Test cases](#test-cases)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.

Example 1:

Input: s = "aaabbb"
Output: true
Explanation:
The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
Hence, every 'a' appears before every 'b' and we return true.

Example 2:

Input: s = "abab"
Output: false
Explanation:
There is an 'a' at index 2 and a 'b' at index 1.
Hence, not every 'a' appears before every 'b' and we return false.

Example 3:

Input: s = "bbb"
Output: true
Explanation:
There are no 'a's, hence, every 'a' appears before every 'b' and we return true.

Constraints:

- 1 <= s.length <= 100

- s[i] is either 'a' or 'b'.
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to decide whether the string looks like some run of 'a's followed by some run of 'b's, with no 'a' ever showing up after a 'b'. Either run is allowed to be empty.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Look at Example 2, "abab": the problem is caused by a 'b' immediately followed by an 'a'. In any valid string, once the first 'b' appears, every character after it must also be 'b'.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

The string has at most 100 characters, so even comparing every pair of positions would be fast enough. Still, a single left-to-right pass is easy here and is the natural target.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a simple linear scan, or equivalently a check for a forbidden adjacent pattern. Validity depends only on the order of characters, so looking at each character once is enough.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

The string is invalid exactly when some 'b' is directly followed by an 'a', so you only need to check whether the substring "ba" occurs anywhere. If any 'a' comes after any 'b', then somewhere between them there must be an adjacent "ba" pair.

</details>

<details>
<summary>Hint 6 · What to track</summary>

If you scan instead of searching for a substring, keep one boolean flag meaning 'a b has been seen so far'. When you meet an 'a' while that flag is already true, you can stop and return false.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Start with the flag `seenB` set to false.
Walk through the characters from left to right.
If the character is 'b', set `seenB` to true.
If the character is 'a' and `seenB` is true, return false.
If you finish the walk without returning, return true.
As a shortcut, you can simply return whether "ba" does not occur in `s`.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The subtle part is that strings with no 'a' ("bbb") or no 'b' ("aaa") are valid, and so is any single-character string. The flag approach handles all of these without special cases. Time is `O(n)` and extra space is `O(1)`.

</details>

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-22 |

```cpp
class Solution {
public:
    bool checkString(string s) {
        bool a = true;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='b')
            {
                a=false;
            }
            else
            {
                if(!a)  return false;
            }
        }
        return true;
    }
};
```

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| s = "aabbb" | true | Block of a's followed by block of b's. |
| s = "abba" | false | An a appears after b's at the end. |
| s = "aaab" | true | Single b after several a's. |
| s = "baaa" | false | Leading b followed by a's. |
| s = "aabbab" | false | A stray a sits in the middle of the b's. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single a | s = "a" | true | Minimum length with no b's. |
| Single b | s = "b" | true | Minimum length with no a's. |
| All a's | s = "aaaa" | true | No b present at all. |
| Smallest invalid | s = "ba" | false | B directly before a. |
| Smallest valid mix | s = "ab" | true | A directly before b. |
| Trailing a | s = "bbbbba" | false | The violation is only at the last index. |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
