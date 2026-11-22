// Check if All A's Appears Before All B's (LeetCode, Easy)
// https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/
// My accepted solution · 2026-11-22

class Solution {
public:
    bool checkString(string s) {
        bool a = true;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='b')
            {
                a=false;
            }
            else
            {
                if(!a)  return false;
            }
        }
        return true;
    }
};
