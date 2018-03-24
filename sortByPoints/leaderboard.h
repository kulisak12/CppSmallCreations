#pragma once

class leaderboard {
public:
	leaderboard(int peopleCount);
	~leaderboard();

	void getPoints();
	void printLeaderboard();

private:
	const int peopleCount;
	int* points;
	int* place;

	void setPlace();
};