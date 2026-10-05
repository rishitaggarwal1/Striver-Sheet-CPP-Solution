class Solution {
public:
    int MOD = 1e9+7;
    int sumSubarrayMins(vector<int>& arr) {
        stack<pair<int,int>> st, st2;
        int n = arr.size();
        vector<int> ps(n), ns(n);
        for(int i=0;i<n;i++)
        {
            while(!st.empty() && st.top().first>=arr[i])
                st.pop();
            if(st.empty())
            {
                ps[i]=-1;
            }
            else
            {
                ps[i]=st.top().second;
            }
            st.push({arr[i],i});
        }
        for(int i=n-1;i>=0;i--)
        {
            while(!st2.empty() && st2.top().first>arr[i])
                st2.pop();
            if(st2.empty())
            {
                ns[i]=n;
            }
            else
            {
                ns[i]=st2.top().second;
            }
            st2.push({arr[i],i});
        }
        long long ans = 0;
        for(int i=0;i<n;i++)
        {
            ans+=((1LL*(i-ps[i])*(ns[i]-i)*arr[i])%MOD);
            ans=ans%MOD;
        }
        return ans;
    }
};