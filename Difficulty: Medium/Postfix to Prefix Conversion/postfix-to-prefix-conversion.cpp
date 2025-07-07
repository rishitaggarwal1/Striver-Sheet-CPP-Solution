// User function Template for C++

class Solution {
  public:
    string postToPre(string post_exp) {
        // Write your code here
        stack<string> st;
        int n=post_exp.length();
        for(int i=0;i<n;i++)
        {
            char c=post_exp[i];
            if((c>='a' && c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9'))
            {
                string s="";
                s.push_back(c);
                st.push(s);
            }
            else 
            {
                string s="";
                string s1=st.top();
                st.pop();
                string s2=st.top();
                st.pop();
                s.push_back(c);
                s+=(s2+s1);
                st.push(s);
            }
        }
        return st.top();
    }
};