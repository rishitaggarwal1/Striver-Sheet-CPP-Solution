class Solution {
public:
    bool checkValidString(string s) {
        int mi = 0, mm = 0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='(')
            {
                mi++;
                mm++;
            }
            else if(s[i]==')')
            {
                mi--;
                mm--;
            }
            else
            {
                mi--;
                mm++;
            }
            if(mi<0)    mi=0;
            if(mm<0)    return false;
        }
        return (mi==0);
    }
};