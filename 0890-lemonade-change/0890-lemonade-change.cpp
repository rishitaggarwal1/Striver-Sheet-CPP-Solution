class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int _5=0,_10=0,x=0;
        while(x<bills.size())
        {
            if(bills[x]==5)
                _5++;
            else if(bills[x]==10)
            {
                if(_5==0)
                    return false;
                _5--;
                _10++;
            }
            else
            {
                if(_5>=3 || (_10>=1 && _5>=1))
                {
                    if(_10>=1)
                    {
                        _10--;
                        _5--;
                    }
                    else
                    {
                        _5-=3;
                    }
                }
                else
                    return false;
            }
            x++;
        }
        return true;
    }
};