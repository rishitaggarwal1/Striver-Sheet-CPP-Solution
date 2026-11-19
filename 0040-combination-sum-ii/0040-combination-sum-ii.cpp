class Solution {
public:
    set<vector<int>> ans;
    void func(int i, vector<int>& curr, int s, vector<int>& candidates, int target)
    {
        int n = candidates.size();
        if(s>target)    return;
        if(s==target)
        {
            ans.insert(curr);
            return;
        }
        for(int j=i;j<n;j++)
        {
            if(j>i && candidates[j]==candidates[j-1])
                continue;
            curr.push_back(candidates[j]);
            func(j+1,curr,s+candidates[j],candidates,target);
            curr.pop_back();
            // func(j,curr,s,candidates,target);
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> curr;
        sort(candidates.begin(),candidates.end());
        func(0,curr,0,candidates,target);
        vector<vector<int>> v(ans.begin(),ans.end());
        return v;
    }
};