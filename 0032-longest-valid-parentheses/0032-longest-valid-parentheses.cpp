class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        int ans = INT_MIN;
        stack<int> st;
        st.push(-1);
        for(int i=0;i<n;i++)
        {
            if(s[i]=='(')
            {
                st.push(i);
            }
            else 
            {
                st.pop();
                if(st.empty())
                {
                    st.push(i);
                }
                ans = max(ans, i - st.top());
            }
        }
        if(ans==INT_MIN)    return 0;
        return ans;
    }
};