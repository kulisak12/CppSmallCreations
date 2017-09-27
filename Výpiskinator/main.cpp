#include <iostream>
#include <fstream>
#include <vector>
#include "entityToUtf8.cpp"
#include "textReplace.cpp"
#include "createHeading.cpp"
#include "searchForList.cpp"
#include "writeListData.cpp"
#include "itemList.h"
using namespace std;

int line = 0;
vector<string> code;

int main() {
	string entityToUtf8(int entityCode);
	void textReplace(string* source, string toReplace, string replaceWith);
	void createHeading(string* source, string toReplace, string replaceWith);
	void writeListData(vector<itemList> &setOfLists, string listType, string* lineStart, int indent);
	
	ifstream sourceFile("note.html", ios::in);
	if (!sourceFile.is_open()) {
		cerr << "File doesn't exist\n";
		return 1;
	}
	ofstream outputFile("output.html", ios::out | ios::trunc);
	if (!outputFile.is_open()) {
		cerr << "File doesn't exist\n";
		sourceFile.close();
		return 1;
	}
	
	string* thisLine = new string;
	int entity, entityStart, entityEnd;
	int indent, space;
	vector<itemList> bulletLists;
	vector<itemList> numberLists;
	vector<itemList> letterLists;
	
	// extract code from file and store it line by line
	while (getline(sourceFile, *thisLine)) {
		// replace HTML entities
		entityStart = thisLine->find("&#");
		while (entityStart != string::npos) {
			entityEnd = thisLine->find(';', entityStart);
			// extract the number from the entity syntax
			entity = stoi(thisLine->substr(entityStart + 2, entityEnd - entityStart - 2));
			thisLine->replace(entityStart, entityEnd - entityStart + 1, entityToUtf8(entity));
			entityStart = thisLine->find("&#", entityStart);
		}
		
		// change arrows
		textReplace(thisLine, "-&gt;", "&rarr;");
		// replace font-size with h2 and h3
		createHeading(thisLine, "<span style=\"font-size:16px\">", "<h2>");
		createHeading(thisLine, "<span style=\"font-size:13px\">", "<h3>");
		// delete all color changing spans
		textReplace(thisLine, "<span style=\"color:#000000\">", "");
		textReplace(thisLine, "</span>", "");
		if (thisLine->find("</p>") != string::npos) {
			cout << "par found";
			// terminate all lists
			line++;
			searchForList(bulletLists, -1);
			searchForList(numberLists, -1);
			searchForList(letterLists, -1);
			line--;
		}
		
		code.push_back(*thisLine);
		// mark the position of a list
		space = thisLine->find(" ");
		if (space == string::npos) {
			space = thisLine->length();
		}
		*thisLine = thisLine->substr(0, space);
		// remove formatting tags
		textReplace(thisLine, "<b>", "");
		textReplace(thisLine, "<u>", "");
		textReplace(thisLine, "<i>", "");
		indent = thisLine->find_first_not_of("\t");
		thisLine->erase(0, indent);
		
		// check if line marks a list item
		if (*thisLine != "") {
			if (*thisLine == "-") {
				writeListData(bulletLists, "-", thisLine, indent);
			} else if (thisLine->substr(thisLine->length() - 1, 1) == ")") {
				if ((*thisLine)[thisLine->length() - 2] >= 48
				&& (*thisLine)[thisLine->length() - 2] < 58) { // 0 to 9
					writeListData(numberLists, "1", thisLine, indent);
				} else {
					writeListData(letterLists, "a", thisLine, indent);
				}
			} else {
				// terminate lists of higher indent
				searchForList(bulletLists, indent);
				searchForList(numberLists, indent);
				searchForList(letterLists, indent);
			}
		}
		line++;
	}
	
	
	// change header
	code[0].replace(0, code[0].find("<p>") + 3,
	"<!--conversion by kulisak-->\n<!DOCTYPE html>\n<html><head><title>Note</title></head><body>\n<h1>");
	code[0].erase(code[0].find("<span style=\"font-size:22px\">"), 29);
	code[0].replace(code[0].find("</p>"), 4, "</h1");
	
	// create lists
	for (int i = 0; i < bulletLists.size(); i++) {
		// for every list
		code[bulletLists[i].itemLines[0]].insert(0, "<ul><li>");
		for (int j = 1; j < bulletLists[i].itemLines.size(); j++) {
			// for every list item
			code[bulletLists[i].itemLines[j] - 1].append("</li>");
			code[bulletLists[i].itemLines[j]].insert(0, "<li>");
		}
		cout << "|" << bulletLists[i].lastLine;
		if (bulletLists[i].lastLine < 200) {
			code[bulletLists[i].lastLine].append("</li></ul>");
		}
	}
	
	for (int i = 0; i < numberLists.size(); i++) {
		// for every list
		code[numberLists[i].itemLines[0]].insert(0, "<ol start=\"" + numberLists[i].firstIndex + "\"><li>");
		for (int j = 1; j < numberLists[i].itemLines.size(); j++) {
			// for every list item
			code[numberLists[i].itemLines[j] - 1].append("</li>");
			code[numberLists[i].itemLines[j]].insert(0, "<li>");
		}
		cout << "|" << numberLists[i].lastLine;
		if (numberLists[i].lastLine < 200) {
			code[numberLists[i].lastLine].append("</li></ol>");
		}
	}
	
	for (int i = 0; i < letterLists.size(); i++) {
		// for every list
		code[letterLists[i].itemLines[0]].insert(0, "<ol type=\"a\"><li>");
		for (int j = 1; j < letterLists[i].itemLines.size(); j++) {
			// for every list item
			code[letterLists[i].itemLines[j] - 1].append("</li>");
			code[letterLists[i].itemLines[j]].insert(0, "<li>");
		}
		cout << "|" << letterLists[i].lastLine;
		if (letterLists[i].lastLine < 200) {
			code[letterLists[i].lastLine].append("</li></ol>");
		}
	}
	
	
	// create output file
	for (int i = 0; i < line - 1; i++) {
		outputFile << code[i] << endl;
	}
	outputFile << code[line - 1] << "</html>";
	cin.get();
	delete thisLine;
	thisLine = NULL;
	sourceFile.close();
	outputFile.close();
	return 0;
}