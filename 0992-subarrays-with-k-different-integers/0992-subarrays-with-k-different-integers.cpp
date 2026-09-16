class Solution {
public:
    int sum(vector<int>& nums, int k) {
        int n = nums.size();
        int l = 0, r = 0;
        int ans = 0;
        if(k<=0)    return 0;
        unordered_map<int,int> m;
        while(r<n)
        {
            m[nums[r]]++;
            while(m.size()>k)
            {
                m[nums[l]]--;
                if(m[nums[l]]==0)
                    m.erase(nums[l]);
                l++;
            }
            if(m.size()<=k)
                ans+=(r-l+1);
            r++;
        }
        return ans;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return sum(nums,k)-sum(nums,k-1);
    }
};