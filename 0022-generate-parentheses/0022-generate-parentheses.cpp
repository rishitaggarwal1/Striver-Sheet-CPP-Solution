class Solution {
public:
    vector<string> ans;
    void gen(string s, int x, int y, int si)
    {
        if(s.length()==2*si)
        {
            ans.push_back(s);
            return;
        }
        if(x<si)
        {
            gen(s+"(",x+1,y,si);
        }
        if(x>y && y<si)
        {
            gen(s+")",x,y+1,si);
        }
        return;
    }
    vector<string> generateParenthesis(int n) {
        gen("",0,0,n);
        return ans;
    }
};