#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void replaceAll(std::string& s, std::string from, std::string to) {
	size_t fromPos = s.find(from);
	while (fromPos != std::string::npos) {
		s.replace(fromPos, from.length(), to);
		fromPos = s.find(from, fromPos + 1);
	}
}

void getInput(std::vector<std::string>& input) {
	std::ifstream inputFile("latina.txt");
	if (!inputFile.is_open()) {
		throw std::runtime_error("Error opening input");
	}

	std::string line;
	while (getline(inputFile, line)) {
		input.push_back(line);
	}

	inputFile.close();
}

std::string replaceInLine(std::string line) {
	std::string translation;
	size_t sep = line.find(';');
	translation = line.substr(sep);
	line.erase(sep);

	replaceAll(line, "á", "ā");
	replaceAll(line, "é", "ē");
	replaceAll(line, "í", "ī");
	replaceAll(line, "ó", "ō");
	replaceAll(line, "ú", "ū");
	replaceAll(line, "Á", "Ā");
	replaceAll(line, "É", "Ē");
	replaceAll(line, "Í", "Ī");
	replaceAll(line, "Ó", "Ō");
	replaceAll(line, "Ú", "Ū");

	return line + translation;
}

void writeOutput(std::vector<std::string>& input) {
	std::ofstream outputFile("latina.txt", std::ios::trunc);
	if (!outputFile.is_open()) {
		throw std::runtime_error("Error opening output");
	}

	for (size_t i = 0; i < input.size(); i++) {
		outputFile << replaceInLine(input[i]) << std::endl;
	}

	outputFile.close();
}

int main() {
	std::vector<std::string> input;
	try {
		getInput(input);
		writeOutput(input);
	}
	catch (std::exception& e) {
		std::cerr << e.what();
		return 1;
	}
    return 0;
}

