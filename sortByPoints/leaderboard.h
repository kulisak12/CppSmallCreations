#pragma once

class leaderboard {
public:
	leaderboard(int peopleCount);
	~leaderboard();

	void printLeaderboard();

private:
	const int peopleCount;
	int* points;
	int* place;

	void getPoints();
	void setPlace();
};