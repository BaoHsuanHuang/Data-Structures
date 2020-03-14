#include <iostream>
#include <algorithm>
#include <cstring>
#include <cctype>

using namespace std;

template<class T>
class mystack{
	public:
		mystack():capacity(1), top(-1){
			stack = new T[capacity];
		}
		void push(T x);
		void pop();
		T Top();
		bool isEmpty();
	private:
		int capacity;
		int top;
		T *stack;
		void DoubleCapacity();
};

template<class T>
void mystack<T>::DoubleCapacity()
{
	capacity = capacity * 2;
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
	if(top == capacity-1) DoubleCapacity();
	stack[++top] = x;
}

template<class T>
void mystack<T>::pop()
{
	if(isEmpty()==1) return;
	top--;
}

template<class T>
T mystack<T>::Top()
{
	if(isEmpty()==1) return -1;
	return stack[top];
}

template<class T>
bool mystack<T>::isEmpty()
{
	if(top == -1) return true;
	else return false;
}


string in2post(string infix)
{
	string postfix;
	mystack <char>stack;
	
	for(auto& token: infix){
		if(isdigit(token)){
			postfix.push_back(token);
		}else if(token=='('){
			stack.push(token);
		}else if(token==')'){
			while(stack.Top()!='('){
				postfix.push_back(stack.Top());
				stack.pop();
			}
			stack.pop();
		}else if(token=='+' || token=='-'){
			if(stack.isEmpty()){
				stack.push(token);
			}else if(!stack.isEmpty()){
				if(stack.Top()=='('){
					stack.push(token);
				}else{
					while(stack.Top()=='+' || stack.Top()=='-' || stack.Top()=='*' || stack.Top()=='/'){
						postfix.push_back(stack.Top());
						stack.pop();
					}
					stack.push(token);		
				}
			}
		}else if(token=='*' || token=='/'){
			if(stack.isEmpty()){
				stack.push(token);
			}else if(!stack.isEmpty()){
				if(stack.Top()=='(' || stack.Top()=='+' || stack.Top()=='-'){
					stack.push(token);
				}else{
					while(stack.Top()=='*' || stack.Top()=='/'){
						postfix.push_back(stack.Top());
						stack.pop();
					}
					stack.push(token);
				}
			}
		}
	}
	while(!stack.isEmpty()){
		postfix.push_back(stack.Top());
		stack.pop();
	}
	return postfix;
}


string in2pre(string infix)
{
	reverse(infix.begin(), infix.end());
	
	string prefix;
	mystack <char>stack;
	
	for(auto& token : infix){
		if(isdigit(token)){
			prefix.push_back(token);
		}else if(token == ')'){
			stack.push(token);
		}else if(token == '('){
			while(stack.Top()!=')'){
				prefix.push_back(stack.Top());
				stack.pop();
			}
			stack.pop();
		}else if(token == '+' || token == '-'){
			if(stack.isEmpty()){
				stack.push(token);
			}else if(!stack.isEmpty()){
				while(stack.Top()=='*' || stack.Top()=='/'){
					prefix.push_back(stack.Top());
					stack.pop();
				}
				stack.push(token);
			}
		}else if(token == '*' || token == '/'){
			stack.push(token);
//			if(stack.isEmpty()){
//				stack.push(token);
//			}else if(!stack.isEmpty()){
//				
//			}
		}
	}
	while(!stack.isEmpty()){
		prefix.push_back(stack.Top());
		stack.pop();
	}
	reverse(prefix.begin(),prefix.end());
	return prefix;
}

long long int evaluate(string postfix)
{
	mystack <long long int>stack;
	long long int a;
	long long int b;
	long long int ans;
	
	for(auto& token: postfix){
		if(isdigit(token)){
			stack.push( (long long int) token - '0');	//pointpointpoint
		}else if(token == '+'){
			b = stack.Top();
			stack.pop();
			a = stack.Top();
			stack.pop();
			ans = a + b;
			stack.push(ans);
		}else if(token == '-'){
			b = stack.Top();
			stack.pop();
			a = stack.Top();
			stack.pop();
			ans = a - b;
			stack.push(ans);
		}else if(token == '*'){
			b = stack.Top();
			stack.pop();
			a = stack.Top();
			stack.pop();
			ans = a * b;
			stack.push(ans);
		}else if(token == '/'){
			b = stack.Top();
			stack.pop();
			a = stack.Top();
			stack.pop();
			ans = a / b;
			stack.push(ans);
		}
	}
	
	return stack.Top();
}


int main(void)
{
	string infix;
	string prefix;
	string postfix;
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


