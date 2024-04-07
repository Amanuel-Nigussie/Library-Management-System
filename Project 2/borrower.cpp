//============================================================================
// Name         : borrower.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "borrower.h"

Borrower::Borrower(string name, string id) 
{
	this->name = name;
	this->id = id;
}
//============================================================================

void Borrower::listBooks() 
{
	if(books_borrowed.size() == 0) {
		cout << "No books borrowed by " << name << "( " << id << " )" << endl;
		return;
	}

	cout << "Books borrowed by " << name << "( " << id << " ): " << endl;
	for (int i = 0; i < books_borrowed.size(); i++) {
		cout << i << ": " << books_borrowed[i]->title << endl;
	}
}