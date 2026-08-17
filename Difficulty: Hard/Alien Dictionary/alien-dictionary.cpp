class Solution {
  public:
    string findOrder(vector<string> &words) {
        // code here
        unordered_set<char> s;
        int n = words.size();
        
        for(int i=0;i<n;i++)
        {
            s.insert(words[i].begin(), words[i].end());
        }
        int k = s.size();
        vector<vector<int>> adj(26);
        vector<int> inD(26,0);
        for(int i=0;i<n-1;i++)
        {
            int len = words[i].size();
            len = len>words[i+1].size()?words[i+1].size():len;
            for(int j=0;j<len;j++)
            {
                if(words[i][j]!=words[i+1][j])
                {
                    adj[words[i][j]-'a'].push_back(words[i+1][j]-'a');
                    inD[words[i+1][j]-'a']++;
                    break;
                }
            }
        }
        queue<int> q;
        for(int i=0;i<26;i++)
        {
            if(inD[i]==0 && s.find('a'+i)!=s.end())   q.push(i);
        }
        int p = 0;
        string str = "";
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            string aa(1,'a'+x);
            p++;
            str = str+aa;
            for(auto it:adj[x])
            {
                inD[it]--;
                if(inD[it]==0)
                {
                    q.push(it);
                }
            }
        }
        // cout<<str<<endl;
        return p==s.size()?str:"";
    }
};