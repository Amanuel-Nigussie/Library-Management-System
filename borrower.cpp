//============================================================================
// Name         : borrower.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "borrower.h"

Borrower::Borrower(string name, string id)     //constructor
{
	this->name = name;    //initialize name
	this->id = id;    //initialize id
}
//============================================================================

void Borrower::listBooks()   //list books borrowed by a borrower
{
	if(books_borrowed.size() == 0) {    //if no books borrowed
		cout << "No books borrowed by " << name << "(" << id << ")" << endl;    //display message
		return;
	}

	cout << "Books borrowed by " << name << " (" << id << "): " << endl;    //display message
	for (int i = 0; i < books_borrowed.size(); i++) {    //loop through books borrowed
		cout << i+1 << ": " << books_borrowed[i]->title << endl;
	}
}