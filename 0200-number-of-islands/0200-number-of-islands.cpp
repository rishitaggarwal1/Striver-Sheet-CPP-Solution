class Solution {
public:
    int dx[4]={0,1,0,-1};
    int dy[4]={1,0,-1,0};
    bool check(int x,int y, int m,int n)
    {
        if((x>=0 && x<m) && (y>=0 &&y<n))   return true;
        return false;
    }
    void bfs(vector<vector<char>>& grid, vector<vector<int>> &vis, pair<int,int> u)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int> > q;
        q.push(u);
        int x = u.first;
        int y = u.second;
        vis[x][y]=1;
        while(!q.empty())
        {
            pair<int,int> temp = q.front();
            x=temp.first;
            y=temp.second;
            q.pop();

            for(int i=0;i<4;i++)
            {
                int a = x+dx[i];
                int b = y+dy[i];
                if(check(a,b,m,n) && vis[a][b]==0 && grid[a][b]=='1')
                {
                    q.push({a,b});
                    vis[a][b]=1;
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans=0;
        vector<vector<int> > vis(m,vector<int>(n,0));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]=='1' && vis[i][j]==0)
                {
                    bfs(grid,vis,{i,j});
                    ans++;
                }
            }
        }
        return ans;
    }
};