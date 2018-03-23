#include "stdafx.h"
#include <string>
#include "functions.h"
#include "calculator.h"

// set divisor and divident
moduloCalculator::moduloCalculator(std::string expression) {
	std::string divisorString, dividentString;
	splitString('%', expression, divisorString, dividentString);
	this->divident = std::stof(removeSpaces(dividentString));
	// if divisor is a decimal number
	if (divisorString.find('/') == std::string::npos) {
		isFraction = 0;
		this->divisor = std::stof(removeSpaces(divisorString));
		// if divisor is a fraction
	}
	else {
		isFraction = 1;
		setCompoundDivisor(divisorString);
	}
}

std::string moduloCalculator::returnAnswer() {
	std::string answer = std::to_string(calculateModulo());
	if (isFraction) {
		answer += " / " + std::to_string(denominator);
	}
	return answer;
}

void moduloCalculator::setCompoundDivisor(std::string divisorString) {
	std::string divisor, denominator;
	splitString('/', divisorString, divisor, denominator);
	this->divisor = std::stof(removeSpaces(divisor));
	this->denominator = std::stoi(removeSpaces(denominator));
}

float moduloCalculator::calculateModulo() {
	if (isFraction) {
		divident *= denominator;
	}

	return modulo(divisor, divident);
}