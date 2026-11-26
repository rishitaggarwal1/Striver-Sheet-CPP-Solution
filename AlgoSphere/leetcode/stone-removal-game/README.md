# Stone Removal Game

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/stone-removal-game/) · Pattern: **Deterministic game simulation**

> Players alternately remove 10, 9, 8, ... stones from a pile of `n`, with Alice taking 10 first; the first player who cannot remove the required amount loses, and you must decide whether Alice wins.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
Alice and Bob are playing a game where they take turns removing stones from a pile, with Alice going first.

- Alice starts by removing exactly 10 stones on her first turn.

- For each subsequent turn, each player removes exactly 1 fewer stone than the previous opponent.

The player who cannot make a move loses the game.

Given a positive integer n, return true if Alice wins the game and false otherwise.

Example 1:

Input: n = 12

Output: true

Explanation:

- Alice removes 10 stones on her first turn, leaving 2 stones for Bob.

- Bob cannot remove 9 stones, so Alice wins.

Example 2:

Input: n = 1

Output: false

Explanation:

- Alice cannot remove 10 stones, so Alice loses.

Constraints:

- 1 <= n <= 50
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

The players have no choices to make: the amounts removed are fixed at 10, 9, 8, 7, and so on, alternating Alice, Bob, Alice. You just need to find out who is the first player unable to take the required amount, because that player loses.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Look at the running totals: after k turns, `10 + 9 + ... + (10-k+1)` stones are gone. The loser is whoever is due to move when the stones left are fewer than the required amount. Also note that the required amount never reaches zero within these limits, since 10+9+...+1 = 55 is more than 50.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

With `n <= 50`, at most about 9 turns can happen, so simply playing the game out is effectively constant time. No cleverer math is needed, though a closed form exists.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is a direct simulation problem. The game is fully deterministic, so the answer comes from replaying the turns in order rather than from game theory or dynamic programming.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Keep taking the required amount while the pile has at least that many stones, then lowering the amount by one. Count how many moves succeeded: Alice wins exactly when an odd number of moves were made, because then Bob was the one stuck.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track three values: `remaining` (stones left in the pile), `need` (stones the current player must take, starting at 10), and either a turn counter or a boolean saying whose move it is.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Set `remaining = n`, `need = 10`, `moves = 0`.
While `remaining >= need`: subtract `need` from `remaining`, add 1 to `moves`, subtract 1 from `need`.
When the loop stops, the player due to move cannot.
Return true if `moves` is odd, false otherwise.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

Use `>=` in the loop check, not `>`. If exactly `need` stones remain, the move is legal and the pile becomes empty, so the next player loses. Check `n < 10`: Alice cannot move, `moves` is 0, so return false. Check n = 10: return true. Check n = 19: Alice takes 10 and Bob takes the remaining 9, so `moves` is 2 and the answer is false. Time is `O(1)` (at most 10 iterations) and space is `O(1)`.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "each player removes exactly 1 fewer stone than the previous opponent" | every move is forced, so there are no choices and nothing to minimax. Just replay the game. |
| "Alice starts by removing exactly 10 stones" | the move sizes are fixed at 10, 9, 8, ..., so the stones used after k moves are the partial sums 10, 19, 27, 34, 40, 45, 49, 52, ... |
| `1 <= n <= 50` | because 10+9+...+4 = 49 and adding 3 gives 52 > 50, the game lasts at most 7 moves. The required amount never reaches 0. |
| Example 2, `n = 1` | Alice can lose before making any move, so zero completed moves means false. |

### What the constraints tell you

With `n` ≤ 50 the game has at most 7 moves, so even a step-by-step simulation costs about 7 operations. Any approach is fine. The interesting goal is getting the parity logic right, and optionally reducing the game to a closed-form check.

### Think it through

Answer each question yourself before opening it.

**Q1. Is this a real game-theory problem where I must explore choices?**

<details>
<summary>Answer</summary>

No. The amount to remove is fixed every turn (10, then 9, then 8...), so the game has exactly one possible playthrough. The winner depends only on how far that playthrough gets.

</details>

**Q2. What decides the loser?**

<details>
<summary>Answer</summary>

The game stops on the first turn where the current player's required amount `need` exceeds the stones left. That player loses. So I only need to know whose turn it is when `n < need` first becomes true.

