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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* ans=NULL;
        ListNode* pnt=ans;
        int carry=0;
        while(l1!=NULL && l2!=NULL)
        {
            int x=l1->val+l2->val+carry;
            carry=x/10;
            ListNode *temp=new ListNode();
            temp->val=x%10;
            if(ans==NULL)
            {    ans=temp; pnt=ans; }
            else
            {
                pnt->next=temp;
                pnt=pnt->next;
            }
            l1=l1->next;
            l2=l2->next;
        }
        while(l1!=NULL)
        {
            int x=l1->val+carry;
            carry=x/10;
            ListNode *temp=new ListNode();
            temp->val=x%10;
            if(ans==NULL)
            {    
                ans=temp; 
                pnt=ans; 
            }
            else
            {
                pnt->next=temp;
                pnt=pnt->next;
            }
            l1=l1->next;
        }
        while(l2!=NULL)
        {
            int x=l2->val+carry;
            carry=x/10;
            ListNode *temp=new ListNode();
            temp->val=x%10;
            if(ans==NULL)
            {    
                ans=temp; 
                pnt=ans; 
            }
            else
            {
                pnt->next=temp;
                pnt=pnt->next;
            }
            l2=l2->next;
        }
        if(carry>0)
        {
            ListNode* temp=new ListNode(carry);
            pnt->next=temp;
        }
        return ans;
    }
};