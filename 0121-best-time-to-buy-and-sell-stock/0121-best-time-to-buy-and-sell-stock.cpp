class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> v(n,0);
        v[0]=prices[0];
        for(int i=1;i<n;i++)
        {
            if(prices[i]<v[i-1])
                v[i]=prices[i];
            else
                v[i]=v[i-1];
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            if(ans<(prices[i]-v[i]))
                ans=prices[i]-v[i];
        }
        return ans;
    }
};