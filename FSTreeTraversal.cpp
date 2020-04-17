/**********************************************
* Comp 15 - Fall 2019
* HW 5
* Erena Inoue
* 11/18/19
* sortAlgs.h
* Class implementation of sortAlgs class
***********************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "DirNode.h"
#include "FSTree.h"

using namespace std;

void storeFiles (DirNode *curr, string path, vector<string> &files);

int main (int argc, char *argv[])
{
	if (argc == 2) {
		vector<string> toStore;
		FSTree myFST = FSTree(argv[1]);
		DirNode *root = myFST.getRoot();
		storeFiles(root, argv[1], toStore);
		for (size_t i = 0; i < toStore.size(); i++) {
			cout << toStore[i] << endl;
		}
	}
	else {
		cerr << "Usage: ./treeTraversal directory" << endl;
	}
	return 0;
}

void storeFiles (DirNode *curr, string path, vector<string> &files)
{
	if (curr == nullptr) {
		return;
	}
	for (int i = 0; i < curr -> numSubDirs(); i++) {	
		storeFiles(curr -> getSubDir(i), 
			path + "/" + curr -> getSubDir(i) -> getName(), files);
	}
	for (int j = 0; j < curr -> numFiles(); j++) {
		// path = path + "/" + curr -> getFile(j);
		files.push_back(path + "/" + curr -> getFile(j));
	}
}
