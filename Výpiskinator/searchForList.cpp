#include "itemList.h"
using namespace std;

extern int line;


int searchForList(vector<itemList> &lists, int indent) {
	int prospectedList = lists.size() - 1;
	if (prospectedList >= 0) {
		while (indent <= lists[prospectedList].indentLevel && prospectedList >= 0) {
			if (!lists[prospectedList].terminated) {
				if (indent == lists[prospectedList].indentLevel) {
					return prospectedList;
				}
				lists[prospectedList].terminated = 1;
				lists[prospectedList].lastLine = line - 1;
			}
			prospectedList--;
		}
		return -1;
	}
	return -1;
}