/*
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};
*/
class Solution {
  public:
    int findMax(Node *root) {
        if(root==NULL)
            return INT_MIN;
        int res=root->data;
        int lres=findMax(root->left);
        int rres=findMax(root->right);
        if(lres>res)
            res=lres;
        if(rres>res)
            res=rres;
        return res;
    }

    int findMin(Node *root) {
        if(root==NULL)
            return INT_MAX;
        int res=root->data;
        int lres=findMin(root->left);
        int rres=findMin(root->right);
        if(lres<res)
            res=lres;
        if(rres<res)
            res=rres;
        return res;
    }
};