class Solution {
public:
    bool isAnagram(string s, string t) {
        int ar[26]={0};
        if(s.length()!=t.length())
            return false;
        for(int i=0;i<s.length();i++)
        {
            ar[s[i]-'a']++;
            ar[t[i]-'a']--;
        }
        for(int i=0;i<26;i++)
        {
            if(ar[i]!=0)
                return false;
        }
        return true;
    }
};