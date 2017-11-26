#include <math.h>
using namespace std;

// convert HTML entity code to a set of UTF-8 encoded characters
string entityToUtf8(int entityCode) {
	string encoded = "";
	// if ASCII
	if (entityCode < 128) {
		encoded = {(char) entityCode};
	} else {
		char bytes[6];
		// get the number of bytes used to encode the character
		int bytesCount = (log2(entityCode) + 4) / 5;
		bytes[0] = - pow(2, 8 - bytesCount); // prepare the first byte
		bytes[bytesCount] = '\0';
		// set the secondary bytes
		while (bytesCount > 1) {
			bytes[bytesCount - 1] = (entityCode % 64) - 128;
			entityCode /= 64;
			bytesCount--;
		}
		// finish the first byte
		bytes[0] += entityCode;
		encoded = bytes;
	}
	return encoded;
}
