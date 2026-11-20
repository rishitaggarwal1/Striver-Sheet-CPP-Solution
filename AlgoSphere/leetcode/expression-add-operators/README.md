# Expression Add Operators

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/expression-add-operators/)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.

Note that operands in the returned expressions should not contain leading zeros.

Note that a number can contain multiple digits.

Example 1:

Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.

Example 2:

Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.

Example 3:

Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.

Constraints:

- 1 <= num.length <= 10

- num consists of only digits.

- -2^31 <= target <= 2^31 - 1
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You must split the digit string into consecutive numbers, put `+`, `-` or `*` between each pair of neighbouring numbers, and list every resulting expression whose value equals `target`. Numbers like `05` are not allowed, though a lone `0` is.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Multiplication binds tighter than addition and subtraction, so in `2+3*2` the `*` acts only on the `3`, not on the running total `5`. Evaluating strictly left to right would give the wrong answer, so you need a way to undo part of the running value when a `*` appears.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With at most 10 digits there are 9 gaps, and each gap can hold one of three operators or nothing (digits joined), giving about `4^9`, roughly 262k, expressions. Enumerating them all is fine. What is too slow is building each full string and re-parsing it from scratch with precedence; the value should be updated incrementally as you go.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking (DFS) over choices. At each position you choose how many digits the next operand takes and which operator goes before it, then recurse on the rest of the string. It fits because the task asks for all valid configurations, and every configuration must be explored anyway.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Track the value of the last multiplicative term separately from the total. When you apply `*` with operand `x`, the new total is `total - last + last * x` and the new last term is `last * x`. For `+` the last term becomes `x`; for `-` it becomes `-x`.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep five things: the current index into `num`, the expression string built so far, the evaluated total so far, the signed value of the last term (so it can be undone for `*`), and the result list. Use 64-bit integers, because operands of up to 10 digits and their products can overflow 32 bits.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Start the DFS at index 0 with an empty expression, total 0 and last term 0.
If the index reaches the end and the total equals `target`, record the expression.
Otherwise, for each end position `j`, take `num[index..j]` as the operand `x`.
If the operand has more than one digit and starts with `0`, stop extending it.
At index 0, just place `x` with total = `x` and last = `x`, with no operator.
Otherwise recurse three times: with `+` (total + `x`, last `x`), with `-` (total - `x`, last `-x`), and with `*` (total - last + last*`x`, last last*`x`).
Return the collected list.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest parts are the `*` undo, which must use the signed last term so that `a-b*c` is handled correctly, and the leading-zero rule: allow `0` as an operand but break the loop as soon as a multi-digit operand would begin with `0`. Other edge cases are a single-digit input (no operators placed), the first operand which gets no operator, and large values that need 64-bit math. Time is `O(n * 4^n)` counting the string building, and extra space is `O(n)` for recursion depth and the current expression, not counting the output.

</details>
