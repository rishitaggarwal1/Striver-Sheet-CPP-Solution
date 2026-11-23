/*
 * Problem   : Product of the Last K Numbers (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/product-of-the-last-k-numbers/
 * Pattern   : Prefix products reset at zero
 * Approach  : Optimal: Prefix products reset on zero
 * Complexity: Time O(1) per call (amortised for append), O(q) for q calls, Space O(n)
 *
 * Maintain prefix, starting as [1], where prefix[i] is the product of the
 * first i numbers since the most recent zero. On add(0), reset prefix to
 * [1]. Otherwise append prefix[last] * num. For getProduct(k): if k >=
 * prefix.length, the window reaches the zero (or the very start before any
 * zero, which k never exceeds), so return 0. Otherwise return prefix[last] /
 * prefix[last - k]. The division is exact and never divides by 0, because
 * all stored factors are non-zero. Each prefix is a contiguous product, so
 * it fits in 32 bits.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
public:
    vector<int> prefix; // prefix[i] = product of the first i numbers since the most recent zero

    ProductOfNumbers() {
        prefix = {1}; // empty product; gives a safe denominator for every division
    }
    
    void add(int num) {
        if (num == 0) {
            prefix = {1}; // any window crossing this zero is 0, so discard older prefixes
        } else {
            prefix.push_back(prefix.back() * num); // contiguous product, guaranteed to fit in 32 bits
        }
    }
    
    int getProduct(int k) {
        int m = prefix.size(); // m - 1 numbers have arrived since the last zero
        if (k >= m) return 0; // window reaches back to the last zero
        return prefix[m - 1] / prefix[m - 1 - k]; // exact: all factors are non-zero
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

int main() {
    vector<string> ops = {"ProductOfNumbers","add","add","add","add","add","getProduct","getProduct","getProduct","add","getProduct"};
    vector<int> args = {0,3,0,2,5,4,2,3,4,8,2};
    vector<string> expected = {"null","null","null","null","null","null","20","40","0","null","32"};
    ProductOfNumbers* obj = nullptr;
    vector<string> got;
    for (size_t i = 0; i < ops.size(); i++) {
        if (ops[i] == "ProductOfNumbers") { obj = new ProductOfNumbers(); got.push_back("null"); }
        else if (ops[i] == "add") { obj->add(args[i]); got.push_back("null"); }
        else { got.push_back(to_string(obj->getProduct(args[i]))); }
    }
    auto show = [](const vector<string>& v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); i++) { if (i) s += ","; s += v[i]; }
        return s + "]";
    };
    cout << "Output:   " << show(got) << "\n";
    cout << "Expected: " << show(expected) << "\n";
    cout << (got == expected ? "PASS" : "FAIL") << "\n";
    delete obj;
    return 0;
}
