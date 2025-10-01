class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int x=numBottles/numExchange;
        int y=numBottles%numExchange;
        int ans=numBottles;
        while(x>0)
        {
            ans+=x;
            numBottles= x+y;
            x=numBottles/numExchange;
            y=numBottles%numExchange;
        }
        return ans;
    }
};