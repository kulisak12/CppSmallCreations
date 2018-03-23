#pragma once

#include <string>

std::string getInput();
std::string removeSpaces(std::string input);
void splitString(char delimiter, std::string input, std::string &firstHalf, std::string &secondHalf);
float modulo(float divisor, float divident);