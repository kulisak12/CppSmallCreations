#include "stdafx.h"
#include <iostream>
#include <string>
#include "range.h"

// game where a human thinks of a number and the computer tries to guess it

// human answer processing
bool getHumanAnswer(int guess, int& minPossible, int& maxPossible) {
	std::string humanAnswer;
	std::cin >> humanAnswer;
	if (humanAnswer == "low") {
		minPossible = guess + 1; // update the minimum for the next guess
		return 0;
	}
	else if (humanAnswer == "high") {
		maxPossible = guess - 1; // update the maximum for the next guess
		return 0;
	}
	else if (humanAnswer == "correct") {
		std::cout << "Hooray!\n";
		return 1;
	}
	else { // invalid answer, prompt a new answer
		std::cout << "Invalid answer. Please say low, high or correct.\n";
		return getHumanAnswer(guess, minPossible, maxPossible);
	}
}

// core
void computerGuesses() {
	int minPossible = guessRangeMin;
	int maxPossible = guessRangeMax;
	int guess;
	bool isCorrect;

	do {
		guess = (minPossible + maxPossible) / 2; // guess the middle value
		std::cout << "I guess " << guess << ".\nIs it low, high or correct?\n";
		isCorrect = getHumanAnswer(guess, minPossible, maxPossible);
	} while (!isCorrect);
}