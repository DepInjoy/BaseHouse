class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> hash4s;
        unordered_map<char, int> hash4t;
        for(int i = 0;i < s.size();i++){
            hash4s[s[i]]++;
        }  
        for(int i = 0;i < t.size();i++){
            hash4t[t[i]]++;
        }
        return hash4s == hash4t;
    }
};