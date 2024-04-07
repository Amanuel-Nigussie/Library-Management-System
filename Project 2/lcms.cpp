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
	int count = 0;
	ifstream zfile;
	zfile.open(path);
	if (zfile.fail()) {
		throw runtime_error("File not found");
	}

	string line;
	while (getline(zfile, line)) {

		stringstream ss(line);
		string zword;

		// Title
		getline(ss, zword, ',');
		string ztitle = zword;
		if (ztitle[0] == '"') {
			getline(ss, zword, '"');
			ztitle = ztitle.substr(1) + "," + zword;
			getline(ss, zword, ',');
		}

		getline(ss, zword, ',');
		string zauthor = zword;
		if (zauthor[0] == '"') {
			getline(ss, zword, '"');
			zauthor = zauthor.substr(1) + "," + zword;
			getline(ss, zword, ',');
		}

		getline(ss, zword, ',');
		string zisbn = zword;

		getline(ss, zword, ',');
		string zpublicationYear = zword;

		getline(ss, zword, ',');
		string zcategory = zword;

		getline(ss, zword, ',');
		string ztotalCopies = zword;

		getline(ss, zword, ',');
		string zavailableCopies = zword;

		Book* zbook = new Book(ztitle, zauthor, zisbn, stoi(zpublicationYear), stoi(ztotalCopies), stoi(zavailableCopies));
		
		Node* znode = libTree->createNode(zcategory);
		znode->books.push_back(zbook);
		count++;
	}
	zfile.close();
	return count;
}
//============================================================================

void LCMS::exportData(string path)     //export all books to a given file
{
	int count = 0;
	ofstream zfile;
	zfile.open(path);
	if (zfile.fail()) {
		throw runtime_error("File not found");
	}
	zfile << "Title,Author,ISBN,Publication Year,Category,Total Copies,Available Copies" << endl;

	MyVector<Node*>* temp = new MyVector<Node*>(0);  
	temp->push_back(libTree->getRoot());  

	while (temp->size() != 0)
	{
		for (int n = temp->size(); n > 0; n--) {
			
			Node* p = temp->at(0);
			temp->erase(0);
			count += libTree->exportData(p, zfile);

			for (int i = 0; i < p->children.size(); i++) {
				temp->push_back(p->children[i]);
			}
		}
	}
	delete temp;
	zfile.close();
	cout << count << " records have been successfully exported to " << path << endl;
	
}
//============================================================================

void LCMS::findAll(string category) //display all books of a category
{
	Node* znode = libTree->getNode(category);
	if (znode == NULL) {
		throw runtime_error("Category not found");
	}
    libTree->printAll(znode);	
}
//============================================================================

void LCMS::findBook(string bookTitle) //Find a given book and display its details
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}
	zbook->display();
}
//============================================================================

void LCMS::addBook()
{
	string ztitle, zauthor, zisbn, zcategory;
	int zpublicationYear, ztotalCopies, zavailableCopies;

	cout << " Enter Title: ";
	cin >> ztitle;
	cout << " Enter Author(s): ";
	cin >> zauthor;
	cout << " Enter ISBN: ";
	cin >> zisbn;
	cout << " Enter Publication Year: ";
	cin >> zpublicationYear;
	cout << " Enter number of Total Copies: ";
	cin >> ztotalCopies;
	cout << " Enter number of Available Copies: ";
	cin >> zavailableCopies;
	cout << " Enter Category: ";
	cin >> zcategory;

	Book* zbook = new Book(ztitle, zauthor, zisbn, zpublicationYear, ztotalCopies, zavailableCopies);
	Node* znode = libTree->createNode(zcategory);
	znode->books.push_back(zbook);
	while(znode != NULL) {
		libTree->updateBookCount(znode, 1);
		znode = znode->parent;
	}

	cout << zbook->title << " has been successfully added into the Catalog" << endl;
}
//============================================================================

void LCMS::editBook(string bookTitle)
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);
	
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}
	
	while (true)
	{
		cout << setw(7) << left << "1:" << "Title" << endl
			 << setw(7) << left << "2:" << "Author" << endl
			 << setw(7) << left << "3:" << "ISBN" << endl
			 << setw(7) << left << "4:" << "Publication Year" << endl
			 << setw(7) << left << "5:" << "Total Copies" << endl
			 << setw(7) << left << "6:" << "Available Copies" << endl
			 << setw(7) << left << "7:" << "exit" << endl
			 << "Choose the number of the field you want to edit: ";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter new Title: ";
			cin >> zbook->title;
			break;
		case 2:
			cout << "Enter new Author(s): ";
			cin >> zbook->author;
			break;
		case 3:
			cout << "Enter new ISBN: ";
			cin >> zbook->isbn;
			break;
		case 4:
			cout << "Enter new Publication Year: ";
			cin >> zbook->publication_year;
			break;
		case 5:
			cout << "Enter new Total Copies: ";
			cin >> zbook->total_copies;
			break;
		case 6:
			cout << "Enter new Available Copies: ";
			cin >> zbook->available_copies;
			break;
		case 7:
			return;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
	}

}
//============================================================================

