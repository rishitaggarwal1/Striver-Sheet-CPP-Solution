class Solution {
  public:
    vector<int> ans;
    void DFS(int node, vector<vector<int>>& adj, vector<bool>& vis)
    {
        for(auto i: adj[node])
        {
            if(!vis[i])
            {
                vis[i]=true;
                ans.push_back(i);
                DFS(i,adj,vis);
            }
        }
        return;
    }
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        int n=adj.size();
        vector<bool> vis(n,false);
        for(int i=0;i<n;i++)
        {
            if(!vis[i]) 
            {
                vis[i]=true;
                ans.push_back(i);
                DFS(i,adj,vis);
            }
        }
        return ans;
    }
};