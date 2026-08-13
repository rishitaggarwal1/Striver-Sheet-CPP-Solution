class Solution {
public:
    bool check(int x, int y, int m, int n)
    {
        return (x>=0 && x<m && y>=0 && y<n)?true:false;
    }
    void solve(vector<vector<char>>& board) {
        int m= board.size(), n = board[0].size();
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        queue<pair<int,int>> q;
        for(int i=0;i<n;i++)
        {
            if(board[0][i]=='O') 
            {
                q.push({0,i});
                vis[0][i]=true;
            }   
            if(board[m-1][i]=='O')
            {
                q.push({m-1,i});
                vis[m-1][i]=true;
            }
        }
        
        for(int i=1;i<m-1;i++)
        {
            if(board[i][0]=='O') 
            {
                q.push({i,0});
                vis[i][0]=true;
            }   
            if(board[i][n-1]=='O')
            {
                q.push({i,n-1});
                vis[i][n-1]=true;
            }
        }
        int dx[4] = {0,1,0,-1};
        int dy[4] = {1,0,-1,0};
        while(!q.empty())
        {
            pair<int,int> p = q.front();
            q.pop();
            int x = p.first;
            int y = p.second;
            for(int i=0;i<4;i++)
            {
                int ux = x + dx[i];
                int uy = y + dy[i];
                if(check(ux,uy,m,n) && !vis[ux][uy] && board[ux][uy]=='O')
                {
                    q.push({ux,uy});
                    vis[ux][uy]=true;
                }
            }
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(board[i][j] == 'O' && !vis[i][j])
                    board[i][j] = 'X';
            }
        }
        return;
    }
};