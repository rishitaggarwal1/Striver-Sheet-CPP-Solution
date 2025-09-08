class Solution {
  public:
    vector<int> twoOddNum(vector<int>& arr) {
        // code here
        int x=0;
        for(int i=0;i<arr.size();i++)
            x=x^arr[i];
        x=x&~(x-1);
        int f=0,s=0;
        for(int i=0;i<arr.size();i++)
        {
            if(x&arr[i])    f=f^arr[i];
            else
                s=s^arr[i];
        }
        if(f>s)
            return {f,s};
        else
            return {s,f};
    }
};