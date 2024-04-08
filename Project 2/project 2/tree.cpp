//============================================================================
// Name         : Tree.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "tree.h"
#include <iomanip>
#include <fstream>


Node::Node(string name)     //constructor
{
	this->name = name;
	this->parent = NULL;
	bookCount = 0;
}
//============================================================================

string Node::getCategory( Node* node)    
{
	string category = "";     //initialize category

	while (node->parent != NULL) {     //while parent is not null
		category = node->name + "/ " + category;     //add parent name to category
	}
	return category;
}
//============================================================================

Node::~Node() 
{
	for( int i = 0; i < children.size(); i++) {      //loop through children
		delete this->children[i];     //delete child
	}
	for( int i = 0; i < books.size(); i++) {      //loop through books
		delete this->books[i];    //delete book
	}
}
//============================================================================

Tree::Tree(string rootName)     //constructor
{
	root = new Node(rootName);
}
//============================================================================

Tree::~Tree()     //destructor
{
	delete this->root;
}
//============================================================================

Node* Tree::getRoot()     //return root of the tree
{
	return root;
}
//============================================================================

void Tree::insert(Node* node, string name)    //insert a new child to a given node of of the tree
{
	Node* new_node = new Node(name);      //new ndoe  
	new_node->parent = node;    
	node->children.push_back(new_node);    //add new node to children
}
//============================================================================
 
void Tree::remove(Node* node, string child_name)     //remove a specific child from a given node of the tree
{
	
	for (int i = 0; i < node->children.size(); i++) {     //loop through children
		if (node->children[i]->name == child_name) {     //if child name is equal to given name
			int count = node->children[i]->bookCount;     //get book count
			delete node->children[i];     //delete child
			node->children.erase(i);    //erase child
			node->children.shrink_to_fit();     
			while (node != NULL) {     //while node is not null
				updateBookCount(node, -count);     //update book count
				node = node->parent;
			}
		return;
		}
	}
	throw runtime_error("node not found");      //throw error if node not found
}
//============================================================================

bool Tree::isRoot( Node* node)    //return true if the given node is the root, false otherwise
{
	return(node == this->root);
}
//============================================================================

Node* Tree::getNode(string Path)     //given a path (category/sub-category/sub-category/..) the method should return the Node if found, false otherwise
{
	Node* current = this->root;     //initialize current to root
	stringstream s(Path);     //initialize stringstream
	string destination;     //initialize destination
	while (getline(s, destination, '/')) {     //while there is a destination
		current = getChild(current, destination);     //get child
		if (current == NULL) {     //if current is null
			return NULL;
		}
	}
	return current;     //return current
}
//============================================================================

Node* Tree::createNode(string path)     //Create a node on a given path, e.g. category/sub-category/sub-category/...
{
	Node* current = this->root;     //initialize current to root
	Node* zchild = NULL;     //initialize zchild to null
	stringstream s(path);     //initialize stringstream
	string destination;     //initialize destination
	while (getline(s, destination, '/')) {    //while there is a destination
		zchild = getChild(current, destination);     //get child
		if (zchild == NULL) {
			insert(current, destination);     //insert child
			current = current->children[current->children.size() - 1];     //update current
		}
		else {
			current = zchild;    //update current
		}
	}
	return current;     //return current
}
//============================================================================

Node* Tree::getChild(Node* ptr, string childname)      //given a node and name of a child, the method returns pointer to the child node if exist, nullptr otherwise
{
	for (int i = 0; i < ptr->children.size(); i++) {      //loop through children
		if (ptr->children[i]->name == childname) {     //if child name is equal to given name
			return ptr->children[i];    //return child
		}
	}
	return NULL;    //return null
}
//============================================================================

void Tree::updateBookCount(Node* ptr, int offset)     //update a books count by an offset e.g. +1/-1
{
	ptr->bookCount = ptr->bookCount + offset;
}
//============================================================================

Book* Tree::findBook(Node* node, string bookTitle)     //find a book in a given node, returns nullptr the book is not found
{
	for (int i = 0; i < node->books.size(); i++) {     //loop through books
		if (node->books[i]->title == bookTitle) {     //if book title is equal to given title
			return node->books[i];     //return book
		}
	}
	return NULL;    //return null
}
//============================================================================

