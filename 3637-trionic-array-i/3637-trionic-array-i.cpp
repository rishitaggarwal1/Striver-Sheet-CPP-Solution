class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        int n = nums.size(), j=0;
        int i=1;
        while(i<n && nums[i-1]<nums[i])  
        {
            j=1;i++;
        }
        if(j==1)
            while(i<n && nums[i-1]>nums[i]) 
            {
                j=2;i++;
            }
        if(j==2)
            while(i<n && nums[i-1]<nums[i])  
            {
                j=3;i++;
            }
        return j==3 && i==n;
    }
};