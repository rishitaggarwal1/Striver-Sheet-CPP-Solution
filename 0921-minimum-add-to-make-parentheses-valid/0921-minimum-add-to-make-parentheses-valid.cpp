class Solution {
public:
    int minAddToMakeValid(string s) {
        int n = s.length();
        int c=0,ans=0;
        for(int i=0;i<n;i++)
        {
            if(s[i]=='(')
            {
                c++;
            }
            else
            {
                c--;
            }
            if(c<0)
            {
                c++;
                ans++;
            }
        }
        return ans+c;
    }
};