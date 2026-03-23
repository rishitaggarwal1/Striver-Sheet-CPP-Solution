class Solution {
public:
    int MOD = 1e9 +7;
    long long ans = INT_MIN;
    // Recursive Approach
    // void helper(vector<vector<int>> g, int i, int j, int m, int n, long long prod)
    // {
    //     if(i>=m && j>=n)    return;
    //     if(i==m-1 && j==n-1)
    //     {
    //         prod = prod * g[i][j];
    //         if(ans<prod)    ans = prod;
    //         return;
    //     }
    //     if(i+1<m)
    //         helper(g,i+1,j,m,n,g[i][j]*prod);
    //     if(j+1<n)
    //         helper(g,i,j+1,m,n,g[i][j]*prod);
    // }

    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // helper(grid,0,0,m,n,1);
        // if(ans<0)   return -1;
        // return (int)(ans%MOD); 

        vector<vector<long long> > mn(m,vector<long long>(n)), mg(m,vector<long long>(n));
        mn[0][0]=mg[0][0]=grid[0][0];

        for(int i =1; i<m;i++)
            mn[i][0] = mg[i][0] = grid[i][0] * mn[i-1][0];

        for(int i =1; i<n;i++)
            mn[0][i] = mg[0][i] = grid[0][i] * mn[0][i-1];

        for(int i=1;i<m;i++)
        {
            for(int j=1;j<n;j++)
            {
                if(grid[i][j]>0)
                {
                    mg[i][j] = max(mg[i-1][j],mg[i][j-1])*grid[i][j];
                    mn[i][j] = min(mn[i-1][j],mn[i][j-1])*grid[i][j];
                }
                else
                {
                    mg[i][j] = min(mn[i-1][j],mn[i][j-1])*grid[i][j];
                    mn[i][j] = max(mg[i-1][j],mg[i][j-1])*grid[i][j];
                }
            }
        }
        if(mg[m-1][n-1]<0 && mn[m-1][n-1]<0)    return -1;
        return (int)((mg[m-1][n-1]>mn[m-1][n-1]?mg[m-1][n-1]:mn[m-1][n-1])%MOD);
    }
};