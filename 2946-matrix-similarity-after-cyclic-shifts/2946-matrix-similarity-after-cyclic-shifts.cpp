class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k = k%n;
        for(int i=0;i<m;i++)
        {
            vector<int> v = mat[i];
            if(i%2==0)
            {
                reverse(mat[i].begin(),mat[i].begin()+k);
                reverse(mat[i].begin()+k,mat[i].end());
                reverse(mat[i].begin(),mat[i].end());
            }
            else
            {
                int d = n-k;
                reverse(mat[i].begin(),mat[i].begin()+d);
                reverse(mat[i].begin()+d,mat[i].end());
                reverse(mat[i].begin(),mat[i].end());
            }
            if(v!=mat[i]) return false;  
        }
        return true;
    }
};