class Solution {
public:
    string reverseWords(string s) {
        string st="",ans="";
        for(int i=0;i<s.length();i++)
        {
            if(s[i]!=' ')
            {
                st+=s[i];
            }
            else if(st!="")
            {
                cout<<"Test\t"<<st<<endl;
                if(ans!="")
                    ans=st+ " " + ans;
                else ans=st+ans;
                st="";
            }
        }
        if(st=="")
            return ans;
        else if(ans=="")
            return st;
        return st+ " " +ans;
    }
};