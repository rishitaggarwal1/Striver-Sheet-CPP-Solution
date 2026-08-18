class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = -1;
        if(k==n)
        {
            for(int i=0;i<n;i++)
            {
                if(nums[i]>ans) ans = nums[i];
            }
        }
        unordered_map<int,int> m;
        for(int i=0;i<n;i++)
        {
            m[nums[i]]++;
        }
        if(k==1)
        {
            for(int i=0;i<n;i++)
            {
                if(ans<nums[i] && m[nums[i]]==1)
                    ans = nums[i];
            }
        }
        else
        {
            if(m[nums[0]]==1)
                ans = max(ans,nums[0]);
            if(m[nums[n-1]]==1)
                ans = max(ans,nums[n-1]);
        }
        return ans;
    }
};