class Solution {
public:
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    bool check(int x, int y, int m, int n)
    {
        return (x>=0 && x<m && y>=0 && y<n)?true:false;
    }
    void bfs(vector<vector<int>> grid, vector<vector<bool>> &vis, queue<pair<int,int>> q)
    {
        int m = grid.size(), n = grid[0].size();
        while(!q.empty())
        {
            pair<int,int> p = q.front();
            int x = p.first;
            int y = p.second;
            q.pop();
            vis[x][y] = true;
            for(int i=0;i<4;i++)
            {
                int ux = x + dx[i];
                int uy = y + dy[i];
                if(check(ux,uy,m,n) && !vis[ux][uy] && grid[ux][uy]==1)
                {
                    vis[ux][uy]=true;
                    q.push({ux,uy});
                }
            }
        }
    }
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int>> q;
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        for(int i=0;i<n;i++)
        {
            if(grid[0][i]==1 && !vis[0][i])
            {
                q.push({0,i});
                vis[0][i]=true;
            }
            if(grid[m-1][i]==1 && !vis[m-1][i])
            {
                q.push({m-1,i});
                vis[m-1][i]=true;
            }
        }
        for(int i=1;i<m-1;i++)
        {
            if(grid[i][0]==1 && !vis[i][0])
            {
                q.push({i,0});
                vis[i][0]=true;
            }
            if(grid[i][n-1]==1 && !vis[i][n-1])
            {
                q.push({i,n-1});
                vis[i][n-1]=true;
            }
        }
        bfs(grid, vis, q);
        int ans =0;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==1 && !vis[i][j])
                    ans++;
            }
        }
        return ans;
    }
};