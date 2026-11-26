# Word Search

**LeetCode** · **Medium** · [Open the problem](https://leetcode.com/problems/word-search/) · ✅ Solved in C++

**Contents:** [Problem](#problem) · [Hints](#hints) · [My solution](#my-solution) · [Test cases](#test-cases)

## Problem

<details>
<summary>Problem statement</summary>

```text
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

Constraints:

- m == board.length

- n = board[i].length

- 1 <= m, n <= 6

- 1 <= word.length <= 15

- board and word consists of only lowercase and uppercase English letters.

Follow up: Could you use search pruning to make your solution faster with a larger board?
```

</details>

## Hints

Try the problem first. When you're stuck, open one hint at a time; each one gives away a little more.

<details>
<summary>Hint 1 · Restate</summary>

You need to decide whether you can trace the word letter by letter through the grid, stepping only up, down, left or right each time, and never stepping on the same cell twice in one trace.

</details>

<details>
<summary>Hint 2 · Observation</summary>

Look at Example 3: the path A, B, C exists and a B sits right next to that C, but it is the B you already used. So you must remember which cells the current path has visited, and this choice depends on the path, not just on the cell.

</details>

<details>
<summary>Hint 3 · Constraints</summary>

The board has at most 36 cells and the word at most 15 letters. After the first letter, each step has at most 3 new directions, so roughly `36 * 3^14` paths is a loose worst-case bound that real pruning cuts down sharply. An exponential search is acceptable here because the inputs are tiny and there is no polynomial trick.

</details>

<details>
<summary>Hint 4 · Pattern</summary>

This is backtracking, which is a depth-first search over grid paths. It fits because you extend a partial path one cell at a time, and you undo your choice when that path cannot be completed.

</details>

<details>
<summary>Hint 5 · Key insight</summary>

Abandon a path the moment the current cell does not match the next needed letter. Mark the cell as used while you explore from it, then unmark it when you return, so other paths can still use it.

</details>

<details>
<summary>Hint 6 · What to track</summary>

Track your current cell `(r, c)` and an index `k` meaning `word[0..k-1]` has already been matched along this path. Also keep a visited marker, for example by temporarily overwriting `board[r][c]` with a sentinel character and restoring it afterwards.

</details>

<details>
<summary>Hint 7 · Approach</summary>

Try every cell in the grid as a possible start with `k = 0`.
At a cell: if it is out of bounds, already used, or not equal to `word[k]`, fail.
If `k` is the last index of the word, succeed.
Mark the cell as used.
Recurse into the 4 neighbors with `k + 1`, and stop as soon as one succeeds.
Unmark the cell and return the result.
Return true if any start succeeds, otherwise false.

</details>

<details>
<summary>Hint 8 · Edge cases & complexity</summary>

The trickiest step is restoring the cell on every exit path, including early returns, or later searches will break. Handle a one-letter word and a word longer than `m * n`. Useful pruning: return false immediately if the board lacks enough copies of some letter the word needs. Also reverse the word when its last letter is rarer on the board than its first, so the search starts from fewer cells. Time is `O(m * n * 3^L)` and extra space is `O(L)` for the recursion depth.

</details>

## My solution

| Language | Runtime | Memory | Tests passed | Attempts | Hints used | Accepted on |
| --- | --- | --- | --- | --- | --- | --- |
| C++ |   |   |   | 1 | 0 of 8 | 2026-11-26 |

```cpp
class Solution {
public:
    bool check(int i, int j, int m, int n)
    {
        return i>=0 && i<m && j>=0 &&j<n;
    }
    bool solve(vector<vector<char>>& board, string& word, int r, int c, int k, vector<vector<bool>>& vis)
    {
        int m = board.size(), n=board[0].size();
        if(k==word.length())
        {
            return true;
        }
        // Down
        if(check(r+1,c,m,n) && !vis[r+1][c] && board[r+1][c]==word[k])
        {
            vis[r][c]=true;
            if(solve(board,word,r+1,c,k+1,vis)) return true;
            vis[r][c]=false;
        }
        //Right
        if(check(r,c+1,m,n) && !vis[r][c+1] && board[r][c+1]==word[k])
        {
            vis[r][c]=true;
            if(solve(board,word,r,c+1,k+1,vis)) return true;
            vis[r][c]=false;
        }
        //Left
        if(check(r,c-1,m,n) && !vis[r][c-1] && board[r][c-1]==word[k])
        {
            vis[r][c]=true;
            if(solve(board,word,r,c-1,k+1,vis)) return true;
            vis[r][c]=false;
        }
        //UP
        if(check(r-1,c,m,n) && !vis[r-1][c] && board[r-1][c]==word[k])
        {
            vis[r][c]=true;
            if(solve(board,word,r-1,c,k+1,vis)) return true;
            vis[r][c]=false;
        }
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n=board[0].size();
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(board[i][j] == word[0])
                {
                    if(solve(board,word,i,j,1,vis))
                        return true;
                }
            }
        }
        return false;
    }
};
```

## Test cases

**Normal cases**

| Input | Expected | What it checks |
| --- | --- | --- |
| board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]<br>word = "SFCS" | true | Path that zigzags across the middle row and up to the top row. |
| board = [["A","B"],["C","D"]]<br>word = "ABDC" | true | Path that walks around a 2x2 square. |
| board = [["A","B"],["C","D"]]<br>word = "AD" | false | Diagonal moves are not allowed. |
| board = [["C","A","A"],["A","A","A"],["B","C","D"]]<br>word = "AAB" | true | Needs backtracking over several A cells before finding the B. |
| board = [["a","b"],["c","d"]]<br>word = "cdba" | true | Lowercase letters, path starting from a non-corner start. |

**Edge cases**

| Case | Input | Expected | Why it matters |
| --- | --- | --- | --- |
| Single cell | board = [["a"]]<br>word = "a" | true | The one-letter word matches. |
| Cell reuse | board = [["a"]]<br>word = "aa" | false | The single cell cannot be used twice. |
| Single row | board = [["a","b"]]<br>word = "ba" | true | The path goes from right to left. |
| Case sensitivity | board = [["A"]]<br>word = "a" | false | Uppercase A does not match lowercase a. |
| All-equal letters | board = [["a","a"],["a","a"]]<br>word = "aaaaa" | false | The word is longer than the number of cells. |
| Tricky backtracking | board = [["A","B","C","E"],["S","F","E","S"],["A","D","E","E"]]<br>word = "ABCESEEEFS" | true | The long path loops through the E cluster. |

---

<sub>Notes made with **AlgoSphere**, designed and built by **Rishit Aggarwal** · [LinkedIn](https://www.linkedin.com/in/rishit-aggarwal/) · [GitHub](https://github.com/rishitaggarwal1) · [Medium](https://medium.com/@rishitaggarwal1)</sub>
