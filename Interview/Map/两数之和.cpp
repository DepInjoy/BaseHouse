class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        //创建HashMap
        std::unordered_map<int, int> tmp;
        for(int i = 0; i < nums.size();i++){
            auto num1 = tmp.find(target - nums[i]);
            //查找到符合条件的数据
            if(num1 != tmp.end()){
                res.push_back(i);
                res.push_back(num1->second);
            }
            //将(数据，索引)添加入HashMap。
           tmp[nums[i]] =  i;
        }
       return res; 
    }
};