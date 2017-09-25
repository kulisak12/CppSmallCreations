#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

void generateLetter() {
    int generated = (rand() % 62) + 65;
    cout << (char) generated << endl;
    int input;
    cin >> hex >> input;
    if (generated == input) {
        cout << "Correct! " << (char) generated << " corresponds to " << hex << generated << endl;
    } else {
        cout << "Incorrect! " << (char) generated << " corresponds to " << hex << generated << endl;
    }
}

int main() {
    srand(time(NULL));
    rand();
    for (int i = 0; i < 10; i++) {
    generateLetter();
    }
    
    cout << "Press enter to exit";
	cin.get(); cin.get();
    return 0;
}