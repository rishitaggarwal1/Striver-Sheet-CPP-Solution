class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int el1,cn1=0,el2,cn2=0,n=nums.size();
        for(int i=0;i<nums.size();i++)
        {
            if(cn1==0 && el2!=nums[i])
            {
                cn1=1;
                el1=nums[i];
            }
            else if(cn2==0 && el1!=nums[i])
            {
                cn2=1;
                el2=nums[i];
            }
            else if(el1==nums[i])
                cn1++;
            else if(el2==nums[i])
                cn2++;
            else
            {
                cn1--;
                cn2--;
            }
        }
        vector<int> ans;
        cn1=0;cn2=0;
        for(int i=0;i<n;i++)
        {
            if(nums[i]==el1)
                cn1++;
            else if(nums[i]==el2)
                cn2++;
        }
        if(cn1>floor(n/3))
            ans.push_back(el1);
        if(cn2>floor(n/3))
            ans.push_back(el2);
        return ans;
    }
};