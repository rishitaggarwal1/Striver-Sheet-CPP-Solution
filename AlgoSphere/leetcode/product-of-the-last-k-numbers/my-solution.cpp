// Product of the Last K Numbers (LeetCode, Medium)
// https://leetcode.com/problems/product-of-the-last-k-numbers/
// My accepted solution · 2026-11-23

class ProductOfNumbers {
public:
    vector<long long> v;
    int lz = -1;
    ProductOfNumbers() {
        v.push_back(1);
    }
    
    void add(int num) {
        int n = v.size();
        if(num == 0)
        {
            lz = n+1;
            v.push_back(1);   
        }
        else
            v.push_back(v[n-1]*num);
    }
    
    int getProduct(int k) {
        int n = v.size();
        if(n-lz <k)    return 0;
        return v[n-1]/v[n-k-1];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */
