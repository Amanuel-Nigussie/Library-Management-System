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
	ifstream zfile;
	zfile.open(path);
	if (zfile.fail()) {
		throw runtime_error("File not found");
	}

	string line;
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
	}
}
//============================================================================


