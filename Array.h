//Array.h
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
using namespace std;

//������ģ�嶨��
template <class T> 
class Array {
private:
	T* list;	//T����ָ�룬���ڴ�Ŷ�̬����������ڴ��׵�ַ
	int size;	//�����С��Ԫ�ظ�����
public:
	Array(int sz = 50);			//���캯��
	Array(const Array<T> &a);	//�������캯��
	~Array();	//��������
	Array<T> & operator = (const Array<T> &rhs); //����"="ʹ�������������帳ֵ
	T & operator [] (int i);	//����"[]"��ʹArray���������C++��ͨ���������
	const T & operator [] (int i) const;	//"[]"�������const�汾
	operator T * ();	//���ص�T*���͵�ת����ʹArray���������C++��ͨ���������
	operator const T * () const;	//��T*����ת����������const�汾
	int getSize() const;	//ȡ����Ĵ�С
	void resize(int sz);	//�޸�����Ĵ�С
};

//���캯��
template <class T>
Array<T>::Array(int sz) {
	size = sz;	// ��Ԫ�ظ�����ֵ������size
	list = new T [size];	//��̬����size��T���͵�Ԫ�ؿռ�
}

//��������
template <class T>
Array<T>::~Array() {
	delete [] list;
}

//�������캯��
template <class T>
Array<T>::Array(const Array<T> &a) {
	//�Ӷ���xȡ�������С������ֵ����ǰ����ĳ�Ա
	size = a.size;
	//Ϊ���������ڴ沢���г�����
	list = new T[size];	// ��̬����n��T���͵�Ԫ�ؿռ�
	//�Ӷ���X��������Ԫ�ص�������  
	for (int i = 0; i < size; i++)
		list[i] = a.list[i];
}

//����"="�������������rhs��ֵ��������ʵ�ֶ���֮������帳ֵ
template <class T>
Array<T> &Array<T>::operator = (const Array<T>& rhs) {
	if (&rhs != this) {
		//����������������С��rhs��ͬ����ɾ������ԭ���ڴ棬Ȼ�����·���
		if (size != rhs.size) {
			delete [] list;		//ɾ������ԭ���ڴ�
			size = rhs.size;	//���ñ�����������С
			list = new T[size];	//���·���n��Ԫ�ص��ڴ�
		}
		//�Ӷ���X��������Ԫ�ص�������  
		for (int i = 0; i < size; i++)
			list[i] = rhs.list[i];
	}
	return *this;	//���ص�ǰ���������
}

//�����±��������ʵ������ͨ����һ��ͨ���±����Ԫ�أ����Ҿ���Խ���鹦��
template <class T>
T &Array<T>::operator[] (int n) {
	return list[n];				//�����±�Ϊn������Ԫ��
}

template <class T>
const T &Array<T>::operator[] (int n) const {
	return list[n];			//�����±�Ϊn������Ԫ��
}

//����ָ��ת�����������Array��Ķ�����ת��ΪT���͵�ָ�룬
//ָ��ǰ�����е�˽�����顣
//���������ʹ����ͨ�����׵�ַһ��ʹ��Array��Ķ�����
template <class T>
Array<T>::operator T * () {
	return list;	//���ص�ǰ������˽��������׵�ַ
}

template <class T>
Array<T>::operator const T * () const {
	return list;	//���ص�ǰ������˽��������׵�ַ
}

//ȡ��ǰ����Ĵ�С
template <class T>
int Array<T>::getSize() const {
	return size;
}

// �������С�޸�Ϊsz
template <class T>
void Array<T>::resize(int sz) {
	if (sz == size)	//���ָ���Ĵ�С��ԭ�д�Сһ����ʲôҲ����
		return;
	T* newList = new T [sz];	//�����µ������ڴ�
	int n = (sz < size) ? sz : size;	//��sz��size�н�С��һ����ֵ��n
	//��ԭ��������ǰn��Ԫ�ظ��Ƶ���������
	for (int i = 0; i < n; i++)
		newList[i] = list[i];
	delete[] list;		//ɾ��ԭ����
	list = newList;	// ʹlistָ��������
	size = sz;	//����size
}
#endif  //ARRAY_H
























#include <iostream>
#include"Array.h"

using namespace std;

//  ��Ϊ������ģʽ�еġ�Ŀ�꣨Target����
template <class T> class Stack {
public:
	Stack() {}
	virtual void push(T &element) = 0;
	virtual void pop() = 0;
	virtual T&top() = 0;
	virtual bool empty() = 0;
};

//  ��Ϊ������ģʽ�еġ���������Adapter����
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

//  ��Ϊ������ģʽ�еġ��û���Client����
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

