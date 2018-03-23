// Create a sorted leaderboard
#include "stdafx.h"
#include <iostream>
#include "leaderboard.h"

int main() {
	// create a leaderboard for 10 people
	leaderboard bowling(10);
	bowling.printLeaderboard();	

	// keep the console open
	std::cout << "\nPress enter to exit";
	std::cin.get();
	return 0;
}