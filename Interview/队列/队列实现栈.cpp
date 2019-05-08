class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        if(!_queue0.empty()) _queue0.push(x);
        if(!_queue1.empty()) _queue1.push(x);
        if(_queue0.empty() && _queue0.empty()) _queue0.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if(_queue0.empty() && _queue1.empty()) return -1;
        
        int res = -1;
        if(!_queue0.empty()){
            int count = _queue0.size();
            while(_queue0.size() > 1){
                _queue1.push(_queue0.front());
                _queue0.pop();
            }
            res = _queue0.front();
            _queue0.pop();
            return res;
        }
        
        if(!_queue1.empty()){
            int count = _queue1.size();
            while(_queue1.size() > 1){
                _queue0.push(_queue1.front());
                _queue1.pop();
            }
            res = _queue1.front();
            _queue1.pop();
        }    
        return res;
    }
    
    /** Get the top element. */
    int top() {
                if(_queue0.empty() && _queue1.empty()) return -1;
        
        int res = -1;
        if(!_queue0.empty()){
            int count = _queue0.size();
            while(_queue0.size() > 1){
                _queue1.push(_queue0.front());
                _queue0.pop();
            }
            res = _queue0.front();
            _queue1.push(res);
            _queue0.pop();
            return res;
        }
        
        if(!_queue1.empty()){
            int count = _queue1.size();
            while(_queue1.size() > 1){
                _queue0.push(_queue1.front());
                _queue1.pop();
            }
            res = _queue1.front();
            _queue0.push(res);
            _queue1.pop();
        }    
        return res;
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       if(_queue0.empty() && _queue1.empty())
           return true;
        return false;
    }
private:
    std::queue<int> _queue0;
    std::queue<int> _queue1;
};