class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int n=nums.size(),maxC=0;
        unordered_set<int> s;
        for(int i=0;i<n;i++)
        {
            s.insert(nums[i]);
        }
        for(auto it:s)
        {
            if(s.find(it-1)==s.end())
            {
                int cn=1,x=it+1;
                while(s.find(x)!=s.end())
                {
                    cn++;
                    x++;
                }
                if(cn>maxC)
                    maxC=cn;
            }
        }
        return maxC;
    }
};