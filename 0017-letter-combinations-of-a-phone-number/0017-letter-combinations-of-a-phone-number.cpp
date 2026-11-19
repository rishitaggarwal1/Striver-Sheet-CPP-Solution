class Solution {
public:
    vector<string> dig = {"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> ans;
    void func(int i, string curr, string digits)
    {
        int n = digits.length();
        if(i==n)
        {
            ans.push_back(curr);
            return;
        }
        int x = digits[i]-'0';
        int nn = dig[x-2].length();
        for(int j=0;j<nn;j++)
        {
            curr+=dig[x-2][j];
            func(i+1,curr,digits);
            curr.pop_back();
        }
    }
    vector<string> letterCombinations(string digits) {
        func(0,"",digits);
        return ans;
    }
};