class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        queue<pair<int,int>> q;
        int tr=0,tf=0;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==2)
                {
                    q.push({i,j});
                    tr++;
                }
                else if(grid[i][j]==1)  tf++;
            }
        }
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        int ans=0;
        while(!q.empty())
        {
            int cnt=q.size();
            bool check=false;
            while(cnt--)
            {
                pair<int,int> p=q.front();
                q.pop();
                for(int i=0;i<4;i++)
                {
                    int x=p.first + dx[i];
                    int y=p.second + dy[i];
                    if(x>=0 && x<m && y>=0 && y<n && grid[x][y]==1)
                    {
                        grid[x][y]=2;
                        q.push({x,y});
                        check=true;
                        tf--;
                    }
                }
            }
            if(check)   ans++;
        }
        if(tf==0)   return ans;
        return -1;
    }
};