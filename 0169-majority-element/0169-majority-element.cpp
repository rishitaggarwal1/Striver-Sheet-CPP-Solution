class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int el;
        int cn=0;
        for(int i=0;i<nums.size();i++)
        {
            if(cn==0)
            {
                cn=1;
                el=nums[i];
            }
            else if(nums[i]==el)
            {
                cn++;
            }
            else
            {
                cn--;
            }
        }
        return el;
    }
};