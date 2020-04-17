/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* Gerp.h
* Class interface for the Gerp class
***********************************************/
#include <string>
#include "HashTable.h"
#include "FSTree.h"
#include "Infos.h"

#ifndef GERP_H_
#define GERP_H_

using namespace std;

class Gerp
{
	public:
		vector <MoreInfo> moreInfo;
		void storeFiles (DirNode *curr, string path, vector<string> &files);
		void readIn(vector<string> files);
		void reportQuery(string query, bool caseSensitive, ofstream &out,
			vector<MoreInfo> &deets);
		void run(ofstream &outfile);
	private:
		bool alreadyFound (vector<string> found, string curr);
		HashTable ht;
};
#endif
