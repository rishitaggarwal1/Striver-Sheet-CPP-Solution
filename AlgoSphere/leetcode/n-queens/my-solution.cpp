// N-Queens (LeetCode, Hard)
// https://leetcode.com/problems/n-queens/
// My accepted solution · 2026-11-24

class Solution {
public:
    vector<vector<string>> ans;
    bool valid(vector<string>& s, int r, int c)
    {
        int n = s.size();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<c;j++)
            {
                if(s[i][j]=='Q')
                {
                    if(i==r || (i+j == r+c) || (r-i == c-j) )
                        return false;
                }
            }
        }
        return true;
    }
    void nqueen(vector<string>& s, int c, int n)
    {
        if(c==n)
        {
            ans.push_back(s);
            return;
        }
        for(int i=0;i<n;i++)
        {
            s[i][c]='Q';
            if(valid(s,i,c))
                nqueen(s,c+1,n);
            s[i][c]='.';
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        string s(n,'.');
        vector<string> v(n,s);
        nqueen(v,0,n);
        return ans;
    }
};
