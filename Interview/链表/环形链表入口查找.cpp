/*
	利用hash表存储，查找下一个结点是否已经存在。
*/
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head || !head->next) return NULL;
        ListNode* node = head;
        std::unordered_set<ListNode*> set;
        while(node && node->next){
            set.insert(node);
            auto res = set.find(node->next);
            if(res != set.end())
                return *res;
            node = node->next;
        }
        return NULL;
    }
};

/*
	首先，快慢指针确定是否存在环
	如果不存在则返回NULL，否则，快慢指针重合位置即环中元素数
	将其中一个指针重置为头结点位置，当两者再次重合，即为环入口。
*/
class Solution {
public:    
    ListNode *detectCycle(ListNode *head) {
        if(!head || !head->next) return NULL;
        
        ListNode* low = head;
        ListNode* fast = head;
        bool hasCycle = false;
        while(low && low->next && fast && fast->next){
            low = low->next;
            fast = fast->next->next;
            if(low == fast){
                hasCycle = true;
                break;
            }
        }  
        if(!hasCycle) return NULL;

        low = head;
        while(low != fast){
            low = low->next;
            fast = fast->next;
        }
        return low;
    }
};