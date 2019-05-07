
/*
	
*/
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head || k <= 0) return head;
        
        std::stack<ListNode*> container;
        ListNode* res = NULL;
        ListNode* pre = NULL;
        ListNode* cur = head;
        while((container.size() < k) && cur){
            container.push(cur); 
            ListNode* next = cur->next;
            if(container.size() == k){
                if(!pre){
                    pre = container.top();
                    container.pop();
                    pre->next = NULL;
                }
                while(!container.empty()){
                    if(!res) res = pre;
                    ListNode* tmp = container.top();
                    tmp->next = NULL;
                    pre->next = tmp;
                    container.pop();
                    pre = pre->next;
                }
                pre->next = next;
            }
            cur = next;
        }
        return (res ? res : head);
    }
};