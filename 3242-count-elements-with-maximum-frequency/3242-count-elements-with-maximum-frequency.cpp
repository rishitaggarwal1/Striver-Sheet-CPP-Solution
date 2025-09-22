class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int,int> m;
        for(int i=0;i<nums.size();i++)
            m[nums[i]]++;
        int mm=INT_MIN, x=0;
        for(auto i:m)
        {
            if(i.second>mm)
            {
                mm=i.second;
                x=1;
            }
            else if(i.second==mm)   x++;
        }
        return x*mm;
    }
};