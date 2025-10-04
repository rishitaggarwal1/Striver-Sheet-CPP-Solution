class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans=-1;
        int i=0,j=height.size()-1;
        while(i<j)
        {
            int x=min(height[i],height[j]);
            int m=x*(j-i);
            if(ans<m)   ans=m;
            if(height[i]<=height[j]) i++;
            else j--;
        }
        return ans;
    }
};