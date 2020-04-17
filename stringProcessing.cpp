/**********************************************
* Comp 15 - Fall 2019
* Project 2 Part 1
* Erena Inoue
* 11/18/19
* stringProcessing.h
* Function definition for stringProcessing.cpp
***********************************************/

#include <iostream>
#include <string>
#include <sstream>
#include "stringProcessing.h"

using namespace std;

// Function stripNonAlphaNum
// Parameters: string word
// Returns: string
// Does: stripes the leading and trailing non alpha and
// numeric characters of a word
string stripNonAlphaNum(string word)
{
	int originalSize = word.length();
	if (originalSize > 0) {
		int  i = 0;
		while(i <= originalSize - 1 and !isalnum(word[i])) {
			i++;
		}
		if (i <= originalSize - 1) {
			word.erase(0, i);
		}
		else {
			word = "";
		}
	}
	int size = word.length();
	if (size > 0) {
		int j = size;
		while(!isalnum(word[j])) {
			j--;
		}
		word.erase(j + 1, size);
	}
	return word;
}

// Function toLower
// Parameters: string word
// Returns: string
// Does: makes the word written in all lower case letters
string toLower(string word)
{
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = tolower(word[i]);
    }

    string str(word);

    return str;
}
