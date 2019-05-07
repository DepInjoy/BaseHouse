/*
	set判重
*/
class Solution {
public:
    bool hasCycle(ListNode *head) {
        int count = 0;
        std:set<ListNode*> tmp;
        while(head){
            tmp.insert(head);
            count += 1;
            if(tmp.size() < count)
                return true;
            head = head->next;
        }
        return false;
    }
};

/*
	快慢指针
*/
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* low = head;
        ListNode* fast = head;
        while(low && fast && low->next && fast->next){
            low = low->next;
            fast = fast->next->next;
            if(low == fast)
                return true;
        }
        return false;   
    }
};