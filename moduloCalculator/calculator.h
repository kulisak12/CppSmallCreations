#pragma once

#include <string>

class moduloCalculator {
public:
	moduloCalculator(std::string expression);
	std::string returnAnswer();

private:
	float divisor;
	float divident;
	bool isFraction;
	int denominator;

	void setCompoundDivisor(std::string divisorString);
	float calculateModulo();
};