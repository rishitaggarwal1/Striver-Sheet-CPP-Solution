# Zigzag Conversion

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/zigzag-conversion/) · Pattern: **Simulation, then periodic index arithmetic**

> Write the characters of `s` down and up across `numRows` rows in a bouncing pattern, then concatenate the rows from top to bottom.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

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

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "written in a zigzag pattern" and then "read line by line" | each character only needs a row label; the visual columns are irrelevant to the output. |
| In Example 2 the row sequence is 0,1,2,3,2,1,0,1,... | the path bounces with period `2*numRows - 2`. That suggests either a direction flag or a modulo formula. |
| Example 3 has `numRows = 1` | a degenerate case where the bounce never happens and the period formula gives 0. It must be special-cased. |
| `s.length <= 1000` and `numRows <= 1000` | the inputs are tiny. The real goal is a clean O(n) pass, not survival against a time limit. |

### What the constraints tell you

n = `s.length` ≤ 1000 and numRows ≤ 1000. A full 2D grid costs about numRows · n/2 ≈ 5·10^5 cells, which is acceptable but wasteful. An O(n) pass is about 10^3 operations, so O(n) is the natural target. Output size is n, so you cannot do better than that.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most literal way to do this?**

<details>
<summary>Answer</summary>

Draw the picture: make a 2D char grid, walk down a column, then go diagonally up-right, and finally read the grid row by row while skipping blanks. That directly mirrors the `PAHN / APLSIIG / YIR` drawing.

</details>

**Q2. Does the output depend on which column a character sits in?**

<details>
<summary>Answer</summary>

No. Reading 'line by line' only cares about which row a character lands in and in what order it arrived. For example, the A at index 4 in Example 2 just needs to be appended to row 2 after Y.

</details>

**Q3. How do I know a character's row without the grid?**

<details>
<summary>Answer</summary>

Keep a current row and a direction. Go down until row `numRows-1`, then up until row 0, then flip again. Append each character to its row's buffer and join the buffers at the end.

</details>

**Q4. Is there a repeating structure I can compute directly?**

<details>
<summary>Answer</summary>

Yes. One full down-and-up trip covers `cycle = 2*numRows - 2` characters (6 when numRows=4). So index `i` is in row `i % cycle` if that value is below numRows, and otherwise in row `cycle - i % cycle`.

</details>

**Q5. Can I generate the output row by row instead of character by character?**

<details>
<summary>Answer</summary>

Yes. Row `r` holds indices `r, r+cycle, r+2*cycle, ...`. Middle rows (not 0 and not numRows-1) also hold the diagonal partner `j + cycle - 2r` after each `j`. For numRows=4, row 1 is indices 1,5,7,11,13, which spells A,L,S,I,G.

</details>

**Q6. What breaks the formula?**

<details>
<summary>Answer</summary>

