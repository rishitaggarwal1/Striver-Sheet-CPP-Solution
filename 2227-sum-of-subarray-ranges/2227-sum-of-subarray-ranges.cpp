class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        long long ans=0;
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            int max=nums[i];
            for(int j=i;j<n;j++)
            {
                max=max>nums[j]?max:nums[j];
                ans+=max;
            }
        }
        for(int i=0;i<n;i++)
        {
            int min=nums[i];
            for(int j=i;j<n;j++)
            {
                min=min<nums[j]?min:nums[j];
                ans-=min;
            }
        }
        return ans;
    }
};