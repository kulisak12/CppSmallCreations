#include <string>
#include <fstream>

extern ifstream inputFile;
extern ofstream outputFile;
extern string* finalOutput;
extern string* instructions;
extern string* command;

// close all files, deallocate memory
void endAll() {
	inputFile.close();
	outputFile.close();
	delete finalOutput;
	finalOutput = NULL;
	delete instructions;
	instructions = NULL;
	delete command;
	command = NULL;
}