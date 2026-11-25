// Smallest Unique Subarray (LeetCode, Hard)
// https://leetcode.com/problems/smallest-unique-subarray/
// My accepted solution · 2026-11-25

class Solution {
public:
    bool hasUnique(vector<int>& nums, int len) {
        const long long base = 100000;
        const long long mod  = 1000000000037LL;

        long long power = 1;                       // base^len
        for (int k = 0; k < len; k++) power = power * base % mod;

        unordered_map<long long, int> count;
        long long h = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            h = (h * base + nums[i]) % mod;        // add new element at the back
            if (i >= len) {                        // remove element leaving the window
                h = (h - (long long)nums[i - len] * power % mod + mod) % mod;
            }
            if (i >= len - 1) count[h]++;          // window [i-len+1, i] is complete
        }
        for (auto& [hash, c] : count)
            if (c == 1) return true;
        return false;
    }
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        int l=1,r = n;
        int ans;
        while(l<=r)
        {
            int mid = l + (r-l)/2;
            if(hasUnique(nums,mid))
            {
                ans = mid;
                r=mid-1;
            }
            else
            {
                l=mid+1;
            }
        }
        return ans;
    }
};
