// Stone Removal Game (LeetCode, Easy)
// https://leetcode.com/problems/stone-removal-game/
// My accepted solution · 2026-11-26

class Solution {
public:
    bool canAliceWin(int n) {
        int x = 10;
        while(n>=x)
        {
            n = n-x;
            x--;
            if(x<=n)
                n = n-x;
            else
                return true;
            x--;
        }
        return false;
    }
};
