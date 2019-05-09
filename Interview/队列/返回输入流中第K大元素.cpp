class KthLargest {
public:  
    KthLargest(int k, vector<int> nums){
        size = k;
        for(auto val = nums.begin();val < nums.end();val++){
            if(minHeap.size() < k){
                minHeap.push(*val);
            }else{
                if(minHeap.top() < *val){
                    minHeap.pop();
                    minHeap.push(*val);
                }
            }
        }
    }
    
    int add(int val) {
        if(minHeap.size() < size){
            minHeap.push(val);
        }else{
            if(minHeap.top() < val){
                if(!minHeap.empty()) minHeap.pop();
                minHeap.push(val);
            }
        }
        return minHeap.top();
    }
    
    private:
        priority_queue<int, deque<int>, greater<int>> minHeap;
        int size;
};