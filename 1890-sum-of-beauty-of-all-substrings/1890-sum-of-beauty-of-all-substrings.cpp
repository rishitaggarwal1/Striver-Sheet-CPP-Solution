class Solution {
public:
    int beautySum(string s) {
        int ans=0;
        int n=s.length();
        for(int i=0;i<n;i++)
        {
            unordered_map<char,int> m;
            int a=ans;
            for(int j=i;j<n;j++)
            {
                m[s[j]]++;
                int mx=INT_MIN, mm=INT_MAX;
                for(auto x:m)
                {
                    if(x.second>mx)  mx=x.second;
                    if(x.second<mm)  mm=x.second;
                }
                ans+=(mx-mm);
            }
            if(a==ans)  break;
        }
        return ans;
    }
};