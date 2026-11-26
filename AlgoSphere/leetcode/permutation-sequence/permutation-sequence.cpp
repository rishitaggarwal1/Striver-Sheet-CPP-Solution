/*
 * Problem   : Permutation Sequence (LeetCode, Hard)
 * Link      : https://leetcode.com/problems/permutation-sequence/
 * Pattern   : Factorial number system (block skipping)
 * Approach  : Brute force: Generate all permutations in order
 * Complexity: Time O(n!·n) worst case, O(k·n) with early stop, Space O(n)
 *
 * Recursively build permutations by trying the unused digits 1..n in
 * increasing order at each position. That order produces permutations
 * lexicographically. Collect them, or count them and stop when the counter
 * reaches k. It is correct because depth-first search over choices in
 * ascending order visits permutations in exactly the sequence shown.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        used.assign(n + 1, false);   // used[d] marks digit d as already placed
        cur.clear();                 // permutation under construction
        answer.clear();              // will hold the k-th permutation
        count = 0;                   // number of full permutations seen so far
        dfs(n, k);                   // generate permutations in lexicographic order
        return answer;
    }

private:
    vector<bool> used;
    string cur, answer;
    int count = 0;

    void dfs(int n, int k) {
        if (!answer.empty()) return;              // already found the k-th, so stop
        if ((int)cur.size() == n) {               // a complete permutation
            if (++count == k) answer = cur;       // record it if it is the k-th
            return;
        }
        for (int d = 1; d <= n; d++) {            // ascending digits give lexicographic order
            if (used[d]) continue;                // skip digits already placed
            used[d] = true;
            cur.push_back(char('0' + d));         // place digit d
            dfs(n, k);
            cur.pop_back();                       // backtrack
            used[d] = false;
            if (!answer.empty()) return;          // propagate the early stop
        }
    }
};

int main() {
    Solution s;
    cout << "n=3,k=3 -> " << s.getPermutation(3, 3) << " (expected 213)" << endl;
    cout << "n=4,k=9 -> " << s.getPermutation(4, 9) << " (expected 2314)" << endl;
    cout << "n=3,k=1 -> " << s.getPermutation(3, 1) << " (expected 123)" << endl;
    return 0;
}
