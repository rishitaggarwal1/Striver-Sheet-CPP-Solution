class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        queue<int> q;
        vector<int> vis(n,0);
        vector<int> adj[n], indeg(n,0);
        for(int i=0;i<invocations.size();i++)
        {
            int u=invocations[i][0];
            int v=invocations[i][1];
            indeg[v]++;
            adj[u].push_back(v);
        }
        q.push(k);
        vis[k]=1;
        while(!q.empty())
        {
            int x = q.front();
            q.pop();
            for(auto it:adj[x])
            {
                indeg[it]--;
                if(vis[it]==0)
                {
                    q.push(it);
                    vis[it]=1;
                }
            }
        }
        vector<int> ans;
        bool z=false;
        for(int i=0;i<n;i++)
        {
            if(vis[i]==1 && indeg[i]>0)
            {
                z=true;
                break;
            }
            else if(vis[i]==0)
            {
                ans.push_back(i);
            }
        }
        if(z)
        {
            vector<int> allNodes(n);
            iota(allNodes.begin(), allNodes.end(), 0);
            return allNodes;
        }
        return ans;
    }
};