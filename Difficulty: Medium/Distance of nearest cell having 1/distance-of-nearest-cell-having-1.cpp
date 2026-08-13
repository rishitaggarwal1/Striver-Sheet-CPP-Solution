class Solution {
  public:
  bool check(int x, int y, int m, int n)
    {
        return (x>=0 && x<m && y>=0 && y<n)?true:false;
    }
    vector<vector<int>> nearest(vector<vector<int>>& mat) {
        // code here
        int m = mat.size();
        int n = mat[0].size();
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        queue<pair<pair<int,int>,int>> q;
        vector<vector<int>> ans(m,vector<int>(n,0));
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(mat[i][j]==1)
                {
                    q.push({{i,j},0});
                }
            }
        }
        int dx[4] = {0,1,0,-1};
        int dy[4] = {1,0,-1,0};
        while(!q.empty())
        {
            pair<pair<int,int>,int> p = q.front();
            q.pop();
            int x = p.first.first;
            int y = p.first.second;
            int d = p.second;
            vis[x][y]=true;
            for(int i=0;i<4;i++)
            {
                int ux = x + dx[i];
                int uy = y + dy[i];
                if(check(ux,uy,m,n) && !vis[ux][uy] && mat[ux][uy]==0)
                {
                    ans[ux][uy]=d+1;
                    vis[ux][uy]=true;
                    q.push({{ux,uy},d+1});
                }
            }
        }
        return ans;
    }
};