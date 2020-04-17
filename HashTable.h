/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* HashTable.h
* Class interface for HashTable class
***********************************************/

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "Infos.h"

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

using namespace std;

class HashTable
{
	public:
		//Big Three
		HashTable();
		HashTable(const HashTable &source);
		HashTable &operator=(const HashTable &source);
		~HashTable();

		void insert(string toAdd, Info toAddInfo);
		void search(string toSearch, bool caseSensitive,
		 ofstream &out, vector<MoreInfo> &deets);

	private:
		struct Word
		{
			string clean;
			vector<Info> infos;
		};
		constexpr static const float LOAD_FACTOR = 0.75;
		int tableSize;
		int numWords;
		vector<Word> *table;
		void expand();
};
#endif
