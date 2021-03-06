// Generator for a particle display in Minecraft Java 1.13
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#define INPUT "particleList.txt"

void openFiles(std::ifstream& inputFile, std::ofstream& outputFile) {
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

void createOutput(std::ifstream& inputFile, std::ofstream& outputFile) {
	int particleNumber = 0;
	std::string particleName;
	while (std::getline(inputFile, particleName)) {
		outputFile << "setblock ~ ~ ~-" << particleNumber * 2 <<
			" command_block{Command:\"particle " << particleName <<
			" ~ ~1.5 ~ 0.2 0.2 0.2 0.01 10 force\"}\n";
		particleNumber++;
	}
}

int main() {
	std::ifstream inputFile;
	std::ofstream outputFile;

	try {
		openFiles(inputFile, outputFile);
	}
	catch (int errorCode) {
		// keep the console open
		std::cout << "\nPress enter to exit";
		std::cin.get();
		return errorCode;
	}

	createOutput(inputFile, outputFile);

	// close files
	inputFile.close();
	outputFile.close();
	return 0;
}