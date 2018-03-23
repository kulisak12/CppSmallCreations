#include "stdafx.h"
#include <iostream>
#include "primes.h"

int* numberLine = NULL;

primes::primes(int upperLimit) {
	this->upperLimit = upperLimit;
	initiallizeNumberLine();
}
primes::~primes() {
	delete[] numberLine;
	numberLine = NULL;
}

void primes::printPrimes() {
	int currentPrime = 2;
	while (currentPrime <= upperLimit) {
		std::cout << currentPrime << ", ";
		removeMultiplesOfPrime(currentPrime);
		currentPrime = findNextPrime(currentPrime);
	}
}

// create an array with numbers 0 through upperLimit
void primes::initiallizeNumberLine() {
	numberLine = new int[upperLimit + 1];
	for (int i = 0; i <= upperLimit; i++) {
		numberLine[i] = i;
	}

	numberLine[1] = 0; // 1 is not prime
}

// find the next number which hasn't been crossed out
int primes::findNextPrime(int currentPrime) {
	do {
		currentPrime++;
	} while (numberLine[currentPrime] == 0 && currentPrime <= upperLimit);
	return currentPrime;
}

void primes::removeMultiplesOfPrime(int prime) {
	for (int i = prime * 2; i <= upperLimit; i += prime) {
		numberLine[i] = 0;
	}
}