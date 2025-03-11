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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA=0,lenB=0;
        ListNode *t=headA;
        while(t!=NULL)
        {
            lenA++;
            t=t->next;
        }
        t=headB;
        while(t!=NULL)
        {
            lenB++;
            t=t->next;
        }
        if(lenA>lenB)
        {
            int diff=lenA-lenB;
            while(diff--)
                headA=headA->next;
        }
        else
        {
            int diff=lenB-lenA;
            while(diff--)
                headB=headB->next;
        }
        while(headA!=NULL && headB!=NULL)
        {
            if(headA==headB)
                return headA;
            headA=headA->next;
            headB=headB->next;
        }
        return NULL;
    }
};