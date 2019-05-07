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
            /*
				注意：此处需要将下一个节点进行备份，否则会进入死循环
				假设k=2,链表为1 -> 2 -> 3 -> 4 -> 5
				第一次读取到k个元素之后，此时cur为2所在位置
				翻转得到2 -> 1 -> 3 -> 4 -> 5
				如果cur->next没有备份，此时2所在位置的next为1所对应的指针，又循环回到1 -> 2 -> 3 -> 4 -> 5的读取
			*/
			ListNode* next = cur->next;
            if(container.size() == k){
                if(!pre){
                    pre = container.top();
                    container.pop();
                }                
                while(!container.empty()){
                    if(!res) res = pre;
                    pre->next = container.top();
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