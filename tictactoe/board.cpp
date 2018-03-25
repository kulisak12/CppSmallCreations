#include "stdafx.h"
#include <iostream>
#include "board.h"

tictactoe::tictactoe() {
	// initiallize the board with empty fields
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			fields[i][j] = '-';
		}
	}
}

void tictactoe::drawBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << fields[i][j];
		}
		std::cout << std::endl;
	}
}

bool tictactoe::playAtField(char sign, int x, int y) {
	// if the field is free
	if (fields[x][y] == '-') {
		fields[x][y] = sign;
		return 0; // success
	}
	// if the field is taken
	else {
		return 1; // invokes a new input
	}
}

// check if there is a streak and return its position
int tictactoe::searchForStreak(char sign, int streakValue) {
	// check rows and collumns for the streak
	for (int i = 0; i < 3; i++) {
		if (signsInRow(sign, i) == streakValue) {
			return 3 + i;
		}
		if (signsInCollumn(sign, i) == streakValue) {
			return 6 + i;
		}
	}
	// check diagonals
	if (signsInDownwardsDiagonal(sign) == streakValue) {
		return 9;
	}
	if (signsInUpwardsDiagonal(sign) == streakValue) {
		return 12;
	}
	return 0;
}

bool tictactoe::handleStreaks(char sign) {
	// look for a streak
	int streakPosition = searchForStreak(sign, 2);
	if (streakPosition > 0) {
		// if the streak is found, play there
		for (int i = 0; i < 3; i++) {
			if (fillStreak(streakPosition, i)) {
				return 1; // success
			}
		}
	}
	return 0; // no streak found
}

void tictactoe::randomMove(char sign) {
	int fieldPosition;
	do {
		fieldPosition = rand() % 9;
	} while (playAtField(sign, fieldPosition / 3, fieldPosition % 3));
}

// calculate how many signs are there in a row
int tictactoe::signsInRow(char sign, int row) {
	int signCount = 0;
	for (int i = 0; i < 3; i++) {
		if (fields[row][i] == sign) { // own sign
			signCount++;
		}
		else if (fields[row][i] != '-') { // opposite sign
			return 0;
		}
	}
	return signCount;
}

// calculate how many signs are there in a collumn
int tictactoe::signsInCollumn(char sign, int collumn) {
	int signCount = 0;
	for (int i = 0; i < 3; i++) {
		if (fields[i][collumn] == sign) { // own sign
			signCount++;
		}
		else if (fields[i][collumn] != '-') { // opposite sign
			return 0;
		}
	}
	return signCount;
}

// calculate how many signs are there in the \ diagonal
int tictactoe::signsInDownwardsDiagonal(char sign) {
	int signCount = 0;
	for (int i = 0; i < 3; i++) {
		if (fields[i][i] == sign) { // own sign
			signCount++;
		}
		else if (fields[i][i] != '-') { // opposite sign
			return 0;
		}
	}
	return signCount;
}

// calculate how many signs are there in the / diagonal
int tictactoe::signsInUpwardsDiagonal(char sign) {
	int signCount = 0;
	for (int i = 0; i < 3; i++) {
		if (fields[i][2 - i] == sign) { // own sign
			signCount++;
		}
		else if (fields[i][2 - i] != '-') { // opposite sign
			return 0;
		}
	}
	return signCount;
}

bool tictactoe::fillStreak(int streakPosition, int i) {
	bool isUnavailable;
	switch (streakPosition / 3) {
	case 1: // row
		isUnavailable = playAtField('o', streakPosition % 3, i);
		break;
	case 2: // collumn
		isUnavailable = playAtField('o', i, streakPosition % 3);
		break;
	case 3: // downwards diagonal
		isUnavailable = playAtField('o', i, i);
		break;
	case 4: // upwards diagonal
		isUnavailable = playAtField('o', i, 2 - i);
		break;
	}
	return isUnavailable;
}