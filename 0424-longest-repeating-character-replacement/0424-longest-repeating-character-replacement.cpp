class Solution {
public:
    int characterReplacement(string s, int k) {
        int l = 0, r = 0;
        int n = s.length();
        unordered_map<char,int> m;
        int mx = 0, mf = 0;
        while(r<n)
        {
            m[s[r]]++;
            mf = max(mf,m[s[r]]);
            int v = (r-l+1)-mf;
            if(v>k)
            {
                m[s[l]]--;
                int t=0;
                for(auto i:m)
                {
                    t =max(t,i.second);
                }
                mf=t;
                l++;
                v = (r-l+1)-mf;
            }
            if(v<=k)
                mx = max(mx,r-l+1);
            r++;
        }
        return mx;
    }
};