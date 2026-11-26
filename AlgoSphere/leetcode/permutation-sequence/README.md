# Permutation Sequence

**LeetCode** · **Hard** · [Open the problem](https://leetcode.com/problems/permutation-sequence/) · ✅ Solved in C++

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
