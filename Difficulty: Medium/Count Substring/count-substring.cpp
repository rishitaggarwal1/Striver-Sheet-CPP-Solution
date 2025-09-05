class Solution {
  public:
    int countSubstring(string s) {
        // Code here
        int ans=0;
        int a=-1,b=-1,c=-1;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='a')   a=i;
            else if(s[i]=='b')  b=i;
            else c=i;
            if(a!=-1 && b!=-1 && c!=-1)
            {
                int x=a<b?a:b;
                x=x<c?x:c;
                ans+=x+1;
            }
        }
        return ans;
    }
};