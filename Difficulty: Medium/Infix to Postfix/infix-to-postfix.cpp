class Solution {
  public:
  int prec(char c) {
      if (c == '^')
        return 3;
      else if (c == '/' || c == '*')
        return 2;
      else if (c == '+' || c == '-')
        return 1;
      else
        return -1;
    }
    string infixToPostfix(string& s) {
        // code here
        string ans="";
        stack<char> st;
        for(int i=0;i<s.length();i++)
        {
            if((s[i]>='a' && s[i]<='z')||(s[i]>='A' && s[i]<='Z')||(s[i]>='0' && s[i]<='9'))
                ans+=s[i];
            else if(s[i]==')')
            {
                while(!st.empty() && st.top()!='(')
                {
                    ans+=st.top();
                    st.pop();
                }
                st.pop();
            }
            else if(s[i]=='(' || st.empty() || prec(st.top())<prec(s[i]))
                st.push(s[i]);
            else
            {
                while(!st.empty() && prec(st.top())>=prec(s[i]))
                {
                    ans+=st.top();
                    st.pop();
                }
                st.push(s[i]);
            }
        }
        while(!st.empty())
        {
            ans+=st.top();
            st.pop();
        }
        return ans;
    }
};
