class Solution {
public:
    bool rotateString(string s, string goal) {
        string ss=s+s;
        return ss.find(goal)!=string::npos && s.length()==goal.length();
    }
};