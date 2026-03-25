class Solution {
public:
    string reverseWords(string s) {
        string st="",ans="";
        int n = s.length();
        stringstream ss(s);
        while(ss>>st)
        {
            ans= st+ " "+ ans;
        }
        n=ans.length();
        return ans.substr(0,n-1);
    }
};