class Solution {
public:
    bool check(string ss)
    {
        int n=ss.length();
        for(int i=0;i<n/2;i++)
        {
            if(ss[i]!=ss[n-1-i])
                return false;
        }
        return true;
    }
    string longestPalindrome(string s) {
        string ans="";
        int n=s.length(),mx=0;
        for(int i=0;i<n;i++)
        {
            for(int j=n-1;j>=i;j--)
            {
                if(j-i+1<mx)    break;
                if(s[j]==s[i])
                {
                    if(check(s.substr(i,j-i+1)))
                    {
                        ans=s.substr(i,j-i+1);
                        mx=j-i+1;
                    }
                }
            }
        }
        return ans;
    }
};