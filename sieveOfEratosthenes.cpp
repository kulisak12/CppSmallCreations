// A program which calculates all primes up to a number using the "Sieve of Eratosthenes" algorithm
#include <iostream>

int* numberLine = NULL;
int upperLimit = 10000;

// create an array with numbers 0 through upperLimit
void initializeNumberLine() {
	numberLine = new int[upperLimit + 1];
	for (int i = 0; i <= upperLimit; i++) {
		numberLine[i] = i;
	}
	
	numberLine[1] = 0; // 1 is not prime
}

int findNextPrime(int currentPrime) {
	do {
		currentPrime++;
	} while (numberLine[currentPrime] == 0 && currentPrime <= upperLimit);
	return currentPrime;
}

void removeMultiplesOfPrime(int prime) {
	for (int i = prime * 2; i <= upperLimit; i += prime) {
		numberLine[i] = 0;
	}
}

int main() {
	initializeNumberLine();
	int currentPrime = 2;
	
	// go through the number line, eliminating all prime multiples
	while (currentPrime <= upperLimit) {
		std::cout << currentPrime << ", ";
		removeMultiplesOfPrime(currentPrime);
		currentPrime = findNextPrime(currentPrime);
	}
	
	// keep the console open
	std::cout << "\nPress enter to exit";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();
	return 0;
}