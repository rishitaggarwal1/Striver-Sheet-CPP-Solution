// User function Template for C++

class Solution {
  public:

    vector<int> replaceWithRank(vector<int> &arr, int N) 
    {
        priority_queue<int,vector<int>, greater<int>> pq;
        
        for(int i=0;i<N;i++)
            pq.push(arr[i]);
        
        map<int,int> m;
        int r=1;
        for(int i=0;i<N;i++)
        {
            int x=pq.top();
            if(m.find(x)==m.end())
            {
                m[x]=r;
                r++;
            }
            pq.pop();
        }
        vector<int> ans(N);
        for(int i=0;i<N;i++)
        {
            ans[i]=m[arr[i]];
        }
        return ans;
    }
};
