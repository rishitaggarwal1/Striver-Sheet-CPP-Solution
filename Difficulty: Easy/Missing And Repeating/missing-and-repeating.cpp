class Solution {
  public:
    vector<int> findTwoElement(vector<int>& arr) {
        // code here
        long n=arr.size();
        long long sum=n*(n+1)/2;
        long long sum2=(n*(n+1)*(2*n+1))/6;
        long long s=0,s2=0;
        for(int i=0;i<n;i++)
        {
            s+=arr[i];
            s2+=((long long)arr[i]* (long long) arr[i]);
        }
        sum=sum-s;
        sum2=sum2-s2;
        sum2=sum2/sum;
        long long miss=(sum+sum2)/2;
        int rep = miss - sum;
        return {rep,(int)miss};
    }
};