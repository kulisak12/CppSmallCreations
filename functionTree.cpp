// Generates files in the form of a binary tree
#include <iostream>
#include <fstream>

std::string path;

int main() {
	void splitIntoHalves(int fromFrame, int toFrame);
	int firstFrame, lastFrame;
	
	// prompt the user to put in initial values
	std::cout << "Put in first and last frame numbers\n";
	std::cin >> firstFrame >> lastFrame;
	std::cout << "Put in function path including namespace\n";
	std::cin >> path;
	
	try {
		splitIntoHalves(firstFrame, lastFrame);
	}
	catch (int errorNumber) {
		// keep the console open
		std::cout << "Press enter to exit";
		std::cin.clear();
		std::cin.sync();
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
		std::cerr << "\nError opening file\nPress enter to continue";
		throw 1;
	}
	
	if (toFrame - fromFrame < 3) {
		// interval small enough to activate individual frames
		for (; fromFrame <= toFrame; fromFrame++) {
			functionFile << "execute if entity @s[scores={Animation=" << fromFrame << "}] run function " << 
			path << "f" << fromFrame << std::endl;
			// execute if @s[scores={Animation=3] function animace:starosta1-1/f3
		}
	} else {
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