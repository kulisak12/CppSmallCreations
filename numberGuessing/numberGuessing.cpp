// A game to guess a number between 1 and 100
#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
	void humanGuesses();
	void computerGuesses();

	// select the game type and run it
	bool doesHumanGuess;
	std::cout << "Who guesses, computer (0) or human (1)?\n";
	std::cin >> doesHumanGuess;
	std::cin.ignore(32767, '\n');

	if (doesHumanGuess) {
		humanGuesses();
	}
	else {
		computerGuesses();
	}

	// keep the console open
	std::cin.ignore(32767, '\n');
	std::cout << "\nPress enter to exit";
	std::cin.get();
	return 0;
}