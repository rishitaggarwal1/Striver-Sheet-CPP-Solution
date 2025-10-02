class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int ori = image[sr][sc];
        image[sr][sc]=color;
        int m=image.size(),n=image[0].size();
        queue<pair<int,int>> q;
        q.push({sr,sc});
        int dx[4]={0,0,1,-1};
        int dy[4]={1,-1,0,0};
        vector<vector<bool>> vis(m,vector<bool>(n,false));
        while(!q.empty())
        {
            pair<int,int> p=q.front();
            vis[p.first][p.second] = true;
            q.pop();
            for(int i=0;i<4;i++)
            {
                int x=p.first + dx[i];
                int y=p.second + dy[i];
                if(x<0 || y<0 || x>=m || y>=n)  continue;
                if(image[x][y]==ori && !vis[x][y])
                {
                    image[x][y] = color;
                    q.push({x,y});
                }
            }
        }
        return image;
    }
};