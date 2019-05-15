class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root == q)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if(left == NULL){		//不在左子树，则在右子树
            return right;
        } else{					//存在在左子树
            if(right == NULL) 	//不存在在右子树，则存在在左子树
                return left;
            else				//既存在在左子树也存在在右子树，则为root
                return root;
        }
    }
};