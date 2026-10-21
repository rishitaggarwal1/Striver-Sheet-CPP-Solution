class Solution {
public:
    int minOperations(string s) {
        if(s.length()==2 && s[0]>s[1])
        {
            return -1;
        }
        bool c = true;
        int x = 0, y=0;
        for(int i=1;i<s.length();i++)
        {
            if(s[x]>s[i])   x=i;
            if(s[y]<=s[i])   y=i;
            if(s[i]<s[i-1]) c = false; 
        }
        if(c)   return 0;
        if(x==0 || y==s.length()-1) return 1;
        if(x==s.length()-1 && y==0) return 3;
        return 2;
    }
};