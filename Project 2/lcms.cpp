//============================================================================
// Name         : lcms.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "lcms.h"
#include <fstream>
#include <limits>

LCMS::LCMS(string name) {
	this->libTree = new Tree(name);
}
//============================================================================

LCMS::~LCMS() {
	delete this->libTree;
	for (int i = 0; i < borrowers.size(); i++) {
		delete borrowers[i];
	}
}
//============================================================================

int LCMS::import(string path) //import books from a csv file
{
	int count = 0;     // number of books imported
	ifstream zfile;     // file stream
	zfile.open(path);     // open file
	if (zfile.fail()) {
		throw runtime_error("File not found");
	}

	string line;     // line read from file
	getline(zfile, line); // skip the first line
	while (getline(zfile, line)) {    // read each line

		stringstream ss(line);    // create a string stream from the line
		string zword;

		// Title
		getline(ss, zword, ',');    // read the first word
		string ztitle = zword;
		if (ztitle[0] == '"') {    // if the first character is a quote
			getline(ss, zword, '"');
			ztitle = ztitle.substr(1) + "," + zword;
			getline(ss, zword, ',');
		}

		getline(ss, zword, ',');    // read the next word
		string zauthor = zword;
		if (zauthor[0] == '"') {    // if the first character is a quote
			getline(ss, zword, '"');
			zauthor = zauthor.substr(1) + "," + zword;
			getline(ss, zword, ',');
		}
		  
		getline(ss, zword, ',');    // read the next word
		string zisbn = zword;

		getline(ss, zword, ',');    // read the next word
		string zpublicationYear = zword;

		getline(ss, zword, ',');    // read the next word
		string zcategory = zword;   

		getline(ss, zword, ',');     // read the next word
		string ztotalCopies = zword;

		getline(ss, zword, ',');    // read the next word
		string zavailableCopies = zword;

		Book* zbook = new Book(ztitle, zauthor, zisbn, stoi(zpublicationYear), stoi(ztotalCopies), stoi(zavailableCopies));    // create a new book
		
		Node* znode = libTree->createNode(zcategory);
		znode->books.push_back(zbook);
		while (znode != NULL) {
			libTree->updateBookCount(znode, 1);
			znode = znode->parent;
		}
		count++;
	}
	zfile.close();
	cout << count << " records have been successfully imported from " << path << endl;
	return count;
}
//============================================================================

void LCMS::exportData(string path)     //export all books to a given file
{
	int count = 0;    // number of books exported
	ofstream zfile;
	zfile.open(path);     // open file
	if (zfile.fail()) {
		throw runtime_error("File not found");
	}
	zfile << "Title,Author,ISBN,Publication Year,Category,Total Copies,Available Copies" << endl;     // write the first line

	MyVector<Node*>* temp = new MyVector<Node*>(0);      // temporary vector
	temp->push_back(libTree->getRoot());      // push the root node

	while (temp->size() != 0)     // loop through the vector
	{		
		Node* p = temp->at(0);    // get the first node
		temp->erase(0);     // remove the first node
		
		for (int i = 0; i < p->books.size(); i++) {
			// Enclose title and author fields within double quotation marks
			zfile << "\"" << p->books[i]->title << "\",\"" << p->books[i]->author << "\","
				<< p->books[i]->isbn << "," << p->books[i]->publication_year << ","
				<< p->name << "," << p->books[i]->total_copies << ","
				<< p->books[i]->available_copies << endl;
			count++;
		}


		for (int i = 0; i < p->children.size(); i++) {    // loop through the children
			temp->push_back(p->children[i]);     // push the children to the vector
		} 
	}
		
	delete temp;    // delete the temporary vector
	zfile.close();     // close the file
	cout << count << " records have been successfully exported to " << path << endl;     // display message
	
}
//============================================================================

void LCMS::findAll(string category) //display all books of a category
{
	Node* znode = libTree->getNode(category);     // get the node
	if (znode == NULL) {     // if the node is not found
		throw runtime_error("Category not found");
	}
    libTree->printAll(znode);	    // print all books of the node
}
//============================================================================

void LCMS::findBook(string bookTitle) //Find a given book and display its details
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book
	if (zbook == NULL) {     // if the book is not found
		throw runtime_error("Book not found");
	}
	zbook->display();    // display the book
}
//============================================================================

