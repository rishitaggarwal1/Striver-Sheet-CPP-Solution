class Solution {
public:
    int larRec(vector<int> &v)
    {
        int n = v.size();
        int ans = INT_MIN;
        stack<int> st;
        int curr;
        for(int i=0;i<=n;i++)
        {
            if(i==n)
                curr = 0;
            else
                curr = v[i];
            while(!st.empty() && v[st.top()]>=curr)
            {
                int j = st.top();
                st.pop();
                int w = st.empty()?i:i-st.top()-1;
                ans = max(ans, v[j]*w);
            }
            st.push(i);
        }
        return ans;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<int>> pref(m,vector<int>(n,0));
        for(int i =0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(matrix[j][i]=='0' || j==0)
                {
                    pref[j][i]=(matrix[j][i]-'0');
                }
                else
                {
                    pref[j][i]=pref[j-1][i] + (matrix[j][i]-'0');
                }
            }
        }
        

        int ans = INT_MIN;
        for(int i=0;i<m;i++)
        {
            int x = larRec(pref[i]);
            ans = max(ans,x);
        }
        return ans;
    }
};