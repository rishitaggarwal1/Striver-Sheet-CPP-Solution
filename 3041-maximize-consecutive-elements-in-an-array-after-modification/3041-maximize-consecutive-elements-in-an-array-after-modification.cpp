class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        unordered_map<int,int> dp;
        int m=INT_MIN;
        for(int i=0;i<n;i++)
        {
            int o = dp[nums[i]];
            int om = dp[nums[i]-1];
            dp[nums[i]+1] = o+1;
            dp[nums[i]] = om+1;
        }
        for(auto it:dp)
        {
            if(m<it.second)
                m=it.second;
        }
        return m;
    }
};