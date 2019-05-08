class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {       
    
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        while(!_queue1.empty()){
            _queue0.push(_queue1.front());
            _queue1.pop();
        }
        
        _queue1.push(x);
        while(!_queue0.empty()){
            _queue1.push(_queue0.front());
            _queue0.pop();
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if(_queue1.empty()) return -1;
        int value = _queue1.front();
        _queue1.pop();
         return value;
    }
    
    /** Get the top element. */
    int top() {
        if(_queue1.empty())
            return -1;
        return _queue1.front(); 
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
       return _queue1.empty(); 
    }
    
    private:
        std::queue<int> _queue0;
        std::queue<int> _queue1;
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */