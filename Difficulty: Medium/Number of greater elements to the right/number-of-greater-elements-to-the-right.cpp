// User function Template for C++

class Solution {
  public:

    vector<int> count_NGE(int n, vector<int> &arr, int queries, vector<int> &indices) {
        // write your code here
        vector<int> ans;
        for(int i=0;i<queries;i++)
        {
            int a=0;
            int x=indices[i];
            for(int j=x+1;j<n;j++)
            {
                if(arr[j]>arr[x])
                    a++;
            }
            ans.push_back(a);
        }
        return ans;
    }
};