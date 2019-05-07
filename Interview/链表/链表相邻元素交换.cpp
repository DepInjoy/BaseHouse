
/*
	我的实现
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
       if(!head || (head && !head->next))
           return head;
        
        ListNode* low = head;
        ListNode* fast = head->next;
        ListNode* pre = NULL;
        head = head->next;
        while(low && fast){
            ListNode* tmp = fast->next;
            fast->next = low;
            low->next = tmp;
            if(pre) pre->next = fast;
            //注意：low和fast被交换
            pre = low;
            low = tmp;
            fast = (tmp ? tmp->next : NULL);
        }
        return head; 
    }
};

/*
	LeetCode上的优秀提交
	利用二级指针，代码很简洁
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || (head && !head->next))
            return head;
       
        ListNode** pp = &head;
        ListNode* cur = head;
        ListNode* next = NULL;
        while((cur = *pp) && (next = cur->next)){
            cur->next = next->next;
            next->next = cur;
            *pp = next;
            pp = &(cur->next);
        }
        return *pp;
    }
};