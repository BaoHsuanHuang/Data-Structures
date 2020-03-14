class TreeNode{
	public:
		friend class Tree;
	private:
		int data;
		TreeNode *left;
		TreeNode *right;
};

class Tree{
	public:
		//constructor
		Tree(void) { root = NULL;}
		
	private:
		TreeNode *root;
		
		
};


void Tree::inorder(TreeNode *current)
{
	
}
