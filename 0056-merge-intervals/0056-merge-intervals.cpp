class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(),intervals.end());
        vector<vector<int>> v;
        int a = intervals[0][0];
        int b = intervals[0][1];
        for(int i=1;i<n;i++)
        {
            if(intervals[i][0]>=a && intervals[i][0]<=b)
            {
                b=max(b,intervals[i][1]);
            }
            else
            {
                v.push_back({a,b});
                a=intervals[i][0];
                b=intervals[i][1];
            }
        }
        v.push_back({a,b});
        return v;
    }
};