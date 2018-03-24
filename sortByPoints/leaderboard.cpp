#include "stdafx.h"
#include <iostream>
#include "leaderboard.h"

int* points = NULL;
int* place = NULL;

leaderboard::leaderboard(int peopleCount)
	: peopleCount(peopleCount)
{
	points = new int[peopleCount];
	place = new int[peopleCount];
}
leaderboard::~leaderboard() {
	delete[] points;
	points = NULL;
	delete[] place;
	place = NULL;
}

// get input
void leaderboard::getPoints() {
	std::cout << "Put in points for " << peopleCount << " people.\n";
	for (int i = 0; i < peopleCount; i++) {
		std::cin >> points[i];
		place[i] = 1; // 1 = first
	}
	std::cin.ignore(32767, '\n');
}

void leaderboard::printLeaderboard() {
	setPlace();
	for (int i = 1; i <= peopleCount; i++) {
		// find the person on i-th place
		for (int j = 0; j < peopleCount; j++) {
			if (place[j] == i) {
				std::cout << i << ") Person " << j + 1 << " with " << points[j] << " points\n";
			}
		}
	}
}

/* for every combination of two people, if the second one has less
points than the first one, increase their place by one */
void leaderboard::setPlace() {
	for (int i = 0; i < peopleCount; i++) {
		for (int j = 0; j < peopleCount; j++) {
			if (points[i] > points[j]) {
				place[j]++;
			}
		}
	}
}