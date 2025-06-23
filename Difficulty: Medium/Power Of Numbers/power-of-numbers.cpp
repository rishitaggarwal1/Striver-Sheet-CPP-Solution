class Solution {
  public:
    int reverseExponentiation(int n) {
        // code here
        int num=n;
        int e=0;
        while(num>0)
        {
            int t=num%10;
            e=e*10+t;
            num=num/10;
        }
        int ans=1;
        while(e>0)
        {
            if(e%2==0)
            {
                n=n*n;
                e=e/2;
            }
            else
            {
                e--;
                ans=ans*n;
            }
        }
        return ans;
    }
};