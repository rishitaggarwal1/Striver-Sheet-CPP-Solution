class Solution {
public:
    void DFS(int node, vector<vector<int>>& adj, vector<bool>& vis)
    {
        int n=adj.size();
        for(int i=0;i<n;i++)
        {
            if(adj[node][i]==1 && !vis[i])
            {
                vis[i]=true;
                DFS(i,adj,vis);
            }
        }
        return;
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int ans=0;
        vector<bool> vis(n,false);
        for(int i=0;i<n;i++)
        {
            if(!vis[i])
            {
                ans++;
                vis[i]=true;
                DFS(i,isConnected,vis);
            }
        }
        return ans;
    }
};