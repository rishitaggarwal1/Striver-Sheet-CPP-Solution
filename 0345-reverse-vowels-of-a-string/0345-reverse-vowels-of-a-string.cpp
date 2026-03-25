class Solution {
public:
    bool check(char ch)
    {
        if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u' || ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U')
            {
                return true;   
            }
            return false;
    }
    string reverseVowels(string s) {
        int l=0, r=s.length();

        while(l<r)
        {
            if(check(s[l]))
            {
                while(!check(s[r--]));
                swap(s[l],s[r+1]);
            }
            l++;
        }
        return s;
    }
};