class Solution {
public:
    string getHash(string str)
    {
        string hash ="";
        vector<int> freq (26,0);
        for(char ch:str)
        {
            freq[ch-'a']++;
        }
        for(int i=0;i<26;i++)
        {
            hash+=(to_string(freq[i]));
            hash+='$';
        }
        return hash;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        int n = strs.size();
        unordered_map<string,int> m;
        vector<vector<string> > ans;
        int k=0;
        for(int i=0;i<n;i++)
        {
            //string s = strs[i];
            //sort(s.begin(),s.end());
            string s = getHash(strs[i]);
            if(m.find(s)!=m.end())
            {
                int x = m[s];
                ans[x].push_back(strs[i]);
            }
            else
            {
                m[s]=k++;
                ans.push_back({strs[i]});
            }
        }
        return ans;
    }
};