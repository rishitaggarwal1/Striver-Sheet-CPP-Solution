class Solution {
public:
    vector<vector<int>> ans;
    void func(int i, vector<int> curr, int s, vector<int>& candidates, int target)
    {
        int n = candidates.size();
        if(s>target)    return;
        if(i==n)
        {
            if(s==target)
            {
                ans.push_back(curr);
            }
            return;
        }
        curr.push_back(candidates[i]);
        func(i,curr,s+candidates[i],candidates,target);
        curr.pop_back();
        func(i+1,curr,s,candidates,target);
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> curr;
        func(0,curr,0,candidates,target);
        return ans;
    }
};