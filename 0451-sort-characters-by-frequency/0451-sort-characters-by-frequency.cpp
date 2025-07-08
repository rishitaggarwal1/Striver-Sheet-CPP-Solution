class Solution {
public:
    string frequencySort(string s) {  
        vector<int> freq(128,0);
        for(int i=0;i<s.length();i++)
            freq[s[i]]++;
        auto comp = [&](char a, char b){
            if(freq[a]==freq[b])    return a<b;
            return freq[a]>freq[b];
        };
        sort(s.begin(),s.end(),comp);
        return s;
    }
};