class Solution {
public:
    int minimizeSum(vector<int>& nums) {
        priority_queue<int> pq;
        priority_queue<int, vector<int>, greater<int>> pq1;
        int n = nums.size();
        int m = INT_MIN;
        int mn = INT_MAX;
        for(int i=0;i<n;i++)
        {
            if(nums[i]>m)   m=nums[i];
            if(nums[i]<mn)   mn=nums[i];
            pq1.push(nums[i]);
            if(pq1.size()>3)
                pq1.pop();
            pq.push(nums[i]);
            if(pq.size()>3)
                pq.pop();
        }
        int a = m-pq.top();
        int b = pq1.top()-mn;
        pq.pop();pq1.pop();
        int c = pq1.top()-pq.top();
        // sort(nums.begin(),nums.end());
        // int a = nums[n-1]-nums[2];
        // int b = nums[n-3]-nums[0];
        // int c = nums[n-2]-nums[1];
        a = a<b?a:b;
        return a<c?a:c;
    }
};