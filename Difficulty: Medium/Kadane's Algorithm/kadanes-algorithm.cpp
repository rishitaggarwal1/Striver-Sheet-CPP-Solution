//{ Driver Code Starts
// Initial Template for C++
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
    
    // Your code here
    int n=arr.size();
    int so_far=0,max_sum=INT_MIN;
    for(int i=0;i<n;i++)
    {
        so_far+=arr[i];
        if(so_far>max_sum)
            max_sum=so_far;
        if(so_far<0)
            so_far=0;
    }
    return max_sum;
        
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    cin.ignore(); // To discard any leftover newline characters
    while (t--)   // while testcases exist
    {
        vector<int> arr;
        string input;
        getline(cin, input); // Read the entire line for the array elements
        stringstream ss(input);
        int number;
        while (ss >> number) {
            arr.push_back(number);
        }

        Solution ob;
        cout << ob.maxSubarraySum(arr) << endl << "~" << endl;
    }
}
// } Driver Code Ends