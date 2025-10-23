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
MyVector<T>::MyVector()     //No argument constructor
{
	v_size = 0;     //initialize size to 0  
	v_capacity = 0;     //initialize capacity to 0
	data = new T[v_capacity];     //allocate memory for data
}
//========================================

template <typename T>
MyVector<T>::MyVector(int cap)    //One Argument Constructor
{
	v_capacity = cap;     //initialize capacity to cap
	v_size = 0;     //initialize size to 0
	data = new T[v_capacity];     //allocate memory for data
}
//========================================

template <typename T>
MyVector<T>::MyVector(const MyVector& other)     //Copy Constructor
{
	this->data = other->data;     //copy data
	this->v_size = other->v_size;     //copy size
	this->v_capacity = other->v_capacity;      //copy capacity
}
//========================================

template <typename T>
MyVector<T>::~MyVector()      //Destructor
{
	delete[] data;      //deallocate memory
}
//========================================

template <typename T>
int MyVector<T>::size() const      //Return current size of vector
{
	return(v_size);      //return size  
}
//========================================

template <typename T>
int MyVector<T>::capacity() const     //Return capacity of vector
{
	return(v_capacity);
}
//========================================

template <typename T>
bool MyVector<T>::empty() const     //Return true if the vector is empty, False otherwise
{
	return(v_size == 0);
}
//========================================

template <typename T>
void MyVector<T>::push_back(T element) {		//Add an element at the end of vector
	
	if (v_size == v_capacity) {     //if size is equal to capacity

		v_capacity = (v_capacity == 0) ? 1 : v_capacity * 2;     //double the capacity

		T* temp = new T[v_capacity];	 //allocate memory for temp
		for (int i = 0; i < v_size; ++i) {		//copy elements to temp
			temp[i] = data[i];
		}
		delete[] data;    //deallocate memory
		data = temp;     //copy temp to data
	}
	data[v_size++] = element;    //add element to the end of vector
}
//===============================================================================

template <typename T>
void MyVector<T>::insert(int index, T element)      //Add an element at the index
{
	if (index < 0 or index > v_size - 1)      //if index is out of range
	{
		throw out_of_range("Index out of range");      
	}
	if (v_size == v_capacity)        //if size is equal to capacity
	{
		v_capacity = v_capacity == 0 ? 1 : v_capacity * 2;      //double the capacity   
		T* temp = new T[v_capacity];      // allocate memory for temp 
		for (int i = 0; i < v_size; i++)       //copy elements to temp
		{
			temp[i] = data[i];
		}
		delete[] data;     // deallocate memory 
		data = temp;     //copy temp to data
	}
	for (int i = v_size; i > index; i--)    // shift elements 
	{
		data[i] = data[i - 1];
	}
	data[index] = element;   // 
	v_size++;    
}
//================================================================================

template <typename T>
void MyVector<T>::erase(int index)      //Removes an element from the index
{
	if (index < 0 or index > v_size - 1)      //if index is out of range
	{
		throw out_of_range("Index out of range");    
	}
	for (int i = index; i < v_size - 1; i++)     // update data    
	{
		data[i] = data[i + 1];
	}
	v_size--;     
}
//==================================================================================

template <typename T>
T& MyVector<T>::operator[](int index)     //return reference of the element at index
{
	if (index < 0 or index > v_size - 1)
	{
		throw out_of_range("Index out of range");     
	}
	return data[index];     // retur the element at index
}
//========================================

template <typename T>
T& MyVector<T>::at(int index)   //return reference of the element at index
{
	if (index < 0 or index > v_size - 1)     //if index is out of range
	{
		throw out_of_range("Index out of range");      
	}
	return data[index];    //return the element at index
}
//========================================

template <typename T>
const T& MyVector<T>::front()     //Returns reference of the first element in the vector
{
	if (empty())
	{
		throw out_of_range("Vector is empty");  
	}
	return data[0];
}
//========================================

template <typename T>
const T& MyVector<T>::back()      //Returns reference of the Last element in the vector
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
	v_capacity = v_size;     //set capacity to size

	T* temp = new T[v_capacity];    //create temp  
	for (int i = 0; i < v_size; i++)     //update temp     
	{
		temp[i] = data[i];
	}
	delete[] data;      //delete temp    
	data = temp;     //copy temp to data
}

#endif
