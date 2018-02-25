// Generator for a particle display in Minecraft Java 1.13
// by kulisak12
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#define INPUT "database.txt"

int main() {
	int particleNumber = 0;
	// allocate memory for strings taken from input
	std::string particleName;
	std::string *finalOutput = new std::string;
	*finalOutput = "";
	std::ifstream inputFile;
	std::ofstream outputFile;

	// open files
	try {
		inputFile.open(INPUT);
		if (!inputFile.is_open()) {
			std::cerr << "Error opening file " << INPUT << "for reading\n";
			throw 1;
		}
		outputFile.open("create_particle_display.mcfunction", std::ios::trunc);
		if (!outputFile.is_open()) {
			std::cerr << "Error writing output\n";
			inputFile.close();
			throw 2;
		}
	}
	catch (int x) {
		// keep the console open
		std::cout << "Press enter to exit";
		std::cin.clear();
		std::cin.sync();
		std::cin.get();
		return x;
	}

	// create output
	while (std::getline(inputFile, particleName)) {
		*finalOutput += "setblock ~ ~ ~-" + std::to_string(particleNumber * 2) + " command_block{Command:\"particle " + particleName + " ~ ~1.5 ~ 0.2 0.2 0.2 0.01 10 force\"}\n";
		particleNumber++;
	}

	// write output, close files
	outputFile << *finalOutput;
	inputFile.close();
	outputFile.close();
	return 0;
}