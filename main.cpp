/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* main.cpp
***********************************************/

#include <functional>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "FSTree.h"
#include "Gerp.h"

using namespace std;

int main (int argc, char *argv[])
{
	if (argc == 3) {
		ofstream outfile; 
		outfile.open(argv[2]);
		Gerp g;
		vector<string> storage;
		FSTree myFST = FSTree(argv[1]);
		DirNode *root = myFST.getRoot();
		g.storeFiles(root, argv[1], storage);
		g.readIn(storage);
		g.run(outfile);
		cout << endl << "Goodbye! Thank you and have a nice day. \n";
		outfile.close();
		myFST.burnTree();
	}
	else 
		cerr << "Usage: gerp directory output_file\n";
	return 0;
}
