class Solution {
  public:
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Code here
        vector<bool> vis(V,false);
        
        vector<vector<int>> edge(V);
        for(int i=0;i<edges.size();i++)
        {
            int x=edges[i][0];
            int y=edges[i][1];
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        
        for(int i=0;i<V;i++)
        {
            if(vis[i])  continue;
            vis[i]=true;
            queue<pair<int,int>> q;
            q.push({i,-1});
            while(!q.empty())
            {
                pair<int,int> p = q.front();
                int x=p.first;
                q.pop();
                for(auto i:edge[x])
                {
                    if(!vis[i])
                    {
                        vis[i]=true;
                        q.push({i,x});
                    }
                    else if(i!=p.second)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};