class Solution {
public:
int sum(vector<int>& nums, int goal) {
    if(goal<0)  return 0;
        int l = 0, r=0, n = nums.size();
        int c = 0, ans = 0;
        while(r<n)
        {
            c+=nums[r];
            while(c>goal)
            {
                c-=nums[l];
                l++;
            }   
            if(c<=goal)
                ans+=(r-l+1);
            r++;
        }
        return ans;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        
        return sum(nums,goal)-sum(nums,goal-1);
    }
};