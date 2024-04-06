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
	getline(zfile, line);
	while (getline(zfile, line)) {
		stringstream line;
		string ztitle, zauthor, zisbn, zpublicationYear, zcategory, ztotalCopies, zavailableCopies;
		getline(line, ztitle, ',');
		getline(line, zauthor, ',');
		getline(line, zisbn, ',');
		getline(line, zpublicationYear, ',');
		getline(line, zcategory, ',');
		getline(line, ztotalCopies, ',');
		getline(line, zavailableCopies, ',');

		Book* zbook = new Book(ztitle, zauthor, zisbn, stoi(zpublicationYear), stoi(ztotalCopies), stoi(zavailableCopies));
		libTree->createNode(zcategory);
		Node* znode = libTree->getNode(zcategory);
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

	MyVector<Node*>* temp;  
	temp->push_back(libTree->getRoot());  

	while (temp->size() != 0)
	{
		for (int n = temp->size(); n > 0; n--) {
			// Dequeue an item from queue and print it
			Node* p = temp->at(0);
			delete temp->at(0);
			temp->erase(0);
			temp->shrink_to_fit();
			count += libTree->exportData(p, zfile);

			for (int i = 0; i < p->children.size(); i++)
				temp->push_back(p->children[i]);
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

}