void LCMS::borrowBook(string bookTitle)
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);

	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->available_copies == 0) {
		throw runtime_error("No available copies");
	}
	zbook->available_copies--;

	string zname, zid;

	cout << " Enter borrower's name  : ";
	cin >> zname;
	cout << " Enter borrower's ID    : ";
	cin >> zid;

	Borrower* zborrower = new Borrower(zname, zid);
	zborrower->books_borrowed.push_back(zbook);
    
	borrowers.push_back(zborrower);
    zbook->currentBorrowers.push_back(zborrower);
	zbook->allBorrowers.push_back(zborrower);
   

	cout << "Book " << zbook->title << "has been successfully issued to " << zborrower->name << endl;

}
//============================================================================

void LCMS::returnBook(string bookTitle)
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->available_copies == zbook->total_copies) {
		throw runtime_error("No copies borrowed");
	}

	string zname, zid;
	cout << " Enter borrower's name  : ";
	cin >> zname;
	cout << " Enter borrower's ID    : ";
	cin >> zid;

	Borrower* zborrower = NULL;
	for (int i = 0; i < zbook->currentBorrowers.size(); i++) {
		if (zbook->currentBorrowers[i]->id == zid && zbook->currentBorrowers[i]->name == zname) {
			zborrower = borrowers[i];
			zbook->currentBorrowers.erase(i);
			break;
		}
	}
	if (zborrower == NULL) {
		throw runtime_error("Borrower not found");
	}

	zbook->available_copies++;
	cout << "Book " << zbook->title << " has been successfully returned by " << zborrower->name << endl;
}
//============================================================================

void LCMS::listCurrentBorrowers(string bookTitle)
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->currentBorrowers.size() == 0) {
		throw runtime_error("No current borrowers");
	}

	for (int i = 0; i < zbook->currentBorrowers.size(); i++) {
		cout << "1:  " << zbook->currentBorrowers[i]->name << " (" << zbook->currentBorrowers[i]->id << ")" << endl;
	}
}
//============================================================================

void LCMS::listAllBorrowers(string bookTitle)
{
	Book* zbook = libTree->searchBook(libTree->getRoot(), bookTitle);
	if (zbook == NULL) {
		throw runtime_error("Book not found");
	}

	if (zbook->allBorrowers.size() == 0) {
		throw runtime_error("No borrowers");
	}

	for (int i = 0; i < zbook->allBorrowers.size(); i++) {
		cout << "1:  " << zbook->allBorrowers[i]->name << " (" << zbook->allBorrowers[i]->id << ")" << endl;
	}
}
//============================================================================

void LCMS::listBooks(string borrower_name_id)
{
	stringstream ss(borrower_name_id);
	string zname, zid;
	getline(ss, zname, ',');
	getline(ss, zid, ',');

	Borrower* zborrower = NULL;
	for (int i = 0; i < borrowers.size(); i++) {
		if (borrowers[i]->name == zname || borrowers[i]->id == zid) {
			zborrower = borrowers[i];
			break;
		}
	}
	if (zborrower == NULL) {
		throw runtime_error("Borrower not found");
	}

	zborrower->listBooks();
}
//============================================================================

void LCMS::removeBook(string bookTitle)
{
	MyVector<Node*>* temp = new MyVector<Node*>(0);
	temp->push_back(libTree->getRoot());
	bool removed = false;

	while (temp->size() != 0)
	{
		for (int n = temp->size(); n > 0; n--) {

			Node* p = temp->at(0);
			temp->erase(0);
			
			removed = libTree->removeBook(p, bookTitle);

			if (removed) {
				while(p->parent != NULL) {
					libTree->updateBookCount(p, -1);
					p = p->parent;
				}

				for (int i = 0; i < temp->size(); i++) {
					temp->erase(i);
				}
				delete temp;
				cout << bookTitle << " has been successfully deleted" << endl;
				return;
			}

			for (int i = 0; i < p->children.size(); i++) {
				temp->push_back(p->children[i]);
			}
		}
	}
	delete temp;
    throw runtime_error("Book not found");	
}
//============================================================================

void LCMS::addCategory(string category)
{
	Node* znode = libTree->createNode(category);
	cout << category << " has been successfully created" << endl;
}
//============================================================================

void LCMS::findCategory(string category)
{
	Node* znode = libTree->getNode(category);
	if (znode == NULL) {
		throw runtime_error("No such category has been found");
	}
	cout << "Category" << category << " has been found in the catalog" << endl;
}
//============================================================================

void LCMS::removeCategory(string category)
{
	Node* znode = libTree->getNode(category);
	if (znode == NULL) {
		throw runtime_error("No such category has been found");
	}

	Node* zparent = znode->parent;
	libTree->remove(zparent, category);
	cout << category << " has been successfully deleted" << endl;
}
//============================================================================

void LCMS::editCategory(string category)
{
	Node* znode = libTree->getNode(category);
	if (znode == NULL) {
		throw runtime_error("No such category has been found");
	}

	string newCategory;
	cout << "Enter new category name: ";
	cin >> newCategory;

	znode->name = newCategory;
	cout << category << " has been successfully renamed to " << newCategory << endl;
}
//============================================================================

