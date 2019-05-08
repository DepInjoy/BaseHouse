class Solution {
public:
    bool isValid(string s) {
        std::stack<char> containter;
        for(int i = 0;i < s.size();i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
                containter.push(s[i]);
            }
            
            if(s[i] == ')' || s[i] == ']' || s[i] == '}'){
                if(containter.empty()) return false;
                if(s[i] == ')'){
                    if(containter.top() == '(') containter.pop();
                    else return false;
                }
                    
                if(s[i] == ']'){
                    if(containter.top() == '[') containter.pop();
                    else return false;
                }
                
                if(s[i] == '}'){
                    if(containter.top() == '{') containter.pop();
                    else return false;
                }
            }
        }
        return containter.empty();
    }
};