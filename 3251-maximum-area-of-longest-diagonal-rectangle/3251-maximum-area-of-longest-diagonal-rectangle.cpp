class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) {
        long long md=0;
        int ma=0;
        for(int i=0;i<dimensions.size();i++)
        {
            long long x=dimensions[i][0]*dimensions[i][0] + dimensions[i][1]*dimensions[i][1];
            if(md<x)
            {
                ma = dimensions[i][0]*dimensions[i][1];
                md=x;
            }
            else if(md==x)
            {
                ma = max(ma,dimensions[i][0]*dimensions[i][1]);
            }
        }
        return ma;
    }
};