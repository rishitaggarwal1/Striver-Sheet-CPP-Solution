class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int ln=landStartTime.size();
        int wn = waterStartTime.size();
        int ln_min = INT_MAX;
        for(int i=0;i<ln;i++)
        {
            int x = landStartTime[i] + landDuration[i];
            if(x<ln_min)    ln_min = x;   
        }
        int wn_min = INT_MAX;
        for(int i=0;i<wn;i++)
        {
            int x = waterStartTime[i] + waterDuration[i];
            if(x<wn_min)    wn_min = x;   
        }
        int ans = INT_MAX;
        for(int i=0;i<wn;i++)
        {
            if(waterStartTime[i]<=ln_min)
            {
                int x = ln_min + waterDuration[i];
                if(x<ans)   ans=x;
            }
            else
            {
                int x = waterStartTime[i] + waterDuration[i];
                if(x<ans)   ans=x;
            }
        }
        for(int i=0;i<ln;i++)
        {
            if(landStartTime[i]<=wn_min)
            {
                int x = wn_min + landDuration[i];
                if(x<ans)   ans=x;
            }
            else
            {
                int x = landStartTime[i] + landDuration[i];
                if(x<ans)   ans=x;
            }
        }
        return ans;
    }
};