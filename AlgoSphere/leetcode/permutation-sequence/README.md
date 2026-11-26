# Permutation Sequence

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/permutation-sequence/) · Pattern: **Factorial number system (block skipping)** · ✅ Solved in C++

> Return, as a string, the k-th permutation (1-indexed) of the digits 1..n when all n! permutations are listed in lexicographic order.

**Contents:** [Problem](#problem) · [Hints](#hints) · [Intuition](#intuition) · [Approaches](#approaches) · [My solution](#my-solution) · [Test cases](#test-cases) · [Mistakes and edge cases](#mistakes-and-edge-cases) · [Practice next](#practice-next) · [Takeaways](#takeaways)

## Problem

<details>
<summary>Problem statement</summary>

```text
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:

- "123"

- "132"

- "213"

- "231"

- "312"

- "321"

Given n and k, return the k^th permutation sequence.

Example 1:

Input: n = 3, k = 3
Output: "213"

Example 2:

Input: n = 4, k = 9
Output: "2314"

Example 3:

Input: n = 3, k = 1
Output: "123"

Constraints:

- 1 <= n <= 9

- 1 <= k <= n!
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

Imagine writing out every arrangement of the digits 1 through n in dictionary order. You need to return the one in position k, ideally without actually writing out all the ones before it.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Look at the n = 3 list: the first two permutations start with 1, the next two with 2, and the last two with 3. Each leading digit owns a block of the same size, and that size is the number of ways to arrange the remaining digits.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

Since n is at most 9, n! is at most 362880, so generating permutations one by one with a next-permutation step would actually pass. Still, you can build the answer digit by digit in about `O(n^2)` time with no enumeration at all, and that is the intended solution.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is factorial number system (Lehmer code) decoding, a form of combinatorial ranking and unranking. It fits because each position's choice splits the remaining permutations into equal-sized blocks of `(m-1)!`, where m is how many digits are still unused.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Switch to a 0-based index `k-1`. With m digits left, the index of the next digit among the remaining sorted digits is `k / (m-1)!`, and the position inside that block becomes `k % (m-1)!`.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Keep a sorted list of the digits not yet used, and precompute factorials `0!` through `(n-1)!`. Track the current 0-based rank inside the current block; it tells you which remaining digit to pick next.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Precompute factorials up to `(n-1)!`.
Put digits 1..n in a sorted list and set k = k - 1.
For each position, let f = (number of remaining digits - 1)!.
Pick the digit at index k / f in the remaining list and append it to the answer.
Remove that digit from the list and set k = k % f.
Repeat until the list is empty, then return the built string.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is converting to 0-based: if you divide the original k, you go off by one whenever k is an exact multiple of a block size. Check the edges: n = 1 gives "1", k = 1 gives the sorted order, and k = n! gives the fully reversed order. Removing from the list costs `O(n)` per step, so the total is `O(n^2)` time and `O(n)` space, which is trivial for n up to 9.

</details>

## Intuition

### Clues in the problem

| Clue | What it suggests |
| --- | --- |
| "listing and labeling all of the permutations in order" | the permutations come in equal-sized blocks that share the same first digit. You can count blocks instead of listing them. |
| For n = 3 each first digit leads exactly 2 = 2! permutations (123,132 \| 213,231 \| 312,321) | the first digit of the answer is the block index found by dividing (k-1) by (n-1)!. |
| 1 <= k <= n! with n <= 9 | k is a rank among n! objects. Decompose it in a mixed-radix base of factorials. |
| Output is a single permutation, not all of them | you should build it digit by digit rather than enumerate. |

### What the constraints tell you

n <= 9 means n! = 362,880. Enumerating up to k permutations at O(n) each costs about 3.3·10^6 operations, which still passes. The factorial-digit method needs only about n^2 = 81 operations. The target is O(n^2), or O(n) per digit with a list of size n, which is effectively constant here.

### Think it through

Answer each question yourself before opening it.

**Q1. What is the most literal way to get the k-th permutation?**

<details>
<summary>Answer</summary>

Generate permutations in lexicographic order and stop at the k-th. With n = 9 and k = 362880 that walks the whole list, so it is correct but does work proportional to k.

</details>

**Q2. Looking at the n = 3 list, what structure do the permutations have?**

<details>
<summary>Answer</summary>

They split into 3 groups of 2 by first digit: 1xx, 2xx, 3xx. In general, fixing the first digit leaves (n-1)! orderings of the rest, so each group has (n-1)! members.

</details>

**Q3. Given that structure, how do I find the first digit without listing anything?**

<details>
<summary>Answer</summary>

Convert to 0-indexed rank r = k-1. The first digit sits at index r / (n-1)! in the sorted list of unused digits. For n = 4, k = 9: r = 8, and 8 / 3! = 1, so the first digit is the element at index 1 of [1,2,3,4], which is 2.

</details>

**Q4. How do I continue after the first digit?**

<details>
<summary>Answer</summary>

Replace r with r % (n-1)! (here 8 % 6 = 2) and remove the chosen digit, leaving [1,3,4]. Then repeat with (n-2)!: 2 / 2! = 1 picks 3, r becomes 0. Then 0 / 1! = 0 picks 1, and the last digit is 4, giving "2314".

</details>

**Q5. Why must I subtract 1 from k?**

<details>
<summary>Answer</summary>

Block indices are 0-based. With k = 6 for n = 3, using k directly gives 6 / 2 = 3, which is out of range. Using r = 5 gives 5 / 2 = 2, so the first digit is 3, and the rest produces "321" correctly.

</details>

**Q6. What is the key insight in one line?**

<details>
<summary>Answer</summary>

k-1 written in the factorial number system (digits r/(n-1)!, r/(n-2)!, ...) tells you directly which remaining digit to take at each position.

</details>

## Approaches

| # | Approach | Time | Space |
| --- | --- | --- | --- |
| 1 | [Brute force: Generate all permutations in order](#1-brute-force-generate-all-permutations-in-order) | `O(k·n) with early stop, O(n!·n) worst case` | `O(n) recursion, or O(n!·n) if all permutations are stored` |
| 2 | [Better: Apply next-permutation k-1 times](#2-better-apply-next-permutation-k-1-times) | `O(k·n)` | `O(n)` |
| 3 | [Optimal: Factorial number system / block skipping](#3-optimal-factorial-number-system--block-skipping) | `O(n^2)` | `O(n)` |

### 1. Brute force: Generate all permutations in order

> **Where you start:** The statement literally describes listing every permutation in order, so building that list and indexing it at k-1 is the first idea.

**Idea.** Recursively build permutations by trying the unused digits 1..n in increasing order at each position. That order produces permutations lexicographically. Collect them, or count them and stop when the counter reaches k. It is correct because depth-first search over choices in ascending order visits permutations in exactly the sequence shown.

**Steps**

1. Keep a used[] array for digits 1..n and a current string.
2. At each depth, try every unused digit in increasing order, append it, and recurse.
3. When the string reaches length n, increment a counter.
4. When the counter equals k, record the string and stop.
5. Return the recorded string.

**Complexity:** time `O(k·n) with early stop, O(n!·n) worst case`, space `O(n) recursion, or O(n!·n) if all permutations are stored`. Every permutation before the k-th is fully built at O(n) cost. When k = n! that is 362,880 × 9 operations. Memory is the recursion stack plus the used array, or the whole list if you store it.

**Why move on:** It passes for n <= 9, but the cost is proportional to k, so it is about 10^5 times more work than needed. It would collapse for n = 15 (1.3·10^12 permutations).

### 2. Better: Apply next-permutation k-1 times

> **How you get here:** The brute force uses recursion and possibly stores a list, yet each permutation only depends on the previous one. Stepping forward in place removes the extra memory.

**Idea.** Start from "123...n" and apply the standard next-permutation step k-1 times. Each step finds the rightmost i with a[i] < a[i+1], swaps a[i] with the smallest larger element to its right, and reverses the suffix. It is correct because next-permutation produces the immediate lexicographic successor, so k-1 steps land on rank k.

**Steps**

1. Initialize array a = [1, 2, ..., n].
2. Repeat k-1 times: find the rightmost i with a[i] < a[i+1].
3. Find the rightmost j > i with a[j] > a[i] and swap a[i] and a[j].
4. Reverse a[i+1..n-1].
5. After the loop, join a into a string and return it.

**Complexity:** time `O(k·n)`, space `O(n)`. There are k-1 successor steps, and each scans and reverses at most n elements. Only the n-element array is kept.

**Why move on:** Memory is now minimal, but the time is still proportional to k. It walks through every permutation before the answer instead of jumping to it.

### 3. Optimal: Factorial number system / block skipping

> **How you get here:** Both previous methods step through permutations one at a time. Yet whole groups of (n-1)! permutations share a prefix, so we can skip an entire group with one division.

**Idea.** Let r = k-1 and keep a sorted list of unused digits. At position i, each choice of digit leads exactly f = (n-1-i)! permutations. So the digit to place is unused[r / f], and r becomes r % f for the subproblem. This works because lexicographic order sorts first by the leading digit, then recursively by the rest. Picking from a sorted list keeps the same correspondence at every level.

**Steps**

1. Precompute factorials 0! through (n-1)!.
2. Build the list unused = [1, 2, ..., n] and set r = k - 1.
3. For i from 0 to n-1, let f = (n-1-i)!.
4. Compute idx = r / f, append unused[idx] to the answer, and remove it from unused.
5. Set r = r % f.
6. Return the built string.

**Complexity:** time `O(n^2)`, space `O(n)`. There are n iterations, and each removes from a list of up to n elements, which shifts O(n) items. That is 81 operations for n = 9. Extra memory is the factorial table and the unused list.

**Why this is the best:** You must output n characters, so Ω(n) is unavoidable. The O(n^2) list removal could become O(n log n) with a Fenwick tree, but that is pointless when n <= 9.

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-26 |

For comparison, the optimal approach (Factorial number system / block skipping) runs in `O(n^2)` time and `O(n)` space.

```cpp
class Solution {
public:
    string getPermutation(int n, int k) {
        string str="";
        vector<int> v;
        int fact = 1;
        for(int i=1;i<n;i++)
        {
            fact = fact*i;
            v.push_back(i);
        }
        v.push_back(n);
        k--;
        while(true)
        {
            str+=to_string(v[k/fact]);
            v.erase(v.begin()+k/fact);
            if(v.size()==0) break;
            k=k%fact;
            fact=fact/v.size();
        }
        return str;
    }
};
```

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| n = 4<br>k = 1 | "1234" | First permutation of n=4. |
| n = 4<br>k = 17 | "3412" | Middle permutation for n=4. |
| n = 5<br>k = 50 | "31254" | Moderate n with mixed factorial digits. |
| n = 6<br>k = 400 | "425361" | Larger n requiring multiple non-zero indices. |
| n = 3<br>k = 5 | "312" | Small n second-to-last permutation. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Minimum size | n = 1<br>k = 1 | "1" | Single element. |
| Max n, first permutation | n = 9<br>k = 1 | "123456789" | Sorted order. |
| Max n, k = n! | n = 9<br>k = 362880 | "987654321" | Reverse-sorted. |
| Small last permutation | n = 2<br>k = 2 | "21" | Swap of two. |
| Block boundary | n = 9<br>k = 40320 | "198765432" | Last permutation starting with 1. |
| Block boundary | n = 9<br>k = 40321 | "213456789" | First permutation starting with 2. |
| Large k | n = 9<br>k = 200000 | "596742183" | Full factorial decomposition at max n. |

## Mistakes and edge cases

**Common mistakes**

- Using k instead of k-1 when dividing by the factorial. For n = 3, k = 2 you get 2/2 = 1, so the answer starts with 2 instead of producing "132". When k = n! the index goes out of range.
- Picking the digit as idx+1 (by value) instead of indexing into the list of remaining digits. This returns already-used digits, for example "2214" for n = 4, k = 9.
- Dividing by n! or (n-i)! instead of (n-1-i)!. The block size is the number of orderings of the digits after the current position.
- Forgetting to update r = r % f after each pick. The later digits then always come out as the first or a wrong block.

**Edge cases to check**

- n = 1, k = 1 → "1". Checks that the loop with f = 0! = 1 works.
- k = 1 (for example n = 3) → "123". Here r = 0, so every index is 0 and the digits come out ascending.
- k = n! (for example n = 3, k = 6 → "321"). Here r = n!-1, which is the maximum valid index at every level. It exposes off-by-one errors.
- n = 9, k = 362880 → "987654321". The largest input, where brute force is slowest and indexing bugs show up.

## Practice next

- [Next Permutation](https://leetcode.com/problems/next-permutation/) · It is the successor operation behind the Better approach. It is the same lexicographic-order reasoning applied one step at a time.
- [Permutations](https://leetcode.com/problems/permutations/) · It is the backtracking enumeration used in the brute force.
- [K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/) · It finds the k-th item by counting the size of each prefix subtree and skipping whole subtrees, the same block-skipping idea.

## Takeaways

- To find the k-th item in an ordered combinatorial list, count how many items share each prefix and skip whole blocks instead of enumerating.
- Convert 1-indexed ranks to 0-indexed (k-1) before doing division and modulo decomposition.
- A permutation's rank is a number in the factorial (mixed-radix) base. Each digit is an index into the remaining unused choices.
- Small n (n <= 9) means even O(n^2) list operations are negligible. Spend effort on correctness of the indexing, not on fancy data structures.

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
