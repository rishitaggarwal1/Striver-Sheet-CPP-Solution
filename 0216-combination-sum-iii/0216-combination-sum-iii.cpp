class Solution {
public:
set<vector<int>> ans;
    void func(int i, vector<int>& curr, int s, int k, int target)
    {
        if(s==target)
        {
            if(curr.size()==k)
                ans.insert(curr);
            return;
        }
        if(s>target || curr.size()>=k)    return;
        for(int j=i;j<=9;j++)
        {
            curr.push_back(j);
            func(j+1,curr,s+j,k,target);
            curr.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> curr;
        func(1,curr,0,k,n);
        vector<vector<int>> v(ans.begin(),ans.end());
        return v;
    }
};