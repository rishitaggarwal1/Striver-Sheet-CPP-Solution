class Solution {
  public:
    long subarrayXor(vector<int> &arr, int k) {
        // code here
        unordered_map<int,int> m;
        int n=arr.size();
        m[0]=1;
        long ans=0;
        long xr=0;
        for(int i=0;i<n;i++)
        {
            xr=xr^arr[i];
            int x=xr^k;
            if(m.find(x)!=m.end())
            {
                ans+=m[x];
            }
            m[xr]++;
        }
        return ans;
    }
};