#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// global variables
const short BOARD_SIZE(3);
char board[BOARD_SIZE][BOARD_SIZE];
short field;
short coordY(-1);
short coordX(-1);
short freeFieldCount;
short freeFields[BOARD_SIZE*BOARD_SIZE];
bool humanPlays;
int i, j;

// convert position on the field to Y and X coordinates
void toCoordComb() {
    coordY = field / BOARD_SIZE;
    coordX = field % BOARD_SIZE;
}

void drawBoard() {
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}


// find all free fields, count them and mark their position
void getFreeFields() {
    freeFieldCount = -1;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == '-') {
                freeFieldCount++; // count the free spots
                freeFields[freeFieldCount] = BOARD_SIZE * i + j; // mark their position
            }
        }
    }
}

// check rows for a row of three (win) or a row of two (-> block)
bool checkRows() {
     // set the sign of the player who just played (x / o)
    char sign;
    if (humanPlays == 1) {
        sign = 'x';
    } else {
        sign = 'o';
    }

    // check for any rows of 2 or 3
    short inRow = 0;
    short missing = -1;
    // check the horizontal rows
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == sign) {
                inRow++;
            } else if (board[i][j] == '-') {
                missing = j;
            }
        }
        if (inRow == 3) { // win
            return 1;
        } else if (inRow == 2 && missing != -1) { // where the computer should play
            coordY = i;
            coordX = missing;
        }
        inRow = 0;
        missing = -1;
    }

    // check the vertical rows
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[j][i] == sign) {
                inRow++;
            } else if (board[j][i] == '-') {
                missing = j;
            }
        }
        if (inRow == 3) { // win
            return 1;
        } else if (inRow == 2 && missing != -1) { // where the computer should play
            coordY = missing;
            coordX = i;
        }
        inRow = 0;
        missing = -1;
    }

    // check the diagonal from top left corner
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][i] == sign) {
            inRow++;
        } else if (board[i][i] == '-') {
            missing = i;
        }
    }
    if (inRow == 3) { // win
        return 1;
    } else if (inRow == 2 && missing != -1) { // where the computer should play
        coordY = missing;
        coordX = missing;
    }
    inRow = 0;
    missing = -1;

    // check the diagonal from top right corner
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][BOARD_SIZE-1-i] == sign) {
            inRow++;
        } else if (board[i][BOARD_SIZE-1-i] == '-') {
            missing = i;
        }
    }
    if (inRow == 3) { // win
        return 1;
    } else if (inRow == 2 && missing != -1) { // where the computer should play
        coordY = missing;
        coordX = BOARD_SIZE-1-missing;
    }
    getFreeFields(); // check if there are any free fields
    return 0;
}

void computerMove() {
    if (freeFieldCount == -1) {
        cout << "No fields left, it's a draw!\n";
        return;
    }

    void humanMove(); // declare a function to initiate human's move
    humanPlays = 0;

    checkRows(); // look if there is a win possibility
    if (board[coordY][coordX] == 'x') { // if human blocked the winning spot
        coordY = -1;
        coordX = -1;
    }

    // if there is no obvious spot to play, choose a random free field
    if (coordY == -1) {
        // randomly choose a field to play and get its coordinates
        // freeFields and freeFieldCount are already calculared from checkRows()
        field = freeFields[rand() % (freeFieldCount + 1)];
        toCoordComb();
    }

    board[coordY][coordX] = 'o'; // mark the move
    drawBoard();
    bool playerWon = checkRows(); // check for a win
    if (playerWon == 0) {
        humanMove(); // pass the move to the human
    } else {
        cout << "The computer beat you. Feel ashamed.\n";
    }
}

void humanInput() {
    cin >> field;
    field--; // now the number is 0 to 8 instead of 1 to 9
    toCoordComb();
    if (board[coordY][coordX] != '-') {
        cout << "This field is not free. Choose another one.\n";
        humanInput(); // prompt new input
    }
}

void humanMove() {
    if (freeFieldCount == -1) {
        cout << "No fields left, it's a draw!\n";
        return;
    }

    humanPlays = 1;
    cout << "It's your turn.\n";
    humanInput(); // ask the human to play a field
    board[coordY][coordX] = 'x';
    coordY = -1; // reset values to allow use by computer AI
    coordX = -1;
    drawBoard();
    bool playerWon = checkRows(); // check for a win and mark possible win spot
    if (playerWon == 0) {
        cout << "Computer's turn.\n";
        computerMove(); // pass the move to the computer
    } else {
        cout << "Congratulations! You won!\n";
    }
}

int main() {
    // initialize the board
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = '-';
        }
    }

    srand(time(NULL)); // set the seed for randomization
    rand(); // generate the first number which isn't really random
    cout << "You play with x's, the computer plays with o's.\n"
    << "In order to play, put in the number of the field you wish to play.\n"
    << "The field numbering goes as follows:\n123\n456\n789\n"
    << "The computer plays first. Good luck.\n\n";
    computerMove(); // start the game, computer plays first

    return 0;
}