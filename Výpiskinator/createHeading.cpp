using namespace std;

void createHeading(string* source, string toReplace, string replaceWith) {
	// change first font size change to heading element
	int heading = source->find(toReplace);
	if (heading != string::npos) {
		source->replace(heading, toReplace.length(), replaceWith);
		// change paragraph start and end
		if (source->substr(0, 3) == "<p>") {
			source->erase(0, 3);
		} else {
			source->insert(0, "</p>");
		}
		source->replace(source->length() - 4, 4, "</" + replaceWith.substr(1) + "<p>");
	}
	
	// remove other font size changes
	heading = source->find(toReplace);
	while (heading != string::npos) {
		source->erase(heading, toReplace.length());
		heading = source->find(toReplace);
	}
}