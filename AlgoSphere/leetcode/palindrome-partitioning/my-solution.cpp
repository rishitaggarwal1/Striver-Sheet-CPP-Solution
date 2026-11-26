// Palindrome Partitioning (LeetCode, Medium)
// https://leetcode.com/problems/palindrome-partitioning/
// My accepted solution · 2026-11-26

class Solution {
public:
    vector<vector<string>> ans;
    bool check(string s)
    {
        int n = s.length();
        for(int i=0;i<n/2;i++)
        {
            if(s[i]!=s[n-i-1])
                return false;
        }
        return true;
    }
    void solve(string s, vector<string>& str)
    {
        if(s.length()==0)
        {
            ans.push_back(str);
        }        
        int n = s.length();
        for(int i=1;i<=n;i++)
        {
            if(check(s.substr(0,i)))
            {
                str.push_back(s.substr(0,i));
                solve(s.substr(i),str);
                str.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> str;
        solve(s,str);
        return ans;
    }
};
