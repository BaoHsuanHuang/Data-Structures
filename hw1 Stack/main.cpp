#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

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



string in2post(string infix)
{
	string post;
	stackArray<char> stack;
	//str.append(1, char)
	//str.push_back(char)
	for(auto & token : infix){
		if(isdigit(token)){
			post.push_back(token);
		}else if(token == '('){
			stack.push((token));
		}else if(token == ')'){
			while(stack.Top() == '+' || stack.Top()=='-' || stack.Top() =='*' || stack.Top()=='/'){
				post.push_back(stack.Top());
				stack.pop();
			}
			if(stack.Top()=='('){
				stack.pop();
			}
		}else if(token == '+' || token == '-'){
			if(!stack.isEmpty()){
				while(stack.Top()=='*' || stack.Top()=='/' || stack.Top()=='+' || stack.Top()=='-'){
					post.push_back(stack.Top());
					stack.pop();
				}
				stack.push(token);
				if(stack.Top() == '('){
					stack.push(token);
				} 				
			}else if(stack.isEmpty()){
				stack.push(token);
			}
		}else if(token == '*' || token == '/'){
			if(!stack.isEmpty()){
				while(stack.Top()=='*' || stack.Top()=='/'){
					post.push_back(stack.Top());
					stack.pop();
				}
				stack.push(token);
				if(stack.Top() == '+' || stack.Top() == '-' || stack.Top() == '('){
					stack.push(token);					
				}			
			}
			else if(stack.isEmpty()==1){
				stack.push(token);	
			}
		}
	}
	while(!stack.isEmpty()){
		post.push_back(stack.Top());
		stack.pop();
	}
	return post;
}


string in2pre(string infix)
{
	reverse(infix.begin(), infix.end());

	string prefix;
	stackArray <char> stack;

	for(auto & token : infix){
		if(isdigit(token)){
			prefix.push_back(token);
		}else if(token == ')'){
			stack.push((token));
		}else if(token == '('){
			while(stack.Top() == '+' || stack.Top()=='-' || stack.Top() =='*' || stack.Top()=='/'){
				prefix.push_back(stack.Top());
				stack.pop();
			}
			if(stack.Top()==')'){
				stack.pop();
			}
		}else if(token == '+' || token == '-'){
			if(!stack.isEmpty()){
				while(stack.Top()=='*' || stack.Top()=='/'){
					prefix.push_back(stack.Top());
					stack.pop();
				}
				stack.push(token);
				//if(stack.Top() == ')' || stack.Top()=='+' || stack.Top()=='-'){
				//	stack.push(token);
				//} 				
			}else if(stack.isEmpty()){
				stack.push(token);
			}
		}else if(token == '*' || token == '/'){
			if(!stack.isEmpty()){
				//while(stack.Top()=='*' || stack.Top()=='/'){
				//	prefix.push_back(stack.Top());
				//	stack.pop();
				//}
				//stack.push(token);
				if(stack.Top() == '+' || stack.Top() == '-' || stack.Top() == ')' || stack.Top()=='*' || stack.Top()=='/'){
					stack.push(token);					
				}			
			}
			else if(stack.isEmpty()==1){
				stack.push(token);	
			}
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
	stackArray <long long int> stack;
	long long int a;
	long long int b;
	long long int ans;
	
	for(auto & token : postfix){
		if(isdigit(token)){
			stack.push( (long long int) token - '0');
		}else{
			if(token == '+'){
				a = stack.Top();
				stack.pop();
				b = stack.Top();
				stack.pop();
				ans = a + b;
				stack.push(ans);			
			}else if(token == '-'){
				a = stack.Top();
				stack.pop();
				b = stack.Top();
				stack.pop();
				ans = b - a;
				stack.push(ans);			
			}else if(token == '*'){
				a = stack.Top();
				stack.pop();
				b = stack.Top();
				stack.pop();
				ans = a * b;
				stack.push(ans);
			}else if(token == '/'){
				a = stack.Top();
				stack.pop();
				b = stack.Top();
				stack.pop();
				ans = b / a;
				stack.push(ans);
			}
		}
	}
	ans = stack.Top();
	return ans;
}


int main()
{
	string infix;
	string postfix;
	string prefix;
	long long int ans;
	
	while (cin >> infix) {
		postfix = in2post(infix);
		prefix = in2pre(infix);
		ans = evaluate(postfix);
		
		cout << postfix << endl;
		cout << prefix << endl;
		cout << ans << endl;
	}
}





