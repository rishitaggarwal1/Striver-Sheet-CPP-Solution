class Solution {
public:
    int mod=1e9+7;
    long long pow(int x,long long y)
    {
        if(y==0)    return 1;
        long long temp = pow(x,y/2);
        if(y%2==1)  return (long long)(x*temp*temp)%mod;
        else return (long long)(temp*temp)%mod;
    }
    int countGoodNumbers(long long n) {
        long long a=(n+1)/2, b=n/2;
        long long ans=(pow(5,a)%mod * pow(4,b)%mod)%mod;
        return (int)ans;
    }
};