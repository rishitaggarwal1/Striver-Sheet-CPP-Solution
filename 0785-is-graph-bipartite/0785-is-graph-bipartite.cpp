class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> vis(n,-1);
        for(int i=0;i<n;i++)
        {
            if(vis[i]==-1)
            {
                queue<int> q;
                q.push(i);
                vis[i]=0;
                while(!q.empty())
                {
                    int x = q.front();
                    q.pop();
                    for(auto it:graph[x])
                    {
                        if(vis[it]==-1)
                        {
                            q.push(it);
                            vis[it]=1-vis[x];
                        }
                        else if(vis[it]==vis[x])
                            return false;
                    }
                }
            }
        }
        return true;
    }
};