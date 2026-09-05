class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> v(n);
        v[n-1] = nums[n-1];
        for(int i = n-2;i>=0;i--)
        {
            if(v[i+1]<nums[i])
                v[i] = v[i+1];
            else
                v[i]=nums[i];
        }
        int m= nums[0];
        for(int i=0;i<n;i++)
        {
            if(m<nums[i])   m= nums[i];
            if(m-v[i]<=k)   return i;
        }
        return -1;
    }
};