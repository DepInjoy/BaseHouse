class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {
            
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        while(!_stack1.empty()){
            _stack0.push(_stack1.top());
            _stack1.pop();
        }
        _stack0.push(x);

        while(!_stack0.empty()){
            _stack1.push(_stack0.top());
            _stack0.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(_stack1.empty()) return -1;
        int value = _stack1.top();
        _stack1.pop();
        return value;
    }
    
    /** Get the front element. */
    int peek() {
        return _stack1.top(); 
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
       return _stack1.empty(); 
    }
    
    private:
        std::stack<int> _stack0;
        std::stack<int> _stack1;
};


/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */