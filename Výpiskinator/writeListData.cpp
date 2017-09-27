#include <string>
#include <vector>
#include "itemList.h"
using namespace std;

extern vector<string> code;

void writeListData(vector<itemList> &setOfLists, string listType, string* lineStart, int indent) {
	void textReplace(string* source, string toReplace, string replaceWith);
	int searchForList(vector<itemList> &lists, int indent);
	vector<itemList>::iterator currentList;
	int space = -1;
	int firstIndex;
	string listSign = (listType == "-") ? "-" : ")";
	
	// remove tabs and dash in the code
	*lineStart = code[line].substr(0, code[line].find(listSign) + 2);
	textReplace(lineStart, "\t", "");
	
	if (listSign == ")") {
		space = lineStart->find_last_not_of("-)0123456789abcdefghijklmnopqrstuvwxyz", lineStart->length() - 2);
		if (space == string::npos) {
			space = -1;
		}
	}
	// write list data to object
	int current = searchForList(setOfLists, indent);
	if (current == -1) {
		setOfLists.push_back(0);
		currentList = setOfLists.end() - 1;
		currentList->indentLevel = indent;
		currentList->terminated = 0;
		currentList->itemLines.push_back(line);
		if (listType == "1") {
			currentList->firstIndex = lineStart->substr(space + 1, lineStart->length() - space - 3);
		}
	} else {
		currentList = setOfLists.begin() + current;
		currentList->itemLines.push_back(line);
	
	}
	
	// remove list sign and space after it
	if (lineStart->substr(lineStart->length() - 1) == " ") {
		lineStart->erase(space + 1);
	} else {
		lineStart->erase(space + 1, lineStart->length() - space - 2);
	}
	code[line].replace(0, code[line].find(listSign) + 2, *lineStart);
}