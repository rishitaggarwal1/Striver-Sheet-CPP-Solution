class Solution {
  public:
    vector<int> bfs(vector<vector<int>> &adj) {
        // Code here
        queue<int> q;
        vector<int> ans;
        vector<bool> vis(adj.size(),false);
        for(int i=0;i<adj.size();i++)
        {
            if(!vis[i])
            {
                q.push(i);
                while(!q.empty())
                {
                    int x= q.front();
                    vis[x]=true;
                    q.pop();
                    ans.push_back(x);
                    for(int j=0;j<adj[x].size();j++)
                    {
                        if(!vis[adj[x][j]])
                        {
                            q.push(adj[x][j]);
                            vis[adj[x][j]]=true;
                        }
                    }
                }
            }
        }
        return ans;
    }
};