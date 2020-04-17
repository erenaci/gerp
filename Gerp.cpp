/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* Gerp.cpp
* Class implementation of the Gerp class 
***********************************************/

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include "HashTable.h"
#include "Gerp.h"
#include "stringProcessing.h"

using namespace std;

// Function storeFiles
// Parameters: DirNode *curr, string path, vector<string> &files
// Returns: nothing
// Does: Traverse the FSTree and store all the files into files vector
void Gerp::storeFiles (DirNode *curr, string path, vector<string> &files)
{
	if (curr == nullptr) {
		return;
	}
	for (int i = 0; i < curr -> numSubDirs(); i++) {	
		storeFiles(curr -> getSubDir(i), 
			path + "/" + curr -> getSubDir(i) -> getName(), files);
	}
	for (int j = 0; j < curr -> numFiles(); j++) {
		files.push_back(path + "/" + curr -> getFile(j));
	}
}

// Function readIn
// Parameters: vector<string> files
// Returns: nothing
// Does: reads in the files and store the words and their information
// in hash table
void Gerp::readIn(vector<string> files)
{
	string line, word, stripped, clean;
	vector <string> found;
	for (size_t i = 0; i < files.size(); i++) {
		ifstream infile;
		infile.open(files[i]);
		if(not infile.is_open()) {
			cerr << "Error.\n";
		}
		int lineNum = 0;
		while(getline(infile, line)) {
			found.clear();
			stringstream ss(line);
			MoreInfo deets(line, lineNum, files[i]);
			moreInfo.push_back(deets);
			while(ss >> word) {
				stripped = stripNonAlphaNum(word);
				if (!alreadyFound(found, stripped)) {
					found.push_back(stripped);
					Info infos(stripped, moreInfo.size() - 1);
					clean = toLower(stripped);
					ht.insert(clean, infos);
				}
			}
			lineNum++;
		}
	}
}

// Function alreadyFound
// Parameters: vector<string> found, string curr
// Returns: boolean value
// Does: checks whether the clean version of the word was already
// read in or not
bool Gerp::alreadyFound (vector<string> found, string curr)
{
	for (size_t i = 0; i < found.size(); i++) {
		if (curr == found[i])
			return true;
	}

	return false;
}

// Function reportQuery
// Parameters: string query, bool caseSensitive, ofstream &out, 
// vector<MoreInfo> &deets
// Returns: nothing
// Does: calls search function in hash table class
void Gerp::reportQuery(string query, bool caseSensitive, ofstream &out,
	vector<MoreInfo> &deets)
{
	ht.search(query, caseSensitive, out, deets);
}

// Function run
// Parameters: ofstream &outfile
// Returns: nothing
// Does: run the user interaction portion of gerp
void Gerp::run(ofstream &outfile)
{
	string command, line, newWord;
	vector <string> commands;
	cout << "Query? ";
	do {
		getline(cin, line);
		stringstream ss(line);
		while (ss >> command) {
			commands.push_back(command);
		}
		for (size_t i = 0; i < commands.size(); i++) {
			if (commands[i] == "@i" or commands[i] == "@insensitive") {
				newWord = stripNonAlphaNum(commands[i+1]);
				reportQuery(newWord, false, outfile, moreInfo);
				i = i + 1;
			}
			else if (commands[i] == "@f") {
				ofstream outfile2(commands[i + 1]);
		 		outfile.swap(outfile2);
		 		outfile2.close();
		 		i = i + 1;
			}
			else if (commands[i] == "@q") {
				return;
			}
			else {
				newWord = stripNonAlphaNum(commands[i]);
				reportQuery(newWord, true, outfile, moreInfo);
			}
			cout << endl << "Query? ";
		}
		commands.clear();
	} while(commands[0] != "@q" and commands[0] != "@quit");
}
