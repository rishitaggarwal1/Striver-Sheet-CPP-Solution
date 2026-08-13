class Solution {
  public:
    bool dfs(vector<vector<int>> &adj, vector<bool> &vis, vector<bool> &path, int sr, vector<bool> &safe)
    {
        if(safe[sr])    return false;
        vis[sr]=true;
        path[sr]=true;
        for(auto it:adj[sr])
        {
            if(!vis[it])
            {
                if(dfs(adj,vis,path,it,safe)==true) return true;
            }
            else if(path[it]) return true;
        }
        path[sr] = false;
        safe[sr] = true;
        return false;
    }
    vector<int> safeNodes(int V, vector<vector<int>>& edges) {
        // Code here
        vector<vector<int>> adj(V);
        for(int i=0;i<edges.size();i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            adj[u].push_back(v);
        }
        vector<bool> vis(V,false),path(V,false),check(V,false);
        vector<int> ans;
        for(int i=0;i<V;i++)
        {
            if(!vis[i])
            {
                dfs(adj,vis,path,i,check);
            }
        }
        for(int i=0;i<V;i++)
        {
            if(check[i])   ans.push_back(i);
        }
        return ans;
    }
};