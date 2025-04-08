class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_map<int,int> m;
        int n=nums.size();
        int k=-1;
        for(int i=n-1;i>=0;i--)
        {
            if(m.find(nums[i])!=m.end())
            {
                k=i;
                break;
            }
            m[nums[i]]++;
        }
        if(k!=-1)
        {
            k++;
            if(k%3!=0)
                return k/3 +1;
            else
                return k/3;
        }
        return 0;
    }
};