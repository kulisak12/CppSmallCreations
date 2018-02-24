// A game used to help remember ASCII values
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

// choose a random ASCII character
void generateLetter() {
    int generated = (rand() % 62) + 65;
    std::cout << (char) generated << std::endl;
	// ask user to put in corresponding ASCII value
    int input;
    std::cin >> std::hex >> input;
    if (generated == input) {
        std::cout << "Correct! " << (char) generated << " corresponds to " << std::hex << generated << std::endl;
    } else {
        std::cout << "Incorrect! " << (char) generated << " corresponds to " << std::hex << generated << std::endl;
    }
}

int main() {
    srand(time(NULL));
    rand();
    for (int i = 0; i < 10; i++) {
		generateLetter();
    }
    
	// keep the console open
    std::cout << "Press enter to exit";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();
    return 0;
}