// a calculator which performs a modulo calculation
// accepts both decimal and fraction form
// example: 15.6 % 7
// example: 22/7 % 2
#include "stdafx.h"
#include <iostream>
#include <string>
#include "calculator.h"

void keepConsoleOpen() {
	std::cout << "\nPress enter to exit...";
	std::cin.get();
}

int main() {
	std::string getInput();

	try {
		moduloCalculator expression(getInput());
		std::cout << expression.returnAnswer() << std::endl;
	} catch (int x) {
		keepConsoleOpen();
		return x;
	}
	
	keepConsoleOpen();
	return 0;
}