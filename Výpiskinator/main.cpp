#include <iostream>
#include <fstream>
#include <vector>
#include "entityToUtf8.cpp"
#include "textReplace.cpp"
#include "createHeading.cpp"
using namespace std;

class itemList {
	public:
		vector<int> itemLines;
		int items = 0;
		int lastLine, indent, firstIndex;
		bool terminated = 0;
};

class listGroup {
	public:
		vector<itemList> itemListsSet;
		
};
class bulletLists: public listGroup {
	
};
class numberLists: public listGroup {
	
};
class letterLists: public listGroup {
	
};

int main() {
	string entityToUtf8(int entityCode);
	void textReplace(string* source, string toReplace, string replaceWith);
	void createHeading(string* source, string toReplace, string replaceWith);
	
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
	vector<string> code(10);
	int line = 0;
	int entity, entityStart, entityEnd;
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
		
		if (*thisLine != "") {
			code[line] = *thisLine;
			line++;
			code.resize(line + 1); // make space for the next line
		}
		
	}
	
	
	// change header
	code[0].replace(0, code[0].find("<p>") + 3,
	"<!--conversion by kulisak-->\n<!DOCTYPE html>\n<html><head><title>Note</title></head><body>\n<h1>");
	code[0].erase(code[0].find("<span style=\"font-size:22px\">"), 29);
	code[0].replace(code[0].find("</p>"), 4, "</h1>");
	
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