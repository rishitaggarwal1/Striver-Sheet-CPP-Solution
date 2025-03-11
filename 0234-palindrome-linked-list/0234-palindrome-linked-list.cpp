/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head->next==NULL)
            return true;
        ListNode *slow=head,*fast=head;
        while(fast!=NULL && fast->next!=NULL)
        {
            slow=slow->next;
            fast=fast->next->next;
        }
        if(fast!=NULL)
            slow=slow->next;
        ListNode* prev=NULL,*curr=slow,*nex=slow->next;
        while(curr!=NULL)
        {
            curr->next=prev;
            prev=curr;
            curr=nex;
            if(curr)
                nex=nex->next;
        }
        while(prev!=NULL)
        {
            if(head->val!=prev->val)
                return false;
            prev=prev->next;
            head=head->next;
        }
        return true;
    }
};