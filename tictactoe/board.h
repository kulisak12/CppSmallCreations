#pragma once

class tictactoe {
public:
	tictactoe();
	void drawBoard();
	bool playAtField(char sign, int x, int y);
	int searchForStreak(char sign, int streakValue);
	bool handleStreaks(char sign);
	void randomMove(char sign);

private:
	char fields[3][3]; // the board

	int signsInRow(char sign, int row);
	int signsInCollumn(char sign, int collumn);
	int signsInDownwardsDiagonal(char sign);
	int signsInUpwardsDiagonal(char sign);
	bool fillStreak(int streakPosition, int i);
};