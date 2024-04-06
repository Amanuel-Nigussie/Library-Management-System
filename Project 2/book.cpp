//============================================================================
// Name         : book.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "book.h"
#include <iomanip>

Book::Book(std::string title, std::string author, std::string isbn, int publication_year, int total_copies, int available_copies) {
	this->title = title;
	this->author = author;
	this->isbn = isbn;
	this->publication_year = publication_year;
	this->total_copies = total_copies;
	this->available_copies = available_copies;
}

void Book::display() {
	cout << "Book found in the library: " << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << setw(18) << left << "Title: " << title << endl;
	cout << setw(18) << left << "Author(s): " << author << endl;
	cout << setw(18) << left << "ISBN: " << isbn << endl;
	cout << setw(18) << left << "Year: " << publication_year << endl;
	cout << setw(18) << left << "Total Copies: " << total_copies << endl;
	cout << setw(18) << left << "Available Copies: " << available_copies << endl;
	cout << "--------------------------------------------------------------" << endl;
 }

