//============================================================================
// Name         : myvector.h
// Author       : 
// Version      : 1.0
// Date Created : 
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
	//to-do
}
//========================================
template <typename T>
MyVector<T>::MyVector(int cap)
{
	//to-do
}
//========================================
template <typename T>
MyVector<T>::MyVector(const MyVector& other)
{
	//to-do
}
//========================================
template <typename T>
MyVector<T>::~MyVector()
{
	//to-do
}
//========================================
template <typename T>
int MyVector<T>::size() const
{
	//to-do
}
//========================================
template <typename T>
int MyVector<T>::capacity() const
{
	//to-do
}
//========================================
template <typename T>
bool MyVector<T>::empty() const
{
	//to-do
}
//========================================
template <typename T>
void MyVector<T>::push_back(T element)
{

	//to-do
}
//===============================================================================
template <typename T>
void MyVector<T>::insert(int index, T element)
{

	//to-do
}
//================================================================================
template <typename T>
void MyVector<T>::erase(int index)
{
	//to-do
}
//==================================================================================
template <typename T>
T& MyVector<T>::operator[](int index)
{
	//to-do
}
//========================================
template <typename T>
T& MyVector<T>::at(int index)
{
	//to-do
}
//========================================
template <typename T>
const T& MyVector<T>::front()
{
	//to-do
}
//========================================
template <typename T>
const T& MyVector<T>::back()
{
	//to-do
}
//======================================
template <typename T>
void MyVector<T>::shrink_to_fit()		//Reduce vector capacity to fit its size.
{
	//to-do
}
#endif
