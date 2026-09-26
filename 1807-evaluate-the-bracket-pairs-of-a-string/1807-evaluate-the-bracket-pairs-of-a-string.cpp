class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string,string> m;
        for(int i=0;i<knowledge.size();i++)
        {
            m[knowledge[i][0]]=knowledge[i][1];
        }
        string ans="";
        bool x= true;
        int y = 0;
        while(y<s.length() && s.find("(",y)!=string::npos)
        {
            int a = s.find("(",y);
            ans+=(s.substr(y,a-y));
            int b = s.find(")",y);
            string ss = s.substr(a+1,b-a-1);
            if(m.find(ss)!=m.end())
            {
                ans+=m[ss];
            }
            else
            {
                ans+="?";
            }
            y=b+1;
        }
        ans+=s.substr(y,s.length()-y);
        return ans;
    }
};