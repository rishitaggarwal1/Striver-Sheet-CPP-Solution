class Solution {
  public:
    bool checkKthBit(int n, int k) {
        //  code here
        int x=1;
        x=x<<k;
        if(n&x) return true;
        return false;
    }
};