</details>

**Q3. How do I track whose turn it is without storing anything?**

<details>
<summary>Answer</summary>

Count completed moves `m`. Alice moves on even indices (0, 2, ...) and Bob on odd ones. If `m` is odd, Alice made the last successful move and Bob is the one who is stuck, so Alice wins.

</details>

**Q4. Could `need` ever drop to 0 and make the game infinite?**

<details>
<summary>Answer</summary>

Only after all of 10+9+...+1 = 55 stones were removed, and `n` ≤ 50 rules that out. The game always ends with someone stuck, after at most 7 moves.

</details>

**Q5. Can I skip the simulation entirely?**

<details>
<summary>Answer</summary>

Yes. `m` is the largest count with 10+9+...+(11-m) ≤ `n`, and Alice wins exactly when `m` is odd. Using the partial sums 10, 19, 27, 34, 40, 45, 49, Alice wins for `n` in [10,18], [27,33], [40,44] and [49,50], and loses otherwise. Check: n=12 gives m=1, so true; n=1 gives m=0, so false.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Recursive turn-by-turn replay](#1-brute-force-recursive-turn-by-turn-replay) | `O(1) (at most 7 calls for n ≤ 50)` | `O(1) (recursion depth ≤ 7)` |
| 2 | [Better: Iterative simulation with a turn counter](#2-better-iterative-simulation-with-a-turn-counter) | `O(1) (at most 7 iterations)` | `O(1)` |
| 3 | [Optimal: Partial-sum thresholds and parity](#3-optimal-partial-sum-thresholds-and-parity) | `O(1)` | `O(1)` |

### 1. Brute force: Recursive turn-by-turn replay

> **Where you start:** Game problems instinctively suggest a recursive 'can the current player win from this state?' function. Here the state is just (stones left, required amount).

**Idea.** Define `win(stones, need)` as whether the player to move wins. If `stones < need`, the mover cannot move and loses, so return false. Otherwise the mover's only move leads to `win(stones - need, need - 1)` for the opponent, so return the negation of that. Alice wins iff `win(n, 10)` is true. This is correct because a forced move means the mover's fate is exactly the opposite of the opponent's fate.

**Steps**

1. Call `win(n, 10)` for Alice.
2. In `win`, if `stones < need`, return false (the mover is stuck).
3. Otherwise compute the opponent's result `win(stones - need, need - 1)`.
4. Return the negation of that result.
5. Return the top-level value.

**Complexity:** time `O(1) (at most 7 calls for n ≤ 50)`, space `O(1) (recursion depth ≤ 7)`. Each call does constant work, and the chain has one call per completed move plus one, which is bounded by 8 for `n` ≤ 50. The call stack is the only extra memory.

**Why move on:** It is correct and fast, but recursion is overkill: there is no branching, so the 'game tree' is a straight line and the negation chain hides the simple parity fact.

### 2. Better: Iterative simulation with a turn counter

> **How you get here:** The recursion has no branching, so its whole effect is 'flip the answer once per completed move'. A loop that counts moves does the same thing more directly.

**Idea.** Keep `need = 10` and a counter `m = 0`. While `n >= need`, subtract `need` from `n`, decrement `need` and increment `m`. When the loop stops, the player at move index `m` is stuck. That is Bob exactly when `m` is odd, so return `m % 2 == 1`. The loop invariant is that after `m` iterations, exactly `m` legal moves have been made in the only possible game.

**Steps**

1. Set `need = 10` and `m = 0`.
2. While `n >= need`: do `n -= need`, `need -= 1`, `m += 1`.
3. When the loop ends, the player to move cannot remove `need` stones.
4. Return true if `m` is odd (Bob is stuck), else false.

**Complexity:** time `O(1) (at most 7 iterations)`, space `O(1)`. The loop runs once per completed move, at most 7 times under the limit. Only three integers are stored.

**Why move on:** This is already optimal for the given constraints. Its only cost is that it re-simulates every time instead of using the fixed partial-sum thresholds.

### 3. Optimal: Partial-sum thresholds and parity

> **How you get here:** The simulation always walks through the same partial sums 10, 19, 27, 34, 40, 45, 49. The answer therefore depends only on which gap between consecutive sums `n` falls into.

**Idea.** After `m` moves, the stones used are S(m) = 10 + 9 + ... + (11 - m). The number of completed moves is the largest `m` with S(m) ≤ `n`, and Alice wins iff that `m` is odd. Listing these gives the winning ranges for Alice: [10,18], [27,33], [40,44], [49,50]. This is the same parity rule as the loop, with the loop's outcomes precomputed.

**Steps**

1. Note the partial sums S(1..7) = 10, 19, 27, 34, 40, 45, 49.
2. Find how many of them are ≤ `n`; call this `m`.
3. Return true iff `m` is odd.
4. Equivalently, return whether `n` lies in [10,18], [27,33], [40,44] or [49,50].

**Complexity:** time `O(1)`, space `O(1)`. At most 7 comparisons against fixed sums, or 4 range checks. There is no extra memory beyond constants.

**Why this is the best:** Constant time cannot be beaten, but the hardcoded ranges are tied to the starting value 10 and to `n` ≤ 50. The loop version generalises to other start values and pile sizes without re-deriving anything.

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| n = 15 | true | Bob cannot remove 9 after Alice takes 10. |
| n = 20 | false | After 10 and 9, one stone remains and Alice cannot take 8. |
| n = 30 | true | Alice's second move of 8 succeeds and Bob cannot take 7. |
| n = 37 | false | Bob's move of 7 leaves 3, so Alice cannot take 6. |
| n = 42 | true | Alice takes 6 to reach 40 removed, and Bob cannot take 5. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum n | n = 1 | false | Alice cannot remove 10. |
| Maximum n | n = 50 | true | After 49 removed, Bob cannot remove 3. |
| Exact boundary | n = 10 | true | Alice removes all 10 and Bob has none. |
| Just below 10 | n = 9 | false | Alice cannot move. |
| Exact boundary | n = 19 | false | Bob removes the last 9 stones. |
| Just below 19 | n = 18 | true | Bob is one stone short. |
| Exact boundary | n = 27 | true | Alice's 8 empties the pile. |

## Mistakes and edge cases

**Common mistakes**

- Reversing the parity: after the loop, the player to move loses. If you return `m % 2 == 0` you claim Alice wins at n=12, where m=1 and Alice wins, but then answer true for n=1, where Alice cannot move.
- Using `n > need` instead of `n >= need`: with n=10, Alice can remove exactly 10 and leave 0, and then Bob loses. A strict comparison wrongly says Alice is stuck.
- Decrementing `need` once per round (both players) instead of once per move: the sequence is 10, 9, 8, ... across alternating players, not 10 for Alice and 10 for Bob.
- Thinking a player wins by taking the last stone: the rule is that the player who cannot remove the required amount loses. With n=12, Bob still has 2 stones but cannot take 9.

**Edge cases to check**

- `n` from 1 to 9: Alice cannot make her first move, so m=0 and the answer is false, as in Example 2.
- `n = 10`: Alice removes everything and Bob faces 0 < 9, so the answer is true. This tests `>=`.
- `n = 19`: Alice takes 10 and Bob takes exactly 9, leaving 0 < 8, so Alice loses. This is the boundary where the winner flips.
- `n = 49` and `n = 50`: these reach the 7th move (Alice takes 4), leaving 0 or 1 < 3, so Alice wins. This is the deepest game in range.

## Practice next

- [Nim Game](https://leetcode.com/problems/nim-game/) · An Easy two-player removal game whose answer reduces to a simple arithmetic or parity check on `n`.
- [Divisor Game](https://leetcode.com/problems/divisor-game/) · Another Alice-vs-Bob game where reasoning about turn parity collapses the game to a one-line condition.
- [Arranging Coins](https://leetcode.com/problems/arranging-coins/) · Same core computation: find how many consecutive decreasing or increasing chunks fit into `n` using partial sums.

## Takeaways

- When every move in a game is forced, there is no game tree. Simulate the single line of play and look at whose turn it is when it stops.
- 'The player who cannot move loses' means the winner is determined by the parity of the number of completed moves.
- Fixed step sizes such as 10, 9, 8, ... turn a simulation into a partial-sum threshold lookup, which gives an O(1) closed form.
- Check boundary values where the remaining stones equal the required amount exactly (n=10, n=19); they expose `>` versus `>=` bugs.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
