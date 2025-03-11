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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int cnt=0;
        ListNode *temp=head;
        if(head==NULL)
            return head;
        while(temp!=nullptr)
        {
            cnt++;
            temp=temp->next;
        }
        int k=cnt-n,i=0;
        temp=head;
        while(i++<k-1)
        {
            temp=temp->next;
        }
        if(temp->next==NULL)
            return NULL;
        if(k==0)
        {    head=head->next; return head;}
        temp->next=temp->next->next;
        return head;
    }
};