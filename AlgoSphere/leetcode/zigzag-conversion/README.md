# Zigzag Conversion

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/zigzag-conversion/)

## Problem

<details>
<summary>Problem statement</summary>

```text
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:

Input: s = "A", numRows = 1
Output: "A"

Constraints:

- 1 <= s.length <= 1000

- s consists of English letters (lower-case and upper-case), ',' and '.'.

- 1 <= numRows <= 1000
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You write the characters one by one, moving down through the rows and then diagonally back up, over and over. The answer is every character in row 0 in the order written, then every character in row 1, and so on to the last row.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Only the row each character lands in matters; the horizontal spacing in the picture is irrelevant. With 3 rows the row numbers go 0,1,2,1,0,1,2,1,... so they bounce between the top row and the bottom row.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

Both the string length and `numRows` are at most 1000, so even an `O(n * numRows)` grid simulation would pass. Still, a clean `O(n)` solution exists in which every character is touched a constant number of times.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a simulation problem: walk through the string once, track a position that moves back and forth, and group characters into buckets. A direct index formula based on the cycle length `2*numRows - 2` is an alternative way to do the same thing.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

You never need a 2D grid. Keep a current row and a direction, add each character to its row's bucket, and flip the direction whenever you reach the top or bottom row.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Store one growing string (or list of characters) per row, a current row index starting at 0, and a step of +1 or -1. Bucket `i` holds the characters of row `i` in left-to-right order, and the step says whether you are moving down or up.

</details>

<details>
<summary>Hint 7 · Approach</summary>

If `numRows` is 1 or at least the string length, return `s` unchanged.
Create `numRows` empty buckets, set row = 0 and step = +1.
For each character, append it to the bucket for the current row.
If row is 0, set step to +1; if row is `numRows-1`, set step to -1.
Add step to row.
Concatenate all buckets from top to bottom and return the result.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest case is `numRows = 1`: the top and bottom rows are the same, so the direction flips every step and the row index goes out of range unless you return early. Also handle strings shorter than `numRows`, where some buckets stay empty, and update the direction before you move the row. Time is `O(n)` and extra space is `O(n)` for the buckets, or `O(1)` beyond the output if you use the cycle formula `2*numRows-2` and read each row directly.

</details>

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
