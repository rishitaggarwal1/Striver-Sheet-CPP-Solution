class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int n = nums.size();
        int ans =0;
        for(int i=0;i<n;i++)
        {
            int x = sqrt(nums[i]);
            int temp =0, count = 0;
            for(int j=1;j<=x;j++)
            {
                if(nums[i]%j==0)
                {
                    if(j*j == nums[i])
                    {
                        count++;
                        temp+=j;
                    }
                    else
                    {
                        count+=2;
                        temp+=(j+nums[i]/j);
                    }
                }
            }
            if(count == 4)  ans+=temp;
        }
        return ans;
    }
};