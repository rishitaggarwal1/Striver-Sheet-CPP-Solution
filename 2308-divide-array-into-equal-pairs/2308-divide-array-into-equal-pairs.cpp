class Solution {
public:
    bool divideArray(vector<int>& nums) {
        unordered_map<int,int> m;
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            m[nums[i]]++;
        }
        for(auto it:m)
        {
            if(it.second%2==1)
                return false;
        }
        return true;
    }
};