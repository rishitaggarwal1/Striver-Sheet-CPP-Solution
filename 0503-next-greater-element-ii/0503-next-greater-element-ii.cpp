class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> s;
        int n=nums.size();
        vector<int> ans(nums.size(),-1);
        for(int i=2*nums.size()-1;i>=0;i--)
        {
            while(!s.empty() && s.top()<=nums[i%n])
                s.pop();
            if (i < n) {
                if (!s.empty()) ans[i] = s.top();
            }
            s.push(nums[i % n]);
        }
        return ans;
    }
};