void LCMS::addBook()     //add a book to the catalog
{
	string ztitle, zauthor, zisbn, zcategory, zpublicationYear, ztotalCopies, zavailableCopies;    // book details
	cout << " Enter Title: ";    
	getline(cin, ztitle);
	cout << " Enter Author(s): ";
	getline(cin, zauthor);
	cout << " Enter ISBN: ";
	getline(cin, zisbn);
	cout << " Enter Publication Year: ";
	getline(cin, zpublicationYear);
	cout << " Enter number of Total Copies: ";
	getline(cin, ztotalCopies);
	cout << " Enter number of Available Copies: ";
	getline(cin, zavailableCopies);
	cout << " Enter Category: ";
	getline(cin, zcategory);

	Book* zbook = new Book(ztitle, zauthor, zisbn, stoi(zpublicationYear) , stoi(ztotalCopies) , stoi(zavailableCopies));    // create a new book
	Node* znode = libTree->createNode(zcategory);     // create a new node
	znode->books.push_back(zbook);    // add the book to the node
	while(znode != NULL) {     // loop through the node
		libTree->updateBookCount(znode, 1);    // update the book count
		znode = znode->parent;
	}

	cout << zbook->title << " has been successfully added into the Catalog" << endl;
}
//============================================================================

void LCMS::editBook(string bookTitle)    //edit a book
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book
	
	if (zbook == NULL) {     // if the book is not found
		throw runtime_error("Book not found");
	}
	
	while (true)    
	{
		cout << setw(7) << left << "1:" << "Title" << endl    // display the options
			 << setw(7) << left << "2:" << "Author" << endl
			 << setw(7) << left << "3:" << "ISBN" << endl
			 << setw(7) << left << "4:" << "Publication Year" << endl
			 << setw(7) << left << "5:" << "Total Copies" << endl
			 << setw(7) << left << "6:" << "Available Copies" << endl
			 << setw(7) << left << "7:" << "exit" << endl
			 << "Choose the number of the field you want to edit: ";
		int choice;    // user choice
		int newPublicationYear, newTotalCopies, newAvailableCopies;
		string newTitle, newAuthor, newIsbn;
		cin >> choice;
		cin.ignore();    // ignore the newline character
		switch (choice)     // switch statement
		{
		case 1:    // edit title
			cout << "Enter new Title: ";     // prompt user to enter new title
			getline(cin, newTitle);
			zbook->title = newTitle;
			break;
		case 2:
			cout << "Enter new Author(s): ";     // prompt user to enter new author
			getline(cin, newAuthor);
			zbook->author = newAuthor;
			break;
		case 3:
			cout << "Enter new ISBN: ";     // prompt user to enter new isbn
			getline(cin, newIsbn);
			zbook->isbn = newIsbn;
			break;
		case 4:
			cout << "Enter new Publication Year: ";     // prompt user to enter new publication year
			cin >> newPublicationYear;
			zbook->publication_year = newPublicationYear;
			break;
		case 5:
			cout << "Enter new Total Copies: ";     // prompt user to enter new total copies
			cin >> newTotalCopies;
			zbook->total_copies = newTotalCopies;
			break;
		case 6:
			cout << "Enter new Available Copies: ";     // prompt user to enter new available copies
			cin >> newAvailableCopies;
			zbook->available_copies = newAvailableCopies;
			break;
		case 7:
			return;
		default:
			cout << "Invalid choice" << endl;     // display message
			break;
		}
	}

}
//============================================================================

void LCMS::borrowBook(string bookTitle)     //borrow a book
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book

	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->available_copies == 0) {     // if no available copies
		throw runtime_error("No available copies");
	}
	zbook->available_copies--;    // decrement the available copies

	string zname, zid;    // name and id of the borrower

	cout << " Enter borrower's name  : ";    // prompt user to enter borrower's name
	getline(cin, zname);
	cout << " Enter borrower's ID    : ";     // prompt user to enter borrower's id
	getline(cin, zid);

	Borrower* zborrower = new Borrower(zname, zid);    // create a new borrower
	zborrower->books_borrowed.push_back(zbook);     // add the book to the borrower
    
	borrowers.push_back(zborrower);     // add the borrower to the list of borrowers
    zbook->currentBorrowers.push_back(zborrower);     // add the borrower to the list of current borrowers
	zbook->allBorrowers.push_back(zborrower);     // add the borrower to the list of all borrowers
   

	cout << "Book " << zbook->title << " has been successfully issued to " << zborrower->name << endl;    // display message

}
//============================================================================

void LCMS::returnBook(string bookTitle)    //return a book
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->available_copies == zbook->total_copies) {     // if no copies borrowed
		throw runtime_error("No copies borrowed");
	}

	string zname, zid;      // name and id of the borrower
	cout << " Enter borrower's name  : ";
	cin >> zname;      // read the name
	cout << " Enter borrower's ID    : ";
	cin >> zid;

	Borrower* zborrower = NULL;     // borrower
	for (int i = 0; i < zbook->currentBorrowers.size(); i++) {     // loop through current borrowers
		if (zbook->currentBorrowers[i]->id == zid && zbook->currentBorrowers[i]->name == zname) {	    // if it is the same	
			zborrower = borrowers[i];
			zbook->currentBorrowers.erase(i);
			break;
		}
	}
	if (zborrower == NULL) {
		throw runtime_error("Borrower not found");
	}

	zbook->available_copies++;     // increment the available copies
	cout << "Book " << zbook->title << " has been successfully returned by " << zborrower->name << endl;
}
//============================================================================

