class Solution {
  public:
    string encode(vector<string>& s) {
        // code here
        string str="";
        for(int i=0;i<s.size();i++)
        {
            int x=s[i].length();
            str+=to_string(x)+"#"+s[i];
        }
        return str;
    }

    vector<string> decode(string& s) {
        
        // code here
        vector<string> ans;
        int k=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='#')
            {
                if(k==0)
                {
                    ans.push_back("");
                }
                else
                {
                    string str = s.substr(i+1,k);
                    ans.push_back(str);
                    i+=k;
                }
                k=0;
            }
            else
            {
                int a=s[i]-'0';
                k=10*k+a;
            }
        }
        return ans;
    }
};