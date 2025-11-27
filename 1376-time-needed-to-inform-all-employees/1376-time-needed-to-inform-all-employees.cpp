class Solution {
public:
    vector<vector<int>> adj;
    vector<int> _inform;
    vector<int> memo;
    int dfs(int emp)
    {
        if(memo[emp]!=-1)   return memo[emp];
        int maxC = 0;

        for(int subC: adj[emp])
        {
            maxC = max(maxC, dfs(subC));
        }
        return memo[emp] = _inform[emp] + maxC;
    }
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        _inform = informTime;
        adj.assign(n,{});
        memo.assign(n,-1);
        for(int i =0;i<n;i++)
        {
            if(manager[i]!=-1)
            {
                adj[manager[i]].push_back(i);
            }
        }

        return dfs(headID);
    }
};