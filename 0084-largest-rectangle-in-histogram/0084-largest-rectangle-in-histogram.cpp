class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        stack<pair<int,int>> st;
        int ans = 0;
        for(int i=0;i<n;i++)
        {
            if(st.empty())
                st.push({i,heights[i]});
            else if(st.top().second>heights[i])
            {
                int lastid;
                while(!st.empty() && st.top().second > heights[i])
                {
                    int x = (i-st.top().first)*(st.top().second);
                    lastid = st.top().first;
                    if(x>ans)   ans =x;
                    st.pop();
                }
                st.push({lastid,heights[i]});
            }
            else
            {
                st.push({i,heights[i]});
            }
        }
        while(!st.empty())
        {
            int x = (n-st.top().first)*(st.top().second);
            if(x>ans)   ans = x;
            st.pop();
        }
        return ans;
    }
};