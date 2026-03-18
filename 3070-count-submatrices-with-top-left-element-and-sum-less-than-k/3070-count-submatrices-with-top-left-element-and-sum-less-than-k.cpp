class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int> > v(m,vector<int>(n,-1));
        v[0][0] = grid[0][0];
        if(grid[0][0]>k)    return 0;
        int ans = 1;
        for(int i=1;i<n;i++)
        {
            v[0][i] = grid[0][i] + v[0][i-1];
            if(v[0][i]<=k)
                ans++;
            else break;
        }
        for(int i=1;i<m;i++)
        {
            v[i][0] = grid[i][0] + v[i-1][0];
            if(v[i][0]<=k)
                ans++;
            else break;
        }
        for(int i = 1;i<m;i++)
        {
            for(int j = 1;j<n;j++)
            {
                if(v[i-1][j]==-1 || v[i][j-1]==-1)  break;
                v[i][j] = v[i-1][j] + v[i][j-1] + grid[i][j] - v[i-1][j-1];
                if(v[i][j]<=k)
                    ans++;
            }
        }
        return ans;
    }
};