class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n=fruits.size();
        int i=0,j=0,c=0;
        int ans=0;
        unordered_map<int,int> m;
        while(j<n)
        {
            m[fruits[j]]++;
            c++;
            while(m.size()>2)
            {
                m[fruits[i]]--;
                c--;

                if(m[fruits[i]]==0)
                    m.erase(fruits[i]);
                i++;
            }
            j++;
            ans=max(ans,c);
        }
        return ans;
    }
};