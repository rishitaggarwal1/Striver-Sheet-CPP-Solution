# Stone Removal Game

**LeetCode** · **Easy** · [Open the problem](https://leetcode.com/problems/stone-removal-game/)

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
