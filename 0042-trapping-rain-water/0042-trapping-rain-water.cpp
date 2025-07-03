class Solution {
public:
    int trap(vector<int>& height) {
        int n=height.size();
        vector<int> pref;
        pref.push_back(height[0]);
        for(int i=1;i<n;i++)
        {
            if(pref[i-1]<height[i])
                pref.push_back(height[i]);
            else
                pref.push_back(pref[i-1]);
        }
        vector<int> suff(n,0);
        suff[n-1]=height[n-1];
        for(int i=n-2;i>=0;i--)
        {
            if(suff[i+1]<height[i])
                suff[i]=height[i];
            else
                suff[i]=suff[i+1];
        }
        int sum=0;
        for(int i=0;i<n;i++)
        {
            int x=0;
            if(pref[i]<suff[i])
                x=pref[i];
            else
                x=suff[i];
            sum+=(x-height[i]);
        }
        return sum;
    }
};