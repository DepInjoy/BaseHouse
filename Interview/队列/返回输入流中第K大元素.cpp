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
			/*	
				堆维护
				如果进入的元素比堆顶元素大，则插入
				否则，不处理
			*/
            if(minHeap.top() < val){
                if(!minHeap.empty()) minHeap.pop();
                minHeap.push(val);
            }
        }
        return minHeap.top();
    }
    
    private:
		//大顶堆
        priority_queue<int, deque<int>, greater<int>> minHeap;
        int size;
};