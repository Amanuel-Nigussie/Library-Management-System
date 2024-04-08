//============================================================================
// Name         : borrower.h
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#ifndef _BORROWER_H
#define _BORROWER_H
#include "myvector.h"
#include "book.h"


class Borrower
{
private:
	string name;
	string id;
	MyVector<Book*> books_borrowed;
public:
	Borrower(string name, string id);
	friend class LCMS;
	friend class Tree;
	friend class Book;
	void listBooks();
};
#endif

