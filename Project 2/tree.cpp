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

Node::Node(string name) 
{
	this->name = name;
	this->parent = NULL;
	bookCount = 0;
}
//============================================================================

string Node::getCategory( Node* node) 
{
	string category = "";

	while (node->parent != NULL) {
		category = node->name + "/ " + category;
	}
}
//============================================================================

Node::~Node() 
{
	for( int i = 0; i < children.size(); i++) {
		delete this->children[i];
	}
	for( int i = 0; i < books.size(); i++) {
		delete this->books[i];
	}
}
//============================================================================

Tree::Tree(string rootName) 
{
	root = new Node(rootName);
}
//============================================================================

Tree::~Tree() 
{
	delete this->root;
}
//============================================================================

Node* Tree::getRoot() 
{
	return root;
}
//============================================================================

void Tree::insert(Node* node, string name)
{
	Node* new_node = new Node(name);     
	new_node->parent = node;    
	node->children.push_back(new_node); 
}
//============================================================================

void Tree::remove(Node* node, string child_name)
{
	for (int i = 0; i < node->children.size(); i++) {
		if (node->children[i]->name == child_name) {
			updateBookCount(node, -node->children[i]->bookCount);
			delete node->children[i];
	        node->children.erase(i);
			node->children.shrink_to_fit();
			return;
		}
	}
	cout << "Child not found" << endl;
}
//============================================================================

bool Tree::isRoot( Node* node)
{
	return(node == this->root);
}
//============================================================================

Node* Tree::getNode(string Path)
{
	Node* current = this->root;
	stringstream s(Path);
	string destination;
	while (getline(s, destination, '/')) {
		bool found = false;
		for (int i = 0; i < current->children.size(); i++) {
			if (current->children[i]->name == destination) {
				current = current->children[i];
				found = true;
				break;
			}
		}
		if (!found) {
			cout << "Node not found" << endl;
			return NULL;
		}
	}
	return current;
}
//============================================================================

Node* Tree::createNode(string path)
{
	Node* current = this->root;
	stringstream s(path);
	string destination;
	while (getline(s, destination, '/')) {
		bool found = false;
		for (int i = 0; i < current->children.size(); i++) {
			if (current->children[i]->name == destination) {
				current = current->children[i];
				found = true;
				break;
			}
		}
		if (!found) {
			insert(current, destination);
			current = current->children[current->children.size() - 1];
		}
	}
	return current;
}
//============================================================================

Node* Tree::getChild(Node* ptr, string childname) 
{
	for (int i = 0; i < ptr->children.size(); i++) {
		if (ptr->children[i]->name == childname) {
			return ptr->children[i];
		}
	}
	return NULL;
}
//============================================================================

void Tree::updateBookCount(Node* ptr, int offset)
{
	ptr->bookCount = ptr->bookCount + offset;
}
//============================================================================

Book* Tree::findBook(Node* node, string bookTitle)
{
	for (int i = 0; i < node->books.size(); i++) {
		if (node->books[i]->title == bookTitle) {
			return node->books[i];
		}
	}
	return NULL;
}
//============================================================================

bool Tree::removeBook(Node* node, string bookTitle)
{
	for (int i = 0; i < node->books.size(); i++) {
		if (node->books[i]->title == bookTitle) {
			delete node->books[i];
			node->books.erase(i);
			node->books.shrink_to_fit();
			updateBookCount(node, -1);
			return true;
		}
	}
	return false;
}
//============================================================================

void Tree::printAll(Node* node)
{
	for (int i =0; i < node->books.size(); i++) {
		cout << setw(13) << left << "Title: " << node->books[i]->title << endl;
		cout << setw(13) << left << "Author(s): " << node->books[i]->author << endl;
		cout << setw(13) << left << "ISBN: " << node->books[i]->isbn << endl;
		cout << setw(13) << left << "Year: " << node->books[i]->publication_year << endl;
		cout << "-----------------------------------------------------" << endl;
	}
	for (int i = 0; i < node->children.size(); i++) {
		printAll(node->children[i]);
	}
}
//============================================================================

bool Tree::isLastChild(Node* ptr)
{
	Node* parent = ptr->parent;
	if (parent->children[parent->children.size() - 1] == ptr) {
		return true;
	}
	return false;
}
//============================================================================

void Tree::print()
{
	print_helper("", "", root);
}
//============================================================================

void Tree::print_helper(string padding, string pointer, Node* node) //helper method for the print method
{
	if (node != nullptr) {
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

int Tree::exportData(Node* node, ofstream& file)
{
	int count = 0;
	for (int i = 0; i < node->books.size(); i++) {
		file << node->books[i]->title << ","
			 << node->books[i]->author << ","
			 << node->books[i]->isbn << "," 
			 << node->books[i]->publication_year << "," 
			 << node->getCategory(node) << node->name << ","
			 << node->books[i]->total_copies << "," 
			 << node->books[i]->available_copies << endl;
		count++;
	}
}
//============================================================================

Book* Tree::searchBook(Node* node , string bookTitle)
{
	Book* zbook = findBook(node, bookTitle);
	if (zbook != NULL) {
		return zbook;
	}

	for (int i = 0; i < node->children.size(); i++) {
		searchBook(node->children[i], bookTitle);
	}

	return NULL;
}
//============================================================================