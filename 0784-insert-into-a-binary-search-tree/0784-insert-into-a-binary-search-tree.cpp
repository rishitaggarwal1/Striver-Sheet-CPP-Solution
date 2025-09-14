/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        TreeNode *temp = new TreeNode(val);
        TreeNode *head=root;
        if(head==nullptr)   return temp;
        while(head!=nullptr)
        {
            if(head->val<val)
            {
                if(head->right!=nullptr)    head=head->right;
                else 
                {
                    head->right=temp;
                    return root;
                }
            }
            else
            {
                if(head->left!=nullptr)    head=head->left;
                else 
                {
                    head->left=temp;
                    return root;
                }
            }
        }
        return root;
    }
};