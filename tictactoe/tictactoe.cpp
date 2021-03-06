// A game of tictactoe on a 3 by 3 grid
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"

tictactoe board;

int main() {
	void performMoves();
	srand(time(NULL)); // set the seed for randomization
	rand(); // generate the first number which isn't really random

	std::cout << "You play with x's, the computer plays with o's.\n" <<
		"In order to play, put in the number of the field you wish to play.\n" <<
		"The field numbering goes as follows:\n012\n345\n678\n" <<
		"The computer plays first. Good luck.\n\n";

	performMoves();
	board.drawBoard();

	// keep the console open
	std::cout << "\nPress enter to exit";
	std::cin.get();
	return 0;
}