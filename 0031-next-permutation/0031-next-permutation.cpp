class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();
        int k=-1;
        for(int i=n-2;i>=0;i--)
        {
            if(nums[i+1]>nums[i])
            {
                k=i; break;
            }
        }
        if(k!=-1)
        {
            int gret=INT_MAX,x=-1;
            for(int i=k+1;i<n;i++)
            {
                if(nums[i]>nums[k] && gret>=nums[i])
                {
                    gret=nums[i];
                    x=i;
                }
            }
            nums[x]=nums[k];
            nums[k]=gret;
        }
        for(int i=0;i<(n-k-1)/2;i++)
        {
            int t=nums[i+k+1];
            nums[i+k+1]=nums[n-i-1];
            nums[n-i-1]=t;
        }
    }
};