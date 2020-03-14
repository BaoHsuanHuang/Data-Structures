#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

int total = 0;

class Node
{
	public:
	    Node(){
	        this->next = NULL;
	        this->pre = NULL; 
	    }
	    Node(const int element , Node *next, Node *pre){
	        this->data = element;
	        this->next = next;
	        this->pre = pre;
	    }
	    ~Node(){
	        this->next = NULL;
	        this->pre = NULL;
	    }
	    friend class Chain;
	    
	    Node *next;
	    int data;
	    Node *pre;
};


class Chain
{
public:
    Chain(){		// constructor
        head = NULL;
        tail = NULL;
    }
    Chain(Node *head){	// copy constructor
        this->head = head;
        this->tail = head;
    }
    void InsertBack(int data);
    void InsertFront(int data);
    void InsertAfter(int data,int data_ref);
    void InsertBefore(int data,int data_ref);
    void Delete(int data);
    void DeleteFront();
    void DeleteBack();
    void Reverse();
    void Rotate(int k);
    void Swap(int k, int j);

    bool IsEmpty(){
    	this->tail = NULL;
        return this->head == NULL;
    }

    std::string PrintChain(){
        Node *cur = this->head;
        std::string result = "";
        if(cur == NULL){
            result = "Empty";
            return result;
        }
        while(cur != NULL){
            int num = cur->data;
            std::string num_str = std::to_string(num);
            result.append(num_str);
            if(cur -> next){
                result.append("->");
            }
            cur = cur->next;
        }
        return result;
    }

    Node *head;
    Node *tail;
};



void Chain::InsertBack(int data)
{
	total = total+1;
	
	if(head==NULL){
		head = new Node();
		head->data = data;
		head->next = NULL;
		head->pre = NULL;
		tail = head;
	}else{
		Node *newptr = new Node();
		newptr->data = data;
		newptr->next = NULL;
		newptr->pre = tail;
		
		tail->next = newptr;
		tail = newptr;
	}
}

void Chain::InsertFront(int data)
{
	total = total+1;
	
	if(head==NULL){
		head = new Node();
		head->data = data;
		head->next = NULL;
		head->pre = NULL;
		tail = head;
	}else{
		Node *newptr = new Node();
		newptr->data = data;
		newptr->next = head;
		newptr->pre = NULL;
		
		head->pre = newptr;
		head = newptr;
	}
}

void Chain::InsertAfter(int data,int data_ref)
{
	total = total+1;
	
	if(head==NULL) return;
	else{
		Node *current = head;
		Node *tmp = new Node();
		Node *p = NULL;
		int find = 0;
		
		tmp->data = data;
		tmp->pre = NULL;
		tmp->next = NULL;
		
//		while(current->data!=data_ref && current!=NULL){
//			current = current->next;
//		}
//		
//		if(data_ref == current->data) find = 1;
		while(current!=NULL){
			if(current->data == data_ref){
				find = 1;
				break;
			}
			current = current->next;
		}
		
		if(find == 1){
			if(current == tail){
				tail->next = tmp;
				tmp->pre = tail;
				tail = tmp;
			}else{
				p = current->next;
				
				current->next = tmp;
				tmp->pre = current;
				
				tmp->next = p;
				p->pre = tmp;			
			}			
		}else return;
	}
}


void Chain::InsertBefore(int data,int data_ref)
{
	total = total+1;
	
	if(head==NULL) return;
	else{
		Node *current = head;
		Node *tmp = new Node();
		Node *p = NULL;
		int find = 0;
		
		tmp->data = data;
		tmp->next = NULL;
		tmp->pre = NULL;
		
		while(current->data!=data_ref && current!=NULL){
			current = current->next;
		}
		
		if(data_ref == current->data) find = 1;
		
		if(find == 1){
			if(current==head){
				tmp->next = head;
				head->pre = tmp;
				head = tmp;
			}else{
				p = current->pre;
				
				p->next = tmp;
				tmp->pre = p;
				
				tmp->next = current;
				current->pre = tmp;			
			}			
		}else return;
	}
}

void Chain::Delete(int data)
{
	Node *current = head;
	Node *tmp = NULL;
	Node *p = NULL;
	Node *n = NULL;
	int find = 0;
	
	if(head==NULL) return;
	else{
		current = head;
		while(current!=NULL){
			if(data == current->data){
				find = 1;
				break;
			}
			current = current->next;
		}
		if(find==1){
			if(total==1){
				tmp = head;
				head = NULL;
				tail = NULL;
				delete tmp;
			}else{
				if(current == head){
					head = current->next;
					head->pre = NULL;
					delete current;
				}else if(current==tail){
					tail = current->pre;
					tail->next = NULL;
					delete current;
				}else{
					p = current->pre;
					n = current->next;
					
					delete current;
					p->next = n;
					n->pre = p;				
				}				
			}
		}else return;				
	}	
//		while(current->data!=data && current!=NULL){
//			current = current->next;
//		}
//		if(data == current->data) find = 1;

//		}
	
	total = total-1;
}

void Chain::DeleteFront()
{
	if(head==NULL) return;
	else{
//		Node *tmp = head->next;
//		head->next = NULL;
//		tmp->pre = NULL;
//		delete head;
//		head = tmp;
		if(total==1){
			Node *tmp = head;
			head = NULL;
			tail = NULL;
			delete tmp;
		}else if(total==2){
			Node *tmp = head;
			head = tail;
			head->pre = NULL;
			head->next = NULL;
			tail->pre = NULL;
			delete tmp;
		}else{
			Node *tmp = head;
			head = head->next;
			head->pre = NULL;
			delete tmp;			
		}
	}
	total = total-1;
}

