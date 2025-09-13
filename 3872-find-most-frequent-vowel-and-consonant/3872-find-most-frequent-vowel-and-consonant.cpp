class Solution {
public:
    bool isVowel(char x)
    {
        if(x=='a' || x=='e' || x=='i' || x=='o' || x=='u')  return true;
        return false;
    } 
    int maxFreqSum(string s) {
        int c=0,v=0;
        map<char,int> m;
        for(int i=0;i<s.length();i++)
        {
            m[s[i]]++;
            if(isVowel(s[i]) && m[s[i]]>v)  v=m[s[i]];
            else if(!isVowel(s[i]) && m[s[i]]>c)  c=m[s[i]];
        }
        return c+v;
    }
};