// User function Template for C++

class Solution {
  public:
    string preToInfix(string pre_exp) {
        // Write your code here
        stack<string> st;
        int n=pre_exp.length();
        for(int i=n-1;i>=0;i--)
        {
            char c=pre_exp[i];
            if((c>='a' && c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9'))
            {
                string s="";
                s.push_back(c);
                st.push(s);
            }
            else 
            {
                string s1=st.top();
                st.pop();
                string s2=st.top();
                st.pop();
                s1="("+s1;
                s1.push_back(c);
                s1+=s2+")";
                st.push(s1);
            }
        }
        return st.top();
    }
};