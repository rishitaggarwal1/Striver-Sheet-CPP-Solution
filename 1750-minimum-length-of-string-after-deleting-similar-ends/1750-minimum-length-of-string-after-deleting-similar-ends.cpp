class Solution {
public:
    int minimumLength(string s) {
        int n = s.length();
        int i =0, j=n-1;
        while(i<j && s[i]==s[j])
        {
            while(i<n && s[i]==s[i+1]) i++;
            while(j>0 && s[j]==s[j-1]) j--;
            i++;
            j--;
        }
        if(j<i) return 0;    
        return (j-i+1);
    }
};