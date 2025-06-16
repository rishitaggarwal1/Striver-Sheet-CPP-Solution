class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int n=nums.size();
        vector<int> v(n,0);
        v[0]=nums[0];
        for(int i=1;i<n;i++)
        {
            if(v[i-1]>nums[i])
                v[i]=nums[i];
            else
                v[i]=v[i-1];
        }
        int ans=INT_MIN;
        for(int i=0;i<n;i++)
        {
            int t=nums[i]-v[i];
            if(t>ans)
                ans=t;
        }
        if(ans==0)
            return -1;
        return ans;
    }
};