void Chain::DeleteBack()
{
	
	if(head==NULL) return;
	else{
//		Node *tmp = tail->pre;
//		tmp->next = NULL;
//		tail->pre = NULL;
//		delete tail;
//		tail = tmp;
		if(total==1){
			Node *tmp = head;
			head = NULL;
//			head->pre = NULL;
//			head->next = NULL;
			tail = NULL;
//			tail->next = NULL;
//			tail->pre = NULL;
			delete tmp;
		}
		else if(total==2){
			Node *tmp = tail;
			tail = head;
			tail->next = NULL;
			tail->pre = NULL;
			head->next = NULL;
			head->pre = NULL;
			delete tmp;
		}
		else{
			Node *tmp = tail;
			tail = tail->pre;
			tail->next = NULL;
			delete tmp;			
		}
	}
	total = total-1;
}

void Chain::Reverse()
{
	Node *current = head;
	Node *tmp = NULL;
	
	if(head==NULL) return;
	else{
		if(total==1) return;
		else if(total==2){
			tmp = head;
			head = tail;
			tail = tmp;
			head->pre = NULL;
			head->next = tail;
			tail->next = NULL;
			tail->pre = head;
		}else{
			current = head;
			while(current->next!=NULL){
				tmp = current->pre;
				current->pre = current->next;
				current->next = tmp;
				current = current->pre;
			}
			tmp = current->pre;
			current->next = tmp;
			current->pre = NULL;
			
			tmp = head;
			head = tail;
			tail = tmp;
			
			head->pre = NULL;
			tail->next = NULL;			
		}
	}
}

void Chain::Rotate(int k)
{
	//int num = total - (k%total);
	int count = 0;
	Node *current = head;
	Node *tmp = NULL;
	
	if(head==NULL) return;
	else{
		if(k==1){
			tmp = tail;
			tail->next = head;
			head->pre = tail;
			tail = tail->pre;
			tail->next = NULL;
			head = tmp;
			head->pre = NULL;
		}else if(k==total){
			head = head;
			tail = tail;
		}else{
//			count = 0;
//			current = head;
//			while(count<=num){
//				current = current->next;
//				count++;
//			}
//			tmp = current->pre;
//			tmp->next = NULL;
//			current->pre = NULL;
//			
//			tail->next = head;
//			head->pre = tail;
//			
//			head = current;
//			tail = tmp;	
			count = 0;
			current = tail;
			while(count < (k%total)-1){
				current = current->pre;
				count++;
			}
			tail->next = head;
			head->pre = tail;
			head = current;
			tail = current->pre;
			head->pre = NULL;
			tail->next = NULL;		
		}
	}
}

void Chain::Swap(int k, int j)
{
//	Node *n1 = NULL;
//	Node *n1_p = NULL;
//	Node *n1_n = NULL;
//	Node *n2 = NULL;
//	Node *n2_p = NULL;
//	Node *n2_n = NULL;
//	
//	Node *current = head;
//	
//	while(current->data!=k){
//		current = current->next;
//	}
//	n1 = current;
//	n1_p = current->pre;
//	n1_n = current->next;
//	
//	current = head;
//	while(current->data!=j){
//		current = current->next;
//	}
//	n2 = current;
//	n2_p = current->pre;
//	n2_n = current->next;
//	
//	n1->next = n2_n;
//	n1->pre = n2_p;
//	
//	n2->next = n1_n;
//	n2->pre = n1_p;

	Node *current = head; 
	Node *tmp = NULL;
	int data1;
	int data2;
	int find1 = 0;
	int find2 = 0;
	
	if(head==NULL) return;
	else{
		find1 = 0;
		find2 = 0;
		current = head;
		while(current!=NULL){
			if(current->data == k){
				find1 = 1;
			}else if(current->data == j){
				find2 = 1;
			}
			current = current->next;
		}
		if(find1==1 && find2==1){
			current = head;
			while(current!=NULL){
				if(current->data == k){
					current->data = j;
				}else if(current->data == j){
					current->data = k;
				}
				current = current->next;
			}
		}
		
		
//		if(find1==1 && find2==1){
//			current->data = data1;
//			tmp->data = data2;
//		}
	}
}


int main()
{
    Chain inst = *(new Chain());

    string command;
    int data , data_ref;

    while(cin>>command){
        if(command == "InsertBack"){
            cin>>data;
            inst.InsertBack(data);
        }else if(command == "InsertFront"){
            cin>>data;
            inst.InsertFront(data);
        }else if(command == "InsertAfter"){
            cin>>data>>data_ref;
            inst.InsertAfter(data , data_ref);
        }else if(command == "InsertBefore"){
            cin>>data>>data_ref;
            inst.InsertBefore(data , data_ref);
        }else if(command == "Delete"){
            cin>>data;
            inst.Delete(data);
        }else if(command == "DeleteFront"){
            inst.DeleteFront();
        }else if(command == "DeleteBack"){
            inst.DeleteBack();
        }else if(command == "Reverse"){
            inst.Reverse();
        }else if(command == "Rotate"){
            int k;
            cin>>k;
            inst.Rotate(k);
        }else if(command == "Swap"){
            int j,k;
            cin>>j>>k;
            inst.Swap(j,k);
        }
        else if(command == "PrintChain"){
            cout<<inst.PrintChain()<<endl;
        }
    }
    return 0;
}

 

