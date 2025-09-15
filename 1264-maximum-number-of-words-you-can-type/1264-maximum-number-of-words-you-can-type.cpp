class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        map<char,int> m;
        for(int i=0;i<brokenLetters.length();i++)
            m[brokenLetters[i]]++;
        int ans=0;
        bool b=true;
        for(int i=0;i<text.length();i++)
        {
            if(text[i]==' ' && b)
            {
                ans++;
            }
            else if(text[i]==' ')
            {
                b=true;
            }
            else if(b && m.find(text[i])!=m.end())
                b=false;
        }
        if(b)
            ans++;
        return ans;
    }
};