class Solution {
public:
    int sum(int x)
    {
        int s=0;
        while(x>0)
        {
            s+=(x%10);
            x=x/10;
        }
        return s;
    }
    int smallestIndex(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            if(sum(nums[i])==i)
                return i;
        }
        return -1;
    }
};