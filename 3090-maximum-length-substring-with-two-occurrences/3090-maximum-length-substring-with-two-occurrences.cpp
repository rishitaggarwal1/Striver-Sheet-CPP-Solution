class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<char,int> m;
        int i=0, j = 0, ans = 0;
        int n = s.length();
        while(j<n)
        {
            m[s[j]]++;
            while(m[s[j]]>2)
            {
                m[s[i]]--;
                i++;
            }
            if(ans<j-i+1) ans = j-i+1;
            j++;
        }
        if(ans<j-i) ans=j-i;
        return ans;
    }
};