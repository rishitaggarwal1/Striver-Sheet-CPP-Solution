class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low=0,high=nums.size()-1;
        int ans=-1;
        while(low<=high)
        {
            int mid=low + (high-low)/2;
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]<target)
            {
                ans=mid;
                low=mid+1;
            }
            else
                high=mid-1;
        }
        return ans+1;
    }
};