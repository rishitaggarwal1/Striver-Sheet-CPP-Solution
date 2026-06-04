class Solution {
public:
    int totalWaviness(int num1, int num2) {
        int i = num1;   
        int v=0, p=0;
        while(i<=num2)
        {
            string t = to_string(i);
            for(int j=1;j<t.length()-1;j++)
            {
                if((t[j] > t[j-1]) && t[j] > t[j+1])  p++;
                if((t[j] < t[j-1]) && t[j] < t[j+1])  v++;
            }
            i++;
        }
        return p+v;
    }
};