class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n=s.length();
        int ans=0,t=0;
        int i=0,j=0;
        unordered_map<char,int> m;
        for(int i=0;i<n;i++)
            m[s[i]]=-1;
        while(j<n)
        {
            if(m[s[j]]<i)
            {
                m[s[j]]=j;
                if(j==n-1 && ans<(j-i+1))   ans=j-i+1;
            }
            else
            {
                if(ans<(j-i)) ans=j-i;
                i=m[s[j]]+1;           
                m[s[j]]=j;
            }
            j++;
        }
        return ans;
    }
};