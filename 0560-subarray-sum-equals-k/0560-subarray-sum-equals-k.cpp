class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> m;
        m[0]=1;
        int n=nums.size();
        int ans=0,sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=nums[i];
            if(m.find(sum-k)!=m.end())
                ans+=m[sum-k];
            m[sum]++;
        }
        return ans;
    }
};