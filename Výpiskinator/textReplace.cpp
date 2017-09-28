using namespace std;

// replace all occurences of string by a different one
void textReplace(string* source, string toReplace, string replaceWith) {
	int element;
	element = source->find(toReplace);
	while (element != string::npos) {
		source->replace(element, toReplace.length(), replaceWith);
		element = source->find(toReplace, element + replaceWith.length());
	}
}