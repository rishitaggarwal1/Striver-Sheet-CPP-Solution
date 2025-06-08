// User function template for C++
class Solution {
  public:
    vector<int> findSubarray(vector<int>& arr) {
        // code here
        int maxS=INT_MIN, maxT=0,start=0,ansS=0,ansE=0;
        for(int i=0;i<arr.size();i++)
        {
            if(arr[i]<0)
            {
                start=0;
                maxT=0;
            }
            if(maxT==0)
                start=i;
            maxT+=arr[i];
            if(maxS<=maxT)
            {
                maxS=maxT;
                ansS = start;
                ansE= i;
            }
            if(maxT<=0)
            {
                maxT=0;
            }
        }
        if(maxS<=0)
            return {-1};
        vector<int> v;
        for(int i=ansS;i<=ansE;i++)
        {
            v.push_back(arr[i]);
        }
        return v;
    }
};