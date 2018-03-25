#include "stdafx.h"
#include <iostream>
#include "board.h"

extern tictactoe board;

bool computerPlays() { // return 1 = end of the game
					   // check if player won
	if (board.searchForStreak('x', 3) > 0) {
		std::cout << "You won! Congrats!\n";
		return 1;
	}
	// computer can win -> finish streak
	if (board.handleStreaks('o')) {
		std::cout << "The computer beat you. Try again.\n";
		return 1;
	}
	// player could win -> block
	if (board.handleStreaks('x')) {
		return 0;
	}
	// else: play a random move
	board.randomMove('o');
	return 0;
}

bool getInput() {
	int fieldPlayed;
	std::cin >> fieldPlayed;
	std::cin.ignore(32767, '\n');

	if (fieldPlayed < 0 || fieldPlayed > 8) {
		std::cerr << "Please put in a number between 0 and 8\n";
		return 1; // invoke a new input
	}
	if (board.playAtField('x', fieldPlayed / 3, fieldPlayed % 3)) {
		std::cerr << "Field taken, please choose a free one\n";
		return 1; // invoke a new input
	}
	return 0;
}

void playerPlays() {
	board.drawBoard();
	while (getInput()); // get input until valid
}

void performMoves() {
	computerPlays(); // start the game, computer plays first

	for (int i = 0; i < 4; i++) { // only 9 moves are possible
		playerPlays();
		if (computerPlays()) { // if the game has ended
			return;
		}
	}

	// all fields have been filled
	std::cout << "It's a draw!\n";
}