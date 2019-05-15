class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(p->val < root->val && q->val < root->val)		//只存在于左子树
            return lowestCommonAncestor(root->left, p, q);
        else if(p->val > root->val && q->val > root->val)	//只存在于右子树
            return lowestCommonAncestor(root->right, p, q);
        else												//跨在两者之间，等于根节点
            return root;
    }
};