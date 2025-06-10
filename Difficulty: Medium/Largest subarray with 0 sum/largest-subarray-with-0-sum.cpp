/*You are required to complete this function*/

class Solution {
  public:
    int maxLen(vector<int>& arr) {
        // code here
        int n=arr.size();
        unordered_map<int,int> m;
        int ans=0;
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=arr[i];
            if(sum==0 && ans<(i+1))
                ans=i+1;
            else if(m.find(sum)!=m.end() && ans<(i-m[sum]))
                ans=(i-m[sum]);
            else if(m.find(sum)==m.end())
                m[sum]=i;
        }
        return ans;
    }
};