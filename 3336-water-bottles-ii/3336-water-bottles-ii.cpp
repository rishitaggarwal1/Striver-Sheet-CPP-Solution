class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {
        int bd = numBottles;
        int eb = numBottles;
        int fb=0;
        while(eb>=numExchange)
        {
            fb++;
            bd++;
            eb-=numExchange;
            numExchange++;
            if(eb<numExchange)
            {
                eb+=fb;
                fb=0;
            }
        }
        return bd;
    }
};