class Solution {
public:
    long long sumAndMultiply(int n) {
        long long sum = 0, x=0, ans =0;
        int t = n;
        while(n>0)
        {
            sum+=n%10;
            if(n%10!=0)
                x=x*10+n%10;
            n=n/10;
        }
        while(x>0)
        {
            ans=ans*10+x%10;
            x=x/10;
        }
        return ans*sum;
    }
};