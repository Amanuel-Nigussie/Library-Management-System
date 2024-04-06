//============================================================================
// Name         : Tree.cpp
// Author       : Amanuel Nigussie Demeke
// Version      : 1.0
// Date Created : April 06, 2024
// Date Modified:
// Description  : 
//============================================================================

#include "tree.h"

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

	if( node->parent == NULL) {
		return category;
	}
	while (node->parent != NULL) {
		category = node->parent->name + "/ " + category;
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
