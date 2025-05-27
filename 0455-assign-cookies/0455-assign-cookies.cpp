class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int ans=0;
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        for(int i=0,j=0;i<s.size() && j<g.size();)
        {
            if(g[j]<=s[i])
            {
                ans++;
                i++;j++;
            }
            else
                i++;
        }
        return ans;
    }
};