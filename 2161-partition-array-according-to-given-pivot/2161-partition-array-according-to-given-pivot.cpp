class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();
        int l=0, g=0, e=0;
        for(int i=0;i<n;i++)
        {
            if(nums[i]<pivot) l++;
            else if(nums[i]>pivot)  g++;
            else e++;
        }
        vector<int> ans(n,pivot);
        int x =0, y=l+e;
        for(int i=0;i<n;i++)
        {
            if(nums[i]<pivot)
            {
                ans[x++]=nums[i];
            }
            else if(nums[i]>pivot)
            {
                ans[y++] = nums[i];
            }
        }
        return ans;
    }
};