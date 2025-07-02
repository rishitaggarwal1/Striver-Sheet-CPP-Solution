class Solution {
public:
    bool isValid(string s) {
        stack<char> ss;
        bool valid=true;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='('||s[i]=='['||s[i]=='{')
            {
                ss.push(s[i]);
            }
            else
            {
                if(ss.empty())
                    return false;
                char x=ss.top();
                if((s[i]==')' && x=='(') || (s[i]=='}' && x=='{') || (s[i]==']' && x=='['))
                {
                    ss.pop();
                }
                else
                {
                    valid=false;
                    break;
                }
            }
        }
        if(!ss.empty())
            return false;
        return valid;
    }
};