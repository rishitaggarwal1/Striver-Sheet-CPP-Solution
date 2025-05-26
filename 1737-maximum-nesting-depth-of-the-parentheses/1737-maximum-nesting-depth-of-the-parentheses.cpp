class Solution {
public:
    int maxDepth(string s) {
        int ans=-1,x=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='(')
                x++;
            if(s[i]==')')
                x--;
            if(ans<x)
                ans=x;
        }
        return ans;
    }
};