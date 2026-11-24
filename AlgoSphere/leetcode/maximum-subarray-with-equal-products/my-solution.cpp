// Maximum Subarray With Equal Products (LeetCode, Easy)
// https://leetcode.com/problems/maximum-subarray-with-equal-products/
// My accepted solution · 2026-11-24

class Solution {
public:
    int gcd(long long a, long long b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        long long prod = nums[0];
        int l = 0, r= 1;
        int ans = 2;
        while(r<n)
        {
            if(gcd(prod,nums[r])==1)
            {
                prod = prod*nums[r];
                r++;
                if(ans<r-l)
                    ans= r-l;
            }
            else
            {
                prod=prod/nums[l];
                l++;
            }
        }
        return ans;
    }
};
