class Solution {
public:
    int countBinarySubstrings(string s) {
        int ans =0;
        int n = s.length();
        int zero = 0, one = 0;
        bool swap = false;

        for(int i=0;i<n;i++)
        {
            if(i!=0 && s[i]!=s[i-1] && zero>0 && one>0)
            {
                ans+=one<zero?one:zero;
                if(s[i]=='0')
                    zero=0;
                else one =0;
            }
            if(s[i]=='0')   zero++;
            else one++;
        }
        ans+=one<zero?one:zero;
        return ans;
    }
};