bool Tree::removeBook(Node* node, string bookTitle)     //remove a book from a given node
{
	for (int i = 0; i < node->books.size(); i++) {     //loop through books
		if (node->books[i]->title == bookTitle) {     //if book title is equal to given title
			string choice;     //initialize choice
			cout << "Are you sure you want to delete the book " << bookTitle << "? (yes / no): ";     //display message
			while (true) {    //while true
				cin >> choice;     //get choice
				if (choice == "yes") {		 //if choice is yes
					cout << "Deleting book " << bookTitle << endl;    //display message
					delete node->books[i];     //delete book
					node->books.erase(i);     //erase book
					node->books.shrink_to_fit();
					while (node != NULL) {     //while node is not null
						updateBookCount(node, -1);     //update book count
						node = node->parent;
					}
					return true;
				}
				else if (choice == "no") {     //if choice is no
					throw runtime_error("Book not deleted");     //throw error
				}
				else {
					cout << "Invalid input! Please enter again (yes/ no): ";     //display message
				}
			}
		}
	}
	return false;
}
//============================================================================

void Tree::printAll(Node* node)     //printAll books of a node and it children recursively
{
	for (int i =0; i < node->books.size(); i++) {     //loop through books
		cout << setw(13) << left << "Title: " << node->books[i]->title << endl;
		cout << setw(13) << left << "Author(s): " << node->books[i]->author << endl;
		cout << setw(13) << left << "ISBN: " << node->books[i]->isbn << endl;
		cout << setw(13) << left << "Year: " << node->books[i]->publication_year << endl;
		cout << "-----------------------------------------------------" << endl;
	}
	for (int i = 0; i < node->children.size(); i++) {     //loop through children
		printAll(node->children[i]);
	}
}
//============================================================================

bool Tree::isLastChild(Node* ptr)    //given a pointer to node, the method should determine that the node is the last child in the children vector or not
{
	Node* parent = ptr->parent;    //initialize parent
	if (parent->children[parent->children.size() - 1] == ptr) {     //if last child
		return true;
	}
	return false;
}
//============================================================================

void Tree::print()     //Print all categories/sub-categories of a the tree
{
	print_helper("", "", root);
}
//============================================================================

void Tree::print_helper(string padding, string pointer, Node* node) //helper method for the print method
{
	if (node != nullptr) {    //if node is not null
		cout << padding << pointer << node->name << "(" << node->bookCount << ")" << endl;
		if (node != root) {
			padding += (isLastChild(node)) ? "   " : "│  ";
		}
		for (int i = 0; i < node->children.size(); i++)	//remove the file/folder from original path
		{
			string marker = isLastChild(node->children[i]) ? "└──" : "├──";
			print_helper(padding, marker, node->children[i]);
		}
	}
}
//============================================================================

int Tree::exportData(Node* node, ofstream& file)    //Export all books of a given node to a specific file.
{
	int count = 0;    //initialize count
	for (int i = 0; i < node->books.size(); i++) {      //loop through books
		Book* zbook = node->books[i];     //initialize zbook
		file << zbook->title << ',' << zbook->author << ',' << zbook->isbn << ','      //export file   
			<< zbook->publication_year << ',' << node->getCategory(node) << ','
			<< zbook->total_copies << ',' << zbook->available_copies << endl;
		count++;    //increment count
	}
	return count;     
}
//============================================================================

Book* Tree::searchBook(Node* node , string bookTitle)      //search a book in a given node and its children recursively
{   
	Book* zbook = findBook(node, bookTitle);     //initialize zbook
	if (zbook != NULL) {     //if zbook is not null
		return zbook;
	}

	for (int i = 0; i < node->children.size(); i++) {      //loop through children
		zbook = searchBook(node->children[i], bookTitle);     //search book
		if (zbook != NULL) {     //if zbook is not null
			return zbook;
		}
	}

	return NULL;     //return null
}
//============================================================================


