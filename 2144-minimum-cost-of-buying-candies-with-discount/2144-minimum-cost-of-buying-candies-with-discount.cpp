class Solution {
public:
    int minimumCost(vector<int>& cost) {
        sort(cost.begin(),cost.end(),greater<>());
        int sum = 0;
        for(int i=0;i<cost.size();i+=2)
        {
            sum+=cost[i];
            if(i+1<cost.size())
            {
                sum+=cost[i+1];
                i++;
            }
        }
        return sum;
    }
};