#include <string>
#include <fstream>
using namespace std;

extern int lineNumber;
extern ifstream inputFile;

// get the next non-comment line
string readLine() {
	string line;

	if (!getline(inputFile, line)) {
		return "#EOF"; // mark that end of file was reached 
	};
	lineNumber++;

	// remove extra spaces and tabs at the beginning of the line
	line.erase(0, line.find_first_not_of({ 9, 32 }));

	// skip line if comment or empty
	if (line[0] == '#' || line.length() == 0) {
		return readLine();
	}

	// remove extra spaces at the end
	line.erase(line.find_last_not_of(' ') + 1);
	return line;
}