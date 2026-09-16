class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> m;
        for(int i=0;i<t.length();i++)
        {
            m[t[i]]++;
        }
        int l = 0, r = 0;
        int sin = -1, ll = INT_MAX;
        int c=0;
        while(r<s.length())
        {
            m[s[r]]--;
            if(m[s[r]]>=0)
                c++;
            while(c==t.length())
            {
                if(r-l+1<ll)
                {
                    sin = l;
                    ll = min(ll,r-l+1);
                }
                m[s[l]]++;
                if(m[s[l]]>0)
                    c--;
                l++;
            }
            r++;
        }
        if(sin == -1)   return "";
        return s.substr(sin,ll);
    }
};