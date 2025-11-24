class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int,int>> v;
        int n = speed.size();
        for(int i=0;i<n;i++)
        {
            v.push_back({position[i],speed[i]});
        }
        sort(v.begin(),v.end());
        stack<float> s;

        for(int i=n-1;i>=0;i--)
        {
            float t = (float)(target - v[i].first)/(float)v[i].second;
            if(s.empty())
            {
                s.push(t);
            }
            else if(t>s.top())
            {
                s.push(t);
            }
        }
        return s.size();
    }
};