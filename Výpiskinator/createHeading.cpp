#include <string>
using namespace std;

extern string* code;

void createHeading(string toReplace, string replaceWith) {
	int heading = code->find(toReplace);
	while (heading != string::npos) {
		code->replace(heading, 29, "\n" + replaceWith);
		code->erase(code->rfind("<p>", heading), 3);
		heading = code->find("</span>", heading + 4);
		code->replace(heading, 7, "</" + replaceWith.substr(1) + "\n");
		code->replace(code->find("<br>", heading), 4, "<p>");
		heading = code->find(toReplace, heading + 8);
	}
}