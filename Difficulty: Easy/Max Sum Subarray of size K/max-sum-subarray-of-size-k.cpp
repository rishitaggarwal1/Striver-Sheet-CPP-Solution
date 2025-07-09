class Solution {
  public:
    int maximumSumSubarray(vector<int>& arr, int k) {
        // code here
        int i=0,n=arr.size();
        int mSum=0,ans;
        for(int i=0;i<k;i++)
            mSum+=arr[i];
        ans=mSum;
        i=k;
        while(i<n)
        {
            mSum=mSum+arr[i]-arr[i-k];
            if(ans<mSum)  ans=mSum;
            i++;
        }
        return ans;
    }
};