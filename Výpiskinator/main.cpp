#include <iostream>
#include <fstream>
#include "entityToUtf8.cpp"
#include "textReplace.cpp"
#include "findBulletList.cpp"
#include "createHeading.cpp"
using namespace std;

string* code = new string;

int main() {
	string entityToUtf8(int entityCode);
	void textReplace(string* source, string toReplace, string replaceWith);
	void createHeading(string toReplace, string replaceWith);
	int findBulletList(int hyphen);
	
	string* line = new string;
	int entity, entityStart, entityEnd;
	int lineBreak, listItem, paragraphEnd, indentLevel;
	
	ifstream sourceFile("note.html", ios::in);
	if (!sourceFile.is_open()) {
		cerr << "File doesn't exist\n";
		return 1;
	}
	ofstream outputFile("output.html", ios::out | ios::trunc);
	if (!outputFile.is_open()) {
		cerr << "File doesn't exist\n";
		return 1;
	}
	
	*code = "";
	// replace numerical HTML entities
	while (getline(sourceFile, *line)) {
		entityStart = line->find("&#");
		while (entityStart != string::npos) {
			entityEnd = line->find(';', entityStart);
			// extract the number from the entity syntax
			entity = stoi(line->substr(entityStart + 2, entityEnd - entityStart - 2));
			line->replace(entityStart, entityEnd - entityStart + 1, entityToUtf8(entity));
			entityStart = line->find("&#", entityStart);
		}
		// put together the code
		*code += *line;
	}
	
	// add line breaks
	textReplace(code, "<br>", "<br>\n");
	
	// change arrows
	textReplace(code, "-&gt;", "&rarr;");
	
	// replace font-size with h2 and h3
	createHeading("<span style=\"font-size:16px\">", "<h2>");
	createHeading("<span style=\"font-size:13px\">", "<h3>");
	
	// delete all color changing spans
	textReplace(code, "<span style=\"color:#000000\">", "");
	textReplace(code, "</span>", "");
	
	// change header
	code->replace(0, code->find("<p>") + 3,
	"<!--conversion by kulisak-->\n<!DOCTYPE html>\n<head><title>Note</title></head><body>\n<h1>");
	code->erase(code->find("<span style=\"font-size:22px\">"), 29);
	code->replace(code->find("</p>"), 4, "</h1>");
	
	// convert hyphen lists to bulleted unordered lists
	lineBreak = findBulletList(0); // find the first list item
	// for every list block
	while (lineBreak != string::npos) {
		listItem = code->find_first_not_of(9, lineBreak + 1);
		// mark the indentation level for future reference
		indentLevel = listItem - lineBreak;
		// replace tabs with list opening tags
		code->replace(lineBreak - 4, indentLevel + 4, "\n<ul><li>");
		// list should be ended with a p closing tag
		paragraphEnd = code->find("</p>", listItem + 1);
		if (paragraphEnd == string::npos) {
			paragraphEnd = code->length();
		}
		
		// handle the rest of items inside of the list
		lineBreak = findBulletList(listItem);
		while (lineBreak < paragraphEnd && lineBreak != string::npos) {
			listItem = code->find_first_not_of(9, lineBreak + 1);
			// if the indentation lowered, marking the end of an inner list
			if (listItem - lineBreak < indentLevel) {
				// no p closing tag
				paragraphEnd = code->find("<br>", listItem);
				code->erase(paragraphEnd, 4);
				break;
			}
			code->replace(lineBreak + 1, indentLevel - 1, "<li>");
			code->replace(lineBreak - 4, 4, "</li>");
			paragraphEnd = code->find("</p>", listItem + 1);
			if (paragraphEnd == string::npos) {
				paragraphEnd = code->length();
			}
			lineBreak = findBulletList(listItem);
		}
		// end the list block
		code->insert(paragraphEnd, "</li></ul>");
		if (lineBreak != string::npos) {
			lineBreak += 10; // inserted some text, position changed
		}
	}
	
	outputFile << *code;
	sourceFile.close();
	outputFile.close();
	delete line;
	line = NULL;
	delete code;
	code = NULL;
	return 0;
}