// A program which calculates all primes up to a number using the "Sieve of Eratosthenes" algorithm
#include "stdafx.h"
#include <iostream>
#include "primes.h"

int main() {
	primes first10k(10000);
	first10k.printPrimes();

	// keep the console open
	std::cout << "\nPress enter to exit";
	std::cin.get();
	return 0;
}