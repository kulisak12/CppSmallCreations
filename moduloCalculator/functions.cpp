#include "stdafx.h"
#include <iostream>
#include <string>
#include "functions.h"

std::string getInput() {
	std::cout << "Please enter the expression to be evaluated:\n";
	std::string input;
	std::getline(std::cin, input);
	return input;
}

// remove spaces at the front and at the back
std::string removeSpaces(std::string input) {
	size_t front = input.find_first_not_of(' ');
	// if string consists of spaces only
	if (front == std::string::npos) {
		std::cerr << "Error: Operand missing\n";
		throw 2;
	}

	input.erase(0, front);
	size_t back = input.find_last_not_of(' ');
	input.erase(back + 1);
	return input;
}

// return parts of string before and after a certain character
void splitString(char delimiter, std::string input, std::string &firstHalf, std::string &secondHalf) {
	size_t half = input.find(delimiter);
	if (half == std::string::npos) {
		std::cerr << "Error: no " << delimiter << " character found\n";
		throw 1;
	}
	firstHalf = input.substr(0, half);
	secondHalf = input.substr(half + 1);
}

// extending modulo to float numbers
float modulo(float divisor, float divident) {
	// take absolute value of divident
	if (divident < 0) {
		divident *= -1;
	}

	while (divisor > divident) {
		divisor -= divident;
	}
	while (divisor < -divident) {
		divisor += divident;
	}
	return divisor;
}