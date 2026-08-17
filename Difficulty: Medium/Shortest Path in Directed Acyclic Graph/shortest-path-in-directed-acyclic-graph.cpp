class Solution {
  public:
    void dfs(vector<vector<pair<int,int>>> &adj, vector<bool> &vis, stack<int> &st, int sr)
    {
        vis[sr]=true;
        for(auto it:adj[sr])
        {
            if(!vis[it.first])
                dfs(adj,vis,st,it.first);
        }
        st.push(sr);
    }
    vector<int> shortestPath(int V, vector<vector<int>>& edges) {
        // code here
        vector<vector<pair<int,int>>> adj(V);
        for(int i=0;i<edges.size();i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adj[u].push_back({v,wt});
        }
        vector<bool> vis(V,false);
        stack<int> st;
        for(int i=0;i<V;i++)
        {
            if(!vis[i])
            {
                dfs(adj,vis,st,i);
            }
        }
        vector<int> dist(V,1e9);
        dist[0]=0;
        while(!st.empty())
        {
            int x = st.top();
            st.pop();
            for (auto it : adj[x]) {
              int v = it.first;
              int wt = it.second;
    
              // Update distance if a shorter path is found
              if (dist[x] + wt < dist[v]) {
                dist[v] = wt + dist[x];
              }
            }
        }
        for (int i = 0; i < V; i++) {
        if (dist[i] == 1e9) {
          dist[i] = -1;
        }
      }
        return dist;
    }
};
