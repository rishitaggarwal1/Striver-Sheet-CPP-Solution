class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if(k%2==0 || k%5==0)  return -1;
        unordered_set<int> s;
        long long n =0;
        int ans = 0;
        do
        {
            n = (n*10 + 1)%k;
            ans++;
            if(s.find(n)!=s.end())  return -1;
            else    s.insert(n);
        }while(n!=0);
        return ans;
    }
};