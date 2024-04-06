//============================================================================
// Name         : myvector.h
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : Vector implementation in C++
//============================================================================
#ifndef MYVECTOR_H
#define MYVECTOR_H
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include <stdexcept>
#include<sstream>

using namespace std;
template <typename T>
class MyVector
{
private:
	T* data;						//pointer to int(array) to store elements
	int v_size;						//current size of vector (number of elements in vector)
	int v_capacity;					//capacity of vector
public:
	MyVector();						//No argument constructor
	MyVector(int cap);				//One Argument Constructor
	MyVector(const MyVector& other);		//Copy Constructor
	~MyVector();					//Destructor
	void push_back(T element);		//Add an element at the end of vector
	void insert(int index, T element); //Add an element at the index 
	void erase(int index);			//Removes an element from the index
	T& operator[](int index);		//return reference of the element at index
	T& at(int index); 				//return reference of the element at index
	const T& front();				//Returns reference of the first element in the vector
	const T& back();				//Returns reference of the Last element in the vector
	int size() const;				//Return current size of vector
	int capacity() const;			//Return capacity of vector
	bool empty() const; 			//Return true if the vector is empty, False otherwise
	void shrink_to_fit();			//Reduce vector capacity to fit its size
};
//========================================

template <typename T>
MyVector<T>::MyVector()
{
	data = NULL;
	v_size = 0;
	v_capacity = 0;
}
//========================================

template <typename T>
MyVector<T>::MyVector(int cap)
{
	data = new T[v_capacity];
	v_size = 0;
	v_capacity = cap;
}
//========================================

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
{
	this->data = other->data;
	this->v_size = other->v_size;
	this->v_capacity = other->v_capacity;
}
//========================================

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data;
}
//========================================

template <typename T>
int MyVector<T>::size() const
{
	return(v_size);
}
//========================================

template <typename T>
int MyVector<T>::capacity() const
{
	return(v_capacity);
}
//========================================

template <typename T>
bool MyVector<T>::empty() const
{
	return(v_size == 0);
}
//========================================

template <typename T>
void MyVector<T>::push_back(T element)
{
	if (v_size == v_capacity)
	{
		v_capacity = v_capacity == 0 ? 1 : v_capacity * 2;
		T* temp = new T[v_capacity];
		for (int i = 0; i < v_size; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}
	data[v_size] = element;
	v_size++;
}
//===============================================================================

template <typename T>
void MyVector<T>::insert(int index, T element)
{
	if (index < 0 or index > v_size - 1)
	{
		throw out_of_range("Index out of range");      
	}
	if (v_size == v_capacity)     
	{
		v_capacity = v_capacity == 0 ? 1 : v_capacity * 2;     
		T* temp = new T[v_capacity];     
		for (int i = 0; i < v_size; i++)     
		{
			temp[i] = data[i];
		}
		delete[] data;    
		data = temp;    
	}
	for (int i = v_size; i > index; i--)     
	{
		data[i] = data[i - 1];
	}
	data[index] = element;      
	v_size++;    
}
//================================================================================

template <typename T>
void MyVector<T>::erase(int index)
{
	if (index < 0 or index > v_size - 1)
	{
		throw out_of_range("Index out of range");    
	}
	for (int i = index; i < v_size - 1; i++)      
	{
		data[i] = data[i + 1];
	}
	v_size--;     
}
//==================================================================================

template <typename T>
T& MyVector<T>::operator[](int index)
{
	if (index < 0 or index > v_size - 1)
	{
		throw out_of_range("Index out of range");     
	}
	return data[index];
}
//========================================

template <typename T>
T& MyVector<T>::at(int index)
{
	if (index < 0 or index > v_size - 1)
	{
		throw out_of_range("Index out of range");      
	}
	return data[index];
}
//========================================

template <typename T>
const T& MyVector<T>::front()
{
	if (empty())
	{
		throw out_of_range("Vector is empty");  
	}
	return data[0];
}
//========================================

template <typename T>
const T& MyVector<T>::back()
{
	if (empty())
	{
		throw out_of_range("Vector is empty");      
	}
	return data[v_size - 1];
}
//======================================

template <typename T>
void MyVector<T>::shrink_to_fit()		//Reduce vector capacity to fit its size.
{
	v_capacity = v_size;    
	T* temp = new T[v_capacity];      
	for (int i = 0; i < v_size; i++)      
	{
		temp[i] = data[i];
	}
	delete[] data;     
	data = temp;
}

#endif
