class Solution {
public:
    vector<string> str;
    void stringGen(string s, int x, int n)
    {
        if(s.length()>n)    return;
        if(s.length()==n)
        {
            str.push_back(s);
            return;
        }
        else
        {
            if(s[x-1]!='a')
            {        
                stringGen(s+"a",x+1,n);
            }
            if(s[x-1]!='b')
            {
                stringGen(s+"b",x+1,n);
            }
            if(s[x-1]!='c')
            {
                stringGen(s+"c",x+1,n);
            }
        }
    }
    string getHappyString(int n, int k) {
        stringGen("a",1,n);
        stringGen("b",1,n);
        stringGen("c",1,n);
        sort(str.begin(),str.end());
        if(k>str.size())    return "";
        return str[k-1];
    }
};