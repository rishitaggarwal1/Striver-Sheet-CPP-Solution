
class Solution {
  public:
    vector<vector<int>> getComponents(int V, vector<vector<int>>& edges) {
        // code here
        
        vector<vector<int> > edge(V);
        for(int i=0;i<edges.size();i++)
        {
            int x=edges[i][0];
            int y=edges[i][1];
            edge[x].push_back(y);
            edge[y].push_back(x);
        }
        
        vector<bool> vis(V,false);
        queue<int> q;
        vector<vector<int> > ans;
        for(int i=0;i<V;i++)
        {
            vector<int> v;
            if(!vis[i])
            {
                q.push(i);
                while(!q.empty())
                {
                    int x=q.front();
                    vis[x]=true;
                    v.push_back(x);
                    q.pop();
                    for(int j=0;j<edge[x].size();j++)
                    {
                        if(!vis[edge[x][j]]) 
                        {
                            q.push(edge[x][j]);
                            vis[edge[x][j]]=true;
                        }
                    }
                }
            }
            if(!v.empty())
                ans.push_back(v);
        }
        return ans;
    }
};
