#include <iostream>
#include <fstream>
#include <vector>
#include "entityToUtf8.cpp"
#include "textReplace.cpp"
#include "createHeading.cpp"
#include "searchForList.cpp"
#include "writeListData.cpp"
#include "createLists.cpp"
#include "itemList.h"
using namespace std;

int line = 0;
vector<string> code;

int main() {
	string entityToUtf8(int entityCode);
	void textReplace(string* source, string toReplace, string replaceWith);
	void createHeading(string* source, string toReplace, string replaceWith);
	void writeListData(vector<itemList> &setOfLists, string listType, string* lineStart, int indent);
	void createLists(vector<itemList> &setOfLists, string listType);
	
	ifstream sourceFile("note.html", ios::in);
	if (!sourceFile.is_open()) {
		cerr << "Couldn't open source file\n";
		return 1;
	}
	ofstream outputFile("output.html", ios::out | ios::trunc);
	if (!outputFile.is_open()) {
		cerr << "Couldn't open output file\n";
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
		
		code.push_back(*thisLine);
		// mark the position of a list
		space = thisLine->find(" ");
		if (space == string::npos) {
			space = thisLine->length();
		}
		*thisLine = thisLine->substr(0, space);
		// remove formatting tags
		textReplace(thisLine, "<b>", "");
		textReplace(thisLine, "</b>", "");
		textReplace(thisLine, "<u>", "");
		textReplace(thisLine, "</u>", "");
		textReplace(thisLine, "<i>", "");
		textReplace(thisLine, "</i>", "");
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
			}
			
			// terminate lists of higher indent
			searchForList(bulletLists, indent);
			searchForList(numberLists, indent);
			searchForList(letterLists, indent);
		}
		line++;
		if (code[line - 1].find("</p>") != string::npos) {
			// terminate all lists
			searchForList(bulletLists, -1);
			searchForList(numberLists, -1);
			searchForList(letterLists, -1);
		}
	}
	
	
	// change header
	code[0].replace(0, code[0].find("<p>") + 3,
	"<!--conversion by kulisak-->\n<!DOCTYPE html>\n<html><head><title>Note</title></head><body>\n<h1>");
	code[0].erase(code[0].find("<span style=\"font-size:22px\">"), 29);
	code[0].replace(code[0].find("</p>"), 4, "</h1>");
	
	// create lists
	createLists(bulletLists, "-");
	createLists(numberLists, "1");
	createLists(letterLists, "a");
	
	// create output file
	for (int i = 0; i < line - 1; i++) {
		outputFile << code[i] << endl;
	}
	outputFile << code[line - 1] << "</html>";
	delete thisLine;
	thisLine = NULL;
	sourceFile.close();
	outputFile.close();
	return 0;
}