void LCMS::listCurrentBorrowers(string bookTitle)     //list current borrowers of a book
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->currentBorrowers.size() == 0) {    // if no current borrowers
		throw runtime_error("No current borrowers");
	}

	for (int i = 0; i < zbook->currentBorrowers.size(); i++) {     // loop through current borrowers
		cout << "1:  " << zbook->currentBorrowers[i]->name << " (" << zbook->currentBorrowers[i]->id << ")" << endl;     // display the borrower
	}
}
//============================================================================

void LCMS::listAllBorrowers(string bookTitle)     //list all borrowers that have ever borrowed a book
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);     // search for the book
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->allBorrowers.size() == 0) {     // if no borrowers
		throw runtime_error("No borrowers");
	}

	for (int i = 0; i < zbook->allBorrowers.size(); i++) {     // loop through all borrowers
		cout << "1:  " << zbook->allBorrowers[i]->name << " (" << zbook->allBorrowers[i]->id << ")" << endl;
	}
}
//============================================================================

void LCMS::listBooks(string borrower_name_id)     // display books a borrower has ever borrowed
{
	stringstream ss(borrower_name_id);     // create a string stream
	string zname, zid;     // name and id of the borrower
	getline(ss, zname, ',');     // read the name
	getline(ss, zid, ',');     // read the id

	Borrower* zborrower = NULL;     // borrower
	for (int i = 0; i < borrowers.size(); i++) {     // loop through borrowers
		if (borrowers[i]->name == zname && borrowers[i]->id == zid) {
			zborrower = borrowers[i];     // get the borrower
			break;
		}
	}
	if (zborrower == NULL) {      // if the borrower is not found
		throw runtime_error("Borrower not found");     // display message
	}

	zborrower->listBooks();     // list books borrowed by the borrower
}
//============================================================================

void LCMS::removeBook(string bookTitle)     //remove a book from the catalog
{
	MyVector<Node*>* temp = new MyVector<Node*>(0);     //temporary vector
	temp->push_back(libTree->getRoot());    //push the root node

	while (temp->size() != 0)     //loop through the vector
	{
		Node* p = temp->at(0);     //get the first node
		temp->erase(0);     //remove the first node
			
		if (libTree->removeBook(p, bookTitle)) {     //if the book is found
			delete temp;     //delete the temporary vector
			cout << bookTitle << " has been successfully deleted." << endl;     //display message
			return;     //exit the function
		}

		for (int i = 0; i < p->children.size(); i++) {     //loop through the children
			temp->push_back(p->children[i]);	//push the children to the vector
		}
	}
	delete temp;     //delete the temporary vector
    throw runtime_error("Book not found");    	
}
//============================================================================

void LCMS::addCategory(string category)     //add a category in the catalog
{
	Node* znode = libTree->createNode(category);    //create a node
	cout << category << " has been successfully created" << endl;     //display message
}
//============================================================================

void LCMS::findCategory(string category)     //find a category in the catalog
{
	Node* znode = libTree->getNode(category);      //get the node
	if (znode == NULL) {     //if the node is not found
		throw runtime_error("No such category has been found!");
	}
	cout << "Category " << category << " has been found in the catalog" << endl;     //display message
}
//============================================================================

void LCMS::removeCategory(string category)     //remove a category from the catalog 
{
	Node* znode = libTree->getNode(category);      //get the node
	string zname = znode->name;     //get the name of the node
	if (znode == NULL) {      //if the node is not found
		throw runtime_error("No such category has been found");
	}

	Node* zparent = znode->parent;      //get the parent node
	libTree->remove(zparent, znode->name);      //remove the node
	cout << zname << " has been successfully deleted" << endl;      //display message
}
//============================================================================

void LCMS::editCategory(string category)     //edit a category from the catalog
{
	Node* znode = libTree->getNode(category);      //get the node
	if (znode == NULL) {      //if the node is not found
		throw runtime_error("No such category has been found");     //display message
	}

	string newCategory;     //new category name
	cout << "Enter new category name: ";      //prompt user to enter new category name
	cin >> newCategory;     //read new category name

	znode->name = newCategory;     //update the category name
	cout << category << " has been successfully renamed to " << newCategory << endl;     //display message
}
//============================================================================

