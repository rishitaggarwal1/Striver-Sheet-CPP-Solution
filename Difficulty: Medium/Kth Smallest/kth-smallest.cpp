// User function template for C++

class Solution {
  public:
    // arr : given array
    // k : find kth smallest element and return using this function
    int kthSmallest(vector<int> &arr, int k) {
        // code here
        priority_queue<int,vector<int>, greater<int>> p;
        for(int i=0;i<arr.size();i++)
            p.push(arr[i]);
        
        while(k-->1)
        {
            p.pop();
        }
        return p.top();
    }
};