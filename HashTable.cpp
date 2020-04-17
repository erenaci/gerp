/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* HashTable.cpp
* Class implmentation of the HashTable class
***********************************************/

#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "HashTable.h"
#include "stringProcessing.h"

using namespace std;

// Default constructor 
// Parameters: none
// Does: Initializes all private variables
HashTable::HashTable()
{
	tableSize = 10;
	numWords = 0;

	table = new vector<Word> [tableSize];
}

// Assignment Overload Operator
// Parameters: const Tree &source
// Does: Sets the value of an existing object using 
// the value of an old one.
HashTable& HashTable::operator=(const HashTable &source) {
    // Check for self assignment
    if (this == &source)
        return *this;
    // Delete dynamic memory in current object
    delete []table;
    // Deep copy
    tableSize = source.tableSize;
    numWords = source.numWords;
    table = new vector<Word> [tableSize];
    for (int i = 0; i < tableSize; i++) {
    	table[i] = source.table[i];
	}

    return *this;
}

// Copy constructor 
// Parameters: const Tree &source
// Does: Deep copies each data member, initializes a
// 'new' object using an old one
HashTable::HashTable(const HashTable &source)
{
	tableSize = source.tableSize;
    numWords = source.numWords;
    table = new vector<Word> [tableSize];
    for (int i = 0; i < tableSize; i++) {
    	table[i] = source.table[i];
	}
}

// Destructor
// Parameters: none
// Does: Frees all allocated memory
HashTable::~HashTable()
{
	delete []table;
	table = nullptr;
}

// Function insert
// Parameters: string toAdd, Info toAddInfo
// Returns: nothing
// Does: Inserts the words and its inormation in the hash table
void HashTable::insert(string toAdd, Info toAddInfo)
{
	float myLoadFactor = numWords/tableSize;
	if (myLoadFactor > LOAD_FACTOR) {
		expand();
	}
	int index = hash<string>{}(toAdd) % tableSize;

	for (size_t i = 0; i < table[index].size(); i++) {
		if (table[index][i].clean == toAdd) {
			table[index][i].infos.push_back(toAddInfo);
			return;
		}
	}

	Word toInsert;
	toInsert.clean = toAdd;
	toInsert.infos.push_back(toAddInfo);
	table[index].push_back(toInsert);
	numWords++;
}

// Function search
// Parameters: string toSearch, bool caseSensitive, ofstream &out, 
// vector<MoreInfo> &deets
// Returns: nothing
// Does: reports the query by searching through the hash table
void HashTable::search(string toSearch, bool caseSensitive, ofstream &out,
	vector<MoreInfo> &deets)
{
	bool found = false;
	string toSearchClean = toLower(toSearch);
	toSearchClean = stripNonAlphaNum(toSearchClean);
	int index = hash<string>{}(toSearchClean) % tableSize;
	for (size_t i = 0; i < table[index].size(); i++) {
		if (table[index][i].clean == toSearchClean) {
			if (caseSensitive == false) {
				found = true;
				for (size_t x = 0; x < table[index][i].infos.size(); x++) {
					int at1 = table[index][i].infos[x].index;
					out << deets[at1].path << ":" << deets[at1].lineNum << 
					": " << deets[at1].line << endl;
				}
			}
			else {
				for (size_t y = 0; y < table[index][i].infos.size(); y++) {
					if (table[index][i].infos[y].raw == toSearch) {
						found = true;
						int at2 = table[index][i].infos[y].index;
						out << deets[at2].path << ":" << deets[at2].lineNum << 
						": " << deets[at2].line << endl;
					}
				}
			}
		}
	}
	if (found == false and caseSensitive == false)
		out << toSearch << " Not Found.\n";
	else if (found == false and caseSensitive == true)
		out << toSearch << " Not Found. Try with @insensitive or @i.\n";
}

// Function expand
// Parameters: none
// Returns: nothing
// Does: expands the hash table when needed
void HashTable::expand()
{
	int newTableSize = tableSize*2 + 1;
	vector<Word> *newTable = new vector<Word>[newTableSize];
	for (int i = 0; i < tableSize; i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			int index = hash<string>{}(table[i][j].clean) % newTableSize;
			newTable[index].push_back(table[i][j]);
		}
	}
	delete []table;
	table = newTable;
	tableSize = newTableSize;
}
