class Solution {
public:
    // Recursive Code
    int nj(vector<int>& nums, int x, int j)
    {
        if(x>=nums.size()-1)
            return j;
        int mi = INT_MAX;
        for(int i=1;i<=nums[x];i++)
        {
            int jj = nj(nums,x+i,j+1);
            mi = min(mi,jj);
        }
        return mi;
    }
    int jump(vector<int>& nums) {
        int l=0,r=0,j=0;
        int n=nums.size()-1;
        while(r<=n-1)
        {
            int f=0;
            for(int i=l;i<=r;i++)
            {
                int c=i+nums[i];
                f=max(f,c);
            }
            j++;
            l=r+1;
            r=f;
        }
        return j;
    }
};