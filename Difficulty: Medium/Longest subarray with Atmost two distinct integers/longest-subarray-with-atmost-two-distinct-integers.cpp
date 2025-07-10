class Solution {
  public:
    int totalElements(vector<int> &arr) {
        // code here
        int n=arr.size();
        int i=0,j=0,c=0;
        int ans=0;
        unordered_map<int,int> m;
        while(j<n)
        {
            m[arr[j]]++;
            c++;
            while(m.size()>2)
            {
                m[arr[i]]--;
                c--;

                if(m[arr[i]]==0)
                    m.erase(arr[i]);
                i++;
            }
            j++;
            ans=max(ans,c);
        }
        return ans;
    }
};