// A game to guess a number between 1 and 100
#include <iostream>
#include <stdlib.h>
#include <time.h>

// game where the computer generates a number and a human tries to guess it
void humanGuess() {
    int number, guess;
    int tries = 1;
    srand(time(NULL)); // set the seed for rand()
    rand(); // the first number generated isn't random
    number = rand() % 101;
    std::cout << "Take a guess, young boy\n";
    std::cin >> guess;
	
    // check the correctness of the guess
    while (number != guess) {
        if (guess < number) {
            std::cout << "Too low\n";
        } else {
            std::cout << "Too high\n";
        }
        std::cin >> guess;
        tries++;
    }
    std::cout << "You got it! It took you " << tries << " tries." << std::endl;
}


// game where a human thinks of a number and the computer tries to guess it

// human answer processing
short humanAnswer(int guess, int *minPossible, int *maxPossible) {
    std::string humanAnswer;
    std::cin >> humanAnswer;
    if (humanAnswer == "low") {
        *minPossible = guess + 1; // update the minimum for the next guess
        return 0;
    } else if (humanAnswer == "high") {
        *maxPossible = guess - 1; // update the maximum for the next guess
        return 0;
    } else if (humanAnswer == "correct") {
        std::cout << "Hooray!\n";
        return 1;
    } else { // invalid answer, prompt a new answer
        std::cout << "Invalid answer. Please say low, high or correct.\n";
        return -1;
    }
}

// core
void computerGuess() {
    int minPossible = 0;
    int maxPossible = 100;
    int guess;
    short isCorrect;
	
    do {
        guess = (minPossible + maxPossible) / 2; // guess the middle value
        std::cout << "I guess " << guess << ".\nIs it low, high or correct?\n";
        isCorrect = humanAnswer(guess, &minPossible, &maxPossible);
		
        if (isCorrect == -1) { // process a new answer if it was invalid
            isCorrect = humanAnswer(guess, &minPossible, &maxPossible);
        }
    } while (isCorrect == 0);
}

int main()
{
    // select the game type and run it
    bool humanGuesses;
    std::cout << "Who guesses, computer (0) or human (1)?\n";
    std::cin >> humanGuesses;
    if (humanGuesses == 0) {
        computerGuess();
    } else {
        humanGuess();
    }
	
	// keep the console open
    std::cout << "Press enter to exit";
	std::cin.clear();
	std::cin.sync();
	std::cin.get();
    return 0;
}
