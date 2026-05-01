class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        int ans = INT_MIN, temp =0, k=0;
        int n = nums.size();
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=nums[i];
            temp+=i*nums[i];
            k++;
        }
        if(temp>ans)    ans = temp;
        for(k=1;k<n;k++)
        {
            temp = temp + sum - n*nums[n-k];
            if(ans<temp)    ans = temp;
        }
        return (int)ans;
    }
};