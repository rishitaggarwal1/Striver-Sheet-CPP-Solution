class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(),potions.end());
        int n=spells.size();
        vector<int> ans(n);
        for(int i=0;i<n;i++)
        {
            int l=0,h=potions.size()-1;
            int a=0;
            while(l<=h)
            {
                int mid=l+(h-l)/2;
                long long x=(long long)potions[mid]*(long long)spells[i];
                if(x<success)
                    l=mid+1;
                else
                {
                    h=mid-1;
                }
            }
            ans[i]=(potions.size()-l);
        }
        return ans;
    }
};