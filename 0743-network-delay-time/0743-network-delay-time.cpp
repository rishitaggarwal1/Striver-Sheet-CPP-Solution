class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for(int i=0;i<times.size();i++)
        {
            int u = times[i][0];
            int v = times[i][1];
            int w = times[i][2];
            adj[u].push_back({v,w});
        }
        vector<int> dist(n+1,1e9);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        dist[k]=0;
        pq.push({0,k});
        while(!pq.empty())
        {
            int wt = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            for(auto it: adj[node])
            {
                int x = it.first;
                int w = it.second;
                if(dist[x]>wt + w)
                {
                    dist[x] = wt+w;
                    pq.push({dist[x],x});
                }
            }
        }
        int ans = -1;
        for(int i = 1;i<=n;i++)
        {
            if(dist[i]==1e9)    return -1;
            if(dist[i]>ans) ans = dist[i];
        }
        return ans;
    }
};