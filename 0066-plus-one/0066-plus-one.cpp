class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int c=0;
        for(int i=digits.size()-1;i>=0;i--)
        {
            digits[i]=digits[i]+1;
            digits[i]>=10 ? c=1:c=0;
            digits[i]%=10;
            if(c==0) break;
        }
        if(c==1)
            digits.insert(digits.begin(),1);
            return digits;
    }
};