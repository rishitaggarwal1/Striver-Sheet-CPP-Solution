class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int so = INT_MAX, se = INT_MAX;
        int n = nums1.size();
        for(int i=0;i<n;i++)
        {
            if(nums1[i]%2==1 && so>nums1[i])
                so = nums1[i];
            else if(nums1[i]%2==0 && se>nums1[i])
                se = nums1[i];
        }
        if(so==INT_MAX) return true;
        if(se>so)   return true;
        return false;
    }
};