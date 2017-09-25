#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// game where the computer generates a number and a human tries to guess it
void humanGuess() {
    int number, guess;
    int tries = 1;
    srand(time(NULL)); // set the seed for rand()
    rand(); // the first number generated isn't random
    number = rand() % 101;
    cout << "Take a guess, young boy\n";
    cin >> guess;

    // check the correctness of the guess
    while (number != guess) {
        if (guess < number) {
            cout << "Too low\n";
        } else {
            cout << "Too high\n";
        }
        cin >> guess;
        tries++;
    }
    cout << "You got it! It took you " << tries << " tries." << endl;
}


// game where a human thinks of a number and the computer tries to guess it

// human answer processing
short humanAnswer(int f_guess, int *p_minPossible, int *p_maxPossible) {
    string humanAnswer;
    cin >> humanAnswer;
    if (humanAnswer == "low") {
        *p_minPossible = f_guess + 1; // update the minimum for the next guess
        return 0;
    } else if (humanAnswer == "high") {
        *p_maxPossible = f_guess - 1; // update the maximum for the next guess
        return 0;
    } else if (humanAnswer == "correct") {
        cout << "Hooray!\n";
        return 1;
    } else { // invalid answer, prompt a new answer
        cout << "Invalid answer. Please say low, high or correct.\n";
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
        cout << "I guess " << guess << ".\nIs it low, high or correct?\n";
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
    cout << "Who guesses, computer (0) or human (1)?\n";
    cin >> humanGuesses;
    if (humanGuesses == 0) {
        computerGuess();
    } else {
        humanGuess();
    }

    return 0;
}
