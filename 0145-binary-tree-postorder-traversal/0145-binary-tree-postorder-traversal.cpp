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
    void postorder(TreeNode* node, vector<int> *nums)
    {
        if(!node)
            return;
        postorder(node->left, nums);
        postorder(node->right,nums);
        (*nums).push_back(node->val);
        return;
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> nums; 
        postorder(root,&nums);
        return nums;
    }
};