typedef struct _node{
	int data;
	struct _node *left;
	struct _node *right;
}Node;


int find_index(string str, int start, int end)
{
    stackArray<char>s;
    int i;

    for(i=start, i<=end; i++){
        if(str[i]=='('){
            s.push(str[i]);
        }else if(str[i]==')'){
            if(s.Top()=='('){
                s.pop();
                if(s.isEmpty()) return i;
            }

        }
    }
}

int find_data(string str, int start, int end)
{
    char num[1000000];
    int i=start+1;
    int j=0;

    memset(num, 0, sizeof(num));
    while(str[i]!='('){
        num[j] = str[i];
        i++;
        j++;
    }

    i=0;
    int a;
    int data=0;
    if(num[0]=='-'){
        while(j>=0){
            a = num[i+1] - '0';
            data += a*pow(10, j-2);
            j--;
            i++;
        }
    }else{
        while(j>=0){
            a = num[i] - '0';
            data += a*pow(10, j-1);
            j--;
            i++;
        }
    }
    return data;
}

Node *construct(string str, int start, int end)
{
    int data;
    Node *root;
    int l_index;
    int r_index;
    int i;

    if(str[start]=='(' && str[start+1]==')') return NULL;

    data = find_data(str, start, end);
    root = newNode(data);

    i=start+1;
    while(str[i]!='('){
        i++;
    }
    l_index = i;
    r_index = find_index(str, l_index, end);

    if(l_index < r_index){
        root->left = construct(str, l_index, r_index);
        root->right = construct(str, r_index+1, end-1);        
    }
    return root;
}

construct(str, 0, str.length()-1);