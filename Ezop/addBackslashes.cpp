#include <string>
using namespace std;

// add extra backslashes to escape quotation marks
void addBackslashes(string *f_command, int newBackslashesPerOld) {
	size_t firstBackslash, lastBackslash;
	int backslashesToAdd;
	firstBackslash = f_command->find_first_of("\\\"");

	// if a backslash or a quotation mark has been found, add backslashes
	while (firstBackslash != string::npos) {
		lastBackslash = f_command->find_first_not_of("\\\"", firstBackslash + 1);
		backslashesToAdd = newBackslashesPerOld * (lastBackslash - firstBackslash);
		f_command->insert(firstBackslash, backslashesToAdd, '\\'); // add backslashes
		firstBackslash = f_command->find_first_of("\\\"", lastBackslash + backslashesToAdd); // look again
	}
}