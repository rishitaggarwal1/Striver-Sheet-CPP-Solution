class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int> > ans;
        sort(intervals.begin(),intervals.end());
        int x=intervals[0][0], y=intervals[0][1];
        for(int i=1;i<intervals.size();i++)
        {
            if(intervals[i][0]>=x && intervals[i][0]<=y)
            {
                y=max(y,intervals[i][1]);
            }
            else
            {
                ans.push_back({x,y});
                x=intervals[i][0];
                y=intervals[i][1];
            }
        }
        ans.push_back({x,y});
        return ans;
    }
};