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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *ans=NULL, *pt=NULL;
        while(list1!=NULL && list2!=NULL)
        {
            ListNode *temp = new ListNode();
            if(list1->val <= list2->val)
            {
                temp->val = list1->val;
                list1=list1->next;
            }
            else
            {
                temp->val = list2->val;
                list2=list2->next;
            }
            if(!ans)
            {
                ans=temp;
                pt=temp;
            }
            else
            {
                pt->next=temp;
                pt=pt->next;
            }
        }

        while(list1!=NULL)
        {
            ListNode *temp = new ListNode(list1->val);
            list1=list1->next;
            if(!ans)
            {
                ans=temp;
                pt=temp;
            }
            else
            {
                pt->next=temp;
                pt=pt->next;
            }
        }
        while(list2!=NULL)
        {
            ListNode *temp = new ListNode(list2->val);
            list2=list2->next;
            if(!ans)
            {
                ans=temp;
                pt=temp;
            }
            else
            {
                pt->next=temp;
                pt=pt->next;
            }
        }
        return ans;
    }
};