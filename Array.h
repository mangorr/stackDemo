//Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
using namespace std;

//数组类模板定义
template <class T> 
class Array {
private:
	T* list;	//T类型指针，用于存放动态分配的数组内存首地址
	int size;	//数组大小（元素个数）
public:
	Array(int sz = 50);			//构造函数
	Array(const Array<T> &a);	//拷贝构造函数
	~Array();	//析构函数
	Array<T> & operator = (const Array<T> &rhs); //重载"="使数组对象可以整体赋值
	T & operator [] (int i);	//重载"[]"，使Array对象可以起到C++普通数组的作用
	const T & operator [] (int i) const;	//"[]"运算符的const版本
	operator T * ();	//重载到T*类型的转换，使Array对象可以起到C++普通数组的作用
	operator const T * () const;	//到T*类型转换操作符的const版本
	int getSize() const;	//取数组的大小
	void resize(int sz);	//修改数组的大小
};

//构造函数
template <class T>
Array<T>::Array(int sz) {
	size = sz;	// 将元素个数赋值给变量size
	list = new T [size];	//动态分配size个T类型的元素空间
}

//析构函数
template <class T>
Array<T>::~Array() {
	delete [] list;
}

//拷贝构造函数
template <class T>
Array<T>::Array(const Array<T> &a) {
	//从对象x取得数组大小，并赋值给当前对象的成员
	size = a.size;
	//为对象申请内存并进行出错检查
	list = new T[size];	// 动态分配n个T类型的元素空间
	//从对象X复制数组元素到本对象  
	for (int i = 0; i < size; i++)
		list[i] = a.list[i];
}

//重载"="运算符，将对象rhs赋值给本对象。实现对象之间的整体赋值
template <class T>
Array<T> &Array<T>::operator = (const Array<T>& rhs) {
	if (&rhs != this) {
		//如果本对象中数组大小与rhs不同，则删除数组原有内存，然后重新分配
		if (size != rhs.size) {
			delete [] list;		//删除数组原有内存
			size = rhs.size;	//设置本对象的数组大小
			list = new T[size];	//重新分配n个元素的内存
		}
		//从对象X复制数组元素到本对象  
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this;	//返回当前对象的引用
}

//重载下标运算符，实现与普通数组一样通过下标访问元素，并且具有越界检查功能
template <class T>
T &Array<T>::operator[] (int n) {
	return list[n];				//返回下标为n的数组元素
}

template <class T>
const T &Array<T>::operator[] (int n) const {
	return list[n];			//返回下标为n的数组元素
}

//重载指针转换运算符，将Array类的对象名转换为T类型的指针，
//指向当前对象中的私有数组。
//因而可以象使用普通数组首地址一样使用Array类的对象名
template <class T>
Array<T>::operator T * () {
	return list;	//返回当前对象中私有数组的首地址
}

template <class T>
Array<T>::operator const T * () const {
	return list;	//返回当前对象中私有数组的首地址
}

//取当前数组的大小
template <class T>
int Array<T>::getSize() const {
	return size;
}

// 将数组大小修改为sz
template <class T>
void Array<T>::resize(int sz) {
	if (sz == size)	//如果指定的大小与原有大小一样，什么也不做
		return;
	T* newList = new T [sz];	//申请新的数组内存
	int n = (sz < size) ? sz : size;	//将sz与size中较小的一个赋值给n
	//将原有数组中前n个元素复制到新数组中
	for (int i = 0; i < n; i++)
		newList[i] = list[i];
	delete[] list;		//删除原数组
	list = newList;	// 使list指向新数组
	size = sz;	//更新size
}
#endif  //ARRAY_H
























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
bool isExpress(char s) {
	if (s == '+' || s == '-' || s == '*' || s == '/')
		return true;
	return false;
}

double getResult(double x1, double y1, char expression) {
	if (expression == '+')
		return x1 + y1;
	if (expression == '-')
		return x1 - y1;
	if (expression == '*')
		return x1 * y1;
	if (expression == '/') {
		if (y1 == 0)
			cout << "Should not be multiply." << endl;
		else
			return x1 / y1;
	}
}

double calculate(char expression[], int num) {
	double firstnum;
	double secondnum;
	double result;
	double express;
	Stack <double> *stack = NULL;
	stack = new MyStack <double>();
	for (int i = 0; i < num; i++) {
		if (isExpress(expression[i])) {
			secondnum = (*stack).top();
			(*stack).pop();
			firstnum = (*stack).top();
			(*stack).pop();
			result = getResult(firstnum, secondnum, expression[i]);
			(*stack).push(result);
		}
		else {
			express = expression[i] - '0';
			(*stack).push(express);
		}
	}
	return (*stack).top();
}

//  作为适配器模式中的“用户（Client）“
int main(int argc, char *argv[])
{
	char expression_1[] = { '8', '2', '-' };          //8 2 - = 8 - 2
	char expression_2[] = { '8', '2', '3', '*', '-' }; //8 2 3 * - = 8 - 2 * 3
	char expression_3[] = { '8', '2', '-', '3', '*' }; //8 2 - 3 * =(8 - 2) * 3
	char expression_4[] = { '8', '2', '/', '3', '/' }; //8 2 / 3 / =8 / 2 / 3

	cout << "expression_1 = " << calculate(expression_1, 3) << endl;
	cout << "expression_2 = " << calculate(expression_2, 5) << endl;
	cout << "expression_3 = " << calculate(expression_3, 5) << endl;
	cout << "expression_4 = " << calculate(expression_4, 5) << endl;
	return 0;
}

