class Solution {
public:
    long long sumAndMultiply(int n) {
        long long sum = 0, x=0, pw =1;
        int t = n;
        while(n>0)
        {
            sum+=n%10;
            if(n%10!=0)
            {
                x+=pw*(n%10);
                pw*=10;
            }
            n=n/10;
        }
        return x*sum;
    }
};