#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;


typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}Node;


Node *newNode(int data)
{
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->data = data;
	tmp->left = NULL;
	tmp->right = NULL;
	
	return tmp;
}

string str;
int ind=0;
int flag=0;
int data2=0;

Node *construct()
{
    Node *root = NULL;
    while(1){
        if(str[ind] == ')'){
            return NULL;
        }else if(str[ind]=='('){
            ind++;
        }else if(str[ind]=='-'){
            ind++;
            flag = 1;
        }else if(isdigit(str[ind])){
            data2 = str[ind] - '0';
            ind++;
            while(isdigit(str[ind])){
                data2 = data2*10;
                data2 += str[ind] - '0';
                ind++;            
            }
            if(flag==1){
                data2 = (-1)*data2;
                root = newNode(data2);
                flag = 0;
            }else{
                root = newNode(data2);
            }
            break;
        }        
    }
    root->left = construct();
    ind++;
    root->right = construct();
    ind++;
    if(str[ind]==')') return root;
}






void preorder(Node *root)
{
	if(root!=NULL){
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(Node *root)
{
	if(root!=NULL){
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void postorder(Node *root)
{
	if(root!=NULL){
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

int getMax(Node *root)
{
	int left_height;
	int right_height;
	
	if(root==NULL) return 0;
	else{
		left_height = getMax(root->left);
		right_height = getMax(root->right);
		if(left_height >= right_height) return left_height+1;
		else if(right_height > left_height) return right_height+1;
	}
}



int countNode(Node *root)
{
	if(root==NULL) return 0;
	return ( 1 + countNode(root->left) + countNode(root->right) );
}
bool complete(Node *root, int index2, int total)
{
	if(root==NULL) return true;
	if(index2 >= total) return false;
	return ( complete(root->left, 2*index2 + 1, total) && 
             complete(root->right, 2*index2 + 2, total) ); 
}






/*
1) If tree is empty, then return true.
2) Convert the left subtree to its mirror image
    mirror(root->left);
3) Check if the structure of left subtree and right subtree is same
   and store the result.
    res = isStructSame(root->left, root->right); 
	//	isStructSame()
	//	recursively compares structures of two subtrees and returns
	//	true if structures are same 
4) Revert the changes made in step (2) to get the original tree.
    mirror(root->left);
5) Return result res stored in step 2.
*/
void mirror(Node *node) 
{ 
    if (node == NULL) return;
    else { 
        Node *tmp;
        
        /* do the subtrees */
        mirror(node->left); 
        mirror(node->right); 
  
        /* swap the pointers in this node */
        tmp = node->left;
        node->left = node->right;
        node->right = tmp;
    } 
} 

bool isStructSame(Node *a, Node *b) 
{ 
    if(a == NULL && b == NULL) return true;
    if(a != NULL && b != NULL && isStructSame(a->left, b->left) && isStructSame(a->right, b->right)) return true;
    return false; 
} 

bool foldable(Node *root)
{
	int result;
	
	if(root==NULL) return true;
	mirror(root->left);
	result = isStructSame(root->left, root->right);
	mirror(root->left);
	return result;
}





long long int helper(Node* node, long long int& l, long long int& r) {
    if (!node) return 0;
    long long int ll = 0, lr = 0, rl = 0, rr = 0;
    l = helper(node->left, ll, lr);
    r = helper(node->right, rl, rr);
    return max(node->data + ll + lr + rl + rr, l + r);
}

long long int QQ(Node* root) {
    long long int l = 0, r = 0;
    return helper(root, l, r);
}




Node *deleteLeaf(Node *root)
{
	if(root == NULL) return NULL;

	if(root->left==NULL && root->right==NULL){
		delete root;
		return NULL;
	}
	
	root->left = deleteLeaf(root->left);
	root->right = deleteLeaf(root->right);
	return root;
}

void freeTree(Node *root)
{
	Node *tmp = root;
	if(tmp!=NULL){
		freeTree(tmp->left);
		freeTree(tmp->right);
		delete tmp;
	}
}


int main(void)
{
	// string str;
	Node *root;
	int ans1;
	int ans2;
	int total;
	int height;
	
	while(cin >> str){
		//root = construct(str, 0, str.length()-1);
		//root = construct(str);
        ind = 0;
        data2 = 0;
        root = construct();
		preorder(root);
		cout << endl;
		inorder(root);
		cout << endl;
		postorder(root);
		cout << endl;
		
		height = getMax(root);
		cout << height << endl;
		
		total = countNode(root);
		ans1 = complete(root, 0, total);
		if(ans1 == 1) cout << "Complete" << endl;
		else cout << "Not complete" << endl;
		
		ans2 = foldable(root);
		if(ans2 == 1) cout << "Foldable" << endl;
		else cout << "Not foldable" << endl;
		
		cout << QQ(root) << endl;
		
		root = deleteLeaf(root);
		
		preorder(root);
		cout << endl;
		inorder(root);
		cout << endl;
		postorder(root);
		cout << endl;
		
		freeTree(root);
	}
	return 0;
}

