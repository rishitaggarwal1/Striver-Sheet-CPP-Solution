// User function Template for C++

class Solution {
  public:
    int find(int n)
    {
        if(n%4==0)
            return n;
        else if (n%4==1)    return 1;
        else if(n%4==2) return n+1;
        else
            return 0;
    }
    int findXOR(int l, int r) {
        // complete the function here
        int a = find(l-1);
        int b = find(r);
        return a^b;
    }
};