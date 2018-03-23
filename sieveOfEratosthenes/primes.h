#pragma once

#include <iostream>

class primes {
public:
	primes(int upperLimit);
	~primes();
	void printPrimes();

private:
	int* numberLine;
	int upperLimit;

	void initiallizeNumberLine();
	int findNextPrime(int currentPrime);
	void removeMultiplesOfPrime(int prime);
};