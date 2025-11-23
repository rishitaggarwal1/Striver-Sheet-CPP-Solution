class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int sum=0;
        vector<int> rem1,rem2;
        int n=nums.size();
        for(int i=0;i<n;i++)
        {
            sum+=nums[i];
            if(nums[i]%3==1)    rem1.push_back(nums[i]);
            else if(nums[i]%3==2)    rem2.push_back(nums[i]);
        }
        if(sum%3==0)    return sum;
        sort(rem1.begin(),rem1.end());
        sort(rem2.begin(),rem2.end());

        if(sum%3==1)
        {
            if(rem1.size()>0 && rem2.size()>1)
            {
                sum-=(rem1[0] < (rem2[0]+rem2[1])?rem1[0]: (rem2[0]+rem2[1]));
            }
            else if(rem1.size()>0)
            {
                sum-= rem1[0];
            }
            else
            {
                sum-= (rem2[0]+rem2[1]);
            }
        }
        else
        {
            int x1 = rem1.size()>1 ? rem1[0] + rem1[1] : INT_MAX;
            int x2 = rem2.size()>0 ? rem2[0] : INT_MAX;
            sum-=x1<x2?x1:x2;
        }
        return sum;
    }
};