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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        int n = descriptions.size();
        map<int,TreeNode *> m;
        set<int> s; 
        for(int i=0;i<n;i++)
        {
            s.insert(descriptions[i][1]);
            TreeNode *p = NULL, *c = NULL;
            if(m.find(descriptions[i][0])!=m.end())
            {
                p=m[descriptions[i][0]];
            }
            else
            {
                TreeNode *t = new TreeNode(descriptions[i][0]);
                p=t;
                m[descriptions[i][0]] = p;
            }
            if(m.find(descriptions[i][1])!=m.end())
            {
                c=m[descriptions[i][1]];
            }
            else
            {
                TreeNode *t = new TreeNode(descriptions[i][1]);
                c=t;
                m[descriptions[i][1]] = c;
            }

            if(descriptions[i][2]==1)
                p->left = c;
            else
                p->right = c;
            
        }
        for(int i=0;i<n;i++)
        {
            if(s.find(descriptions[i][0])==s.end())  return m[descriptions[i][0]];
        }
        return NULL;
    }
};