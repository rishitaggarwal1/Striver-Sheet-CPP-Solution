class Solution {
public:
    bool check(vector<int>& nums) {
        int i=0;
        while((nums.size()-1)!=i && nums[i]<=nums[i+1])
        {
            i++;
        }
        if(i==nums.size()-1)
            return true;
        reverse(nums.begin(),nums.begin()+i+1);
        reverse(nums.begin()+i+1,nums.end());

        for(i=0;i<nums.size()-1;i++)
        {
            if(nums[i]<nums[i+1])
                return false;
        }
        return true;
        
    }
};