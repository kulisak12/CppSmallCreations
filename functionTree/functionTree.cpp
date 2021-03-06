// Generates files in the form of a binary tree
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

std::string path;

int main() {
	void splitIntoHalves(int fromFrame, int toFrame);
	void getInput(int &firstFrame, int &lastFrame);

	int firstFrame, lastFrame;
	getInput(firstFrame, lastFrame);
	try {
		// begin splitting
		splitIntoHalves(firstFrame, lastFrame);
	}
	catch (int errorNumber) {
		// keep the console open
		std::cout << "\nPress enter to exit";
		std::cin.get();
		return errorNumber;
	}
	return 0;
}

// create one file which handes the set interval and activates other functions
void splitIntoHalves(int fromFrame, int toFrame) {
	// open file for writing
	std::ofstream functionFile(std::to_string(fromFrame) + "az" + std::to_string(toFrame) + ".mcfunction", std::ios::trunc);
	if (!functionFile.is_open()) {
		std::cerr << "Error opening file\n";
		throw 1;
	}

	if (toFrame - fromFrame < 3) {
		// interval small enough to activate individual frames
		for (; fromFrame <= toFrame; fromFrame++) {
			functionFile << "execute if entity @s[scores={Animation=" << fromFrame << "}] run function " <<
				path << "f" << fromFrame << std::endl;
			// execute if @s[scores={Animation=3] function animace:starosta1-1/f3
		}
	}
	else {
		// split interval into halves; activate function again
		int half = (fromFrame + toFrame) / 2;
		functionFile << "execute if entity @s[scores={Animation=.." << half << "}] run function " <<
			path << fromFrame << "az" << half << std::endl;
		splitIntoHalves(fromFrame, half);

		functionFile << "execute if entity @s[scores={Animation=" << half + 1 << "..}] run function " <<
			path << half + 1 << "az" << toFrame << std::endl;
		splitIntoHalves(half + 1, toFrame);
	}

	functionFile.close();
}

// prompt the user to put in initial values
void getInput(int& firstFrame, int& lastFrame) {
	std::cout << "Put in first and last frame numbers\n";
	std::cin >> firstFrame >> lastFrame;
	std::cin.ignore(32767, '\n');
	std::cout << "Put in function path including namespace\n";
	std::cin >> path;
	std::cin.ignore(32767, '\n');
}