class Solution {
public:
    void bfs(vector<vector<int>>& isConnected, int u, vector<int> &vis)
    {
        int n=isConnected.size();
        queue<int> q;
        q.push(u);
        vis[u]=1;
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0;i<n;i++)
            {
                if(isConnected[x][i]==1 && vis[i+1]==0)
                {
                    q.push(i);
                    vis[i+1]=1;
                }
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        vector<int> vis(n+1,0);
        int ans = 0;
        for(int i=0;i<n;i++)
        {
            if(vis[i+1]==0)
            {
                bfs(isConnected,i,vis);
                ans++;
            }
        }
        return ans;
    }
};