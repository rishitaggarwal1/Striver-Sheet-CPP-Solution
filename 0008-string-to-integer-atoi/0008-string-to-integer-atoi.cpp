class Solution {
public:
    int myAtoi(string s) {
        long ans=0;
        int k=1,x=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i] == ' ' && x==0)
                continue;
            else if(s[i]=='-' && x==0)
            {
                x=1;
                k=-1;
            }
            else if(s[i]=='+' && x==0)
            {
                x=1;
                k=1;
            }
            else if(s[i]>=48 && s[i]<=57)
            {
                ans=ans*10 + (s[i]-'0');
                if(ans*k>INT_MAX) return INT_MAX;
                if(ans*k<INT_MIN) return INT_MIN;
                x=1;
            }
            else
            {
                break;
            }
        }
        return ans*k;
    }
};