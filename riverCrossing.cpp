// A program to solve the river crossing problem
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main() {
	char pickRandom(std::string listOfPeople);
	
	int speed[4] = {1, 3, 7, 10};
	std::string side1;
	std::string side2;
	std::string history;
	int currentTime;
	int totalTime;
	std::string current;
	
	std::srand(time(NULL));
	std::rand();
	// try until the desired time is achieved
	do {
		// reset values
		side1 = "0123";
		side2 = "";
		history = "";
		totalTime = 0;
		// simulate river crossing
		for (int i = 0; i < 5; i++) {
			// select two random people to go to the other side
			current = pickRandom(side1);
			currentTime = speed[std::stoi(current)]; // get person's speed
			side1.erase(side1.find(current), 1);
			current += pickRandom(side1);
			// get the slower person and get their speed
			if (speed[std::stoi(current.substr(1))] > currentTime) {
				currentTime = speed[std::stoi(current.substr(1))];
			}		
			side1.erase(side1.find(current.substr(1)), 1);
			totalTime += currentTime;
			side2 += current;
			history += current + "\n";
			
			// check if there are any people left
			if (side1 == "") {
				break;
			} else {
				// select one random person to go back
				current = pickRandom(side2);
				totalTime += speed[std::stoi(current)];
				side2.erase(side2.find(current), 1);
				side1 += current;
				history += current + "\n";
			}
		}
	} while (totalTime > 20); // repeat if not fast enough
	std::cout << history;
	
	// keep the console open
    std::cout << "Press enter to exit";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();
	return 0;
}

char pickRandom(std::string listOfPeople) {
	return listOfPeople[std::rand() % listOfPeople.length()];
}