class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        long long ans =0;
        int n = nums.size();
        long long mn = INT_MAX, mx= INT_MIN;
        for(int i=0;i<n;i++)
        {
            if(nums[i]>mx)  mx = nums[i];
            if(nums[i]<mn)  mn = nums[i];
        }
        return k*(mx-mn);
    }
};