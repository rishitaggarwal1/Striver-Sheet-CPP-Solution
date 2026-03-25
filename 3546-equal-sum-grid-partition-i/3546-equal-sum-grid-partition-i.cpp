class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<long> r(m,0), c(n,0);

        for(int i=0;i<m;i++)
        {
            long s =0;
            for(int j=0;j<n;j++)
            {
                s+=grid[i][j];
            }
            r[i]=s;
        }

        for(int i=0;i<n;i++)
        {
            long s =0;
            for(int j=0;j<m;j++)
            {
                s+=grid[j][i];
            }
            c[i]=s;
        }

        vector<long> pc(n,0);
        pc[0]=c[0];
        for(int i=1;i<n;i++)
        {
            pc[i] = c[i] + pc[i-1];
        }
        long suff = c[n-1];
        for(int i=n-2;i>=0;i--)
        {
            if(suff == pc[i])   return true;
            suff+=c[i];
        }

        
        vector<long> pr(m,0);
        pr[0]=r[0];
        for(int i=1;i<m;i++)
        {
            pr[i] = r[i] + pr[i-1];
        }
        suff = r[m-1];
        for(int i=m-2;i>=0;i--)
        {
            if(suff == pr[i])   return true;
            suff+=r[i];
        }
        return false;
    }
};