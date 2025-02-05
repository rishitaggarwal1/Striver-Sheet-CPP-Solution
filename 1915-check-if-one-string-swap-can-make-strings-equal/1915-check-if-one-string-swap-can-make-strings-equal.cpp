class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int x=0;
        int a1=-1,a2=-1;
        for(int i=0;i<s1.length();i++)
        {
            if(s1[i]!=s2[i])
            {
                x++;
                if(a1==-1)
                    a1=i;
                else
                    a2=i;
            }
            if(x>2)
                return false;
        }
        if(a1!=-1 && a2!=-1)
        {
            char ch=s2[a1];
            s2[a1]=s2[a2];
            s2[a2]=ch;
        }
        if(s1==s2 && x==2 || x==0)
            return true;
        return false;
    }
};