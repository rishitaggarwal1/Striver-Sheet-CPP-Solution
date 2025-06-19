class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low=0,high=nums.size()-1;
        int end=-1,start=-1;
        while(low<=high)
        {
            int mid=low+(high-low)/2;
            if(nums[mid]==target)
                end=mid;
            if(nums[mid]<=target)
            {
                low=mid+1;
            }
            else
                high=mid-1;
        }
        if(end==-1)
            return {-1,-1};
        low=0;high=nums.size()-1;
        while(low<=high)
        {
            int mid=low+(high-low)/2;
            if(nums[mid]==target)
                start=mid;
            if(nums[mid]>=target)
            {
                high=mid-1;
            }
            else
                low=mid+1;
        }
        return {start,end};
    }
};