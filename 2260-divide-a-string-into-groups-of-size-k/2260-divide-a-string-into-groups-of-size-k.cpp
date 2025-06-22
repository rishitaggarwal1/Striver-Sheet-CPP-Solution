class Solution {
public:
    vector<string> divideString(string s, int k, char fill) {
        vector<string> v;
        int n=s.length(),i=0;
        for(;i<n;i+=k)
        {
            int x=i+k<n?k:n-i;
            string t=s.substr(i,x);
            v.push_back(t);
        }
        if(i<n)
        {
            string t=s.substr(i,n-i);
            v.push_back(t);
        }
        if(n%k!=0)
        {
            for(int i=v[v.size()-1].length();i<k;i++)
            {
                v[v.size()-1]+=fill;
            }
        }
        return v;
    }
};