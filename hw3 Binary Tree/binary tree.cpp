#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <math.h>

using namespace std;

string str;


template<class T>
class stackArray{
	private:
		int top;
		int capacity;
		T *stack;
		void DoubleCapacity();
		
	public:
		//constructor
		stackArray():top(-1), capacity(1){
			stack = new T[capacity];
		}
		void push(T x);
		void pop();
		bool isEmpty();
		T Top();	
};

template<class T>
void stackArray<T>::DoubleCapacity()
{
	capacity *= 2;
	T *newstack;
	int i;
	
	newstack = new T[capacity];
	for(i=0;i<capacity/2;i++){
		newstack[i] = stack[i];
	}
	delete []stack;
	stack = newstack;
}

template<class T>
void stackArray<T>::push(T x)
{
	if(top == capacity-1){
		DoubleCapacity();
	}
	stack[++top] = x;
}

template<class T>
void stackArray<T>::pop()
{
	if(isEmpty() == 1) return;
	top--;
}

template<class T>
T stackArray<T>::Top()
{
	if(isEmpty()==1){
		return -1;
	}
	return stack[top];
}

template<class T>
bool stackArray<T>::isEmpty()
{
	//if(top == -1) reutrn true;
	//else return false;
	return (top == -1);
}

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



int find_index(int start, int end)
{
    stackArray<char>s;
    int i;

	if(start > end) return -1;

    for(i=start; i<=end; i++){
        if(str[i]=='('){
            s.push(str[i]);
        }else if(str[i]==')'){
            if(s.Top()=='('){
                s.pop();
                if(s.isEmpty()) return i;
            }
        }
    }
	return -1;
}

long long int find_data(int start, int end)
{
    char num[1000000];
    int i=start+1;
    int j=0;

    memset(num, 0, sizeof(num));
    while(str[i]!='(' && str[i]!=')'){
        num[j] = str[i];
        i++;
        j++;
    }

    i=0;
    int a;
    long long int data=0;
    if(num[0]=='-'){
        while((j-2)>=0){
            a = num[i+1] - '0';
            data += a*pow(10, j-2);
            j--;
            i++;
        }
        data = (-1)*data;
    }else{
        while((j-1)>=0){
            a = num[i] - '0';
            data += a*pow(10, j-1);
            j--;
            i++;
        }
    }
    return data;
}

Node *construct(int start, int end)
{
    long long int data;
    Node *root;
    int l_index;
    int r_index;
    int i;

	// cout << "start : " << start << endl;
	// cout << "end : " << end  << endl;

    if(str[start]=='(' && str[start+1]==')') return NULL;
	
    data = find_data(start, end);
    root = newNode(data);
    //cout << "data : " << data << endl;

    i=start+1;
    while(str[i]!='(' && str[i]!=')'){
        i++;
    }
    l_index = i;
    r_index = find_index(l_index, end);

	//	cout << "l : " << l_index << endl;
	//	cout << "r : " << r_index << endl;
	if(l_index < r_index  && r_index!=-1){
	    root->left = construct(l_index, r_index);
	    root->right = construct(r_index+1, end-1);		
	}
    return root;
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
bool complete(Node *root, int index, int total)
{
	if(root==NULL) return true;
	if(index >= total) return false;
	return ( complete(root->left, 2*index + 1, total) && 
             complete(root->right, 2*index + 2, total) ); 
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
		root = construct(0, str.length()-1);
		//root = construct(str);
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



/*
int findIndex(string str, int si, int ei) 
{ 
    if(si > ei) return -1; 
  
    // Inbuilt stack 
    stackArray<char>s; 
  
    for(int i = si; i <= ei; i++){ 
        // if open parenthesis, push it 
        if(str[i] == '('){
        	s.push(str[i]); 
		}
        // if close parenthesis 
        else if(str[i] == ')'){ 
            if(s.Top() == '('){ 
                s.pop();
                // if stack is empty, this is  
                // the required index 
                if (s.isEmpty()) 
                    return i; 
            } 
        } 
    } 
    // if not found return -1 
    return -1; 
} 

Node *construct(string str, int si, int ei)
{
	char num[1000000];
	int data=0;
	int a=0;
	int s;

    //if(si > ei) return NULL; 
  	if(str[si]=='(' && str[si+1]==')') return NULL;

    cout << "si : " << si << endl; 
    cout << "ei : " << ei << endl;
    if(str[si]!=')'){
    	s = si+1;
		int i = 0;
    	int count=0;
    	memset(num,0,sizeof(num));
    	while(str[s]!='('){
    		num[i] = str[s];
    		i++;
    		s++;
    		count++;
		}
		i=0;
		a=0;
		data=0;
		if(num[0]=='-'){
			while(i<count-1){
				int a = num[i+1]-'0';
				data += a*pow(10,count-i-2);
				i++;
			}
			data = (-1)*data;
		}else{
			while(i<count){
				int a = num[i]-'0';
				data += a*pow(10,count-i-1);
				i++;
			}
		}
		cout << "->data:" << data << endl;
	    Node *root = newNode(data); 
	    int index = -1; 
 
	    // if next char is '(' find the index of its complement ')' 
	    if(si + 1 <= ei && str[si + count + 1] == '('){
	    	index = findIndex(str, si + count + 1, ei);
	    	cout << "index:" << index << endl;
		}     	

	    cout << "count:" << count << endl;
	    cout << endl;
	    if(index != -1) {  
	        root->left = construct(str, si+count+1, index); 
	        root->right = construct(str, index+1, ei-1); 
	    } 
	    return root;		
	}
}
*/


/*
int sum=0;
void SumLevel(Node *root,int level)
{
	if(root!=NULL && level==1){
		sum += root->data;
	}else if(root!=NULL && level>1){			// point
		level--;
		SumLevel(root->left,level);
		SumLevel(root->right,level);
	}
}

int QQ(Node *root, int height)
{
	int i=1;
	int odd = 0;
	int even = 0;
	
	for(i=1;i<=height;i=i+2){
		SumLevel(root,i);
		odd = odd + sum;
		sum = 0;
	}
	for(i=2;i<=height;i=i+2){
		SumLevel(root,i);
		even = even + sum;
		sum = 0;
	}
	if(odd > even) return odd;
	else return even;
}
*/
