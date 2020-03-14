#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

template<class T>
class mystack{
	public:
		mystack():capacity(1), top(-1){
			stack = new T[capacity];
		}
		void push(T x);
		void pop();
		bool isEmpty();
		T Top();	
	private:
		int capacity;
		int top;
		T *stack;
		void DoubleCapacity();
};

template<class T>
void mystack<T>::DoubleCapacity()
{
	capacity = capacity*2;
	T *newstack = new T[capacity];
	int i;
	
	for(i=0;i<capacity/2;i++){
		newstack[i] = stack[i];
	}
	delete []stack;
	stack = newstack;
}

template<class T>
void mystack<T>::push(T x)
{
	if(top == capacity-1){
		DoubleCapacity();
		stack[++top] = x;
	}else{
		stack[++top] = x;
	}
}

template<class T>
void mystack<T>::pop()
{
	if(isEmpty()==1) return;
	else top--;
}

template<class T>
bool mystack<T>::isEmpty()
{
	if(top==-1) return true;
	else return false;
}

template<class T>
T mystack<T>::Top()
{
	if(isEmpty()==1) return -1;
	else return stack[top];
}












int main(void)
{
	string infix;
	string postfix;
	string prefix;
	long long int ans;
	
	while(cin >> infix){
		postfix = in2post(infix);
		prefix = in2pre(infix);
		ans = evaluate(postfix);
		
		cout << postfix << endl;
		cout << prefix << endl;
		cout << ans << endl; 
	}
} 
