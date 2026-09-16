class Solution {
public:
    int sum(vector<int>& nums, int k) {
        int l=0,r=0;
        int n = nums.size();
        int c=0, ans=0;
        while(r<n)
        {
            if(nums[r]%2==1)    c++;
            while(c>k)
            {
                c= c-nums[l]%2;
                l++;
            }
            if(c<=k)   ans+=(r-l+1);
            r++;
        }
        return ans;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
        return sum(nums,k)-sum(nums,k-1);
    }
};