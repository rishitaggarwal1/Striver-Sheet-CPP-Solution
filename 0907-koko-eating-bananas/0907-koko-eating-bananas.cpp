class Solution {
public:
    long long calcH(vector<int> p, int a)
    {
        long long ans=0;
        for(int i=0;i<p.size();i++)
        {
            ans+=ceil((double)(p[i])/(double(a)));
        }
        return ans;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        int high=-1, low=1;
        for(int i=0;i<piles.size();i++)
        {
            if(piles[i]>high)
                high=piles[i];
        }
        while(low<=high)
        {
            int mid = low + (high-low)/2;
            long long x=calcH(piles,mid);
            if(x<=h)
            {
                high=mid-1;
            }
            else
                low=mid+1; 
        }
        return low;
    }
};