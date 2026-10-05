class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        int n = asteroids.size();
        for(int i=0;i<n;i++)
        {
            if(st.empty())
            {
                st.push(asteroids[i]);
            }
            else
            {
                if(asteroids[i]<0 && st.top()>0)
                {
                    int x;
                    while(!st.empty() && st.top()>0)
                    {
                        x=st.top();
                        if(x<abs(asteroids[i]))
                            st.pop();
                        else if(x==abs(asteroids[i]))
                        {
                            st.pop();
                            break;
                        }
                        else
                            break;
                    }
                    if(x<abs(asteroids[i]))
                        st.push(asteroids[i]);
                }
                else
                    st.push(asteroids[i]);
            }
        }
        vector<int> ans;
        while(!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};