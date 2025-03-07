//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        // code here
        map<int,int> m;
        int n=arr.size(), maxLen=0;
        int sum=0;
        for(int i=0;i<n;i++)
        {
            sum+=arr[i];
            if(sum==k)
            {
                if(i+1>maxLen)
                    maxLen=i+1;
            }
            else
            {
                int x=sum-k;
                if(m.find(x)!=m.end() && (i-m[x]+1)>maxLen)
                {
                    maxLen=i-m[x];
                }
            }
            if(m.find(sum)==m.end())
                m[sum]=i;
        }
        return maxLen;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    cin.ignore(); // Ignore newline character after t

    while (t--) {
        vector<int> arr;
        int k;
        string inputLine;

        getline(cin, inputLine); // Read the array input as a line
        stringstream ss(inputLine);
        int value;
        while (ss >> value) {
            arr.push_back(value);
        }

        cin >> k;
        cin.ignore(); // Ignore newline character after k input

        Solution solution;
        cout << solution.longestSubarray(arr, k) << "\n";
        cout << "~\n";
    }

    return 0;
}

// } Driver Code Ends