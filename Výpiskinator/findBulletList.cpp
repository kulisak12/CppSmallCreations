#include <string>
using namespace std;

extern string* code;
void textReplace(string* source, string toReplace, string replaceWith);

int findBulletList(int hyphen) {
	string untilHyphen;
	hyphen = code->find("-", hyphen);
	if (hyphen == string::npos) {
		return string::npos;
	}
	int lineBreak = code->rfind("\n", hyphen);
	
	// check if hyphen marks a list item
	// that means that there are only tabs and modifiers before the hyphen
	untilHyphen = code->substr(lineBreak + 1, hyphen - lineBreak - 1);
	textReplace(&untilHyphen, "<b>", "");
	textReplace(&untilHyphen, "<u>", "");
	textReplace(&untilHyphen, "<i>", "");
	/*if (untilHyphen == "") {
		code->erase(hyphen, 1);
		return lineBreak;
	}*/
	if (untilHyphen.find_first_not_of(9) == string::npos) {
		code->erase(hyphen, 1);
		return lineBreak;
	}
	// else look again
	return findBulletList(hyphen + 1);
}