// A game used to help remember ASCII values
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

// choose a random ASCII character from 21 to 7e
void generateLetter() {
	int generated = (std::rand() % 94) + 33;
	std::cout << (char) generated << std::endl;
	// ask user to put in corresponding ASCII value
	int input;
	std::cin >> std::hex >> input;
	std::cin.ignore(32767, '\n');
	if (generated == input) {
		std::cout << "Correct! \n";
	}
	else {
		std::cout << "Incorrect! " << (char) generated << " corresponds to " << std::hex << generated << std::endl;
	}
}

int main() {
	std::srand(std::time(NULL));
	std::rand();
	for (int i = 0; i < 10; i++) {
		generateLetter();
	}

	// keep the console open
	std::cout << "\nPress enter to exit...";
	std::cin.get();
	return 0;
}