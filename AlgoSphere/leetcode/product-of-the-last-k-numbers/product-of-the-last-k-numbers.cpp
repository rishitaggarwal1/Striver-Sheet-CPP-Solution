/*
 * Problem   : Product of the Last K Numbers (LeetCode, Medium)
 * Link      : https://leetcode.com/problems/product-of-the-last-k-numbers/
 * Pattern   : Prefix products reset at zero
 * Approach  : Brute force: Store list, multiply last k
 * Complexity: Time O(1) per add, O(k) per getProduct, Space O(n)
 *
 * Append each num to a list. For getProduct(k), multiply the last k
 * elements. It is trivially correct because it computes exactly the
 * definition. You can stop early when you hit a 0.
 *
 * Notes made with AlgoSphere by Rishit Aggarwal (https://github.com/rishitaggarwal1)
 */

#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        // nums starts empty; nothing else to set up
    }
    
    void add(int num) {
        nums.push_back(num); // store every number so any suffix can be re-multiplied later
    }
    
    int getProduct(int k) {
        int p = 1;                       // multiplicative identity
        int n = (int)nums.size();
        for (int i = n - 1; i >= n - k; --i) { // walk the last k numbers, newest first
            if (nums[i] == 0) return 0;  // a zero anywhere makes the product 0, so stop early
            p *= nums[i];                // fits in 32 bits per the problem guarantee
        }
        return p;
    }

private:
    vector<int> nums; // the full stream in arrival order
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
    vector<string> out;
    for (size_t i = 0; i < ops.size(); ++i) {
        if (ops[i] == "ProductOfNumbers") { obj = new ProductOfNumbers(); out.push_back("null"); }
        else if (ops[i] == "add") { obj->add(args[i]); out.push_back("null"); }
        else { out.push_back(to_string(obj->getProduct(args[i]))); }
    }
    auto show = [](const vector<string>& v) {
        string s = "[";
        for (size_t i = 0; i < v.size(); ++i) { if (i) s += ","; s += v[i]; }
        return s + "]";
    };
    cout << "Output:   " << show(out) << "\n";
    cout << "Expected: " << show(expected) << "\n";
    delete obj;
    return 0;
}
