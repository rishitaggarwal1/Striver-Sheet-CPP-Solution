class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n=nums.size();
        vector<vector<int>> v(n,vector<int>{});
        unordered_map<int,int> m;
        for(int i=0;i<n;i++)
            m[nums[i]]++;
        for(auto it:m)
        {
            int x = it.second;
            v[x-1].push_back(it.first);
        }
        vector<int> ans;
        for(int i=n-1;i>=0;i--)
        {
            if(v[i].size()==0)  continue;
            for(auto it:v[i])
            {
                ans.push_back(it);
                if(k==ans.size())
                    return ans;
            }
        }
        return ans;
    }
};