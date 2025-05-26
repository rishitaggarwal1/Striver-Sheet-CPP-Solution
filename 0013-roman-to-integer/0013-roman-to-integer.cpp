class Solution {
public:
    int romanToInt(string s) {
        map<char,int> m;
        int ans=0;
        m['M']=1000; m['D']=500; m['C']=100; m['L']=50; m['X']=10; m['V']=5; m['I']=1;  
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='I' && i<s.length() && (s[i+1]=='V' || s[i+1]=='X'))
                ans+=(m[s[i++ +1]]-1);
            else if(s[i]=='X' && i<s.length() && (s[i+1]=='L' || s[i+1]=='C'))
                ans+=(m[s[i++ +1]]-10);
            else if(s[i]=='C' && i<s.length() && (s[i+1]=='D' || s[i+1]=='M'))
                ans+=(m[s[i++ +1]]-100);
            else
                ans+=m[s[i]];
        }
        return ans;
    }
};