class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int mod = 1e9+7;
        int i=0,j=nums.size()-1;
        long long ans=0;
        int n = nums.size();
        vector<int> p(n,1);
        p[0]=1;
        for(int i =1;i<n;i++)
        {
            p[i]=(p[i-1]*2)%mod;
        }
        while(i<=j)
        {
            if(nums[i]+nums[j]>target) j--;
            else
            {
                ans = (ans+(p[j-i]%mod))%mod;
                
                i++;
            }
        }
        return (int)ans%mod;
    }
};