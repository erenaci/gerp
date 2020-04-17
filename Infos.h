/**********************************************
* Comp 15 - Fall 2019
* Project 2
* Erena Inoue
* 11/19/19
* Info.h
* Declaration of multiple structs 
***********************************************/

#include <string>

#ifndef INFOS_H_
#define INFOS_H_

using namespace std;

struct MoreInfo
{
	MoreInfo (string _line, int _lineNum, string _path){
		line = _line;
		lineNum = _lineNum + 1;
		path = _path;
	}
	string line;
	int lineNum;
	string path;
};

struct Info
{
	Info(string word, size_t num) {
		raw = word;
		index = num;
	}
	string raw;
	size_t index;
}; 
#endif
