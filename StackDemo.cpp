#include <iostream>
#include"Array.h"

using namespace std;

//  作为适配器模式中的“目标（Target）“
template <class T> class Stack {
public:
	Stack() {}
	virtual void push(T &element) = 0;
	virtual void pop() = 0;
	virtual T&top() = 0;
	virtual bool empty() = 0;
};

//  作为适配器模式中的“适配器（Adapter）”
template <class T> class MyStack :public Stack<T> {
public:
	MyStack() {
		topItem = -1;
	}
	void push(T & element) {
		array[++topItem] = element;
	}
	void pop() {
		if (this->empty())
			cout << "the stack is empty" << endl;
		else
			topItem--;
	}
	T &top(T &charType) {
		return array[topItem];
	}
	T &top() {
		return array[topItem];
	}
	bool empty() {
		if (topItem == -1)
			return true;
		else
			return false;
	}
private:
	Array<T> array;
	int topItem;
};

bool isRight(char s) {
	if (s == ')' || s == ']' || s == '}'||s=='>')
		return true;
	return false;
}

char validate(char expression[], int num) {
	int i = 0;
	char firstnum;
	char secondnum;
	bool result=false;
	Stack <char> *stack = NULL;
	stack = new MyStack <char>();
	for (i = 0; i < num; i++) {
		if (isRight(expression[i])) {
			(*stack).push(expression[i]);
			secondnum = (*stack).top();
			//cout <<secondnum;
			(*stack).pop();
			firstnum = (*stack).top();
			//cout <<firstnum;
			(*stack).pop();
			if (((firstnum == '(')&&(secondnum == ')')) || ((firstnum == '[') && (secondnum == ']')) || ((firstnum == '{') && (secondnum == '}'))|| ((firstnum == '<') && (secondnum == '>')))
				result = true;
			else result = false;

			if (!result) {
				cout << "括号不配对" << endl;
				goto L;
				//break;
			}

			/*if (i == num && result)
				cout << "括号配对" << endl;*/
			/*result = getResult(firstnum, secondnum, expression[i]);
			(*stack).push(result);*/
		}
		else {
			(*stack).push(expression[i]);
		}
	}
	if((*stack).top() == '(' || (*stack).top() == '[' || (*stack).top() == '{' || (*stack).top() == '<')
		cout << "括号不配对" << endl;
	if ((*stack).top()!='(' && (*stack).top() != '['&& (*stack).top() != '{'&& (*stack).top() != '<'&& result)
		cout << "括号配对" << endl;

	L:return (*stack).top();
}

//  作为适配器模式中的“用户（Client）“
int main(int argc, char *argv[])
{
	char expression_1[] = { '(', '[', ']', ')' }; // ( [ ] )
	char expression_2[] = { '[', '(', ')', '<', '>' }; // [ ( ) < >
	// { ( ) { [ ( ) } ] } 
	char expression_3[] = { '{', '(', ')', '{', '[', '(', ')', '}', ']', '}' };
	cout << "expression_1 " << validate(expression_1, 4) << endl;
	cout << "expression_2 " << validate(expression_2, 5) << endl;
	cout << "expression_3 " << validate(expression_3, 10) << endl;

	return 0;
}
