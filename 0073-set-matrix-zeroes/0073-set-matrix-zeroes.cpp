class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m=matrix.size(),n=matrix[0].size();
        int col0=0,row0=0;
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(matrix[i][j]==0)
                {
                    if(i==0)
                        row0=-1;
                    else
                        matrix[i][0]=-1;
                    if(j==0)
                        col0=-1;
                    else
                        matrix[0][j]=-1;
                }
            }
        }

        for(int i=1;i<m;i++)
        {
            if(matrix[i][0]==-1)
            {
                for(int j=0;j<n;j++)
                {
                    matrix[i][j]=0;
                }
            }
        }
        for(int i=0;i<n;i++)
        {
            if((i==0 && col0==-1) || matrix[0][i]==-1)
            {
                for(int j=0;j<m;j++)
                {
                    matrix[j][i]=0;
                }
            }
        }
        if(row0==-1)
        {
            for(int j=0;j<n;j++)
            {
                matrix[0][j]=0;
            }
        }
        return;
    }
};