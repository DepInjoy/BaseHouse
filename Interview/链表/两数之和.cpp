class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1 || !l2) return NULL;
        
        ListNode* res = NULL;
        ListNode* node = NULL;
        int sum = 0;
        while(l1 || l2 || (sum / 10)){
            int val1 = l1 ? l1->val : 0;
            int val2 = l2 ? l2->val : 0;
            sum = (sum / 10) + val1 + val2;
            if(!node) {
                node = new ListNode(sum % 10);
                res = node;
            }else{
                node->next = new ListNode(sum % 10);
                node = node->next;
            }
            if(l1) l1 = l1->next;
            if(l2) l2 = l2->next;
        }
        return res;
    }
};