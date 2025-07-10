class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int i=0,j=0,n=nums.size();
        int ans=0;
        queue<int> q;
        while(j<n)
        {
            if(nums[j]==0)
            {
                if(q.size()<k)
                {
                    q.push(j);
                }
                else if(!q.empty())
                {
                    i=q.front()+1;
                    q.pop();
                    q.push(j);
                }
                else    i=j+1;
            }
            if(ans<(j-i+1)) ans=j-i+1;
            j++;
        }
        return ans;
    }
};