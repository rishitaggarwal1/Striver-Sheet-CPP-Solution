class Solution {
public:
    double myPow(double x, int n) {
        if(n==0)
            return 1;
        long long N=n;
        if(n<0)
        {
            x=1/x;
            N=-N;
        }
        double temp = myPow(x,N/2);
        if(n%2==0)  return temp*temp;
        else
            return x*temp*temp;
    }
};