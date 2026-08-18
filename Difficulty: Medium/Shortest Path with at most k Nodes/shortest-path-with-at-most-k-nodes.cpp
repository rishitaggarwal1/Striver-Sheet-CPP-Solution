class Solution {
  public:
    int findCheapestCost(int n, vector<vector<int>>& edges, int src, int dst, int k) {
        // code here
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<edges.size();i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            adj[u].push_back({v,w});
        }
        vector<int> dist(n,1e9);
        queue<pair<int,pair<int,int>>> pq;
        pq.push({0,{src,0}});
        dist[src]=0;
        while(!pq.empty())
        {
            int stp = pq.front().first;
            int node = pq.front().second.first;
            int ds = pq.front().second.second;
            pq.pop();
            if(stp>k)   continue;
            for(auto it:adj[node])
            {
                int x = it.first;
                int wt = it.second;
                if(dist[x]>ds+wt && stp<=k)
                {
                    dist[x] = ds+wt;
                    pq.push({stp+1,{x,dist[x]}});
                }
            }
        }
        if(dist[dst]==1e9)
            return -1;
        return dist[dst];
    }
};