When numRows=1, `cycle` = 0, so stepping by `cycle` loops forever. Return `s` directly in that case, and also whenever numRows ≥ n, because then every row holds at most one character and the output equals `s`.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: 2D grid simulation](#1-brute-force-2d-grid-simulation) | `O(numRows · n)` | `O(numRows · n)` |
| 2 | [Better: Row buffers with direction flip](#2-better-row-buffers-with-direction-flip) | `O(n)` | `O(n)` |
| 3 | [Optimal: Direct index arithmetic per row](#3-optimal-direct-index-arithmetic-per-row) | `O(n)` | `O(1) besides the output` |

### 1. Brute force: 2D grid simulation

> **Where you start:** The problem literally shows a picture, so the first instinct is to build that picture in a matrix and read it back out.

**Idea.** Allocate a grid with `numRows` rows and enough columns: each cycle of `2*numRows-2` characters uses `numRows-1` columns. Place characters going straight down a column, then diagonally up-right one cell per character until row 0, and repeat. Reading the grid row by row, skipping empty cells, gives exactly the line-by-line order. This is correct because the grid is a faithful copy of the drawn zigzag.

**Steps**

1. If numRows is 1, return s.
2. Compute the number of columns: ceil(n / cycle) * (numRows - 1).
3. Create a grid of that size filled with a blank marker.
4. Walk through s: move down while row < numRows-1, otherwise move up-right (row-1, col+1), and flip at the boundaries.
5. Scan the grid row by row and append every non-blank cell to the result.

**Pseudocode**

```text
 1 │ function convert(s, numRows)
 2 │   n ← length(s)
 3 │   if numRows = 1
 4 │     return s  // a single row is the string itself (and cycle would be 0)
 5 │   cycle ← 2 * numRows - 2  // characters in one down-then-diagonal pass
 6 │   cols ← ceil(n / cycle) * (numRows - 1)  // each cycle uses numRows-1 columns
 7 │   grid ← numRows × cols table, every cell ← BLANK
 8 │   row ← 0
 9 │   col ← 0
10 │   for i from 0 to n - 1
11 │     grid[row][col] ← s[i]
12 │     if (i mod cycle) < numRows - 1  // first numRows-1 chars of a cycle go straight down
13 │       row ← row + 1
14 │     else
15 │       row ← row - 1  // diagonal: up one row ...
16 │       col ← col + 1  // ... and right one column
17 │   result ← ""
18 │   for r from 0 to numRows - 1
19 │     for c from 0 to cols - 1
20 │       if grid[r][c] ≠ BLANK  // skip the gaps of the zigzag
21 │         result ← result + grid[r][c]
22 │   return result
```

**Time complexity: `O(numRows · n)`**

| Part | Cost | Why |
| --- | --- | --- |
| Grid allocation (line 7) | numRows × cols cells × O(1) | Every cell must be initialised to BLANK, and cols ≈ n/2, so this is about numRows·n/2 work. |
| Placement loop (lines 10-16) | n iterations × O(1) | Each character is written once and the cursor moves by a constant step. |
| Row-by-row scan (lines 18-21) | numRows × cols iterations × O(1) | Every cell is visited once, including the blank ones, which are the majority. |

- **Adding it up:** numRows·cols + n + numRows·cols, with cols = ceil(n/(2·numRows−2))·(numRows−1) ≈ n/2, gives about numRows·n + n = O(numRows · n); the grid allocation and scan dominate the O(n) placement
- **Best vs worst case:** Best case is numRows = 1, which returns immediately in O(1) (O(n) if the string is copied). Every other input pays the full numRows·cols grid cost, and the worst case is large numRows with a large n.
- **At the maximum input:** n = 1000, numRows = 1000 → cycle = 1998, cols = 999, so about 10^6 cells to fill and scan, which runs in a few milliseconds

**Space complexity: `O(numRows · n)`**

| Part | Cost | Why |
| --- | --- | --- |
| grid (line 7) | numRows × cols ≈ numRows · n / 2 cells | The whole zigzag drawing is stored, blanks included. |
| Scalars n, cycle, cols, row, col, i, r, c (lines 2-19) | O(1) | A fixed number of integers, independent of the input size. |

- **Adding it up:** O(numRows · n) + O(1) = O(numRows · n)
- **Not counted:** The output string result (length n) and the input s are not counted. There is no recursion.

**Dry run** on `s = "PAYPAL", numRows = 3 (a smaller input than Example 1; · marks a BLANK cell)`

| Step | Line | What happens | State (step 1) / what changed |
| --- | --- | --- | --- |
| 1 | 7 | n = 6 and cycle = 2·3−2 = 4. cols = ceil(6/4)·2 = 4, so a 3×4 grid is created with every cell blank. | `numRows = 3`<br>`n = 6`<br>`cycle = 4`<br>`cols = 4`<br>`s = [P, A, Y, P, A, L]`<br>`grid = 3×4 table: [·, ·, ·, ·] [·, ·, ·, ·] [·, ·, ·, ·]` |
| 2 | 13 | i = 0: 'P' is written at (0,0). Since 0 mod 4 = 0 < 2, we keep going down, so row becomes 1. | `i = 0`<br>`row = 1`<br>`col = 0`<br>`s = [P, A, Y, P, A, L]` (i→0)<br>`grid = 3×4 table: [P, ·, ·, ·] [·, ·, ·, ·] [·, ·, ·, ·]` (cursor→[1,0]) |
| 3 | 13 | i = 1: 'A' is written at (1,0). Since 1 mod 4 = 1 < 2, we still move down, so row becomes 2. | `i = 1`<br>`row = 2`<br>`s = [P, A, Y, P, A, L]` (i→1)<br>`grid = 3×4 table: [P, ·, ·, ·] [A, ·, ·, ·] [·, ·, ·, ·]` (cursor→[2,0]) |
| 4 | 16 | i = 2: 'Y' is written at the bottom cell (2,0). Since 2 mod 4 = 2 is not < 2, the diagonal starts and the cursor moves up-right to (1,1). | `i = 2`<br>`row = 1`<br>`col = 1`<br>`s = [P, A, Y, P, A, L]` (i→2)<br>`grid = 3×4 table: [P, ·, ·, ·] [A, ·, ·, ·] [Y, ·, ·, ·]` (cursor→[1,1]) |
| 5 | 16 | i = 3: 'P' is written on the diagonal at (1,1). Since 3 mod 4 = 3 is not < 2, we move up-right again, to (0,2). | `i = 3`<br>`row = 0`<br>`col = 2`<br>`s = [P, A, Y, P, A, L]` (i→3)<br>`grid = 3×4 table: [P, ·, ·, ·] [A, P, ·, ·] [Y, ·, ·, ·]` (cursor→[1,1]) |
| 6 | 13 | i = 4: a new cycle begins and 'A' is written at the top cell (0,2). Since 4 mod 4 = 0 < 2, we go down, so row becomes 1. | `i = 4`<br>`row = 1`<br>`s = [P, A, Y, P, A, L]` (i→4)<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, ·, ·] [Y, ·, ·, ·]` (cursor→[1,2]) |
| 7 | 13 | i = 5: 'L' is written at (1,2). Since 5 mod 4 = 1 < 2, row moves down to 2. The loop then ends because all 6 characters are placed. | `i = 5`<br>`row = 2`<br>`s = [P, A, Y, P, A, L]` (i→5)<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` (cursor→[2,2]) |
| 8 | 17 | The grid now matches the drawn zigzag. The result string starts empty, ready for the row-by-row read. | `result = ""`<br>`s = [P, A, Y, P, A, L]`<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` |
| 9 | 21 | r = 0: the non-blank cells (0,0)='P' and (0,2)='A' are appended. Shown at c = 2, the last append in this row; c = 3 is blank. | `r = 0`<br>`c = 2`<br>`result = "PA"`<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` (scan→[0,2]) |
| 10 | 21 | r = 1: the cells (1,0)='A', (1,1)='P' and (1,2)='L' are appended, so result becomes "PAAPL". | `r = 1`<br>`result = "PAAPL"`<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` (scan→[1,2]) |
| 11 | 21 | r = 2: only (2,0)='Y' is non-blank, so result becomes "PAAPLY". The remaining cells in this row are blanks and are skipped. | `r = 2`<br>`c = 0`<br>`result = "PAAPLY"`<br>`grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` (scan→[2,0]) |
| 12 | 22 | The scan is finished and "PAAPLY" is returned. | `grid = 3×4 table: [P, ·, A, ·] [A, P, L, ·] [Y, ·, ·, ·]` |

**Result:** "PAAPLY" — the grid is an exact copy of the zigzag (P A on the top row, A P L in the middle, Y at the bottom), so reading it row by row gives the required order.

**C++ solution**

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows == 1) return s;                 // no zigzag; also avoids cycle == 0
        int cycle = 2 * numRows - 2;                // chars in one down + diagonal pass
        int cols = ((n + cycle - 1) / cycle) * (numRows - 1); // ceil(n/cycle) cycles, numRows-1 columns each
        vector<string> grid(numRows, string(cols, '\0')); // '\0' is BLANK; '.' can't be used since s may contain it
        int row = 0, col = 0;                       // current cell of the cursor
        for (int i = 0; i < n; ++i) {
            grid[row][col] = s[i];                  // place the character
            if (i % cycle < numRows - 1) {
                ++row;                              // still on the vertical stroke: go down
            } else {
                --row;                              // on the diagonal: go up ...
                ++col;                              // ... and one column right
            }
        }
        string result;
        result.reserve(n);                          // the output has exactly n characters
        for (int r = 0; r < numRows; ++r)           // read line by line
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] != '\0')             // skip the empty cells
                    result += grid[r][c];
        return result;
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
    string convert(string s, int numRows) {
        int n = s.size();
        if (numRows == 1) return s;                 // no zigzag; also avoids cycle == 0
        int cycle = 2 * numRows - 2;                // chars in one down + diagonal pass
        int cols = ((n + cycle - 1) / cycle) * (numRows - 1); // ceil(n/cycle) cycles, numRows-1 columns each
        vector<string> grid(numRows, string(cols, '\0')); // '\0' is BLANK; '.' can't be used since s may contain it
        int row = 0, col = 0;                       // current cell of the cursor
        for (int i = 0; i < n; ++i) {
            grid[row][col] = s[i];                  // place the character
            if (i % cycle < numRows - 1) {
                ++row;                              // still on the vertical stroke: go down
            } else {
                --row;                              // on the diagonal: go up ...
                ++col;                              // ... and one column right
            }
        }
        string result;
        result.reserve(n);                          // the output has exactly n characters
        for (int r = 0; r < numRows; ++r)           // read line by line
            for (int c = 0; c < cols; ++c)
                if (grid[r][c] != '\0')             // skip the empty cells
                    result += grid[r][c];
        return result;
    }
};

int main() {
    Solution sol;
    vector<tuple<string, int, string>> tests = {
        {"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
        {"PAYPALISHIRING", 4, "PINALSIGYAHRPI"},
        {"A", 1, "A"}
    };
    for (auto& [s, rows, expected] : tests) {
        string got = sol.convert(s, rows);
        cout << "convert(\"" << s << "\", " << rows << ") = \"" << got
             << "\"  expected \"" << expected << "\""
             << (got == expected ? "  [OK]" : "  [FAIL]") << "\n";
    }
    return 0;
}
```

</details>

**Why move on:** It still passes at these limits (about 5·10^5 cells), but it allocates and scans a mostly empty matrix. It also forces you to get the column-count arithmetic right, all to compute columns the output never uses.

### 2. Better: Row buffers with direction flip

> **How you get here:** The grid's columns are pure waste: the output only needs each row's characters in arrival order. So keep one growing buffer per row instead of a matrix.

**Idea.** Keep `numRows` string buffers, a current row index, and a step of +1 or -1. For each character of s, append it to `buffers[row]`. Flip the step when row hits 0 or `numRows-1`, then move. Characters within a row arrive left to right in the picture, so concatenating the buffers top to bottom reproduces the line-by-line reading. The invariant is that `row` always equals the row the zigzag would place the current character in.

**Steps**

1. If numRows is 1 or numRows ≥ n, return s.
2. Create numRows empty buffers, and set row = 0 and step = +1.
3. For each character c in s, append c to buffers[row].
4. If row is 0, set step = +1; if row is numRows-1, set step = -1.
5. Add step to row.
6. Join all buffers in order and return the result.

**Complexity:** time `O(n)`, space `O(n)`. Each character is appended once and joined once, so the work is linear in n. The buffers together hold exactly n characters, plus numRows small buffer objects.

**Why move on:** This is already linear and is what most interviewers accept. Its only overhead is numRows separate buffers, which costs extra allocation when numRows is large (up to 1000).

### 3. Optimal: Direct index arithmetic per row

> **How you get here:** The direction-flip simulation is periodic with period `cycle = 2*numRows - 2`. So each row's indices can be computed directly, and the answer can be written in final order with no per-row buffers.

**Idea.** Row 0 and row numRows-1 contain the indices `r + k*cycle`. A middle row r contains `j = r + k*cycle` and also the diagonal character `j + cycle - 2r`, which is the same distance from the next cycle start as `j` is from the current one. Emitting rows in order, and indices in increasing order within each row, produces the output directly. Correctness follows from the fact that position `i % cycle` uniquely determines a character's row.

**Steps**

1. If numRows is 1 or numRows ≥ n, return s.
2. Set cycle = 2*numRows - 2.
3. For each row r from 0 to numRows-1, loop j = r, r+cycle, r+2*cycle, ... while j < n.
4. Append s[j] to the result.
5. If r is a middle row and j + cycle - 2r < n, also append s[j + cycle - 2r].
6. Return the result.

**Complexity:** time `O(n)`, space `O(1) besides the output`. Every character is visited exactly once across all rows, so the total work is n appends. Apart from the n-character output, only a few integers are used.

**Why this is the best:** The output itself has length n, so O(n) time is a lower bound and cannot be beaten. The cost is readability: the `cycle - 2r` offset is easy to get off by one, whereas the buffer simulation is easier to get right under pressure.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| s = "ABCDEFGHIJ"<br>numRows = 3 | "AEIBDFHJCG" | Basic 3-row zigzag with partial final cycle. |
| s = "abcdefgh"<br>numRows = 2 | "acegbdfh" | Two rows alternate characters. |
| s = "HelloWorld"<br>numRows = 4 | "HoeWrlolld" | Mixed case with 4 rows including diagonal characters. |
| s = "a,b.c"<br>numRows = 3 | "ac,.b" | Punctuation characters handled. |
| s = "ABCDEFGHIJKLMN"<br>numRows = 5 | "AIBHJCGKDFLNEM" | Five rows with multiple diagonal entries. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single row | s = "AB"<br>numRows = 1 | "AB" | String unchanged. |
| Rows exceed length | s = "ABC"<br>numRows = 1000 | "ABC" | String unchanged. |
| Rows equal length | s = "ABCD"<br>numRows = 4 | "ABCD" | One vertical column. |
| Length one more than rows | s = "ABCDE"<br>numRows = 4 | "ABCED" | Single diagonal character. |
| All equal characters | s = "aaaa"<br>numRows = 2 | "aaaa" | Output identical. |
| Single character | s = "z"<br>numRows = 2 | "z" | Minimum length. |

## Mistakes and edge cases

**Common mistakes**

- Forgetting the numRows = 1 case. In the formula `cycle` becomes 0 and the loop never advances; in the simulation the step flips every character and row goes out of bounds.
- In the formula approach, adding the diagonal character for row 0 or the last row too, which duplicates characters (j + cycle - 2r equals the next j or the current j).
- Flipping direction after moving instead of before, so row becomes -1 or numRows, which causes an index-out-of-range error.
- Using `cycle = 2*numRows` instead of `2*numRows - 2`, which counts the top and bottom turning points twice.

**Edge cases to check**

- numRows = 1 (e.g. "A", 1): the cycle length is zero, so return s unchanged.
- numRows ≥ s.length (e.g. "AB", 5): the zigzag never turns, every row has at most one character, and the output equals s.
- numRows = 2: there are no middle rows, so the formula never adds diagonal characters. "ABCD" becomes "ACBD".
- The last cycle is partial (e.g. "PAYPALISHIRING" with 4 rows, n=14 while cycle=6): the diagonal index must be bounds-checked against n separately from j.

## Practice next

- [Decode the Slanted Ciphertext](https://leetcode.com/problems/decode-the-slanted-ciphertext/) · This is the reverse direction: text is written along a fixed geometric path in a grid, and you recover the order by index arithmetic instead of drawing.
- [Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/) · It is also a bouncing traversal with a direction flag that flips at the boundaries.
- [Spiral Matrix](https://leetcode.com/problems/spiral-matrix/) · It simulates a structured walk with direction changes at the edges, and the same off-by-one care at the turning points applies.

## Takeaways

- When a problem shows a picture, ask which coordinates the output actually depends on. Here only the row mattered, so the columns could be dropped.
- A bouncing walk between 0 and k-1 has period 2k-2. Positions in the second half of each period mirror back as `period - (i % period)`.
- Simulate first to find the period, then replace the simulation with direct index formulas when you want to avoid extra buffers.
- Any formula involving the expression `2k-2` needs a guard for k=1, where the period collapses to zero.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
