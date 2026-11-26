// Word Search (LeetCode, Medium)
// https://leetcode.com/problems/word-search/
// My accepted solution · 2026-11-26

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
