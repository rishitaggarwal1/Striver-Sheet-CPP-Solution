class Solution {
public:
    int numberOfSubstrings(string s) {
        int ans=0;
        int r =0;
        int n = s.length();
        unordered_map<char,int> m;
        m['a']=-1; 
        m['b']=-1; 
        m['c']=-1;
        while(r<n)
        {
            m[s[r]]=r;
            if(m['a']>=0 && m['b']>=0 && m['c']>=0)
            {
                int x = min(m['a'],m['b']);
                x= min(x,m['c']);
                ans += x+1;
            }
            r++;
        }
        return ans;
    }
};