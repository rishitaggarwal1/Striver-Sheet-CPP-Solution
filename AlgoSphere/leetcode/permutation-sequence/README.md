# Permutation Sequence

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/permutation-sequence/) · ✅ Solved in C++

**Contents:** [Problem](#problem) · [Hints](#hints) · [My solution](#my-solution)

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

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-26 |

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

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
