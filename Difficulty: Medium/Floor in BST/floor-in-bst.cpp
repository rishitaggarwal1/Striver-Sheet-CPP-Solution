// Function to search a node in BST.
class Solution {

  public:
  int f=-1;
    int floor(Node* root, int x) {
        // Code here
        if(!root) {}
        else if(root->data==x)    f = x;
        else if(root->data>x)    floor(root->left,x);
        else 
        {
            f=root->data;
            floor(root->right,x);
        }
        return f;
    }
};