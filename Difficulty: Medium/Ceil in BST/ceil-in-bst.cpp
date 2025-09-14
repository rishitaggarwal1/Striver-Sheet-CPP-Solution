class Solution {
  public:
  int ceil=-1;
    int findCeil(Node* root, int x) {
        // code here
        if(!root) {}
        else if(root->data==x)    ceil = x;
        else if(root->data<x)    findCeil(root->right,x);
        else 
        {
            ceil=root->data;
            findCeil(root->left,x);
        }
        return ceil;
    }
};
