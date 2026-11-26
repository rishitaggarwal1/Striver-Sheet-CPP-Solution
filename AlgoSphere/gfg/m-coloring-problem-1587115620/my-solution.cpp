// M-Coloring Problem (GeeksforGeeks, Medium)
// https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1
// My accepted solution · 2026-11-26 · runtime 0.81 s

class Solution {
  public:
    bool safe(int i, vector<vector<int>> &adj, vector<int>& col, int c)
    {
        for(int k = 0; k<adj[i].size();k++)
        {
            if(col[adj[i][k]]==c)    
            {
                return false;
            }
        }
        return true;
    }
    bool func(int i, vector<vector<int>> &adj, vector<int>& col, int m)
    {
        if(i==adj.size())   return true;
        for(int j=1;j<=m;j++)
        {
            if(safe(i,adj,col,j))
            {
                col[i] = j;
                if(func(i+1,adj,col,m))
                    return true;
                col[i] = -1;
            }
        }
        return false;
    }
    bool graphColoring(vector<vector<int>> &adj, int m) {
        // code here
        int n = adj.size();
        vector<int> col(n,-1);
        return func(0,adj,col,m);
    }
};
