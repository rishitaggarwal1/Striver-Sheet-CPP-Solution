/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow=head,*fast=head;
        int k=0;
        while(fast!=NULL && fast->next!=NULL)
        {
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast)
            {
                k=1;
                break;
            }
        }
        if(k==0)
            return NULL;
        unordered_map<ListNode *,int> s;
        slow=head;
        while(1)
        {
            s[slow]++;
            if(s[slow]==2)
                return slow;
            slow=slow->next;
        }
        return slow;
    }
};