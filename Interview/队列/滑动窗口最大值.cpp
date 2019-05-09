class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if(nums.size() < k || (k <= 0))
            return res;
        
        deque<int> windows;
        for(int i = 0;i < nums.size();i++){
            if(!windows.empty() && i >= k && windows.front() <= i - k)
                windows.pop_front();                
            
            while(!windows.empty() && nums[windows.back()] < nums[i])
                windows.pop_back();
            windows.push_back(i);
            
            if(i >= k - 1)
                res.push_back(nums[windows.front()]);
        }
        return res;
    }        
};