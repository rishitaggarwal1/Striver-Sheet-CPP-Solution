class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxtill=0,maxans=INT_MIN;
        for(int i=0;i<nums.size();i++)
        {
            maxtill+=nums[i];
            if(maxans<maxtill)
                maxans=maxtill;
            if(maxtill<0)
                maxtill=0;
        }
        return maxans;
    }
};