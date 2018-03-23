#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "range.h"

// game where the computer generates a number and a human tries to guess it
int guessUntilCorrect() {
	// generate a random number
	srand(time(NULL)); // set the seed for rand()
	rand(); // the first number generated isn't random
	int number = rand() % (guessRangeMax + 1) + guessRangeMin;

	int tries = 0;
	int guess;
	do {
		tries++;
		std::cin >> guess;
		// check the correctness of the guess
		if (guess < number) {
			std::cout << "Too low\n";
		}
		else {
			std::cout << "Too high\n";
		}
	} while (number != guess);

	return tries;
}

// core
void humanGuesses() {
	std::cout << "Take a guess, young boy\n";
	int tries = guessUntilCorrect();
	std::cout << "You got it! It took you " << tries << " tries.\n";
}