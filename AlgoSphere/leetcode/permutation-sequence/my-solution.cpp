// Permutation Sequence (LeetCode, Hard)
// https://leetcode.com/problems/permutation-sequence/
// My accepted solution · 2026-11-26

class Solution {
public:
    string getPermutation(int n, int k) {
        string str="";
        vector<int> v;
        int fact = 1;
        for(int i=1;i<n;i++)
        {
            fact = fact*i;
            v.push_back(i);
        }
        v.push_back(n);
        k--;
        while(true)
        {
            str+=to_string(v[k/fact]);
            v.erase(v.begin()+k/fact);
            if(v.size()==0) break;
            k=k%fact;
            fact=fact/v.size();
        }
        return str;
    }
};
