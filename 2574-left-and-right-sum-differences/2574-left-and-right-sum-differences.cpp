class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        int tot_sum = 0;
        for(int i =0;i<n;i++)   tot_sum+=nums[i];
        vector<int> ans(n,0);
        int right_sum = 0;
        for(int i=n-1;i>=0;i--)
        {
            tot_sum -=nums[i];
            ans[i] = abs(tot_sum - right_sum);
            right_sum+=nums[i];
        }
        return ans;
    }
};