class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> u;
        for(int i=0;i<nums.size();i++)
        {
            int t=target-nums[i];
            if(u.find(t)!=u.end())
            {
                return {i,u[t]};
            }
            u[nums[i]]=i;
        }
        return {};
    }
};