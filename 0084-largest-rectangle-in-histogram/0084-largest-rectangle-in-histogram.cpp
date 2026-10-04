class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> ns(n,n), ps(n,-1);
        stack<int> st,st1;
        for(int i=0;i<n;i++)
        {
            while(!st.empty() && heights[st.top()]>=heights[i])
            {
                st.pop();
            }
            if(!st.empty())
                ps[i] = st.top();
            st.push(i);
        }
        for(int i=n-1;i>=0;i--)
        {
            while(!st1.empty() && heights[st1.top()]>=heights[i])
            {
                st1.pop();
            }
            if(!st1.empty())
                ns[i] = st1.top();
            st1.push(i);
        }
        int ans = INT_MIN;
        for(int i=0;i<n;i++)
        {
            int x = i-ps[i];
            int y = ns[i]-i-1;
            int z = (x+y)*heights[i];
            ans = max(ans,z);
        }
        return ans;
    }
};